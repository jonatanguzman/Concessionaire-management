#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#include "Vehiculo.h"

Vehiculo::Vehiculo() {
    _idVehiculo = 0;
    strcpy(_marca, "S/D");
    strcpy(_modelo, "S/D");
    strcpy(_version, "S/D");
    strcpy(_color, "S/D");
    _anioFabricacion = 2024;
    _stock = 0;
    _precioUnidad = 0;
    _estado = false;
}

Vehiculo::Vehiculo(int i, string m, string mo, string v, string c, int a, int s, float p, bool e) {
    _idVehiculo = i;
    strcpy(_marca, m.c_str());
    strcpy(_modelo, mo.c_str());
    strcpy(_modelo, v.c_str());
    strcpy(_color, c.c_str());
    _anioFabricacion = a;
    _stock = s,
        _precioUnidad = p,
        _estado = false;
}

void Vehiculo::setIdVehiculo(int i) {
    _idVehiculo = i;
}

int Vehiculo::getIdVehiculo() {
    return _idVehiculo;
}

void Vehiculo::setMarca(string m) {
    if (m.size() <= 40) {
        strcpy(_marca, m.c_str());
    }
    else {
        strcpy(_marca, "S/D");
    }
}

string Vehiculo::getMarca() {
    return _marca;
}

void Vehiculo::setModelo(string mo) {
    if (mo.size() <= 40) {
        strcpy(_modelo, mo.c_str());
    }
    else {
        strcpy(_modelo, "S/D");
    }
}
string Vehiculo::getModelo() {
    return _modelo;
}

void Vehiculo::setVersion(string v) {
    if (v.size() <= 40) {
        strcpy(_version, v.c_str());
    }
    else {
        strcpy(_version, "S/D");
    }
}
string Vehiculo::getVersion() {
    return _version;
}

void Vehiculo::setColor(string c) {
    if (c.size() <= 40) {
        strcpy(_color, c.c_str());
    }
    else {
        strcpy(_color, "S/D");
    }
}
string Vehiculo::getColor() {
    return _color;
}

void Vehiculo::setAnioFabricacion(int a) {
    _anioFabricacion = a;
}
int Vehiculo::getAnioFabricacion() {
    return _anioFabricacion;
}

void Vehiculo::setStock(int s) {
    _stock = s;
}
int Vehiculo::getStock() {
    return _stock;
}

void Vehiculo::setPrecioUnidad(float p) {
    _precioUnidad = p;
}
float Vehiculo::getPrecioUnidad() {
    return _precioUnidad;
}

void Vehiculo::setEstado(bool s) {
    _estado = s;
}
bool Vehiculo::getEstado() {
    return _estado;
}
