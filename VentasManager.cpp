#define _CRT_SECURE_NO_WARNINGS 
#include "FuncionesGenerales.h"
#include "VentasManager.h"
#include "ClienteManager.h"
#include "SucursalManager.h"
#include "VendedorManager.h"
#include "VehiculosManager.h"
#include "Sistema.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "rlutil.h"
using namespace std;


VentasManager::VentasManager() : _archivo("Ventas.dat")
{

}

void showItemVentas(const char* text, int posx, int posy, bool selected)
{

    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::LIGHTRED);
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

void VentasManager::Menu()
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

        showItemVentas("--- MENU VENTAS ---", 50, 2, false);
        showItemVentas("Cargar ", 53, 4, y == Opcion1);
        showItemVentas("Listar ", 53, 5, y == Opcion2);
        showItemVentas("Buscar ", 53, 6, y == Opcion3);
        showItemVentas("Editar ", 53, 7, y == Opcion4);
        showItemVentas("Borrar ", 53, 8, y == Opcion5);
        showItemVentas("Crear Backup ", 53, 9, y == Opcion6);
        showItemVentas("Restaurar Backup ", 53, 10, y == Opcion7);
        showItemVentas("Regresar al Menu Principal ", 53, 13, y == Opcion8);

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
                agregarVenta();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                menuListados();
                break;
            case Opcion3:
                rlutil::cls();
                buscadorDeVentas();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                editarVenta();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                borrarVenta();
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
    } while (op != 0);
}

Venta VentasManager::crearVenta()
{
    int id = _archivo.leerUltimoId() + 1;
    int nroLegajo, idSucursal, idVehiculo;
    long long dni;
    float gastos, total = 0;
    Fecha f(1,1,1990);
    Venta reg;

    std::cout << "Venta: #" << id << endl;
    reg.setIdVenta(id);
    
    std::cout << "* Ingrese fecha de Venta: " << endl;
    f.Cargar();
    reg.setFechaVenta(f);
    std::cout << endl;
    
    dni = validarLong("* Ingrese DNI del Cliente: ");
    std::cout << endl;
    
    //Validacion del cliente
    int posCliente = validarCliente(dni);
    if (posCliente >= 0) {
        reg.setDniCliente(dni);
    }
    else {
        int opc;
        opc = validarInt("El cliente no existe. Desea agregarlo? (1)Si - (2)No: ");
        std::cout << endl;
        switch (opc) {
        case 1:
            crearNuevoCliente(dni);
            reg.setDniCliente(dni);
            posCliente = validarCliente(dni); 
            system("cls");
            break;

        case 2:
            std::cout << "* No se pudo finalizar la creacion de la venta *" << endl;
            exit(1);
        }
    }
    mostrarClienteAsociado(posCliente);
    std::cout << endl;
    
    idSucursal = validarInt("* Ingrese ID de Sucursal: ");
    std::cout << endl;
    
    //Validacion Sucursal
    int posSucursal = validarSucursal(idSucursal);
    if (posSucursal >= 0) {
        reg.setIdSucursal(idSucursal);
    }
    else {
        do {
            std::cout << "* La sucursal no existe. Intente nuevamente *" << endl;
            idSucursal = validarInt("* Ingrese ID de Sucursal: ");
            posSucursal = validarSucursal(idSucursal); 
        } while (posSucursal < 0);
        system("cls");
        reg.setIdSucursal(idSucursal);
        
    }
    mostrarSucursalAsociada(posSucursal);
    std::cout << endl;

    
    
    nroLegajo = validarInt("* Ingrese Legajo del Vendedor: ");
    std::cout << endl;

    //Validacion Vendedor
    int posVendedor = validarVendedor(nroLegajo);
    if (posVendedor >= 0) {
        reg.setNroLegajo(nroLegajo);
    }
    else {
        do {
            std::cout << "* El vendedor no existe. Intente nuevamente *" << endl;
            nroLegajo = validarInt("* Ingrese Legajo del Vendedor: ");
            posVendedor = validarVendedor(nroLegajo);
        } while (posVendedor < 0);
        system("cls");
        reg.setNroLegajo(nroLegajo); 

    }
    mostrarVendedorAsociado(posVendedor);
    std::cout << endl;
    
    idVehiculo = validarInt("* Ingrese ID del Vehiculo adquirido: ");
    std::cout << endl;

    //Validacion Vehiculo
    bool vehiculoDisponible = validarVehiculo(idVehiculo);
    
    if (vehiculoDisponible == true) { 
        reg.setIdVehiculo(idVehiculo);
    }
    mostrarVehiculoAsociado(idVehiculo);
    std::cout << endl;
    
    gastos = pedirNumeroFloat("* Ingrese Gastos Administrativos: $");
    reg.setGastosAdm(gastos); 

    total = calcularPrecioTotal(reg.getGastosAdm(), obtenerPrecioVehiculo(idVehiculo));
    reg.setTotalVentas(total);
    std::cout << endl;
    std::cout << "* Total Venta: $" << formatearNumero(reg.getTotalVenta()) << endl;
    std::cout << endl;
    reg.setEliminado(false);

    return reg;
}

