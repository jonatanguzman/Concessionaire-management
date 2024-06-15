#define _CRT_SECURE_NO_WARNINGS 
#include "SucursalManager.h"
#include <iostream>
#include <iomanip>
using namespace std;

SucursalManager::SucursalManager() : _archivo()
{

}

void SucursalManager::Menu()
{
    int opcion;
    do {
        system("cls");
        cout << "----- MENU SUCURSAL -----" << endl;
        cout << "---------------------------- " << endl;
        cout << endl;
        cout << "1. Agregar Registro    " << endl;
        cout << "2. Listar Registros    " << endl;
        cout << "3. Modificar Registros " << endl;
        cout << "4. Buscar Sucursal     " << endl;
        cout << "5. Borrar Sucursal     " << endl;
        cout << "6. Backup              " << endl;
        cout << "7. Restaurar backup    ";

        cout << endl;
        cout << "0. SALIR DEL PROGRAMA " << endl;
        cout << "---------------------------- " << endl;
        cout << "OPCION: " << endl;
        cin >> opcion;
        system("cls");

        switch (opcion) {
        case 1:
            agregarRegistro();
            system("pause");
            break;

        case 2:
            listarRegistros();
            system("pause");
            break;
        case 3:
            editarRegistro();
            system("pause");
            break;
        case 4:
            buscarSucursal();
            system("pause");
            break;
        case 5:
            bajaLogica();
            system("pause");
            break;
        case 6:
            backupArchivo();
            system("pause");
            break;
        case 7:
            restaurarBackup();
            system("pause");
            break;
        case 0:

            break;
        }
    } while (opcion != 0);
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

void SucursalManager::listarRegistros()
{
    Sucursal reg;
    int cant = _archivo.contarRegistro();

    salidaEnPantalla();

    for (int i = 0; i < cant; i++) {
        reg = _archivo.leerRegistro(i);
        if (reg.getEstado() == false) {
            mostrarRegistro(reg);
            cout << endl;
        }
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

void SucursalManager::buscarSucursal()
{
    int opc;

    cout << "** Busqueda de Sucursales **" << endl;
    cout << "1 - Buscar por ID" << endl;
    cout << "2 - Buscar por Nombre" << endl;

    cout << "Ingrese su opcion: ";
    cin >> opc;

    switch (opc)
    {
    case 1:
    {
        buscarSucursalID();
        break;
    case 2:
        buscarSucursalNombre();
        break;

    }
    default:
        break;
    }

}

void SucursalManager::buscarSucursalID()
{
    int id, pos;
    Sucursal reg;

    cout << "Ingrese ID de la Sucursal que desea Buscar " << endl;
    cin >> id;
    cin.ignore();
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);
        if (reg.getIdSucursal() == id) {
            mostrarRegistro(reg);
        }
    }
    else {
        cout << "No se encontro la sucursal." << endl;
    }
}

void SucursalManager::buscarSucursalNombre()
{
    string nombre;
    Sucursal reg;
    int cant = _archivo.contarRegistro();

    cout << "Ingrese Nombre de la Sucursal que desea Buscar " << endl;
    cin.ignore();
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
    int id; 
    string nombre; 
    string telefono; 
    Direccion d; 

    cout << "---- Cargar Registro ----" << endl; 
    cout << endl; 

    cout << "Ingrese Id Sucursal: ";
    cin >> id;
    cin.ignore();
    reg.setIdSucursal(id); 
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

    cout << "Ingrese ID de la Sucursal que desea Modificar " << endl;
    cin >> id;
    cin.ignore();
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);
        if (reg.getEstado() == false) {
            cout << endl << "Sucursal a Modificar: " << endl;
            reg.Mostrar();

            cout << endl;
            cout << "* Que dato desea Editar? " << endl;
            cout << "1 - Nombre" << endl;
            cout << "2 - Direccion" << endl;
            cout << "3 - Telefono" << endl;
            cin >> opcion;
            cin.ignore();

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

    cout << "Ingrese ID de la Sucursal que desea dar de baja " << endl;
    cin >> id;
    cin.ignore();
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
        cout << endl << "Backup realizado con exito. " << endl;
    }
    else {
        cout << "Hubo un error al copiar el archivo. " << endl;
    }
}

