#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <utility>
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "embarcacao.hpp"

class GameController {

private:
    Grid *gA, *gB;
    int player_da_vez;
    int tamJanela;
    vector<Embarcacao> naviosA, naviosB;

public:
    GameController(int tamJanela){
        this -> tamJanela = tamJanela;
        gA = new Grid(tamJanela);
        gB = new Grid(tamJanela);
        naviosA.clear();
        naviosB.clear();
        this -> player_da_vez = 1;
        int id = 1;
        //Criando os Submarinos
        for(int i = 0; i < 4; i++){
            naviosA.push_back(Embarcacao(id, SUBMARINO));
            naviosB.push_back(Embarcacao(id++, SUBMARINO));
        }

        //Criando os ContraTorpedeiros
        for(int i = 0; i < 3; i++){
            naviosA.push_back(Embarcacao(id, CONTRATORPEDEIROS));
            naviosB.push_back(Embarcacao(id++, CONTRATORPEDEIROS));
        }

        //Criando os Submarinos
        for(int i = 0; i < 2; i++){
            naviosA.push_back(Embarcacao(id, NAVIO_TANQUE));
            naviosB.push_back(Embarcacao(id++, NAVIO_TANQUE));
        }

        //Criando os Submarinos
        naviosA.push_back(Embarcacao(id, PORTA_AVIAO));
        naviosB.push_back(Embarcacao(id, PORTA_AVIAO));
    }

    pair<int,int> getMouseClickPos(sf::RenderWindow &window){
        sf::Vector2i p = sf::Mouse::getPosition(window);
        pair<int,int> pos;
        pos.first = p.x;
        pos.second = p.y;
        return pos;
    }

    bool valid(pair<int, int> pos){
        return (pos.first >= 0 and pos.second >= 0 and pos.first < TAM_CAMPO and pos.second < TAM_CAMPO);
    }

    void setPlayer(int player_da_vez){
        this -> player_da_vez = player_da_vez;
    }

    int getPlayer(){
        return player_da_vez;
    }

    Celula getCelula(pair<int,int> pos){
        if(valid(pos)){
            if(player_da_vez == 1){
                return gA -> getCelula(pos);
            } else {
                return gB -> getCelula(pos);
            }
        }
        return Celula();
    }

    void setMorto(pair<int, int> pos){
        if(valid(pos)){
            if(player_da_vez == 1){
                gA -> setMorto(pos);
                int id = gA -> getCelula(pos).getIdBarco();
                if(id != -1){
                    int parte = gA -> getCelula(pos).getParte();
                    naviosA[id - 1].mataCorpo(parte - 1);
                }
            } else {
                gB -> setMorto(pos);
                int id = gB -> getCelula(pos).getIdBarco();
                if(id != -1){
                    int parte = gB -> getCelula(pos).getParte();
                    naviosB[id - 1].mataCorpo(parte - 1);
                }
            }
            
        }
    }

    void render(sf::RenderWindow &window, vector<sf::Texture> &texturas, bool fimJogo = false){
        if(player_da_vez == 1){
            gA -> render(window, naviosA, texturas, fimJogo);
        } else {
            gB -> render(window, naviosB, texturas, fimJogo);
        }
    }

    void gerarNovoJogo(){
        gA = new Grid(tamJanela);
        gB = new Grid(tamJanela);
    }

    bool fimJogo(){
        if(player_da_vez == 1){
            for(int i = 0; i < naviosA.size(); i++){
                if(!naviosA[i].estaMorto()){
                    return false;
                }
            }
            return true;
        } else {
            for(int i = 0; i < naviosB.size(); i++){
                if(!naviosB[i].estaMorto()){
                    return false;
                }
            }
            return true;
        }
    }

    Grid* getCampo(int idCampo){
        if(idCampo == 1){
            return gA;
        } else {
            return gB;
        }
    }

    void mostrarFimJogo(sf::RenderWindow &window, vector<sf::Texture> &texturas1, vector<sf::Texture> &texturas2, int TAM_JANELA){
        window.setTitle("SinkShip - Fim de jogo");
        sf::Font font;
        font.loadFromFile("Fontes/Aller_Bd.ttf");
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(25);
        if (getPlayer() == 1){
            text.setColor(sf::Color(0, 210, 50));
        } else {
            text.setColor(sf::Color(200, 30, 0));
        }
        string winner = (getPlayer() == 1 ? "Jogador(a)" : "Computador");
        text.setString("Vencedor: " + winner);
        text.setPosition(sf::Vector2f(TAM_JANELA / 2 - (getPlayer() == 1 ? 140 : 170), TAM_JANELA / 2 - 55));
        sf::Text retryText;
        retryText.setFont(font);
        retryText.setCharacterSize(18);
        if (getPlayer() == 1){
            retryText.setColor(sf::Color(0, 210, 50));
        } else{
            retryText.setColor(sf::Color(200, 30, 0));
        }
        retryText.setString("\n\n\nPressione \"Enter\" para reiniciar\nou \"Esc\" para encerrar.");
        retryText.setPosition(sf::Vector2f(TAM_JANELA / 2 - 170, TAM_JANELA / 2 + 20));

        window.clear(sf::Color::Black);

        render(window, (getPlayer() == 1 ? texturas1 : texturas2), true);

        window.draw(text);
        window.draw(retryText);
        window.display();
    }

};

#endif