void VentasManager::mostrarVenta(Venta reg)
{
    std::cout << left;
    std::cout << setw(0) << "Venta: #" << reg.getIdVenta() << "         " << "Fecha de Venta: " << reg.getFechaVenta().toString();
    std::cout << endl << endl;
    std::cout << "Cliente: " << mostrarNombreCliente(reg.getDniCliente()) << " - DNI: " << reg.getDniCliente() << endl;
    std::cout << "Sucursal: " << mostrarNombreSucursal(reg.getIdSucursal()) << endl;
    std::cout << "Vendedor: " << mostrarNombreVendedor(reg.getNroLegajo()) << endl;
    std::cout << "Vehiculo comprado: " << mostrarNombreVehiculo(reg.getIdVehiculo()) << endl;
    string gastosFormateado = formatearNumero(reg.getGastosAdm());
    std::cout << "Gastos Administrativos: $" << gastosFormateado << endl;
    string totalFormateado = formatearNumero(reg.getTotalVenta());
    std::cout << "Total Venta: $" << totalFormateado << endl;
}

void VentasManager::encabezadoListadoVentas() 
{
    std::cout << left;
    std::cout << setw(55) << " " << "* Ventas *" << endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    std::cout << setw(5) << "#ID";
    std::cout << setw(14) << "Fecha Venta ";
    std::cout << setw(19) << "Cliente ";
    std::cout << setw(25) << "Sucursal ";
    std::cout << setw(20) << "Vendedor ";
    std::cout << setw(26) << "Vehiculo comprado ";
    std::cout << setw(19) << "Gastos Adm ";
    std::cout << setw(16) << "Total Venta ";
    std::cout << endl;

}

void VentasManager::mostrarVentaEnLinea(Venta reg)
{
    std::cout << left;
    std::cout << endl;
    std::cout << setw(5) << reg.getIdVenta();
    std::cout << setw(14) << reg.getFechaVenta().toString();
    std::cout << setw(19) << mostrarNombreCliente(reg.getDniCliente());
    std::cout << setw(25) << mostrarNombreSucursal(reg.getIdSucursal());
    std::cout << setw(20) << mostrarNombreVendedor(reg.getNroLegajo());
    std::cout << setw(26) << mostrarNombreVehiculo(reg.getIdVehiculo());
    string gastosFormateado = formatearNumero(reg.getGastosAdm());
    std::cout << setw(2) << "$ " << setw(16) << gastosFormateado;
    string totalFormateado = formatearNumero(reg.getTotalVenta());
    std::cout << setw(2) << "$ " << setw(16) << totalFormateado;
    
    
}

void VentasManager::agregarVenta()
{
    if (_archivo.guardarVenta(crearVenta())) {
        std::cout << "* La venta se guardo correctamente *" << endl;
    }
    else {
        std::cout << "* No se pudo guardar la venta *" << endl;
    }
}

enum OpcionesLVentas {
    Opcion1LVentas = 0,
    Opcion2LVentas = 1,
    Opcion3LVentas = 2,
    salir = 3,
};

