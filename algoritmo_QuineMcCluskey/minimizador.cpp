#include "header.h"

int cont = 0;

class Minimizador {
    //atributos
    private:
        ui cantidadVariables;
        ui cantidadMinterminos;
        ui nMin; //variable auxiliar de la variable cantidadMinterminos
        vector < vector <int> > Emes; //donde se guardan los minterminos combinables (como enteros)
        vector < vector <Casilla> > Estructura;
        vector < vector <int> > EmesAux;
        vector < vector <Casilla> > EstructuraAux;
        vector < int > NoImplicantes; //Guarda los índices de la Estructura, con el fin de rescatar los que si son implicantes primos
        vector < string > FinalEstructura;
        vector < vector <int> > FinalEmes;
        string resultado;
    //métodos
    public:
        Minimizador(int, int, vector < vector <Casilla> >, vector < vector <int> >);
        void minimizar();
        void displayRes();
        void filtrarResultado(ui, vector <int>);
        string getResultado();
        ~Minimizador();
    private:
        void comparar(ui); //recursivo
        void normalizador(vector <Casilla>, int);
        void guardaImplicantes();
        void QuitarRepetidos();
        ui encontrarIndiceMinterminos(int, vector <int>);
        ui buscarIndiceEmes(int, vector < vector <int> >);
        bool existeMin(vector <int>, int);
        void generarExpresion(ui); //para los esenciales
        void generarExpresionNoEsenciales(vector <int>);
        void filtrarResultadoNoEsenciales(vector <int>, vector <int>);
};
//Constructor
Minimizador::Minimizador(int min, int var, vector < vector <Casilla> > Estructura, vector < vector <int> > Emes) {
    this->cantidadVariables = var;
    this->cantidadMinterminos = min;
    this->Estructura = Estructura;
    this->Emes = Emes;
    nMin = 0;
    EstructuraAux.clear();
    resultado = "S = ";
}

void Minimizador::minimizar() {
    bool control = true;
    //generara tablas y hará comparación recursiva hasta que todos sean implicantes primos
    while(control) {
        ui i = 0;
        comparar(i);

        if(NoImplicantes.empty()) {
            control = false;
        }
        guardaImplicantes();
        NoImplicantes.clear();
        //Borro lo que tenía el vector de m, y le asigno el nuevo que ya contempla los cambios luego de las comparaciones
        Emes.clear();
        Emes = EmesAux;
        EmesAux.clear();
        //Borro el contenido de la Estructura (vector de vectores de casillas) y le asigno su auxiliar con los nuevos cambios
        Estructura.clear();
        Estructura = EstructuraAux;
        EstructuraAux.clear();
        //cout << endl;
        cantidadMinterminos = nMin;
        nMin = 0;
    }
    QuitarRepetidos();
}
//Función recursiva, se usa para ir comparando las expresiones (Ej. 00X1) con el resto para saber si son combinables
void Minimizador::comparar(ui i) {
    ui respuesta1, respuesta2, posDif;
    ui k;
    for(k = i+1; k < cantidadMinterminos; k++) {
        bool iguales = true;
        int diferencias = 0;
        for(ui j = 0; j < cantidadVariables; j++) {
            if(k+1 <= cantidadMinterminos) {
                    respuesta1 = Estructura[i][j].t ^ Estructura[k][j].t;
                    respuesta2 = Estructura[i][j].f ^ Estructura[k][j].f;

                if(respuesta1 == 1 && respuesta2 == 1) {
                    diferencias++;
                    posDif = j;
                }
                if(respuesta1 != respuesta2) {
                    iguales = false;
                    break;
                }
                if(diferencias > 1) {
                    iguales = false;
                    break;
                }
            }
        }
        if(diferencias == 1 && iguales) { //esto indica que son combinables
            normalizador(Estructura[i], posDif);
            vector <int> auxiliar;
            for(ui t = 0; t < Emes[i].size(); t++) {
                auxiliar.push_back(Emes[i][t]);
            }
            for(ui t = 0; t < Emes[k].size(); t++) {
                auxiliar.push_back(Emes[k][t]);
            }
            EmesAux.push_back(auxiliar);
            nMin++;
            auxiliar.clear();
            //Guardando los índices de los no implicantes
            if(find(NoImplicantes.begin(), NoImplicantes.end(), i) == NoImplicantes.end()) {
                NoImplicantes.push_back(i);
            }
            if(find(NoImplicantes.begin(), NoImplicantes.end(), k) == NoImplicantes.end()) {
                NoImplicantes.push_back(k);
            }
        }
    }
    if(i < cantidadMinterminos) comparar(i+1); //se vuelve a llamar la función ya una vez que se han comparado todas las expresiones
}

void Minimizador::normalizador(vector <Casilla> c1, int posDif) { //posDif, posición de la diferencia, requerida para hacer el cambio
    // Dado que es una diferencia, esa casilla en se modifica 0 - 0, que representa el estado X
    c1[posDif].t = 0;
    c1[posDif].f = 0;
    EstructuraAux.push_back(c1);
    c1.clear();
}

