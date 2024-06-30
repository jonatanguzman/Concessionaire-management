#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <locale>
#include "ClienteManager.h"
#include "FuncionesGenerales.h"
#include "Sistema.h"
#include "rlutil.h"
using namespace std;

ClienteManager::ClienteManager() : _archivo("Clientes.dat")
{
}

void showItemC(const char* text, int posx, int posy, bool selected)
{

    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
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
    Salir = 8
};

void ClienteManager::Menu()
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

        showItemC("--- MENU CLIENTES ---", 50, 2, false);

        showItemC("Cargar ", 53, 5, y == Opcion1);
        showItemC("Listar Clientes ", 53, 6, y == Opcion2);
        showItemC("Buscador de Clientes ", 53, 7, y == Opcion3);
        showItemC("Editar información ", 53, 8, y == Opcion4);
        showItemC("Borrar ", 53, 9, y == Opcion5);
        showItemC("Crear backup ", 53, 10, y == Opcion6);
        showItemC("Restaurar backup ", 53, 11, y == Opcion7);
        showItemC("Regresar al Menu Principal ", 53, 15, y == Opcion8);

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
                agregarCliente();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                menuListado();
                system("pause");
                break;
            case Opcion3:
                rlutil::cls();
                buscadorDeClientes();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                editarCliente();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                borrarCliente();
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
                programa.Menu();
                break;
            }


        }


    }

    while (op != 0);
    system("pause");

    return;
}

Cliente ClienteManager::crearCliente()
{
    string email, tel;
    Direccion d;
    Cliente reg;
    int opc;
    std::cout << "------------- Ingreso de nuevo Cliente -------------" << endl;
    regreso:
    reg.CargarPersona();
    bool resultado = DniRepetido(reg.getDni());
    if (resultado) {
        std::cout << "* Cliente ya existente *";
        opc = validarInt("Desea cargar un nuevo cliente? (1)Si - (2)No : ");

        switch (opc)
        {
        case 1:
            system("cls");
            goto regreso;
            break;
        case 2:
            Menu();
            break;
        
        default:
            break;
        }

    }

    std::cout << "EMAIL: ";
    getline(cin, email);
    reg.setEmail(email);
    tel = validarStringNumerico("TELEFONO: ");
    reg.setTelefono(tel);
    std::cout << "DIRECCION: " << endl;
    d.Cargar();
    reg.setDireccion(d);
    reg.setEliminado(false);

    return reg;
}

Cliente ClienteManager::crearCliente(long long dni)
{
    string email, tel;
    Direccion d;
    Cliente reg;
    char opc;
    std::cout << "------------- Ingreso de nuevo Cliente -------------" << endl;
    reg.CargarPersona(dni);
    std::cout << "EMAIL: ";
    getline(cin, email);
    reg.setEmail(email);
    tel = validarStringNumerico("TELEFONO: ");
    reg.setTelefono(tel);
    std::cout << "DIRECCION: " << endl;
    d.Cargar();
    reg.setDireccion(d);
    reg.setEliminado(false);

    return reg;
}


void ClienteManager::mostrarCliente(Cliente reg)
{
    reg.MostrarPersona();
    std::cout << endl;
    std::cout << "EMAIL: " << reg.getEmail() << endl;
    std::cout << "TELEFONO: " << reg.getTelefono() << endl;
    std::cout << "DIRECCION: " << reg.getDireccion().toString();
}

void ClienteManager::mostrarClienteEnLinea(Cliente reg) 
{
    reg.MostrarPersonaEnLinea();
    std::cout << setw(33) << reg.getEmail();
    std::cout << setw(20) << reg.getTelefono();
    std::cout << setw(30) << reg.getDireccion().toString();
    std::cout << endl;
}

void ClienteManager::agregarCliente()
{
    if (_archivo.guardarCliente(crearCliente())) {
        std::cout << "El cliente se guardó correctamente." << endl;
    }
    else {
        std::cout << "No se pudo guardar el cliente." << endl;
    }
}

