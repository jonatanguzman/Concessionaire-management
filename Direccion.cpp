#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Direccion.h"
#include <cstring>

using namespace std;


Direccion::Direccion() {
    strcpy(_calle, "");
    _numero = 0;
    strcpy(_provincia, "");
    _cp = 0;
}

Direccion::Direccion(string calle, int numero, string provincia, int cp) {
    strcpy(_calle, calle.c_str());
    _numero = numero;
    strcpy(_provincia, provincia.c_str());
    _cp = cp;
}

string Direccion::getCalle() {
    
    return _calle;
}

int Direccion::getNumero() {
    return _numero;
}

string Direccion::getProvincia() {
    return _provincia;
}

int Direccion::getCP() {
    return _cp;
}

void Direccion::setCalle(string c) {
    strcpy(_calle, c.c_str());
}

void Direccion::setNumero(int n) {
    _numero = n;
}

void Direccion::setProvincia(string p) {
    strcpy(_provincia, p.c_str());
}

void Direccion::setCP(int cp) {
    _cp = cp;
}

void Direccion::Cargar() {
    string c, p; 
    int n, cp; 

    cout << "Calle: ";
    getline(cin, c);
    setCalle(c);
    cout << "Numero #";
    cin >> n;
    cin.ignore();
    setNumero(n);
    cout << "Provincia: ";
    getline(cin, p);
    setProvincia(p);
    cout << "Codigo Postal: #";
    cin >> cp;
    cin.ignore();
    setCP(cp);
}

void Direccion::Mostrar() {
    cout << "Calle: " << _calle << endl;
    cout << "Numero #" << _numero << endl;
    cout << "Provincia: " << _provincia << endl;
    cout << "Codigo Postal: #" << _cp << endl;
}

void Direccion::MostrarEnLinea()
{
    cout << _calle << " " <<  _numero << ", " << _provincia << ", CP: #" << _cp;
}

string Direccion::toString()
{
    string valorADevolver;
    valorADevolver = getCalle() + " #" + to_string(getNumero()) + ", " + getProvincia() + ", CP: " + to_string(getCP());

    return valorADevolver;
}