void VentasManager::menuListados()
{
    int op = 1;
    int y = 0;
    rlutil::hidecursor();
    
    do {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemVentas("- Como desea ordenar el listado de Ventas? -", 50, 2, false);
        showItemVentas("Por ID", 53, 4, y == Opcion1LVentas);
        showItemVentas("Por Fecha de Venta", 53, 5, y == Opcion2LVentas);
        showItemVentas("Regresar al Menu Ventas", 53, 8, y == salir);


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
            case Opcion1LVentas:
                rlutil::cls();
                listarVentas();
                system("pause");
                break;
            case Opcion2LVentas:
                rlutil::cls();
                listarVentasXFecha();
                system("pause");
                break;
            case salir:
                rlutil::cls();
                Menu();
                break;
            }
        }
    } while (op != 0);
}

void VentasManager::listarVentas()
{
    int i, cantidad = _archivo.contarVentas();
    Venta reg;

    if (cantidad == 0) {
        std::cout << "* No hay Ventas para mostrar *" << endl;
    }
    else {
        encabezadoListadoVentas();

        for (i=0; i < cantidad; i++) {
        
            reg = _archivo.leerVenta(i);
            if (reg.getEliminado() == false) {
                mostrarVentaEnLinea(reg); 
            }
        
        }
        std::cout << endl;

    }
    std::cout << endl;
    
}

void VentasManager::ordenar(vector<Venta>& vec, int cantidad) {
    Venta aux;

    for (int i = 0; i < cantidad; i++) {

        for (int j = i; j < cantidad; j++) {

            if (vec[i].getFechaVenta() > vec[j].getFechaVenta()) {
                 
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

            }
        }
    }
}

void VentasManager::listarVentasXFecha()
{
    int i, cantidad = _archivo.contarVentas();
    Venta reg;
    vector <Venta> vec;

    if (cantidad == 0) {
        std::cout << "* No hay Ventas para mostrar *" << endl;
    }
    else {
        encabezadoListadoVentas();
        for (i = 0; i < cantidad; i++) {
            reg = _archivo.leerVenta(i);
            vec.push_back(reg);
        }

        ordenar(vec, cantidad); 
        for (i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                mostrarVentaEnLinea(vec[i]);
            }
        }
        std::cout << endl;

    }
}

int VentasManager::buscarVenta(int idVenta)
{
    Venta reg;
    FILE* p;
    int pos = 0;
    p = fopen(_archivo.getNombreArchivo().c_str(), "rb");
    if (p == nullptr) {
        return -2; //no se abrio el archivo
    }
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        if (reg.getIdVenta() == idVenta) {
            fclose(p); //cierro el archivo porque ya encontre la empresa
            return pos;
        }
        pos++;
    }
    fclose(p);

    return -1; //se recorrio el archivo y no existe el codigo
}

void VentasManager::editarVenta()
{
    int id, opcion;

    id = validarInt("Ingrese ID de Venta a editar: ");
    cout << endl;

    int pos = buscarVenta(id);

    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);

        if (reg.getEliminado() == false) {
            cout << endl << "Venta a Editar: " << endl;
            mostrarVenta(reg);

            cout << endl;
            cout << "¿Que dato desea editar?" << endl;
            cout << "1 - Fecha de Venta" << endl;
            cout << "2 - Gastos Administrativos" << endl << endl;
            cout << "0 - Volver al menu anterior" << endl << endl;
            opcion = validarInt("Opcion: ");
            cout << endl;

            switch (opcion) {
            case 1:
            {
                Fecha f;
                f.Cargar();
                reg.setFechaVenta(f);
                break;
            }
            case 2:
            {
                float gastos;
                gastos = validarFloat("Ingrese nuevo valor de Gastos Administrativos: $");
                reg.setGastosAdm(gastos);
                break;

            case 0:
                break;

            default:
                cout << "* Opcion invalida *";
                break;
            }
            }
            cout << endl;
            bool result = _archivo.sobreescribirVenta(reg, pos);

            if (result == true && opcion != 0) {
                cout << "* Se edito correctamente la venta *" << endl;
            }
            else {
                cout << "* No se edito la venta *" << endl;
            }


        }
        else {
            cout << "* La venta buscada se encuentra eliminada *" << endl;
        }

    }
    else {
        cout << "* Error al buscar la venta. Codigo: (";
        if (pos == -1) {
            cout << pos << ") La venta no existe *" << endl;
        }
        if (pos == -2) {
            cout << pos << ") No se pudo abrir el archivo *" << endl;

        }
    }
}

