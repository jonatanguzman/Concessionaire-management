#pragma once
#include "Persona.h"
#include "Direccion.h"
#include "PersonaManager.h"

class Cliente :
    public PersonaManager 
{
private:
    char _email[50];
    char _telefono[20];
    Direccion _direccion;
    bool _eliminado;

public:
    Cliente();
    std::string getEmail();
    std::string getTelefono();
    Direccion getDireccion();
    bool getEliminado();

    void setEmail(std::string e);
    void setTelefono(std::string tel);
    void setDireccion(Direccion d);
    void setEliminado(bool e);

};

