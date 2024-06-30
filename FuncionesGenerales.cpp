#include <iostream>
#include <string> 
#include <sstream>
#include <iomanip>
#include "FuncionesGenerales.h"
using namespace std;

// funciona pero si ingresas por ejemplo 12r toma el 12 y no vuelve a pedir por lo que no la estoy usando en el codigo.
int pedirNumeroPositivo(const string& mensaje) { 
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < 0) { //pregunta si hay error en el cin y si es negativo
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignora la entrada invalida limpiando el buffer para que podamos hacer un nuevo ingreso
            cout << "Ingreso invalido. Por favor, ingrese un numero valido." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada
            return valor;
        }
    }
}

int validarInt(const std::string& mensaje) {
    string ingreso;
    int num;
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
        }
        else {//Si es Valido
            num = stoi(ingreso);//Convierte el ingreso en tipo String a un a un Int y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

long long validarLong(const std::string& mensaje) {
    string ingreso;
    long long num;
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
        }
        else {//Si es Valido
            num = stoll(ingreso);//Convierte el ingreso en tipo String a un a un Int y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

// la funcion de stof no me devuelve la parte de los decimales por lo que no la estoy usando en el codigo. La dejo por si podemos revisarla.
float validarFloat(const std::string& mensaje) 
{
    string ingreso; 
    float num;
    bool puntoEncontrado = false;
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) { //Si encuentra un caracter que no es un digito
                if (ingreso[i] == '.' && puntoEncontrado == false) {
                    puntoEncontrado = true;
                }
                else {
                    esValido = false;//Bandera en False
                    break;//Sale del Bucle

                }
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos (acepta decimales) *" << endl;
        }
        else {//Si es Valido
            num = stof(ingreso);//Convierte el String a un a un float y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

float pedirNumeroFloat(const string& mensaje) { 
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) { //pregunta si hay error en el cin y si es negativo
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignora la entrada invalida limpiando el buffer para que podamos hacer un nuevo ingreso
            cout << "Ingreso invalido. Por favor, ingrese un numero valido." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada
            return valor;
        }
    }
}

string validarStringNumerico(const std::string& mensaje) {
    string ingreso;
    
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
        }
        else {//Si es Valido
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return ingreso;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve ingreso
}


int contarDigitos(int num)
{
    int contador = 0;
    while (num > 0) {
        num /= 10;
        contador++;
    }
    return contador;
}


string formatearNumero(float numero) {
    ostringstream oss{};//ostringstream llamado oss
    oss << fixed << setprecision(2) << numero;
    //fixed asegura de que el numero se formatee en notacion decimal fija. setprecision(2) establece que se usen dos decimales
    string numeroStr = oss.str();//oss.str() convierte el flujo oss a una cadena (string) y se guarda en numeroStr
    size_t punto = numeroStr.find('.');//find('.') encuentra la posicion del punto decimal en numeroStr
    string parteEntera = numeroStr.substr(0, punto);//substr(0, punto) obtiene la parte entera de la cadena(todo antes del punto)
    string parteDecimal = numeroStr.substr(punto);//substr(punto) obtiene la parte decimal de la cadena (incluyendo el punto).
    string parteEnteraFormateada;
    int longitud = parteEntera.length();//longitud guarda la longitud de parteEntera
    for (int i = 0; i < longitud; ++i) {
        parteEnteraFormateada += parteEntera[i];
        if ((longitud - i - 1) % 3 == 0 && (i != longitud - 1)) {
            //(longitud - i - 1) % 3 == 0 verifica si el caracter actual esta en una posicion de mil.
            //(i != longitud - 1) asegura que no se agrega una coma al final de la cadena.
            parteEnteraFormateada += ',';
        }
    }
    return parteEnteraFormateada + parteDecimal;//retorna la parte entera formateada concatenada con la parte decimal.
}

string aMinuscula(string cadena) {
    for (string::size_type i = 0; i < cadena.length(); i++) {
        //size_t, y se usa para asegurar la compatibilidad con el tamaño de la cadena.
        //cadena.length() asegura que el bucle se ejecute desde el primer caracter(i = 0) hasta el ultimo caracter
        cadena[i] = tolower(cadena[i]);
        //tolower(cadena[i]) convierte el caracter actual a minusculas.
    }
    return cadena;//Devuelve cadena completamente en minuscula
}

string validarStr() {
    string cad;
    while (true) {
        bool esValido = true;
        getline(cin, cad);
        for (int i = 0; i < cad.size(); i++) {//Recorre cada caracter de la cadena desde el indice 0 hasta cad.size()
            if (!isalpha(cad[i]) && cad[i] != ' ') {//Si se encuentra un caracter no alfabetico
                esValido = false;
                break;//Sale del Bucle
            }
        }
        if (!esValido) {
            cout << "* Ingreso No Valido, Solo se Admiten Caracteres *" << endl;
            cout << "- Intentelo Nuevamente: ";
        }
        else {
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return cad;///Si el bucle completa la iteracion sin encontrar caracteres no alfabaticos, la funcion devuelve true.
}

int validarInt() {
    string ingreso;
    int num;
    while (true) {
        bool esValido = true;
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
            cout << "- Intentelo Nuevamente: ";
        }
        else {//Si es Valido
            num = stoi(ingreso);//Convierte el ingreso en tipo String a un a un Int y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

int validarNumero() {
    string entrada;
    int num;
    while (true) {
        bool esValido = true;// Bandera
        getline(cin, entrada); //Lee el ingreso como una cadena.
        for (char c : entrada) {//Itera sobre cada caracter en la cadena entrada.En cada iteracion, el caracter actual se copia en la variable c
            if (c < '0' || c > '9') {//Si algun caracter no esta entre 0 y 9, se establece esValido en false y se rompe el bucle.
                esValido = false;//si al menos un caracter no es un digito, no es necesario seguir verificando los demas caracteres
                break;//Salir del Bucle
            }
        }
        if (esValido) {// Convertir la cadena a un entero
            num = 0;
            for (char c : entrada) {
                //char c variable de tipo caracter que tomara el valor de cada caracter en entrada durante cada iteracion.
                //: entrada se iterara sobre cada car?cter de la cadena "entrada".
                num = num * 10 + (c - '0'); //realiza la conversion y acumulacion del valor numerico del caracter c.
                //Al restar '0' de un caracter numerico, obtienes el valor entero correspondiente.
                //Multiplica el valor actual de num por 10. Esto desplaza el valor numerico a la izquierda en una posicion decimal
            }
            break; //Sale del bucle si la conversion es exitosa
        }
        cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
        cout << "- Intentelo Nuevamente: ";
    }
    cin.ignore(numeric_limits<size_t>::max());///Lipia el Buffer de Entrada por completo
    return num; //Retornar el numero valido
}


bool creciente(int num, int num2) {
    return num < num2;
}

bool decreciente(int num, int num2) {
    return num > num2;
}

bool creciente(std::string  n, std::string m) {
    return n < m;
}

bool decreciente(std::string n, std::string m) {
    return n > m;
}