void VentasManager::backupArchivo()
{
    string origen = "Ventas.dat";
    string copia = "Ventas.bkp";

    string comando = "copy " + origen + " " + copia;

    int resultado = system(comando.c_str());
    
    if (resultado == 0) {
        std::cout << endl << "* Backup realizado con exito *" << endl;
    }
    else {
        std::cout  << "* Hubo un error al copiar el archivo *" << endl;
    }
   
}

void VentasManager::restaurarBackup()
{
    string origen = "Ventas.bkp";
    string copia = "Ventas.dat";

    string comando = "copy " + origen + " " + copia;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        std::cout << endl << "* Backup restaurado con exito *" << endl;
    }
    else {
        std::cout << "* Hubo un error al restaurar el archivo *" << endl;
    }

}



void VentasManager::borrarVenta()
{
    int id;
    int opc;

    id = validarInt("Ingrese ID de Venta a borrar: ");
    std::cout << endl;

    int pos = buscarVenta(id); 

    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);

        std::cout << endl << "Venta a Borrar: " << endl;
        mostrarVenta(reg);
        std::cout << endl;

        opc =  validarInt("Confirma que desea borrar esta venta? (1)Si - (2)No: ");

        if (opc == 1) {
            reg.setEliminado(true);
            bool result = _archivo.sobreescribirVenta(reg, pos);
            if (result) {
                std::cout << "* La venta se ha borrado correctamente *" << endl;
            }
            else {
                std::cout << "* No se pudo eliminar la venta *" << endl;
            }
        }
        else {
            std::cout << endl << "* Se cancelo el borrado de la venta *" << endl;
        }

    }
    else {
        std::cout << "* La venta buscada no existe *" << endl;
    }

}

