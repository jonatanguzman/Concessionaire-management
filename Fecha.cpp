#define _CRT_SECURE_NO_WARNINGS
#include "Fecha.h"
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
        cin.ignore();
        cout << "Dia no valido. Intente nuevamente:" << endl;
        cin >> d;
        this->setDia(d);
        cin.ignore();
    }
}

void Fecha::setMes(int m) {
    if (m <= 12 && m >= 1) {
        _mes = m;
    }
    else {
        cout << "Mes no valido. Intente nuevamente:" << endl;
        cin >> m;
        this->setMes(m);
    }
}

void Fecha::setAnio(int a) {
    if (a <= Fecha::obtenerAnioactual()) {
        _anio = a;
    }
    if (a > Fecha::obtenerAnioactual()) {
        cout << "* El Anio No puede ser Mayor al Anio Actual *" << endl;
        cout << "- Ingreselo Nuevamente: ";
        cin >> a;
        this->setAnio(a);
    }
    if (a < 1900) {
        cout << "* El Anio No puede ser Menor a 1900" << endl;
        cout << "- Ingreselo Nuevamente: ";
        cin >> a;
        this->setAnio(a);
    }
}

int Fecha::getDia() { return _dia; }

int Fecha::getMes() { return _mes; }

int Fecha::getAnio() { return _anio; }

void Fecha::Cargar() {
    int d, m, a;
    cout << "Dia: ";
    cin >> d;
    setDia(d);
    cin.ignore();
    cout << "Mes: ";
    cin >> m;
    setMes(m);
    cin.ignore();
    cout << "Año: ";
    cin >> a;
    setAnio(a);
    //cin.ignore();
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

int Fecha::obtenerAnioactual()
{
    time_t t = time(0);
    tm* tiempoLocal = localtime(&t);
    return 1900 + tiempoLocal->tm_year;  // tm_year es el número de años desde 1900
    
    /*
    primera linea; obtiene el tiempo actual en segundos desde el 1 de enero de 1970.
    segunda linea; convierte este tiempo en una estructura tm que contiene información de fecha y hora desglosada.
    tercer linea; obtiene el año actual, ya que tm_year representa el número de años transcurridos desde 1900.
    */
}



