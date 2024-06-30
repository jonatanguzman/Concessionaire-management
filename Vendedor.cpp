#include <iostream>
#include "Vendedor.h"
#include "VendedorManager.h"
#include "FuncionesGenerales.h"
using namespace std;

//Constructores

Vendedor::Vendedor() {
    _nroLegajo = 0;
    _fechaIngreso = Fecha();
    _antiguedad = 0;
    _eliminado = false;
}

Vendedor::Vendedor(int nroLegajo, Fecha fechaIngreso, int antiguedad, bool eliminado) {
    setNroLegajo(nroLegajo);
    setFechaIngreso(fechaIngreso);
    setAntiguedad(antiguedad);
    eliminado = eliminado;
}

//Getters

int Vendedor::getNroLegajo() {
    return _nroLegajo;
}

Fecha Vendedor::getFechaIngreso() {
    return _fechaIngreso;
}

int Vendedor::getAntiguedad() {
    return _antiguedad;
}

bool Vendedor::getEliminado() {
    return _eliminado;
}

//Setters

void Vendedor::setNroLegajo(int nroLegajo) {
    
    VendedorManager vm;
    while (!validar(nroLegajo) || vm.LegajoRepetido(nroLegajo)) {
        cin.clear();//limpia el estado de error
        cin.ignore(numeric_limits<int>::max(), '\n');
        cout << "Legajo no valido." << endl;
        nroLegajo = validarInt("LEGAJO: ");
    }
    _nroLegajo = nroLegajo;
}

void Vendedor::setFechaIngreso(Fecha fechaIngreso) {
    _fechaIngreso = fechaIngreso;
}

void Vendedor::setAntiguedad(int antiguedad) {
    
    _antiguedad = antiguedad;
}

int Vendedor::calcularAntiguedad()
{
    int antiguedad = _fechaIngreso.obtenerAnioActual() - _fechaIngreso.getAnio();

    return antiguedad;
}

void Vendedor::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

int Vendedor::contarDigitos(int num) {
    int contador = 0;
    while (num > 0) {
        num /= 10;
        contador++;
    }
    return contador;
}

bool Vendedor::validar(int legajo) {
    int numDigitos = contarDigitos(legajo);
    int minimoDigito = 4;
    int maximoDigito = 6;

    if (numDigitos >= minimoDigito && numDigitos <= maximoDigito) {
        return true;
    }
    return false;
}

