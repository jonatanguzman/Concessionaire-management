#include <iostream>
#include "Sistema.h"
using namespace std;

Sistema::Sistema() : _vehiculos(), _ventas(), _clientes(), _vendedores(), _sucursales(), _informes(), _configuracion()
{
}

void Sistema::Menu()
{
    int opc;
    do {
        system("cls");
        cout << "--- Sistema de Gestion ---" << endl;
        cout << "-----> Lab2 Grupo34 <-----" << endl;
        cout << "----- Menu Principal -----" << endl;
        cout << "--------------------------" << endl;
        cout << " 1) Vehiculos " << endl;
        cout << " 2) Ventas " << endl;
        cout << " 3) Vendedores " << endl;
        cout << " 4) Sucursales " << endl;
        cout << " 5) Clientes " << endl;
        cout << endl;
        cout << " 6) Informes " << endl;
        cout << " 7) Configuracion " << endl;
        cout << endl;
        cout << "---------------------------" << endl;
        cout << " 8) Integrantes" << endl;
        cout << "---------------------------" << endl;
        cout << endl;
        cout << " 0) Salir del Programa" << endl;
        cout << "---------------------------" << endl;
        cout << "Selecione una opcion: ";
        cin >> opc;
        system("cls");
        switch (opc) {
        case 1: _vehiculos.Menu();
            break;
        case 2: _ventas.Menu();
            break;
        case 3: _vendedores.Menu();
            break;
        case 4: _sucursales.Menu();
            break;
        case 5: _clientes.Menu();
            break;
        case 6: _informes.Menu();
            break;
        case 7: _configuracion.Menu();
            break;
        case 8: Creditos();
            system("pause");
            break;
        case 0:cout << endl << " Adios!! " << endl;
            break;
        default:cout << endl << "* Selecione una Opcion Correcta! *" << endl << endl;;
            system("pause");
        }

    } while (opc != 0);
}

void Sistema::Creditos()
{
    cout << "------------------ GRUPO 34: ------------------" << endl;
    cout << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "		Integrantes:				" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << endl;
    cout << "1) Julieta Barraza" << endl;
    cout << "2) Jonatan Guzman" << endl;
    cout << "3) Yamil Diaz " << endl;
    cout << "4) Jesica Valdez";
    cout << endl << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "		Profesor asignado:   		" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << endl;
    cout << " Mariano Varela								";
    cout << endl << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "		Universidad:				" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Universidad Tecnologica Nacional				" << endl;
    cout << "Facultad Regional General Pacheco				" << endl;
    cout << "Tecnicatura Universitaria en Programacion TUP	" << endl;
    cout << "Laboratorio de Programacion II" << endl << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "		Año 2024					" << endl;
    cout << "-----------------------------------------------" << endl;
}
