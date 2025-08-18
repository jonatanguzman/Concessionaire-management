#define _CRT_SECURE_NO_WARNINGS
#include "Fecha.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

Fecha::Fecha(int dia, int mes, int anio) {
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

Fecha::Fecha() {
    setDia(1);
    setMes(1);
    setAnio(1900);

}

void Fecha::setDia(int d) {
    if (d <= 31 && d >= 1) {
        _dia = d;
    }
    else {
        cout << "Dia no valido. Intente nuevamente." << endl;
        d = validarInt("Dia: ");
        this->setDia(d);
    }
}

void Fecha::setMes(int m) {
    if (m <= 12 && m >= 1) {
        _mes = m;
    }
    else {
        cout << "Mes no valido. Intente nuevamente." << endl;
        m = validarInt("Mes: ");
        this->setMes(m);
    }
}

void Fecha::setAnio(int a) {
    if (a >= 1900) {
        _anio = a;
    }
    else {
        cout << "Año no valido. Intente nuevamente." << endl;
        a = validarInt("Año: ");
        this->setAnio(a);
    }
}

int Fecha::getDia() { return _dia; }

int Fecha::getMes() { return _mes; }

int Fecha::getAnio() { return _anio; }

void Fecha::Cargar() {
    int dia, mes, anio;
    dia = validarInt("Dia: ");
    setDia(dia);
    mes = validarInt("Mes: ");
    setMes(mes);
    anio = validarInt("Año: ");
    setAnio(anio); 

    if(esFechaValida(dia,mes,anio) == false) {
        cout << "Fecha No Valida, Ingresela Nuevamente " << endl;
        Fecha::Cargar();
    }

}


bool Fecha::operator>(const Fecha& otra) {
    if (this->_anio > otra._anio) {
        return true;
    }
    else {
        if (this->_anio == otra._anio) {
            if (this->_mes > otra._mes) {
                return true;
            }
            else {
                if (this->_mes == otra._mes) {
                    if (this->_dia > otra._dia) {
                        return true;
                    }
                    else {
                        if (this->_dia == otra._dia) {
                            return false;
                        }
                        else {
                            return false;
                        }
                    }


                }
                else return false;
            }

        }
        else return false;
    }
}

bool Fecha::operator>=(const Fecha& otra) {
    if (this->_anio > otra._anio) {
        return true;
    }
    if (this->_anio == otra._anio) {
        if (this->_mes > otra._mes) {
            return true;
        }
        if (this->_mes == otra._mes) {
            if (this->_dia >= otra._dia) {
                return true;
            }
        }
    }
    return false;
}

string Fecha::toString()
{
    string valorADevolver;
    valorADevolver = to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);

    if (to_string(_dia).size() == 1) {
        if (to_string(_mes).size() == 1) {
            valorADevolver = "0" + to_string(_dia) + "/0" + to_string(_mes) + "/" + to_string(_anio);
        }
        else {
            valorADevolver = "0" + to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);
        }
    }
    else {
        if (to_string(_mes).size() == 1) {
            valorADevolver = to_string(_dia) + "/0" + to_string(_mes) + "/" + to_string(_anio);
        }
    }
    return valorADevolver;





}

int Fecha::obtenerAnioActual()
{
    time_t t = time(0);
    tm* tiempoLocal = localtime(&t);
    return 1900 + tiempoLocal->tm_year;  // tm_year es el numero de años desde 1900

    /*
    primera linea; obtiene el tiempo actual en segundos desde el 1 de enero de 1970.
    segunda linea; convierte este tiempo en una estructura tm que contiene informacion de fecha y hora desglosada.
    tercer linea; obtiene el año actual, ya que tm_year representa el numero de años transcurridos desde 1900.
    */
}

int Fecha::obtenerMesActual()
{
    time_t t = time(0);
    tm* tiempoLocal = localtime(&t);
    return tiempoLocal->tm_mon+1;
}

int Fecha::obtenerDiaActual()
{
    time_t t = time(0);
    tm* tiempoLocal = localtime(&t);
    return tiempoLocal->tm_mday;
}

Fecha Fecha::obtenerFechaActual() 
{
    time_t t = time(0);
    tm* tiempoLocal = localtime(&t);

    return Fecha(tiempoLocal->tm_mday, tiempoLocal->tm_mon+1, tiempoLocal->tm_year+1900);

}

bool Fecha::esFechaValida(int dia, int mes, int anio) {
    /// Obtiene la fecha actual
    time_t now = time(0);
    tm* f = localtime(&now);
    /// Verifica si la fecha es anterior o igual a la fecha actual
    if (anio > f->tm_year + 1900 || (anio == f->tm_year + 1900 && mes > f->tm_mon + 1) || (anio == f->tm_year + 1900 && mes == f->tm_mon + 1 && dia > f->tm_mday)) {
        cout << "------------------------------" << endl;
        cout << "La fecha debe ser anterior o igual a la fecha actual." << endl;
        cout << "Fecha actual:" << f->tm_mday << "/" << f->tm_mon + 1 << "/" << f->tm_year + 1900 << endl;
        return false;
    }
    /// Verifica si el año es bisiesto (tiene 29 días en febrero)
    bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);

    /// Verifica si el día es válido para el mes y año dados
    if (mes == 2) { /// Febrero
        if (esBisiesto) {
            return dia >= 1 && dia <= 29;
        }
        else {
            return dia >= 1 && dia <= 28;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { /// Abril, Junio, Septiembre, Noviembre
        return dia >= 1 && dia <= 30;
    }
    return true;
}