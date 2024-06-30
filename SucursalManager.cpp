#define _CRT_SECURE_NO_WARNINGS 
#include "SucursalManager.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <iomanip>
#include "Sistema.h"
#include "rlutil.h"
using namespace std;

SucursalManager::SucursalManager() : _archivo()
{

}
void showItemSucursal(const char* text, int posx, int posy, bool selected)
{

    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::CYAN);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << text << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
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
};

void SucursalManager::Menu()
{
    Sistema programa;
    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {

        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemSucursal("--- MENU SUCURSAL ---", 50, 2, false);
        showItemSucursal("Agregar Sucursal ", 53, 4, y == Opcion1);
        showItemSucursal("Listar Sucursales ", 53, 5, y == Opcion2);
        showItemSucursal("Modificar Sucursal ", 53, 6, y == Opcion3);
        showItemSucursal("Buscar Sucursal ", 53, 7, y == Opcion4);
        showItemSucursal("Borrar Sucursal ", 53, 8, y == Opcion5);
        showItemSucursal("Backup ", 53, 9, y == Opcion6);
        showItemSucursal("Restaurar Backup ", 53, 10, y == Opcion7);
        showItemSucursal("Regresar al Menu Principal ", 53, 13, y == Opcion8);


        switch (rlutil::getkey()) {
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
            if (y > 8) {
                y = 8;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case Opcion1:
                rlutil::cls();
                agregarRegistro();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                listarRegistros();
                system("pause");
                break;
            case Opcion3:
                rlutil::cls();
                editarRegistro();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                buscarSucursal();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                bajaLogica();
                system("pause");
                break;
            case Opcion6:
                rlutil::cls();
                backupArchivo();
                system("pause");
                break;
            case Opcion7:
                rlutil::cls();
                restaurarBackup();
                system("pause");
                break;
            case Opcion8:
                rlutil::cls();
                programa.Menu();
                break;
            }
        }
    } while (op != 0);
}

void SucursalManager::salidaEnPantalla()
{
    cout << left;
    cout << setw(5) << "ID";
    cout << setw(21) << "Nombre";
    cout << setw(54) << "Direccion";
    cout << setw(20) << "Telefono";
    cout << endl;
}

bool SucursalManager::validarIDUnico(int id)
{
    Sucursal reg;

    int cant = _archivo.contarRegistro();
    for (int i = 0; i < cant; i++) {
        reg = _archivo.leerRegistro(i);
        if (reg.getIdSucursal() == id) {
            return true;
        }
    }
    return false;
}


void SucursalManager::agregarRegistro()
{
    if (_archivo.guardarRegistro(crearRegistro())) {
        cout << "La Sucursal se guardo correctamente." << endl;
    }
    else {
        cout << "No se pudo guardar la sucursal." << endl;
    }
}

void SucursalManager::ordenarNombre(Sucursal obj[], int tam)
{
    Sucursal aux;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (obj[j].getNombre() > obj[j + 1].getNombre()) {
                aux = obj[j];
                obj[j] = obj[j + 1];
                obj[j + 1] = aux;
            }
        }
    }
}

