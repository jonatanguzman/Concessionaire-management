#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "Venta.h"
#include "FuncionesGenerales.h"
using namespace std;

//Constructores

Venta::Venta() : _fechaVenta()
{
    setIdVenta(999);
    setDniCliente(1111111);
    setIdSucursal(999999);
    setNroLegajo(0);
    setIdVehiculo(0);
    setGastosAdm(0);
    setTotalVentas(0);
    setEliminado(false);
}

Venta::Venta(int idVenta, Fecha fechaVenta, long long dni, int idSucursal, int nroLegajo, int idVehiculo, float gastos, double total, bool eliminado)
{
    setIdVenta(idVenta);
    setFechaVenta(fechaVenta);
    setDniCliente(dni);
    setIdSucursal(idSucursal);
    setNroLegajo(nroLegajo);
    setIdVehiculo(idVehiculo);
    setGastosAdm(gastos);
    setTotalVentas(total);
    setEliminado(eliminado);

}


//getters

int Venta::getIdVenta()
{
    return _idVenta;
}

Fecha Venta::getFechaVenta()
{
    return _fechaVenta;
}

long long Venta::getDniCliente()
{
    return _dniCliente;
}

int Venta::getIdSucursal()
{
    return _idSucursal;
}

int Venta::getNroLegajo()
{
    return _nroLegajo;
}

int Venta::getIdVehiculo()
{
    return _idVehiculo;
}

float Venta::getGastosAdm()
{
    return _gastosAdm;
}

double Venta::getTotalVenta()
{
    return _totalVenta;
}

bool Venta::getEliminado()
{
    return _eliminado;
}

//setters

void Venta::setIdVenta(int id) 
{
    if (id >= 0) {
        _idVenta = id; 
    }
    else {
        cout << "Id de Venta incorrecto. Intente nuevamente." << endl;
        id = validarInt("ID de venta: ");
        this->setIdVenta(id);
    }
}

void Venta::setFechaVenta(Fecha f)
{
    _fechaVenta = f;
}

void Venta::setDniCliente(long long dni) 
{
    while (!validar(dni)) {
        cin.clear();//limpia el estado de error
        cin.ignore(numeric_limits<long long>::max(), '\n');
        cout << "DNI no valido. Intente nuevamente. " << endl;
        dni = validarLong("* Ingrese DNI del Cliente: ");
    }

    _dniCliente = dni;
    
}

void Venta::setIdSucursal(int id) //se tiene que hacer validacion para que sea una sucursal existente
{
    if (id >= 0) {
        _idSucursal = id;
    }
    else {
        cout << "Id de Sucursal incorrecto. Intente nuevamente." << endl;
        id = validarInt("* Ingrese ID de Sucursal: ");
        this->setIdSucursal(id);
    }
}

void Venta::setNroLegajo(int nro) //se tiene que hacer validacion para que sea un vendedor existente
{
    _nroLegajo = nro;
}

void Venta::setIdVehiculo(int id) //se tiene que hacer validacion para que sea un vehiculo existente
{
    _idVehiculo = id;
}

void Venta::setGastosAdm(float gastos)
{
    if (gastos >= 0) {
        _gastosAdm = gastos;
    }
    else {
        cout << "* Los Gastos Administrativos No Pueden Ser Negativos *" << endl;
        gastos = pedirNumeroFloat("* Ingrese Gastos Administrativos: $");
        this->setGastosAdm(gastos);
    }
}

void Venta::setTotalVentas(double total)
{
    if (total >= 0) {
        _totalVenta = total;
    }
    else {
        _totalVenta = 0;
    }
}

void Venta::setEliminado(bool e)
{
    _eliminado = e;
}

//Funciones

int Venta::contarDigitos(long long num) {
    int contador = 0;
    while (num > 0) {
        num /= 10;
        contador++;
    }
    return contador;
}

bool Venta::validar(long long  dni) { 
    int numDigitos = contarDigitos(dni);
    int  minimoDigito = 7;
    int maximoDigito = 10;

    if (numDigitos >= minimoDigito && numDigitos <= maximoDigito) {
        return true;
    }
    return false;
}