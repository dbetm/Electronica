#include "header.h"

typedef unsigned short Nodo;
typedef unsigned int ui;

struct Casilla {
    Nodo t;
    Nodo f;
};

class Plot {
    private:
        ui cantidadVariables;
        ui cantidadMinterminos;
        vector <vector <Casilla> > Estructura;
        vector <vector <int> > Emes;
    public:
        Plot(int, int);
        void generarEstructura(vector <int>); //genera el arreglo de arreglos de Casillas(estructura)
        void mostrarEstructura(); // --testing
        vector <vector <Casilla> > getEstructura();
        vector <vector <int> > getEmes();
        ~Plot();
};

Plot::Plot(int cantidadVar, int numMinterminos) {
    this->cantidadVariables = cantidadVar;
    this->cantidadMinterminos = numMinterminos;
    //cout << "numVar: " << cantidadVariables << "\nnumMin: " << cantidadMinterminos << endl;
}
//Genera la estructura inicial
void Plot::generarEstructura(vector <int> Min) {
    ui temp;
    for(ui i = 0; i < cantidadMinterminos; i++) {
        vector <Casilla> C;
        for(int j = cantidadVariables - 1; j >= 0; j--) {
            Casilla aux;
            temp = (Min[i] >> j) & 1;
            if(temp == 1) {
                aux.t = 1;
                aux.f = 0;
            }
            else {
                aux.t = 0;
                aux.f = 1;
            }
            C.push_back(aux);
        }
        //Agrega en un primer momento los minterminos (como enteros) en un arreglo.
        vector <int> m;
        m.push_back(Min[i]);
        Emes.push_back(m);
        //C es un arreglo de estructuras tipo casillas, se genera una C para cada mintérmino
        Estructura.push_back(C);
    }
}

void Plot::mostrarEstructura() { // -- test
    for(ui i = 0; i < cantidadMinterminos; i++) {
        for(ui j = 0; j < cantidadVariables; j++) {
            if(Estructura[i][j].t == 0 && Estructura[i][j].f == 0) cout << "X";
            else if(Estructura[i][j].t == 1 && Estructura[i][j].f == 0) cout << "1";
            else cout << "0";
        }
        cout << endl;
    }
}

vector <vector <Casilla> > Plot::getEstructura() {
    return this-> Estructura;
}

vector <vector <int> > Plot::getEmes() {
    return this->Emes;
}

Plot::~Plot() {
    if(!Estructura.empty()) Estructura.clear();
    if(!Emes.empty()) Emes.clear();
}
