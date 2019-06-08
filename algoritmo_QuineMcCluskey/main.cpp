#include "header.h"
#include "tabla.cpp"
#include "plot.cpp"
#include "minimizador.cpp"

int menu();
void manual();
void info();

int main(int argc, char const *argv[]) {
    int numVar, opt;
    bool control = true;

    do {
        system("clear");
        opt = menu();
        switch(opt) {
            case 1: {
                // ---- Tabla ----
                cout << "Escriba el número de variables: ";
                do {
                    numVar = Tabla::validarEntero();
                    if(numVar < 1) cout << "Vuelva a intentarlo: ";
                    if(numVar > 10) {
                        cout << "WARNING: Considere que debe introducir 2^" << numVar << " salidas :), puede abortar la ejecución del programa con CTRL+C." << endl;
                        break;
                    }
                } while(numVar < 1);

                Tabla t(numVar); //se genera un nuevo objeto tabla
                cout << "\nA continuación escriba la salida para cada estado de la función: " << endl;
                t.leerSalida();
                //t.mostrarSalida(); -- test

                // ---- Estructura para contemplar 3 estados -----
                Plot p(t.getCantidadVariables(), t.getNumMin()); //se construye un nuevo objeto
                p.generarEstructura(t.getMinterminos());
                // -- Test p.mostrarEstructura(); //muestra la estructura de 3 estados

                // --- Minimizador (hace lo más importante) ---
                    //se le pasan como parámetros, cantidadMinterminos, cantidadVariables, Estructura, emes
                Minimizador m(t.getNumMin(), t.getCantidadVariables(), p.getEstructura(), p.getEmes());
                m.minimizar();
                //m.displayRes(); // -- test
                m.filtrarResultado(t.getNumMin(), t.getMinterminos()); //para mostrar la salida de mintérminos en letras
                //cout << m.getResultado() << endl;
                cout << "\n---- >> " << m.getResultado() << endl;
                cout << "\nPresione enter para continuar...";
                cin.get();
            } break;
            case 2:
                manual();
                break;
            case 3:
                info();
                break;
            case 4:
                control = false;
                break;
            default:
                cout << "\nOpción no válida" << endl;
                break;
        }

    } while(control);
    return 0;
}

int menu() {
    int opcion;
    cout << "\n\tMinimizador - QuineMcCluskey\n" << endl;
    cout << "       1) Nueva minimización" << endl;
    cout << "       2) ¿Cómo usar?" << endl;
    cout << "       3) Acerca de" << endl;
    cout << "       4) Salir" << endl;
    cout << " --->> ";
    opcion = Tabla::validarEntero();
    return opcion;
}

void manual() {
    cout << "\n\t\t<MQM> \t\tv1.0." << endl;
    cout << "\nPara realizar una nueva minimización usted lo puede hacer de la siguiente manera: " << endl;
    cout << "\n1) Elegir 'Nueva minimización' escribiendo '1' en el menú principal." << endl;
    cout << "\n\nLa entrada de teclado debe ser validada, de esta manera mientras no de una entrada válida podrá volver a intentarlo." << endl;
    cout << "\n2) A continuación deberá escribir el número de variables, ejemplo, si se tienen 4 entradas, estamos hablando de 4 variables, por lo que deberá escribir '4' y dar enter." << endl;
    cout << "\n3) Deberá teclear cada salida para las diferentes combinaciones de las variables, es decir, escribir '0' ó '1'." << endl;
    cout << "\n4) Después del paso 3, se mostrará la función minimizada de las variables representadas en letras mayúsculas." << endl;
    cout << "\n\nNOTAS: " << endl;
    cout << "\nTenga en cuenta que se le pedirán en la salida 2^n, donde n es el número de variables." << endl;
    cout << "\nDeberá tener a la mano una tabla de verdad o conocer las salidas." << endl;
    cout << "\nLa salida tendrá la forma de mintérminos o suma de productos, ejemplo, ABC´+A´B´, donde la comilla(') hace referencia a la negación." << endl;
    cout << "\n\nPuede reportar problemas en el siguiente e-mail: davbetm@gmail.com" << endl;

    cout << "\nPresione enter para continuar...";
    cin.get();
}

void info() {
    system("clear");
    cout << "\n\t\t\tMINIMIZADOR <MQM> v1.0." << endl;
    cout << "\tUn programa que implementa el algoritmo de Quine-McCluskey para minimizar funciones booleanas." << endl;
    cout << "\n\tDesarrollado por: " << "\n\t\tDavid Betancourt Montellano @dabetm | @dbetm (GitHub)."
         << "\n\t\tJuan Hernández Montalvo @dons." << endl;
    cout << "\tProyecto departamental de la unidad de aprendizaje 'Fundamentos de diseño digítal'." << endl;
    cout << "\tCompilado con: gcc version 5.4.0 | g++ main.cpp -o main.\n" << endl;

    cout << "\nPresione enter para continuar...";
    cin.get();
}