void VentasManager::restaurarVentaBorrada() {
    int cantReg = _archivo.contarVentas();
    if (cantReg == -1) {
        std::cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int id, pos, opc;
        id = validarInt("Ingrese el ID de la Venta: ");
        system("cls");
        
        pos = buscarVenta(id);
        if (pos == -1) {
            std::cout << endl << "* No Existe ese ID de Venta *" << endl << endl;
        }
        if (pos >= 0) {
            Venta reg;
            reg = _archivo.leerVenta(pos);
            if (reg.getEliminado() == true) {
                std::cout << "Desea Restaurar el Registro? (1)Si (2)NO " << endl;
                opc = validarInt("Seleccione una Opcion: ");
                system("cls");

                switch (opc) {
                case 1: {
                    reg.setEliminado(false);
                    std::cout << endl;
                    mostrarVenta(reg);
                    bool restaurar = _archivo.sobreescribirVenta(reg, pos);
                    if (restaurar == true) {
                        std::cout << endl << setw(25) << " " << "* Registro Restaurado con Exito *" << endl << endl;
                    }
                    else {
                        std::cout << endl << "* No se Pudo Restaurar el Registro *" << endl;
                    }
                        system("pause");
                }
                case 2:
                    break;
                default:std::cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
            }
            else {
                std::cout << endl << "* El Registro Se Restauro con Exito *" << endl << endl;
                system("pause");
            }
        }
    }
    std::cout << endl;
}

int VentasManager::validarCliente(long long dni)
{
    ClienteManager cm; 
    int resultado = cm.buscarCliente(dni);
    if (resultado >= 0) {
        return resultado;
    }
    else {
        return -1;
    }
}

void VentasManager::crearNuevoCliente(long long dni)
{
    ClienteManager cm;
    ClienteArchivo ca;
    
    ca.guardarCliente(cm.crearCliente(dni));

    
}

void VentasManager::mostrarClienteAsociado(int pos)
{
    ClienteManager cm;
    ClienteArchivo ca; 
    Cliente aux;

    aux = ca.leerCliente(pos); 
    std::cout << "Cliente que realiza la compra: " << endl;
    cm.mostrarCliente(aux);
    std::cout << endl;

}

std::string VentasManager::mostrarNombreCliente(long long dni)
{
    ClienteManager cm;
    ClienteArchivo ca;
    

    int pos = cm.buscarCliente(dni);

    Cliente aux = ca.leerCliente(pos);
    
    return aux.getApellidoNombre();


}

int VentasManager::validarSucursal(int id)
{
    SucursalArchivo sa;
    int resultado = sa.buscarPosicion(id);
    if (resultado >= 0) {
        return resultado;
    }
    else {
        return -1;
    }
}

void VentasManager::mostrarSucursalAsociada(int pos)
{
    SucursalArchivo sa;
    Sucursal aux;

    aux = sa.leerRegistro(pos); 
    std::cout << "Sucursal asignada: " << endl;
    std::cout << "Id Sucursal: #" << aux.getIdSucursal() << endl;
    std::cout << "Nombre: " << aux.getNombre() << endl;
    std::cout << "Dirección: " << aux.getDireccion().toString();
    std::cout << endl;
    std::cout << "Telefono: " << aux.getTelefono() << endl << endl;
}

std::string VentasManager::mostrarNombreSucursal(int id)
{
    SucursalManager sm;
    SucursalArchivo sa; 
    

    int pos = sa.buscarPosicion(id);

    Sucursal aux = sa.leerRegistro(pos); 

    string valor = to_string(aux.getIdSucursal()) + " - " + aux.getNombre();
    
    return valor;
}

int VentasManager::validarVendedor(int nroLegajo)
{
    VendedorArchivo va;

    int resultado = va.BuscarId(nroLegajo);
    if (resultado >= 0) {
        return resultado;
    }
    else {
        return -1;
    }
}

void VentasManager::mostrarVendedorAsociado(int pos)
{
    VendedorManager vm; 
    VendedorArchivo va; 
    Vendedor aux; 

    aux = va.leerRegistro(pos);
    std::cout << "Vendedor asignado: " << endl;
    aux.MostrarPersona();
    std::cout << endl;
    std::cout << "NRO LEGAJO: " << aux.getNroLegajo() << endl;
    std::cout << "FECHA DE INGRESO: " << aux.getFechaIngreso().toString() << endl;
    std::cout << "ANTIGUEDAD: " << aux.getAntiguedad();
    std::cout << endl;
}

std::string VentasManager::mostrarNombreVendedor(int nrolegajo)
{
    VendedorArchivo va;
    int pos = va.BuscarId(nrolegajo);

    Vendedor aux = va.leerRegistro(pos);

    string valor = aux.getApellido() + ", " + aux.getNombre();

    return valor;
}

bool VentasManager::validarVehiculo(int& id)
{
    VehiculosArchivo va;
    bool resultado = false;

    int pos = va.buscarRegistro(id);
    
    if (pos >= 0) {
        Vehiculo aux = va.leerRegistro(pos);
        if (aux.getStock() > 0) {
            aux.setStock(aux.getStock() - 1);
            va.modificarRegistro(aux, pos);
            return true;

        }
        else {
            do {
                std::cout << "* El vehiculo no tiene stock y no puede ser vendido. *" << endl;
                id = validarInt("* Ingrese un nuevo id de vehiculo: ");
                resultado = validarVehiculo(id);

            } while (resultado == false);
            system("cls");
        }
        

    }
    else {
        do {
            std::cout << "* El vehiculo ingresado no existe *" << endl;
            id = validarInt("* Ingrese un nuevo id de vehiculo: ");
            resultado = validarVehiculo(id);
        } while (resultado == false);
        
    }
    
}

void VentasManager::mostrarVehiculoAsociado(int id)
{
    VehiculosManager vm;
    VehiculosArchivo va;
    Vehiculo aux;
    int pos = va.buscarRegistro(id);

    aux = va.leerRegistro(pos); 
    std::cout << "Vehiculo vendido: " << endl;
    std::cout << "ID Vehiculo: " << aux.getIdVehiculo() << endl;
    std::cout << "Marca y Modelo: " << aux.getMarca() << " " << aux.getModelo() << endl;
    std::cout << "Version: " << aux.getVersion() << endl;
    std::cout << "Color: " << aux.getColor() << endl;
    std::cout << "Año de fabricación: " << aux.getAnioFabricacion() << endl;
    //cout << "Stock actualizado: " << aux.getStock() << endl;
    std::cout << "Precio unidad: $" << formatearNumero(aux.getPrecioUnidad());
    std::cout << endl;
}

std::string VentasManager::mostrarNombreVehiculo(int id)
{
    VehiculosArchivo va;
    VehiculosManager vm;

    int pos = va.buscarRegistro(id);

    Vehiculo aux = va.leerRegistro(pos);

    string valor = to_string(id)+ " - " + aux.getMarca() + " " + aux.getModelo();

    return valor;
}

float VentasManager::obtenerPrecioVehiculo(int id)
{
    VehiculosArchivo va;
    Vehiculo aux;
    int pos = va.buscarRegistro(id);
    aux = va.leerRegistro(pos); 

    return aux.getPrecioUnidad();
}

float VentasManager::calcularPrecioTotal(float gastos, float precio)
{
    return gastos + precio;
}

std::string VentasManager::formatearNumero(double numero)
{
    ostringstream oss{};
    oss << fixed << setprecision(2) << numero;
    string numeroStr = oss.str();
    size_t punto = numeroStr.find('.');
    string parteEntera = numeroStr.substr(0, punto);
    string parteDecimal = numeroStr.substr(punto);
    string parteEnteraFormateada;
    int longitud = parteEntera.length();
    for (int i = 0; i < longitud; ++i) {
        parteEnteraFormateada += parteEntera[i];
        if ((longitud - i - 1) % 3 == 0 && (i != longitud - 1)) {
            parteEnteraFormateada += ',';
        }
    }
    return parteEnteraFormateada + parteDecimal;
}

enum OpcionesBVentas {
    Opcion1BVentas = 0,
    Opcion2BVentas = 1,
    Opcion3BVentas = 2,
};

void VentasManager::buscadorDeVentas()
{
    int cantReg = _archivo.contarVentas();
    if (cantReg == -1) {
        std::cout << endl << "* Error de Archivo *" << endl;
    }

 

    else {

        int op = 1;
        int y = 0;
        rlutil::hidecursor();
        
        do {
            rlutil::cls();

            rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
            rlutil::setColor(rlutil::COLOR::WHITE);
            rlutil::hidecursor();

            showItemVentas("- Buscar Venta -", 50, 2, false);
            showItemVentas("Por ID ", 53, 4, y == Opcion1BVentas);
            showItemVentas("Por Fecha de Venta ", 53, 5, y == Opcion2BVentas);
            showItemVentas("Regresar al Menu Ventas ", 53, 8, y == Opcion3BVentas);


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
                case Opcion1BVentas:
                    rlutil::cls();
                    buscarVentaPorID();
                    system("pause");
                    break;
                case Opcion2BVentas:
                    rlutil::cls();
                    buscarVentaPorFecha();
                    system("pause");
                    break;
                case Opcion3BVentas:
                    Menu();
                    break;
                }
            }
        } while (op != 0);
    }
}

