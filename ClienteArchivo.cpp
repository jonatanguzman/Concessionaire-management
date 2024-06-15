#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include "ClienteArchivo.h"
using namespace std;

ClienteArchivo::ClienteArchivo() {
    strcpy(_nombreArchivo, "Clientes.dat");
}

ClienteArchivo::ClienteArchivo(std::string n = "Clientes.dat")
{
    if (n.size() < 40) {
        strcpy(_nombreArchivo, n.c_str());
    }
    else {
        cout << "Nombre invalido";        
    }
}

string ClienteArchivo::getNombreArchivo()
{
    return _nombreArchivo;
}

Cliente ClienteArchivo::leerCliente(int pos)
{
    Cliente reg; 
    FILE* p;

    p = fopen(_nombreArchivo, "rb"); 
    if (p == nullptr) return reg;
    fseek(p, sizeof reg * pos, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);
    return reg;
}

int ClienteArchivo::contarClientes()
{
    FILE* p;  
    p = fopen(_nombreArchivo, "rb"); 
    if (p == nullptr) return -1; 

    fseek(p, 0, 2);
    int tam = ftell(p) / sizeof(Cliente);
    fclose(p);
    return tam;
}

bool ClienteArchivo::guardarCliente(Cliente reg)
{
    FILE* p;
    p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) return false;

    bool result = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return result;
}

bool ClienteArchivo::sobreescribirCliente(Cliente reg, int pos)
{
    FILE* p;
    bool result;
    p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) {
        return false;
    }
    fseek(p, sizeof reg * pos, 0);
    result = fwrite(&reg, sizeof reg, 1, p); //escribo sobre ese registro
    fclose(p);

    return result;
}
