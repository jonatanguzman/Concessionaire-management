#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <locale>
#include "Sistema.h"
#include "FuncionesGenerales.h"

using namespace std;



int main()
{
    setlocale(LC_ALL, "spanish");
    Sistema programa;

    programa.Menu();

    return 0;
}

