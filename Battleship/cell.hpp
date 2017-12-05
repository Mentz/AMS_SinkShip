#ifndef CELL_HPP
#define CELL_HPP

#include <utility>
#include <SFML/Graphics.hpp>

using namespace std;

class Celula {
private:
    int id_barco;
    bool morto;
    int parte;
    string filename;

public:
    Celula(int id_barco = -1, int parte = -1, string filename = "Imagens/agua.png"){
        morto = false;
        this -> id_barco = id_barco;
        this -> parte = parte;
        this -> filename = filename;
    } 

    void setMorto(){
        this -> morto = true;
    }

    void setIdBarco(int id){
        id_barco = id;
    }
    
    void setParte(int parte){
        this -> parte = parte;
    }

    bool getMorto(){
        return morto;
    }

    int getIdBarco(){
        return id_barco;
    }

    string getFilename(){
        return filename;
    }

    void setFilename(string filename){
        this -> filename = filename;
    }

    int getParte(){
        return parte;
    }
};

#endif