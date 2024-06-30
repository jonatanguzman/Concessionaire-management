#include <iostream>
#include "Sistema.h"
#include "FuncionesGenerales.h"
#include "rlutil.h"
using namespace std;

Sistema::Sistema() : _vehiculos(), _ventas(), _clientes(), _vendedores(), _sucursales(), _informes(), _configuracion()
{
}
void showItem(const char* t, int px, int py, bool sd)
{

    if (sd) {
        rlutil::setBackgroundColor(rlutil::COLOR::BLUE);
        rlutil::locate(px - 3, py);
        std::cout << " " << t << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::locate(px - 3, py);
        std::cout << "   " << t << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

enum Opciones {
    Opcion1 = 0,
    Opcion2 = 1,
    Opcion3 = 2,
    Opcion4 = 3,
    Opcion5 = 4,
    Opcion6 = 5,
    Opcion7 = 6,
    Opcion8 = 7,
    Opcion9 = 8
};

void Sistema::Menu()
{
    int messi = 10;

    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItem("UNIVERSIDAD TECNOLOGICA NACIONAL", 50, 2, false);
        showItem("Programa Gestor de Ventas ", 53, 4, false);
        showItem("Laboratorio de Programacion II", 50, 5, false);

        showItem("MENU PRINCIPAL", 59, 8, false);
        showItem("_____________________________________________ ", 43, 9, false);

        showItem("Vehiculos", 60, 12, y == Opcion1);
        showItem("Ventas", 60, 14, y == Opcion2);
        showItem("Vendedores", 60, 16, y == Opcion3);
        showItem("Sucursales", 60, 18, y == Opcion4);
        showItem("Clientes", 60, 20, y == Opcion5);
        showItem("Informes", 60, 22, y == Opcion6);
        showItem("Configuracion", 60, 24, y == Opcion7);
        showItem("Creditos", 60, 26, y == Opcion8);
        showItem("SALIR", 60, 29, y == Opcion9);

        switch (rlutil::getkey())
        {
        case 14: // UP
            rlutil::locate(28, 10 + y);
            std::cout << " " << std::endl;
            y--;
            if (y < 0) {
                y = 0;
            }
            break;
        case 15: // DOWN
            rlutil::locate(28, 10 + y);
            std::cout << " " << std::endl;
            y++;
            if (y > 9) {
                y = 9;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case Opcion1: _vehiculos.Menu();
                break;
            case Opcion2: _ventas.Menu();
                break;
            case Opcion3: _vendedores.Menu();
                break;
            case Opcion4: _sucursales.Menu();
                break;
            case Opcion5: _clientes.Menu();
                break;
            case Opcion6: _informes.Menu();
                break;
            case Opcion7: _configuracion.Menu();
                break;
            case Opcion8:
                rlutil::cls();
                Creditos();
                system("pause");
                break;
            case Opcion9:
                rlutil::cls();
                showItem("Gracias por utilizar nuestro programa...", 50, 5, false);
                exit(messi);
            }

        }


    } while (op != 0);
   
}

void Sistema::Creditos()
{

    showItem("Grupo 34", 50, 2, false);
    showItem("Integrantes", 53, 5, false);
    showItem("Julieta Barraza", 53, 6, false);
    showItem("Jonatan Guzman", 53, 7, false);
    showItem("Yamil Diaz", 53, 8, false);
    showItem("Jesica Valdez", 53, 9, false);
    showItem("Profesor asignado", 53, 12, false);
    showItem("Mariano Varela", 53, 13, false);
    showItem("Universidad Tecnologica Nacional", 53, 16, false);
    showItem("Facultad Regional General Pacheco", 53, 18, false);
    showItem("Tecnicatura Universitaria en Programacion TUP", 53, 20, false);
    showItem("Laboratorio de Programacion II", 53, 22, false);
    showItem("Año 2024", 53, 25, false);

}