void ClienteManager::encabezadoClientes()
{
    std::cout << left;
    std::cout << setw(55) << " " << "* Listado de Clientes *" << endl;
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    std::cout << setw(14) << "DNI";
    std::cout << setw(20) << "Nombre ";
    std::cout << setw(20) << "Apellido ";
    std::cout << setw(23) << "Fecha de Nacimiento ";
    std::cout << setw(33) << "Email ";
    std::cout << setw(20) << "Telefono ";
    std::cout << setw(30) << "Direccion ";
    std::cout << endl;
}

enum OpcionesCL {
    Opcion1CL = 0,
    Opcion2CL = 1,
    Opcion3CL = 2
};


void ClienteManager::menuListado()
{

    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        showItemC("- Como desea ordenar el listado de Clientes? -", 50, 2, false);
        showItemC("Ordenar por carga", 53, 5, y == Opcion1CL);
        showItemC("Ordenar por apellido", 53, 6, y == Opcion2CL);
        showItemC("Regresar al Menu Clientes", 53, 9, y == Opcion3CL);

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
            case Opcion1CL:
                rlutil::cls();
                listarClientes();
                system("pause");
                break;
            case Opcion2CL:
                rlutil::cls();
                listarClientesXApellido();
                system("pause");
                break;
            case Opcion3CL:
                rlutil::cls();
                Menu();
                break;
            }
        }    
    } while (op != 0);
}

void ClienteManager::listarClientes() //por oden de carga
{
    int i, cantidad = _archivo.contarClientes();
    Cliente reg;

    encabezadoClientes();

        for (i = 0; i < cantidad; i++) {
            reg = _archivo.leerCliente(i);
            if (reg.getEliminado() == false) {
                mostrarClienteEnLinea(reg);
            }
        
        }

}

void ClienteManager::listarClientesXApellido()
{

    int i, cantidad = _archivo.contarClientes();
    Cliente reg;
    vector <Cliente> vec;

    if (cantidad == 0) {
        std::cout << "* No hay Clientes para mostrar *" << endl;
    }
    else {
        encabezadoClientes();
        for (i = 0; i < cantidad; i++) {
            reg = _archivo.leerCliente(i);
            vec.push_back(reg);
        }
        ordenar(vec, cantidad);
        for (i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                mostrarClienteEnLinea(vec[i]);
            }
        }
        std::cout << endl;

    }
}

void ClienteManager::ordenar(vector<Cliente>& vec, int cantidad) {
    Cliente aux;

    for (int i = 0; i < cantidad; i++) {

        for (int j = i; j < cantidad; j++) {

            if (vec[i].getApellido() > vec[j].getApellido()) {

                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

            }
        }
    }

}

int ClienteManager::buscarCliente(long dni)
{
    Cliente reg;
    FILE* p;
    int pos = 0;
    p = fopen(_archivo.getNombreArchivo().c_str(), "rb");
    if (p == nullptr) {
        return -2; //no se abrio el archivo
    }
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        if (reg.getDni() == dni) {
            fclose(p); //cierro el archivo porque ya encontre la empresa
            return pos;
        }
        pos++;
    }
    fclose(p);

    return -1; //se recorrio el archivo y no existe el codigo
}

