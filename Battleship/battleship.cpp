#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "gameController.hpp"
#include "enemy.hpp"

using namespace std;

#define TAM_JANELA 480

void fullTextures(vector<sf::Texture> &vet){
    for(int i = 0; i < TAM_CAMPO * TAM_CAMPO; i++){
        sf::Texture temp;
        vet.push_back(temp);
    }
}

int main(int argc, const char *argv[]){

    sf::RenderWindow window(sf::VideoMode(TAM_JANELA, TAM_JANELA), "SinkShip - Jogador da vez: Humano",
                            sf::Style::Close | sf::Style::Titlebar);
    vector<sf::Texture> texturas1, texturas2;
    srand(time(NULL));
    fullTextures(texturas1);
    fullTextures(texturas2);
    GameController *gc = new GameController(TAM_JANELA);
    Enemy *enemy = new Enemy();
    bool noGame = false;
    while(window.isOpen()){
        if(noGame){
            gc -> mostrarFimJogo(window, texturas1, texturas2, TAM_JANELA);
            sf::Event evnt;
            while(window.pollEvent(evnt)){
                if(evnt.type == sf::Event::Closed){
                    window.close();
                }
                if(evnt.type == sf::Event::KeyReleased){
                    switch (evnt.key.code){
                        case sf::Keyboard::Return: 
                            fullTextures(texturas1);
                            fullTextures(texturas2);
                            delete(gc);
                            gc = new GameController(TAM_JANELA);
                            noGame = false;
                            break;
                        case sf::Keyboard::Escape: window.close(); break;
                        default: break;
                    }
                }
            }
        } else {
            stringstream title;
            title << "SinkShip - Jogador da vez: " << ((gc -> getPlayer() == 1) ? "Humano": "Computador");
            window.setTitle(title.str());
            sf::Event evnt;
            bool f = false;
            bool sshot = false;
            bool aux = false;
            while(window.pollEvent(evnt)){
                if(evnt.type == sf::Event::Closed){
                    window.close();
                }
                if(evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::F3){
                    noGame = 1; // instawin
                } else if(evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::F4){
                    noGame = 1;
                    gc -> setPlayer(2);
                    aux = true;
                    break;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(gc -> getPlayer() == 1){
                        pair<int, int> posMouse = gc -> getMouseClickPos(window);
                        posMouse.first = floor(posMouse.first / (double)((TAM_JANELA / TAM_CAMPO)));
                        posMouse.second = floor(posMouse.second / (double)((TAM_JANELA / TAM_CAMPO)));
                        if(!gc -> getCelula(posMouse).getMorto() && gc -> valid(posMouse)){
                            gc -> setMorto(posMouse);
                            if(gc -> fimJogo()){
                                noGame = true;
                                break;
                            }
                            sshot = (gc -> getCelula(posMouse).getIdBarco() != -1);
                            f = true;
                        }
                    }
                }
            }

            window.clear(sf::Color::White);
            gc -> render(window, (gc -> getPlayer() == 1 ? texturas1 : texturas2));
            window.display();

            if(gc -> getPlayer() == 2 and not aux){
                sf::Time t = sf::milliseconds(500.f);
                sf::sleep(t);
                pair<int,int> pos = enemy -> play(gc -> getCampo(2));
                gc -> setMorto(pos);
                if(gc -> fimJogo()){
                    noGame = true;
                } else {
                    sshot = (gc -> getCelula(pos).getIdBarco() != -1);
                    f = true;
                }
            }
            if(f and !sshot){
                window.clear(sf::Color::White);
                gc -> render(window, (gc -> getPlayer() == 1 ? texturas1 : texturas2));
                window.display();
                sf::Time t = sf::milliseconds(500.f);
                sf::sleep(t);
                gc -> setPlayer((gc -> getPlayer() == 1 ? 2 : 1));
            }

            if(noGame){
                for (int i = 0; i < TAM_CAMPO; i++){
                    for (int j = 0; j < TAM_CAMPO; j++){
                        gc -> setMorto(make_pair(i, j));
                    }
                }
            }
        }
    }

    return 0;
}
