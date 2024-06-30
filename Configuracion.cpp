# include<iostream>
using namespace std;
#include "VehiculosManager.h"
#include "VentasManager.h"
#include "SucursalManager.h"
#include "VendedorManager.h"
#include "ClienteManager.h"
#include "Configuracion.h"
#include "FuncionesGenerales.h"
#include "Sistema.h"
#include "rlutil.h"


void showItemCf(const char* text, int posx, int posy, bool selected)
{

    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::LIGHTBLUE);
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
};

void Configuracion::Menu() 
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

        showItemCf("--- CONFIGURACIÓN ---", 50, 2, false);

        showItemCf("SubMenu Vehiculos ", 53, 4, y == Opcion1);
        showItemCf("SubMenu Ventas ", 53, 5, y == Opcion2);
        showItemCf("SubMenu Sucursales ", 53, 6, y == Opcion3);
        showItemCf("SubMenu Vendedores ", 53, 7, y == Opcion4);
        showItemCf("SubMenu Clientes ", 53, 8, y == Opcion5);
        showItemCf("Regresar al Menu Principal ", 53, 11, y == Opcion6);

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
            if (y > 6) {
                y = 6;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case Opcion1:
                rlutil::cls();
                subMenuVehiculos();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                subMenuVentas();
                system("pause");
                break;
            case Opcion3:
                rlutil::cls();
                subMenuSucursales();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                subMenuVendedores();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                subMenuClientes();
                system("pause");
                break;
            case Opcion6:
                programa.Menu();
            }
        }
    } while (op != 0);
}

enum OpionesAVehiculos
{
    opcion1AVehiculos= 1,
    opcion2AVehiculos = 2,
    opcion3AVehiculos = 3
};

void Configuracion::subMenuVehiculos() {
    VehiculosManager vehiculos;

    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do{
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemCf("--- ARCHIVO VEHICULOS ---", 50, 2, false);
        showItemCf("Realizar Backup ", 53, 4, y == opcion1AVehiculos);
        showItemCf("Restaurar Backup ", 53, 5, y == opcion2AVehiculos);
        showItemCf("Regresar al menu anterior ", 53, 8, y == opcion3AVehiculos);

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
            if (y > 3) {
                y = 3;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case opcion1AVehiculos:
                rlutil::cls();
                vehiculos.realizarBackup();
                system("pause");
                break;
            case opcion2AVehiculos:
                rlutil::cls();
                vehiculos.restaurarBackup();
                system("pause");
                break;
            case opcion3AVehiculos:
                rlutil::cls();
                Menu();
                break;
            }
        }
    } while (op != 0);
}

enum OpionesSVentas
{
    opcion1SVentas = 1,
    opcion2SVentas = 2,
    opcion3SVentas = 3
};

void Configuracion::subMenuVentas() {
    VentasManager ventas;

    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemCf("--- ARCHIVO VENTAS ---", 50, 2, false);
        showItemCf("Realizar Backup ", 53, 4, y == opcion1SVentas);
        showItemCf("Restaurar Backup ", 53, 5, y == opcion2SVentas);
        showItemCf("Regresar al Menu ", 53, 8, y == opcion3SVentas);

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
            if (y > 3) {
                y = 3;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case opcion1SVentas:
                rlutil::cls();
                ventas.backupArchivo();
                system("pause");
                break;
            case opcion2SVentas:
                rlutil::cls();
                ventas.restaurarBackup();
                system("pause");
                break;
            case opcion3SVentas:
                rlutil::cls();
                Menu();
                break;
            }
        } 
    } while (op != 0);
}

enum OpionesSSucursales
{
	opcion1SSucursales = 1,
	opcion2SSucursales = 2,
	opcion3SSucursales = 3
};

void Configuracion::subMenuSucursales() {
    SucursalManager sucursales;

    int opc = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemCf("--- ARCHIVO SUCURSALES ---", 50, 2, false);
        showItemCf("Realizar Backup ", 53, 4, y == opcion1SSucursales);
        showItemCf("Restaurar Backup ", 53, 5, y == opcion2SSucursales);
        showItemCf("Regresar al Menu ", 53, 8, y == opcion3SSucursales);

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
             if (y > 3) {
	    		y = 3;
	   		}
             break;
        case 1: // ENTER
              switch (y) {
	    		case opcion1SSucursales:
                    rlutil::cls();
					sucursales.backupArchivo();
					system("pause");
                    break;
			    case opcion2SSucursales:
                    rlutil::cls();
					sucursales.restaurarBackup();
					system("pause");
					break;
				case opcion3SSucursales:
                    rlutil::cls();
					Menu();
					break;
			  }
		}
    } while (opc != 0);
}

enum OpionesSVendedores
{
	opcion1SVendedores = 1,
	opcion2SVendedores = 2,
	opcion3SVendedores = 3
};

void Configuracion::subMenuVendedores() {
    VendedorManager vendedores;

    int opc = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemCf("--- ARCHIVO VENDEDORES ---", 50, 2, false);
        showItemCf("Realizar Backup ", 53, 4, y == opcion1SVendedores);
        showItemCf("Restaurar Backup ", 53, 5, y == opcion2SVendedores);
        showItemCf("Regresar al Menu ", 53, 8, y == opcion3SVendedores);


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
            if (y > 3) {
                y = 3;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case opcion1SVendedores:
                rlutil::cls();
                vendedores.realizarBackupVendedores();
                system("pause");
                break;
            case opcion2SVendedores:
                rlutil::cls();
                vendedores.restaurarBackupVendedores();
                system("pause");
                break;
            case opcion3SVendedores:
                rlutil::cls();
                Menu();
                break;
            }
        }
    } while (opc != 0);
}

enum OpionesSClientes
{
	opcion1SClientes = 1,
	opcion2SClientes = 2,
	opcion3SClientes = 3
};

void Configuracion::subMenuClientes() {
    ClienteManager clientes;

    int opc = 1;
    int y = 0;
    rlutil::hidecursor();


    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemCf("--- ARCHIVO CLIENTES ---", 50, 2, false);
        showItemCf("Realizar Backup ", 53, 4, y == opcion1SClientes);
        showItemCf("Restaurar Backup ", 53, 5, y == opcion2SClientes);
        showItemCf("Regresar al Menu ", 53, 8, y == opcion3SClientes);

        
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
                if (y > 3) {
					y = 3;
				}
                break;
			case 1: // ENTER
				switch (y) {
				case opcion1SClientes:
                    rlutil::cls();
					clientes.backupArchivo();
					system("pause");
					break;
				case opcion2SClientes:
                    rlutil::cls();
					clientes.restaurarBackup();
					system("pause");
					break;
				case opcion3SClientes:
                    rlutil::cls();
					Menu();
					break;
				}
			}
        } while (opc != 0);
    }