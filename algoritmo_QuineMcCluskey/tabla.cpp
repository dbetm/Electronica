#include "header.h"

class Tabla {
    private:
        int cantidadVariables;
        vector <int> Salida;
        vector <int> Minterminos;
        unsigned int numMin;
    public:
        Tabla(int); //su parámetro es el número de variables
        Tabla();
    	int getCantidadVariables();
    	void setCantidadVariables(int);
        vector <int> getSalida();
        vector <int> getMinterminos();
        unsigned int getNumMin();
        void leerSalida();
        void mostrarSalida(); // --
        static int validarEntero();
        ~Tabla();
    private:
        void generarMinterminosArray();
};

Tabla::Tabla(int numVar) {
    this->cantidadVariables = numVar;
}

int Tabla::getCantidadVariables() {
    return this->cantidadVariables;
}

void Tabla::setCantidadVariables(int numVar) {
    this->cantidadVariables = numVar;
}

unsigned int Tabla::getNumMin() {
    return Minterminos.size();
}

vector <int> Tabla::getSalida() {
    return this->Salida;
}

vector <int> Tabla::getMinterminos() {
    return this->Minterminos;
}

void Tabla::leerSalida() {
    unsigned int n = pow(2, this->cantidadVariables);
    int salida;
    for(unsigned int i = 0; i < n; i++) {
        cout << i << "| ";
        for(int j = this->cantidadVariables - 1; j >= 0; j--)
            cout << ((i >> j) & 1); //desplaza j bits a i de forma decreciente y hace la operación lógica con 00...01
        cout << " --> ";

        do {
            salida = validarEntero();
            if(salida != 0 && salida != 1) cout << "\nVuelva a intentarlo: ";
        } while(salida != 0 && salida != 1);

        Salida.push_back(salida);
    }
    generarMinterminosArray();
}

void Tabla::generarMinterminosArray() {
    for(int unsigned i = 0; i < Salida.size(); i++) {
        if(Salida[i] == 1) {
            Minterminos.push_back(i);
        }
    }
    cout << "\nLos mintérminos son: {"; // -- *
    for(int unsigned j = 0; j < Minterminos.size(); j++) {
        if(j < Minterminos.size() - 1) cout << Minterminos[j] << ", ";
        else cout << Minterminos[j] << "}" << endl;
    }
}

void Tabla::mostrarSalida() { // --
    unsigned int n = pow(2, this->cantidadVariables);
    for(int unsigned i = 0; i < n; i++) {
        cout << i << "| ";
        for(int j = this->cantidadVariables - 1; j >= 0; j--)
            cout << ((i >> j) & 1);
        cout << " --> ";
        cout << Salida[i] << endl;
    }
}

int Tabla::validarEntero() {
    int num, ok, ch;
    do {
        fflush(stdout);
        if((ok = scanf("%d", &num)) == EOF) return EXIT_FAILURE;
        if((ch = getchar()) != '\n') {
            ok = 0;
            cout << "\nVuelva a intentarlo: ";
            while((ch = getchar()) != EOF && ch != '\n');
        }
    } while(!ok);
    return num;
}

Tabla::~Tabla() {
    if(!Salida.empty()) Salida.clear();
    if(!Minterminos.empty()) Minterminos.clear();
}
