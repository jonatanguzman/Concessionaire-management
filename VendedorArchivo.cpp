#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "VendedorArchivo.h"



VendedorArchivo::VendedorArchivo()
{
    strcpy(_nombreArchivo, "Vendedores.dat");
}

VendedorArchivo::VendedorArchivo(std::string nombreArchivo = "Vendedores.dat") {
    strcpy(_nombreArchivo, nombreArchivo.c_str());
}

Vendedor VendedorArchivo::leerRegistro(int pos) {
    Vendedor registro;
    FILE* pFile;

    pFile = fopen(_nombreArchivo, "rb");

    if (pFile == nullptr) {
        return registro;
    }

    fseek(pFile, sizeof(Vendedor) * pos, SEEK_SET);

    fread(&registro, sizeof(Vendedor), 1, pFile);

    fclose(pFile);

    return registro;
}

int VendedorArchivo::ContarRegistro() {
    FILE* pFile;
    int tam;

    pFile = fopen(_nombreArchivo, "rb");

    if (pFile == nullptr) {
        return 0;
    }

    fseek(pFile, 0, SEEK_END);

    tam = ftell(pFile) / sizeof(Vendedor);

    fclose(pFile);

    return tam;
}

bool VendedorArchivo::GuardarRegistro(Vendedor registro) {
    bool resultado;
    FILE* pFile;

    pFile = fopen(_nombreArchivo, "ab");

    if (pFile == nullptr) {
        return false;
    }

    resultado = fwrite(&registro, sizeof(Vendedor), 1, pFile);

    fclose(pFile);
    return resultado;
}

bool VendedorArchivo::Sobreescribir(int pos, Vendedor reg) {
    FILE* pFile;

    pFile = fopen(_nombreArchivo, "rb+");
    if (pFile == nullptr) {
        return false;
    }

    fseek(pFile, sizeof(Vendedor) * pos, SEEK_SET);

    bool resultado = fwrite(&reg, sizeof(Vendedor), 1, pFile);

    fclose(pFile);

    return resultado;
}

int VendedorArchivo::BuscarId(int indice) {
    Vendedor reg;
    int pos = 0;
    FILE* pFile;

    pFile = fopen(_nombreArchivo, "rb");
    if (pFile == nullptr) {
        return -1;
    }

    while (fread(&reg, sizeof(Vendedor), 1, pFile)) {
        if (reg.getNroLegajo() == indice) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}