void Minimizador::guardaImplicantes() {
    vector <int> Implicantes;
    string expresion = "";
    for(ui i = 0; i < cantidadMinterminos; i++) {
        if(find(NoImplicantes.begin(), NoImplicantes.end(), i) == NoImplicantes.end())
            Implicantes.push_back(i); //guardo los índices de los implicantes primos
    }
    for(ui i = 0; i < Implicantes.size(); i++) {
        expresion = "";
        for(ui k = 0; k < cantidadVariables; k++) {
            if(Estructura[Implicantes[i]][k].t == 0 && Estructura[Implicantes[i]][k].f == 0) expresion += "X";
            else if(Estructura[Implicantes[i]][k].t == 1 && Estructura[Implicantes[i]][k].f == 0) expresion += "1";
            else expresion += "0";
        }
        FinalEstructura.push_back(expresion);
        FinalEmes.push_back(Emes[Implicantes[i]]);
    }
}

void Minimizador::QuitarRepetidos() { //se quitan los implicantes primos repetidos
    ui n = FinalEstructura.size();
    for(ui i = 0; i < n; i++) {
        for(ui j = i + 1; j < FinalEstructura.size(); j++) {
            if(FinalEstructura[i] == FinalEstructura[j]) {
                FinalEstructura.erase(FinalEstructura.begin()+j);
                FinalEmes.erase(FinalEmes.begin()+j);
                j--;
                continue;
            }
        }
        if(i >= FinalEstructura.size()) break;
    }
}
//Implicantes esenciales
void Minimizador::filtrarResultado(ui numMin, vector <int> Minter) {
    ui A[FinalEmes.size()][numMin];
    vector <ui> indicesGuardados;
    vector <int> nEsenciales;
    ui index;
    //rellenar con 0's la matriz
    for(ui i = 0; i < FinalEmes.size(); i++) {
        for(ui j = 0; j < numMin; j++) {
            A[i][j] = 0;
        }
    }
    //agregar un 1, donde en determinada fila y columna
    for(ui i = 0; i < FinalEmes.size(); i++) {
        for(ui j = 0; j < FinalEmes[i].size(); j++) {
            index = encontrarIndiceMinterminos(FinalEmes[i][j], Minter);
            A[i][index] = 1;
        }
    }
    //Generamos la función
    ui cont, ind;
    for(ui j = 0; j < numMin; j++) { //se recorre la matriz de la manera no convencional
        cont = 0;
        for(ui i = 0; i < FinalEmes.size(); i++) {
            if(A[i][j] == 1) {
                cont++;
                ind = i;
                if(cont == 2) break;
            }
        }
        if(cont == 1) { //quiere decir que en esa fila se encuentra la expresión implicante primo esencial
            if(find(indicesGuardados.begin(), indicesGuardados.end(), ind) == indicesGuardados.end()) {
                generarExpresion(ind);
                indicesGuardados.push_back(ind);
                //almaceno las emes de los esenciales, ya teniendo esto, su complemento es lo que me interesa
                for(ui k = 0; k < FinalEmes[ind].size(); k++) {
                    if(find(nEsenciales.begin(), nEsenciales.end(), FinalEmes[ind][k]) == nEsenciales.end())
                        nEsenciales.push_back(FinalEmes[ind][k]);
                }
            }
        }
    }
    if(nEsenciales.size() < Minter.size())filtrarResultadoNoEsenciales(nEsenciales, Minter);
}