void SucursalManager::listarPorNombre()
{
    int cantidad = _archivo.contarRegistro();
    Sucursal* vec, reg;

    vec = new Sucursal[cantidad];
    if (vec == nullptr) {
        std::cout << "No hay memoria.";
    }

    if (cantidad == 0) {
        std::cout << "No hay sucursal para mostrar." << std::endl;
    }
    else {
        salidaEnPantalla();
        for (int i = 0; i < cantidad; i++) {
            reg = _archivo.leerRegistro(i);
            vec[i] = reg;
        }

        ordenarNombre(vec, cantidad);
        for (int i = 0; i < cantidad; i++) {
            if (vec[i].getEstado() == false) {
                mostrarRegistro(vec[i]);
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    delete[]vec;
}

void SucursalManager::ordenarID(Sucursal obj[], int tam)
{
    Sucursal aux;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (obj[j].getIdSucursal() > obj[j + 1].getIdSucursal()) {
                aux = obj[j];
                obj[j] = obj[j + 1];
                obj[j + 1] = aux;
            }
        }
    }
}

void SucursalManager::listarPorID()
{
    int cantidad = _archivo.contarRegistro();
    Sucursal* vec, reg;

    vec = new Sucursal[cantidad];
    if (vec == nullptr) {
        std::cout << "No hay memoria.";
    }

    if (cantidad == 0) {
        std::cout << "No hay sucursal para mostrar." << std::endl;
    }
    else {
        salidaEnPantalla();
        for (int i = 0; i < cantidad; i++) {
            reg = _archivo.leerRegistro(i);
            vec[i] = reg;
        }

        ordenarID(vec, cantidad);
        for (int i = 0; i < cantidad; i++) {
            if (vec[i].getEstado() == false) {
                mostrarRegistro(vec[i]);
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    delete[]vec;
}

enum OpcionesLR {
    opcion1LR = 0,
    opcion2LR = 1,
    opcion3LR = 2,
};

void SucursalManager::listarRegistros()
{

    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        showItemSucursal("- Listado de Sucursales -", 53, 2, false);
        showItemSucursal("Por ID", 53, 4, y == opcion1LR);
        showItemSucursal("Por Nombre", 53, 5, y == opcion2LR);
        showItemSucursal("Volver al menu anterior", 53, 8, y == opcion3LR);

        switch (rlutil::getkey()) {
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
            if (y > 2) {
                y = 2;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case opcion1LR:
                rlutil::cls();
                listarPorID();
                system("pause");
                break;
            case opcion2LR:
                rlutil::cls();
                listarPorNombre();
                system("pause");
                break;
            case opcion3LR:
                rlutil::cls();
                Menu();
                break;
            }
        }
    } while (op != 0);
}

enum OpcionesBS {
	Opcion1BS = 0,
	Opcion2BS = 1,
    Opcion3BS = 2,
};

void SucursalManager::buscarSucursal()
{
    int opc = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemSucursal("--- BUSCAR SUCURSAL ---", 50, 2, false);
        showItemSucursal("Por ID ", 53, 4, y == Opcion1BS);
        showItemSucursal("Por Nombre ", 53, 5, y == Opcion2BS);
        showItemSucursal("Regresar al Menu Sucursal ", 53, 8, y == Opcion3BS);

        switch (rlutil::getkey()) {
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
                if (y > 2) {
					y = 2;
				}
                break;
			case 1: // ENTER
				switch (y) {
					case Opcion1BS:
						rlutil::cls();
						buscarSucursalID();
						system("pause");
						break;
					case Opcion2BS:
						rlutil::cls();
						buscarSucursalNombre();
						system("pause");
						break;
					case Opcion3BS:
						rlutil::cls();
						Menu();
						break;
				}
		}
	} while (opc != 0);
}

void SucursalManager::buscarSucursalID()
{
    int id, pos;
    Sucursal reg;

    id = validarInt("Ingrese ID de la Sucursal que desea Buscar: ");
    cout << endl;

    pos = _archivo.buscarPosicion(id);
    salidaEnPantalla();

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);
        if (reg.getIdSucursal() == id) {
            mostrarRegistro(reg);
        }
    }
    else {
        cout << "No se encontro la sucursal." << endl;
    }
    cout << endl;

}

void SucursalManager::buscarSucursalNombre()
{
    string nombre;
    Sucursal reg;
    int cant = _archivo.contarRegistro();

    cout << "Ingrese Nombre de la Sucursal que desea Buscar: ";
    getline(cin, nombre);
    cout << endl;

    if (cant >= 0) {
        for (int i = 0; i < cant; i++) {
            reg = _archivo.leerRegistro(i);
            if (reg.getNombre() == nombre) {
                mostrarRegistro(reg);
            }
        }
    }
    else {
        cout << "No se encontro la sucursal." << endl;
    }
}