void ClienteManager::editarCliente()
{
    long long dni;
    int opcion;

    dni = validarLong("Ingrese DNI del Cliente a editar: ");
    cout << endl;

    int pos = buscarCliente(dni);

    if (pos >= 0) {
        Cliente reg;
        reg = _archivo.leerCliente(pos);

        if (reg.getEliminado() == false) {
            cout << endl << "Cliente a Editar: " << endl;
            mostrarCliente(reg);

            cout << endl << endl;
            cout << "¿Que dato desea editar?" << endl;
            cout << "1 - Email" << endl;
            cout << "2 - Telefono" << endl;
            cout << "3 - Direccion" << endl;
            cout << "Volver al menu anterior" << endl;
            opcion = validarInt("Opcion: ");

            switch (opcion) {
            case 1:
            {
                string e;
                cout << "Ingrese nuevo email:";
                getline(cin, e);
                reg.setEmail(e);
                break;
            }
            case 2:
            {
                string tel;
                tel = validarStringNumerico("Ingrese nuevo telefono: ");
                reg.setTelefono(tel);
                break;
            }
            case 3:
            {
                Direccion d;
                cout << "Ingrese nueva dirección: ";
                d.Cargar();
                reg.setDireccion(d);
                break;
            }
            default:
                cout << "Opcion invalida.";
                break;
            }

            cout << endl;
            bool result = _archivo.sobreescribirCliente(reg, pos);

            if (result == true) {
                cout << "Se editó correctamente el cliente." << endl;
            }
            else {
                cout << "No se pudo editar el cliente." << endl;
            }


        }
        else {
            cout << "El cliente buscado se encuentra eliminado" << endl;
        }

    }
    else {
        cout << "Error al buscar el cliente. Codigo error " << pos << endl;
    }
    
}

void ClienteManager::backupArchivo()
{
    string origen = "Clientes.dat";
    string copia = "Clientes.bkp";

    string comando = "copy " + origen + " " + copia; 

    int resultado = system(comando.c_str()); 

    if (resultado == 0) {
        std::cout << endl << "Backup realizado con exito." << endl;
    }
    else {
        std::cout << "Hubo un error al copiar el archivo." << endl;
    }
}

void ClienteManager::restaurarBackup()
{
    string origen = "Clientes.bkp";
    string copia = "Clientes.dat";

    string comando = "copy " + origen + " " + copia; 

    int resultado = system(comando.c_str()); 

    if (resultado == 0) {
        std::cout << endl << "Backup restaurado con exito." << endl;
    }
    else {
        std::cout << "Hubo un error al restaurar el archivo." << endl;
    }
}

void ClienteManager::borrarCliente()
{
    long long dni;
    int opc;

    dni = validarLong("Ingrese DNI del Cliente a borrar: ");
    std::cout << endl;

    int pos = buscarCliente(dni);

    if (pos >= 0) {
        Cliente reg;
        reg = _archivo.leerCliente(pos);

        std::cout << endl << "Cliente a Borrar: " << endl << endl;
        mostrarCliente(reg);
        std::cout << endl;
        opc = validarInt("Confirma que desea borrar este Cliente? (1)Si - (2)No: ");

        if (opc == 1) {
            reg.setEliminado(true);
            bool result = _archivo.sobreescribirCliente(reg, pos);
            if (result) {
                std::cout << "* El cliente se ha borrado correctamente *" << endl;
            }
            else {
                std::cout << "* No se pudo eliminar el cliente *" << endl;
            }
        }
        else {
            std::cout << endl << "* Se cancelo el borrado del cliente *" << endl;
        }

    }
    else {
        std::cout << "* El cliente buscado no existe *" << endl;
    }
}

void ClienteManager::buscadorDeClientes()
{
    int cantReg = _archivo.contarClientes();
    if (cantReg == -1) {
        std::cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int pos;
        long long dni;
        dni = validarLong("Ingrese el DNI a buscar: ");
        std::cout << endl;
        
        pos = buscarCliente(dni);
        if (pos == -1) {
            std::cout << endl << "* No se Encontraron Clientes con el DNI buscado *" << endl;
        }
        if (pos >= 0) {
            Cliente reg = _archivo.leerCliente(pos);
            if (reg.getEliminado() == false) {
                mostrarCliente(reg);
                std::cout << endl;
            }
            else {
                std::cout << "* El Registro se Encuentra Eliminado *" << endl;
            }
        }
        std::cout << endl;
    
    
    }
}

bool ClienteManager::DniRepetido(long long idPersona) {
    ClienteArchivo ca;
    Cliente registro;
    int cantidad = ca.contarClientes();

    for (int i = 0; i < cantidad; i++) {
        registro = ca.leerCliente(i);

        if (registro.getDni() == idPersona) {
            return true;
        }
    }
    return false;
}