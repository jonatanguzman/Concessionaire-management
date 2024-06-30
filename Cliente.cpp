#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "Cliente.h"

using namespace std;

Cliente::Cliente() : _direccion()
{
    setEmail("nnnnnn");
    setTelefono("1");
    setEliminado(false);

}

string Cliente::getEmail()
{
	return _email;
}

string Cliente::getTelefono()
{
    return _telefono;
}

Direccion Cliente::getDireccion()
{
	return _direccion;
}

bool Cliente::getEliminado()
{
    return _eliminado;
}

void Cliente::setEmail(string e)
{
    if (e.size() < 50 && e.size() >= 6) {
	    strcpy(_email, e.c_str());
    }
    else {
        cout << "Email no cumple con limite de caracteres (6 a 50). Intente nuevamente:" << endl;
        getline(cin, e); 
        this->setEmail(e);
    }
}

void Cliente::setTelefono(string tel)
{
    if (tel.size() <= 19) {
        strcpy(_telefono, tel.c_str());
    }
    else {
        cout << "Telefono no cumple con limite de caracteres (20). Intente nuevamente:" << endl;
        getline(cin, tel); 
        this->setTelefono(tel);
    }
}

void Cliente::setDireccion(Direccion d)
{
    _direccion = d;
}

void Cliente::setEliminado(bool e)
{
    _eliminado = e;
}