string Minimizador::getResultado() { //resultado final S = AB' + ACD'
    string resultadoAcortado = ""; //se usa lo de acortado para quitar ' + '
    for(ui i = 0; i < this->resultado.size() - 3; i++) {
        resultadoAcortado += this->resultado[i];
    }
    return resultadoAcortado;
}
//para la primera etapa
ui Minimizador::encontrarIndiceMinterminos(int min, vector <int> Min) {
    ui index = 0;
    for(ui i = 0; i < Min.size(); i++) {
        if(Min[i] == min) {
            index = i;
            break;
        }
    }
    return index;
}
//Implicantes no esenciales
void Minimizador::filtrarResultadoNoEsenciales(vector <int> nEsenciales, vector <int> Minter) {
    vector <int> nE; //Implicantes no esenciales
    vector < vector <int> > emes = FinalEmes;
    vector < vector <int> > aux;
    int index;
    //obtenemos el complemento, o sea los no esenciales pero que deben de ir
    for(ui i = 0; i < Minter.size(); i++) {
        if(find(nEsenciales.begin(), nEsenciales.end(), Minter[i]) == nEsenciales.end())
            nE.push_back(Minter[i]);
    }
    Minter = nE;

    vector <int> indices;
    for(ui i = 0; i < nE.size(); i++) {
        index = buscarIndiceEmes(nE[i], emes);
        if(find(indices.begin(), indices.end(), index) == indices.end()) {
            indices.push_back(index);
            aux.push_back(emes[index]);
        }
    }

    emes = aux;
// ---------------
    nEsenciales.clear();
    ui A[emes.size()][Minter.size()]; //generamos la matriz
    vector <ui> indicesGuardados;
    //rellenar con 0's la matriz
    for(ui i = 0; i < emes.size(); i++) {
        for(ui j = 0; j < nE.size(); j++) {
            A[i][j] = 0;
        }
    }
    //agregar un 1, donde en determinada fila y columna
    for(ui j = 0; j < Minter.size(); j++) {
        for(ui i = 0; i < emes.size(); i++) {
            if(existeMin(emes[i], Minter[j])) A[i][j] = 1;
        }
    }
    // ---------------- generar la función
    ui cont, ind;
    nEsenciales.clear();
    for(ui j = 0; j < Minter.size(); j++) { //se recorre la matriz de la manera no convencional
        cont = 0;
        for(ui i = 0; i < emes.size(); i++) {
            if(A[i][j] == 1) {
                cont++;
                ind = i;
                if(cont == 2) break;
            }
        }
        if(cont == 1) {
            if(find(indicesGuardados.begin(), indicesGuardados.end(), ind) == indicesGuardados.end()) {
                generarExpresionNoEsenciales(emes[ind]); //buscará las eme[ind], en las emesFinal, y trabajará con su expresión correspondiente
                indicesGuardados.push_back(ind);
                //almaceno las emes de los esenciales, ya teniendo esto, su complemento es lo que me interesa
                for(ui k = 0; k < emes[ind].size(); k++) {
                    if(find(nEsenciales.begin(), nEsenciales.end(), FinalEmes[ind][k]) == nEsenciales.end())
                        nEsenciales.push_back(emes[ind][k]);
                }
            }
        }
    }

    if(Minter.size() > 0) filtrarResultadoNoEsenciales(nEsenciales, Minter); //para que sea recursivo
}
//retorna la posición donde se encuentra el mintérmino más simplificado
ui Minimizador::buscarIndiceEmes(int num, vector < vector <int> > emes) {
    ui index;
    ui numX = 0;
    ui aux = 0;
    for(ui i = 0; i < emes.size(); i++) {
        aux = 0;
        for(ui j = 0; j < emes[i].size(); j++) {
            if(num == emes[i][j]) {
                for(ui k = 0; k < cantidadVariables; k++) {
                    if(FinalEstructura[k] == "X") aux++;
                }
                if(aux >= numX) {
                    index = i;
                    numX = aux;
                    break;
                }
            }
        }
    }
    return index;
}
//para saber si en un índice de emes se encuentra determinado mintérmino
bool Minimizador::existeMin(vector <int> eme, int min) {
    bool respuesta = false;
    for(ui i = 0; i < eme.size(); i++) {
        if(min == eme[i]) {
            respuesta = true;
            break;
        }
    }
    return respuesta;
}
//genera los términos de la expresión, se utiliza ASCII para determinar las literales de acuerdo al número de variables
void Minimizador::generarExpresion(ui i) {
    string termino = "";
    for(ui k = 0; k < cantidadVariables; k++) {
        if(FinalEstructura[i][k] == '0'){ //negación
            //se emplea el código ASCII
            termino += (char)(k+65);
            termino += "'";
        }
        else if(FinalEstructura[i][k] == 'X'){
            continue;
        }
        else if(FinalEstructura[i][k] == '1'){
            termino += (char)(k+65);
        }
    }
        termino += " + ";
        resultado += termino;
}
//ubica ciertas emes, en las FinalEmes para saber el índice de la expresión a la que corresponde
void Minimizador::generarExpresionNoEsenciales(vector <int> emes) {
    ui index;
    bool respuesta;
    for(ui i = 0; i < FinalEmes.size(); i++) {
        respuesta = true;
        if(emes.size() == FinalEmes[i].size()) {
            for(ui j = 0; j < FinalEmes[i].size(); j++) {
                if(emes[j] != FinalEmes[i][j]) {
                    respuesta = false;
                    break;
                }
            }
        }
        else respuesta = false;
        if(respuesta) {
            index = i;
            break;
        }
    }
    generarExpresion(index);
}
// -- Test
void Minimizador::displayRes() {
    for(ui i = 0; i < FinalEstructura.size(); i++) {
        cout << FinalEstructura[i] << " ->";
        for(ui k = 0; k < FinalEmes[i].size(); k++) {
            cout << FinalEmes[i][k] << " ";
        }
        cout << endl;
    }
}

Minimizador::~Minimizador() {
    if(!Estructura.empty()) Estructura.clear();
    if(!Emes.empty()) Emes.clear();
    if(!EstructuraAux.empty()) EstructuraAux.clear();
    if(!EmesAux.empty()) EmesAux.clear();
    if(!FinalEmes.empty()) FinalEmes.clear();
    if(!FinalEstructura.empty()) FinalEstructura.clear();
    if(!NoImplicantes.empty()) NoImplicantes.clear();
}
