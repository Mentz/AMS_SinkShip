#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"
#include "embarcacao.hpp"
#include <time.h>
#include <vector>

using namespace std;

const int TAM_CAMPO = 10;

class Grid {
private:
    vector<vector<Celula> > campo;
    int tamQuad;

    void setShip(const int qtd, const int tam, const string shipName, int &id){
        for(int i = 0; i < qtd; i++){
            int x = rand() % TAM_CAMPO;
            int y = rand() % TAM_CAMPO;
            while(!posValida(x, y, tam)){
                x = rand() % TAM_CAMPO;
                y = rand() % TAM_CAMPO;
            }
            for(int j = 0; j < tam; j++){
                campo[x][y].setIdBarco(id);
                campo[x][y].setParte(j + 1);
                campo[x][y].setFilename("Imagens/" + shipName + "_" + to_string(j + 1) + ".png");
                x++;
            }
            id++;
        }
    }

public:

    bool valid(int x, int y){
        return (x >= 0 and y >= 0 and x < TAM_CAMPO and y < TAM_CAMPO);
    }

    bool posValida(int x, int y, int passo){
        for(int i = 0; i < passo; i++){
            if(campo[x][y].getIdBarco() != -1) return false;
            
            if(x - 1 >= 0 && x + 1 < TAM_CAMPO && y - 1 >= 0 && y + 1 < TAM_CAMPO)
            {
                if (campo[x-1][y-1].getIdBarco() != -1 ||
                    campo[x-1][y  ].getIdBarco() != -1 ||
                    campo[x-1][y+1].getIdBarco() != -1 ||
                    campo[x  ][y-1].getIdBarco() != -1 ||
                    campo[x  ][y+1].getIdBarco() != -1 ||
                    campo[x+1][y-1].getIdBarco() != -1 ||
                    campo[x+1][y  ].getIdBarco() != -1 ||
                    campo[x+1][y+1].getIdBarco() != -1)
                {
                    return false;
                }
            }
            
            x++;
            if(!valid(x, y)){
                return false;
            }
        }
        return true;
    }

    Grid(int tamJanela){
        campo = vector<vector<Celula> > (TAM_CAMPO);
        for(int i = 0; i < TAM_CAMPO; i++){
            campo[i] = vector<Celula>(TAM_CAMPO);
        }

        this -> tamQuad = (tamJanela / TAM_CAMPO);
        for(int i = 0; i < TAM_CAMPO; i++){
            for(int j = 0; j < TAM_CAMPO; j++){
                this -> campo[i][j] = Celula();
            }
        }
        int id = 1;
        setShip(4, 1, string("b1"), id);
        setShip(3, 2, string("b2"), id);
        setShip(2, 3, string("b3"), id);
        setShip(1, 4, string("b4"), id);
    }

    void render(sf::RenderWindow &window, vector<Embarcacao> &navios, vector<sf::Texture> &texturas, bool fimJogo){
        for(int i = 0; i < TAM_CAMPO; i++){
            for(int j = 0; j < TAM_CAMPO; j++){
                sf::Sprite teste;
                bool cellState = campo[i][j].getMorto();
                if(cellState){
                    int idBarco = campo[i][j].getIdBarco();
                    if(idBarco == -1){
                        sf::Texture& temp = texturas[i * TAM_CAMPO + j];
                        temp.loadFromFile("Imagens/bomba.png");
                        teste.setTexture(temp);
                    } else {
                        texturas[i * TAM_CAMPO + j].loadFromFile(campo[i][j].getFilename());
                        sf::Texture &temp = texturas[i * TAM_CAMPO + j];
                        teste.setTexture(temp);
                    }
                } else {
                    sf::Texture& temp = texturas[i * TAM_CAMPO + j];
                    temp.loadFromFile("Imagens/agua.png");
                    teste.setTexture(temp);
                }
                teste.setPosition(sf::Vector2f(i * tamQuad, j * tamQuad));
                if(fimJogo){
                    teste.setColor(sf::Color(255,255,255,40));
                } else {
                    teste.setColor(sf::Color(255,255,255,255));
                }
                window.draw(teste);
            }
        }
        
    }

    Celula getCelula(pair<int, int> pos){
        return campo[pos.first][pos.second];
    }

    void setMorto(pair<int, int> pos){
        campo[pos.first][pos.second].setMorto();
    }
};

#endif