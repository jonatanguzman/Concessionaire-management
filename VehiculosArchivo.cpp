#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "VehiculosArchivo.h"
using namespace std;

VehiculosArchivo::VehiculosArchivo() {
    strcpy(_nombreArchivo, "Vehiculos.dat");
}

VehiculosArchivo::VehiculosArchivo(std::string n = "Vehiculos.dat") {
    if (n.size() <= 40) {
        strcpy(_nombreArchivo, n.c_str());
    }
    else {
        cout << "* Error de Archivo *" << endl;
    }
}

Vehiculo VehiculosArchivo::leerRegistro(int pos) {
    Vehiculo reg;
    FILE* p;
    p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, sizeof reg * pos, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);
    return reg;
}

int VehiculosArchivo::contarRegistros() {
    FILE* p;
    p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -1;
    fseek(p, 0, 2);
    int tam = ftell(p) / sizeof(Vehiculo);
    fclose(p);
    return tam;
}

bool VehiculosArchivo::guardarRegistro(Vehiculo reg) {
    FILE* p;
    p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool guardo = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return guardo;
}

int VehiculosArchivo::buscarRegistro(int id) {
    Vehiculo reg;
    int pos = 0;
    FILE* p;
    p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -2;
    while (fread(&reg, sizeof(Vehiculo), 1, p)) {
        if (reg.getIdVehiculo() == id) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

bool VehiculosArchivo::modificarRegistro(Vehiculo reg, int pos) {
    FILE* p;
    p = fopen(_nombreArchivo, "rb+");
    if (p == NULL)return false;
    fseek(p, sizeof reg * pos, 0);
    bool modifico = fwrite(&reg, sizeof(Vehiculo), 1, p);
    fclose(p);
    return modifico;
}