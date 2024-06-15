#pragma once
#include "Persona.h"

class PersonaManager : public Persona
{
private:
    Persona _persona;
public:

    void CargarPersona();
    void MostrarPersona();
    void MostrarPersonaEnLinea();
};