void VentasManager::buscarVentaPorID()
{
    int id, pos; 
    id = validarInt("Ingrese el ID a buscar: ");
    std::cout << endl;
    pos = buscarVenta(id);
    if (pos == -1) {
        std::cout  << endl << "* No se Encontraron Registros *" << endl;
    }
    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);
        if (reg.getEliminado() == false) {
            mostrarVenta(reg);
            std::cout << endl;
        }
        else {
            std::cout << "* El Registro se Encuentra Eliminado *" << endl;
        }
    }
    std::cout << endl;
}

void VentasManager::buscarVentaPorFecha()
{
    Fecha f;
    Venta reg;
    int cantReg, contador = 0;

    std::cout << "Ingrese fecha a buscar:" << endl;
    f.Cargar();
    std::cout << endl;

    cantReg = _archivo.contarVentas();
    for (int i = 0; i < cantReg; i++) {
        reg = _archivo.leerVenta(i);
        if (reg.getEliminado() == false && reg.getFechaVenta().getAnio() == f.getAnio() && reg.getFechaVenta().getMes() == f.getMes() && reg.getFechaVenta().getDia() == f.getDia()) {
            if (contador == 0) {
                encabezadoListadoVentas();
                mostrarVentaEnLinea(reg);
                contador++;
            }
            else {
                mostrarVentaEnLinea(reg);
                contador++;

            }
        }
    }
    if (contador == 0) {
        std::cout << "* No hay ventas para la fecha buscada * " << endl;
    }

}

 