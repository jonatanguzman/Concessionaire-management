#pragma once
#include <string>
class Direccion
{
private:
    char _calle[40];
    int _numero;
    char _provincia[40];
    int _cp;
public:
    Direccion();
    Direccion(std::string calle, int numero, std::string provincia, int cp);
    std::string getCalle();
    int getNumero();
    std::string getProvincia();
    int getCP();
    void setCalle(std::string c);
    void setNumero(int n);
    void setProvincia(std::string p);
    void setCP(int cp);
    bool validar(int cp);
    void Cargar();
    void Mostrar();
    void MostrarEnLinea();
    std::string toString();
};

