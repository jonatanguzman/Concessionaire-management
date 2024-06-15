#pragma once
#include <string>
class Fecha
{
private:
    int _dia, _mes, _anio;
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();

    void Cargar();
    bool operator>(const Fecha& otra); // if fecha > fecha otra == true
    std::string toString();
    int obtenerAnioactual();

};

