#ifndef EMBARCACAO_HPP
#define EMBARCACAO_HPP

#include <vector>

using namespace std;

#define SUBMARINO 0
#define CONTRATORPEDEIROS 1
#define NAVIO_TANQUE 2
#define PORTA_AVIAO 3

class Embarcacao {
private:
    bool morto;
    int id;
    vector<bool> corpo;
public:
    Embarcacao(int id, int tipo){
        this -> morto = false;
        this -> id = id;     
        if(tipo == SUBMARINO){
            corpo = vector<bool>(1, true);
        } else if(tipo == CONTRATORPEDEIROS){
            corpo = vector<bool>(2, true);
        } else if(tipo == NAVIO_TANQUE){
            corpo = vector<bool>(3, true);
        } else {
            corpo = vector<bool>(4, true);
        }
    }

    void mataCorpo(int parte){
        corpo[parte] = false;
        bool f = 0;
        for(bool b : corpo){
            if(b){
                f = 1;
                break;
            }
        }
        if(!f){
            setMorto();
        }
    }

    void setMorto(){
        morto = true;
    }

    bool estaMorto(){
        return morto;
    }

    bool verificaMorte(){
        for(bool b : corpo){
            if(b){
                return false;
            }
        }
        return true;
    }
};

#endif