Sucursal SucursalManager::crearRegistro()
{
    Sucursal reg;
    string id;
    int idSucursal;
    string nombre;
    string telefono;
    Direccion d;

    cout << "---- Cargar Registro ----" << endl;
    cout << endl;

    idSucursal = validarInt("Ingrese Id Sucursal: ");
    reg.setIdSucursal(idSucursal);
    cout << "Ingrese Nombre de Sucursal: ";
    getline(cin, nombre);
    reg.setNombre(nombre);
    cout << "Ingrese Dirección: ";
    d.Cargar();
    reg.setDireccion(d);
    cout << "Ingrese Telefono: ";
    getline(cin, telefono);
    reg.setTelefono(telefono);

    return reg;
}

void SucursalManager::mostrarRegistro(Sucursal reg)
{
    cout << left;
    cout << setw(5) << reg.getIdSucursal();
    cout << setw(21) << reg.getNombre();
    cout << setw(54) << reg.getDireccion().toString();
    cout << setw(20) << reg.getTelefono();

}

void SucursalManager::editarRegistro()
{
    int id, pos, opcion;
    Sucursal reg;

    id = validarInt("Ingrese ID de la Sucursal que desea Modificar: ");
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);
        if (reg.getEstado() == false) {
            cout << endl << "Sucursal a Modificar: " << endl;
            mostrarRegistro(reg);

            cout << endl;
            cout << "* Que dato desea Editar? " << endl;
            cout << "1 - Nombre" << endl;
            cout << "2 - Direccion" << endl;
            cout << "3 - Telefono" << endl;
            cout << "Volver al menu anterior" << endl;
            opcion = validarInt("Opcion: ");

            switch (opcion) {
            case 1:
            {
                string n;
                cout << "Ingrese nuevo Nombre: ";
                getline(cin, n);
                reg.setNombre(n);
                break;
            }
            case 2:
            {
                Direccion d;
                cout << "Ingrese nueva direccion: ";
                d.Cargar();
                reg.setDireccion(d);
                break;
            }
            case 3:
            {
                string tel;
                cout << "Ingrese nuevo telefono: ";
                getline(cin, tel);
                reg.setTelefono(tel);
                break;
            }
            case 0:
                break;
            default:
                cout << "Opcion invalida.";
                break;
            }

            cout << endl;
            bool modificacion = _archivo.sobreescribirRegistro(reg, pos);

            if (modificacion = true) {
                cout << "La sucursal se modifico correctamente." << endl;
            }
            else {
                cout << "No se pudo modificar la sucursal." << endl;
            }


        }
        else {
            cout << "La sucursal buscada se encuentra eliminada." << endl;
        }
    }
}

void SucursalManager::bajaLogica()
{
    int id, pos;
    Sucursal reg;

    id = validarInt("Ingrese ID de la Sucursal que desea dar de baja: ");
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);
        if (reg.getEstado() == true) {
            cout << "La sucursal ya se encuentra eliminada." << endl;
        }
        else {
            reg.setEstado(true);
            bool modificacion = _archivo.sobreescribirRegistro(reg, pos);

            if (modificacion = true) {
                cout << "La sucursal se dio de baja correctamente." << endl;
            }
            else {
                cout << "No se pudo dar de baja la sucursal." << endl;
            }
        }
    }
    else {
        cout << "No se encontro la sucursal." << endl;
    }
}

void SucursalManager::backupArchivo()
{
    string origen = "Sucursales.dat";
    string copia = "Sucursales.bkp";

    string comando = "copy " + origen + " " + copia;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << endl << "Backup realizado con exito. " << endl;
    }
    else {
        cout << "Hubo un error al copiar el archivo. " << endl;
    }
}

void SucursalManager::restaurarBackup()
{
    string origen = "Sucursales.dat";
    string copia = "Sucursales.bkp";

    string comando = "copy " + origen + " " + copia;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << endl << "Restauracion realizada con exito. " << endl;
    }
    else {
        cout << "Hubo un error al restaurar el archivo. " << endl;
    }
}