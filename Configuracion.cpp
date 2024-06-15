# include<iostream>
using namespace std;
#include"Configuracion.h"

void Configuracion::Menu() {
    int opc;
    cout << "------ Configuracion ------" << endl;
    cout << "---------------------------" << endl;
    cout << "1) SubMenu Vehiculos " << endl;
    cout << "2) SubMenu Ventas " << endl;
    cout << "3) SubMenu Sucursales " << endl;
    cout << "4) SubMenu Vendedores " << endl;
    cout << "5) SubMenu Clientes " << endl << endl;
    cout << "----------------------------" << endl;
    cout << "0) Regresar al Menu Principal " << endl << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1:system("cls");
            subMenuVehiculos();
            return;
        case 2:system("cls");
            subMenuVentas();
            return;
        case 3:system("cls");
            subMenuSucursales();
            return;
        case 4:system("cls");
            subMenuVendedores();
            return;
        case 5:system("cls");
            subMenuClientes();
            return;
        case 0:
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc!=0);
}

void realizarBackupVehiculos() {
    int opc;
    cout << endl;
    cout << "- Confirma el Backup del Archivo Vehiculos?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1:
            cout << endl;
            system("copy Vehiculos.dat Vehiculos.bkp");
            cout << "* Backup Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void restaurarBackupVehiculos() {
    int opc;
    cout << endl;
    cout << "- Confirma la Restauracion del Archivo Vehiculos?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1:
            cout << endl;
            system("copy Vehiculos.bkp Vehiculos.dat");
            cout << "* Restauracion Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void Configuracion::subMenuVehiculos() { 
    int opc;
    cout << "--- Archivo Vehiculos ---" << endl;
    cout << "1) Realizar Backup " << endl;
    cout << "2) Restaurar Backup " << endl;
    cout << "0) Regresar al Menu " << endl;
    cout << "Ingrese una Opcion: ";
    do {
        cin >> opc;
        switch (opc)
        {
        case 1: 
            realizarBackupVehiculos();
            system("cls");
            return;
        case 2:
            restaurarBackupVehiculos();
            system("cls");
            return;
        case 0:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 0);
}

void realizarBackupVentas() {
    int opc;
    cout << "- Desea Relizar Backup del Archivo Ventas?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Ventas.dat Ventas.bkp");
            cout << "* Backup Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void restaurarBackupVentas() {
    int opc;
    cout << "- Desea Restaurar el Archivo Ventas?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Ventas.bkp Ventas.dat");
            cout << "* Restauracion Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void Configuracion::subMenuVentas() {
    int opc;
    cout << "--- Archivo Ventas ---" << endl;
    cout << "1) Realizar Backup " << endl;
    cout << "2) Restaurar Backup " << endl;
    cout << "0) Regresar al Menu " << endl;
    cout << "Ingrese una Opcion: ";
    do {
        cin >> opc;
        switch (opc)
        {
        case 1: realizarBackupVentas();
            system("cls");
            return;
        case 2: restaurarBackupVentas();
            system("cls");
            return;
        case 0:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 0);
}

void realizarBackupSucursales() {
    int opc;
    cout << "- Desea Relizar Backup del Archivo Sucursales?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Sucursales.dat Sucursales.bkp");
            cout << "* Backup Realizado con Exito! *" << endl;
            break;
        case 2:
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void restaurarBackupSucursales() {
    int opc;
    cout << "- Desea Restaurar el Archivo de Sucursales?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Sucursales.bkp Sucursales.dat");
            cout << "* Restauracion Realizado con Exito! *" << endl;
            break;
        case 2:
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void Configuracion::subMenuSucursales() {
    int opc;
    cout << "--- Archivo Sucursales ---" << endl;
    cout << "1) Realizar Backup " << endl;
    cout << "2) Restaurar Backup " << endl;
    cout << "0) Regresar al Menu " << endl;
    cout << "Ingrese una Opcion: ";
    do {
        cin >> opc;
        switch (opc)
        {
        case 1: realizarBackupSucursales();
            system("cls");
            return;
        case 2: restaurarBackupSucursales();
            system("cls");
            return;
        case 0:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 0);
}

void realizarBackupVendedores() {
    int opc;
    cout << "- Desea Relizar Backup del Archivo Vendedores?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Vendedores.dat Vendedores.bkp");
            cout << "* Backup Realizado con Exito! *" << endl;
            break;
        case 2:
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}


void restaurarBackupVendedores() {
    int opc;
    cout << "- Desea Restaurar el Archivo de Vendedores?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Vendedores.bkp Vendedores.dat");
            cout << "* Restauracion Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void Configuracion::subMenuVendedores() {
    int opc;
    cout << "--- Archivo Vendedores ---" << endl;
    cout << "1) Realizar Backup " << endl;
    cout << "2) Restaurar Backup " << endl;
    cout << "0) Regresar al Menu " << endl;
    cout << "Ingrese una Opcion: ";
    do {
        cin >> opc;
        switch (opc)
        {
        case 1: realizarBackupVendedores();
            system("cls");
            return;
        case 2: restaurarBackupVendedores();
            system("cls");
            return;
        case 0:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 0);
}

void restaurarBackupClientes() {
    int opc;
    cout << "- Desea Restaurar el Archivo de Clientes?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Clientes.bkp Clientes.dat");
            cout << "* Restauracion Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void realizarBackupClientes() {
    int opc;
    cout << "- Desea Relizar Backup del Archivo Clientes?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "Selecione una Opcion: ";
    do {
        cin >> opc;
        switch (opc) {
        case 1: system("copy Clientes.dat Clientes.bkp");
            cout << "* Backup Realizado con Exito! *" << endl;
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 2);
}

void Configuracion::subMenuClientes() {
    int opc;
    cout << "--- Archivo Clientes ---" << endl;
    cout << "1) Realizar Backup " << endl;
    cout << "2) Restaurar Backup " << endl;
    cout << "0) Regresar al Menu " << endl;
    cout << "Ingrese una Opcion: ";
    do {
        cin >> opc;
        switch (opc)
        {
        case 1: realizarBackupClientes();
            system("cls");
            return;
        case 2: restaurarBackupClientes();
            system("cls");
            return;
        case 0:
            system("cls");
            return;
        default:
            cout << "* Opcion Incorrecta *" << endl;
            cout << "- Seleccione una Opcion Correcta: ";
        }
    } while (opc != 0);
}