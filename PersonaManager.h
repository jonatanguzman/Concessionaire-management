#pragma once
#include "Persona.h"

class PersonaManager : public Persona
{
private:
    Persona _persona;
public:

    void CargarPersona();
    void CargarPersona(long long dni);
    void MostrarPersona();
    void MostrarPersonaEnLinea();
};
