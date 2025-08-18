#pragma once
#include <string>
class Fecha
{
private:
    int _dia, _mes, _anio;
    void setDia(int d);
    void setMes(int m);
public:
    void setAnio(int a);
    Fecha();
    Fecha(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();

    void Cargar();
    bool operator>(const Fecha& otra); // if fecha > fecha otra == true
    bool operator>=(const Fecha& otra); // if fecha >= fecha otra == true
    std::string toString();
    int obtenerAnioActual();
    int obtenerMesActual();
    int obtenerDiaActual();
    Fecha obtenerFechaActual();

    bool esFechaValida(int dia, int mes, int anio);

};

