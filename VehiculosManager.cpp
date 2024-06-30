#include "VehiculosManager.h"
#include "FuncionesGenerales.h"
#include "Fecha.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Sistema.h"
#include "rlutil.h"


using namespace std;

VehiculosManager::VehiculosManager() : _vehiculosArchivo("Vehiculos.dat")
{

}

void VehiculosManager::tituloVehiculo() {
    std::cout << left;
    std::cout << setw(26) << " " << "- Datos del Vehiculo -" << endl;
    std::cout << "-----------------------------------------------------------------------------------" << endl;
    std::cout << setw(4) << "ID ";
    std::cout << setw(10) << "Marca ";
    std::cout << setw(14) << "Modelo ";
    std::cout << setw(12) << "Version ";
    std::cout << setw(10) << "Color ";
    std::cout << setw(8) << "Anio ";
    std::cout << setw(8) << "Stock ";
    std::cout << setw(20) << "Precio por Unidad ";
    std::cout << endl;

}

void showItemV(const char* text, int posx, int posy, bool selected)
{

    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::DARKGREY);
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
    Opcion9 = 8
};

void VehiculosManager::Menu() {
    Sistema programa;
    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {

        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemV("--- MENU VEHICULOS ---", 50, 2, false);
        showItemV("Cargar ", 53, 4, y == Opcion1);
        showItemV("Listar ", 53, 5, y == Opcion2);
        showItemV("Buscar ", 53, 6, y == Opcion3);
        showItemV("Editar ", 53, 7, y == Opcion4);
        showItemV("Eliminar registro ", 53, 8, y == Opcion5);
        showItemV("Reestablecer registro ", 53, 9, y == Opcion6);
        showItemV("Realizar Backup ", 53, 10, y == Opcion7);
        showItemV("Restaurar Backup ", 53, 11, y == Opcion8);
        showItemV("Regresar al Menu Principal ", 53, 14, y == Opcion9);


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
            if (y > 9) {
                y = 9;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case Opcion1:
                rlutil::cls();
                agregarVehiculo();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                listarVehiculos();
                system("pause");
                break;
            case Opcion3:
                rlutil::cls();
                buscarVehiculo();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                editarVehiculo();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                eliminarVehiculo();
                system("pause");
                break;
            case Opcion6:
                rlutil::cls();
                resturarVehiculo();
                system("pause");
                break;
            case Opcion7:
                rlutil::cls();
                realizarBackup();
                system("pause");
                break;
            case Opcion8:
                rlutil::cls();
                restaurarBackup();
                system("pause");
                break;
            case Opcion9:
                programa.Menu();
                break;
            }
        }
    } while (op != 0);
}

void VehiculosManager::agregarVehiculo() {
    if (_vehiculosArchivo.guardarRegistro(cargarVehiculo())) {
        std::cout << "* Registro Agregado! *" << endl;
    }
    else {
        std::cout << "* No se Pudo Agregar el Registro *" << endl;
    }
}

Vehiculo VehiculosManager::cargarVehiculo() {
    string marca, modelo, version, color;
    int id, anio, stock;
    float precio;
    Fecha año;
    VehiculosArchivo archivo;
    int cantReg = archivo.contarRegistros();
    if (cantReg == -1) {
        cantReg = 0;
        std::cout << "* Archivo Nuevo *" << endl;
    }
    Vehiculo reg;
    id = ++cantReg;
    std::cout << "- Ingrese Los Datos del Vehiculo -" << endl;
    std::cout << "- ID: ";
    std::cout << id << endl;
    reg.setIdVehiculo(id);
    std::cout << "- Marca: ";
    getline(cin, marca);
    reg.setMarca(marca);
    std::cout << "- Modelo: ";
    getline(cin, modelo);
    reg.setModelo(modelo);
    std::cout << "- Version: ";
    getline(cin, version);
    reg.setVersion(version);
    std::cout << "- Color: ";
    getline(cin, color);
    reg.setColor(color);
    while (true) {
        std::cout << "- Ingrese el Año de Fabricacion: ";
        anio = validarInt();
        if (anio > año.obtenerAnioActual()) {
            std::cout << "* El Año de Fabricacion No puede ser Mayor al Año Actual *" << endl;
        }
        if (anio < 2000) {
            std::cout << "* El Año de Fabricacion No puede ser Menor a 2000 *" << endl;
        }
        if (anio <= año.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }
    reg.setAnioFabricacion(anio);
    std::cout << "- Stock: ";
    stock = validarInt();
    reg.setStock(stock);
    std::cout << "- Precio por Unidad: $ ";
    precio = validarInt();
    reg.setPrecioUnidad(precio);
    reg.setEstado(true);
    return reg;
}

void VehiculosManager::mostrarVehiculo(Vehiculo reg) {
    if (reg.getEstado() == true) {
        std::cout << left;
        std::cout << setw(4) << reg.getIdVehiculo();
        std::cout << setw(10) << reg.getMarca();
        std::cout << setw(14) << reg.getModelo();
        std::cout << setw(12) << reg.getVersion();
        std::cout << setw(10) << reg.getColor();
        std::cout << setw(8) << reg.getAnioFabricacion();
        std::cout << setw(8) << reg.getStock();
        string numeroFormateado = formatearNumero(reg.getPrecioUnidad());
        std::cout << setw(2) << "$ " << setw(18) << numeroFormateado;
        std::cout << endl;
    }
    else {
        std::cout << reg.getIdVehiculo() << "   Este Registro se Encuentra Eliminado! " << endl;
    }
}

enum OpcionesLV {
    Opcion1LV = 0,
    Opcion2LV = 1,
    Opcion3LV = 2,
};

void VehiculosManager::listarVehiculos() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        std::cout << endl << "* Error de Archivo *" << endl << endl;
        system("pause");
    }
    if (cantReg == 0) {
        std::cout << endl << "* No Hay Registros para Mostrar *" << endl << endl;
        system("pause");
    }
    if (cantReg > 0) {

        int op = 1;
        int y = 0;
        rlutil::hidecursor();

        do {
            rlutil::cls();

            showItemV("- Como desea Visualizar los Registros? -", 50, 2, false);
            showItemV("Por ID ", 53, 4, y == Opcion1LV);
            showItemV("Por Precio ", 53, 5, y == Opcion2LV);
            showItemV("Regresar ", 53, 8, y == Opcion3LV);


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
                case Opcion1LV:
                    rlutil::cls();
                    listarPorId();
                    break;
                case Opcion2LV:
                    rlutil::cls();
                    listarPorPrecio();
                    break;
                case Opcion3LV:
                    Menu();
                    break;
                }
            } 

        } while (op != 0);

    }
}

void VehiculosManager::listarPorId() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg;
    std::cout << left;
    std::cout << setw(26) << " " << "- Datos de los Vehiculos -" << endl;
    std::cout << "-----------------------------------------------------------------------------------" << endl;
    std::cout << setw(4) << "ID ";
    std::cout << setw(10) << "Marca ";
    std::cout << setw(14) << "Modelo ";
    std::cout << setw(12) << "Version ";
    std::cout << setw(10) << "Color ";
    std::cout << setw(8) << "Año ";
    std::cout << setw(8) << "Stock ";
    std::cout << setw(20) << "Precio por Unidad ";
    std::cout << endl;
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            mostrarVehiculo(reg);
        }
    }
    std::cout << endl;
    system("pause");
} 

void VehiculosManager::listarPorPrecio() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg, aux;
    vector<Vehiculo> ordenado;
   std::cout << left;
   std::cout << setw(26) << " " << "- Datos de los Vehiculos -" << endl;
   std::cout << "-----------------------------------------------------------------------------------" << endl;
   std::cout << setw(4) << "ID ";
   std::cout << setw(10) << "Marca ";
   std::cout << setw(14) << "Modelo ";
   std::cout << setw(12) << "Version ";
   std::cout << setw(10) << "Color ";
   std::cout << setw(8) << "Año ";
    std::cout << setw(8) << "Stock ";
    std::cout << setw(20) << "Precio por Unidad ";
    std::cout << endl;
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        ordenado.push_back(reg);
    }
    for (int i = 0; i < cantReg; i++) {
        for (int j = i; j < cantReg; j++) {
            if (ordenado[i].getPrecioUnidad() > ordenado[j].getPrecioUnidad()) {
                aux = ordenado[i];
                ordenado[i] = ordenado[j];
                ordenado[j] = aux;
            }
        }
    }
    for (int i = 0; i < cantReg; i++) {
        if (ordenado[i].getEstado() == true) {
            mostrarVehiculo(ordenado[i]);
        }
    }
    std::cout << endl;
    system("pause");
} 

enum OpcionesBV {
    Opcion1BV = 0,
    Opcion2BV = 1,
    Opcion3BV = 2,
    Opcion4BV = 3,
    Opcion5BV = 4,
    Opcion6BV = 5
};


void VehiculosManager::buscarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        std::cout << endl << "* Error de Archivo *" << endl << endl;
        system("pause");
    }
    if (cantReg == 0) {
        std::cout << endl << "* No Hay Registros para Buscar *" << endl << endl;
        system("pause");
    }
    if (cantReg > 0) {
        
        int op = 1;
        int y = 0;
        rlutil::hidecursor();

        do {

            rlutil::cls();

            rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
            rlutil::setColor(rlutil::COLOR::WHITE);
            rlutil::hidecursor();

            showItemV("--  BUSCAR VEHICULOS --", 50, 2, false);
            showItemV("Por ID ", 53, 4, y == Opcion1BV);
            showItemV("Por Marca ", 53, 5, y == Opcion2BV);
            showItemV("Por Modelo ", 53, 6, y == Opcion3BV);
            showItemV("Por Año de Fabricacion ", 53, 7, y == Opcion4BV);
            showItemV("Por Color ", 53, 8, y == Opcion5BV);
            showItemV("Regresar ", 53, 11, y == Opcion6BV);
            
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
					buscarPorID();
                    break;
				case Opcion2:
					rlutil::cls();
					buscarPorMarca();
					break;
				case Opcion3:
					rlutil::cls();
					buscarPorModelo();
					break;
				case Opcion4:
					rlutil::cls();
					buscarPorAnio();
					break;
				case Opcion5:
					rlutil::cls();
					buscarPorColor();
					break;
				case Opcion6:
					Menu();
					break;
				}
			}
        } while (op != 0);
    } 
}

void VehiculosManager::buscarPorID() {
    int id, pos;
    std::cout << "- Ingrese el ID: ";
    id = validarInt();
    system("cls");
    pos = _vehiculosArchivo.buscarRegistro(id);
    if (pos == -1) {
        std::cout << endl << "* No se Encontraron Registros *" << endl;
    }
    if (pos >= 0) {
        Vehiculo reg;
        reg = _vehiculosArchivo.leerRegistro(pos);
        if (reg.getEstado() == true) {
            std::cout << endl;
            tituloVehiculo();
            mostrarVehiculo(reg);
            std::cout << endl;
        }
        else {
            std::cout << endl << "* El Registro se Encuentra Eliminado *" << endl;
        }
    }
    std::cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorMarca() {
    string marca, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    std::cout << "- Ingrese la Marca: ";
    getline(cin, marca);
    
    cadena1 = aMinuscula(marca);
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            cadena2 = aMinuscula(reg.getMarca());
            if (cadena2 == cadena1) {
                resultado.push_back(reg);
            }
        }
    }
    if (resultado.empty() == true) {
        std::cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        std::cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    std::cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorModelo() {
    string modelo, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    std::cout << "- Ingrese el Modelo: ";
    getline(cin, modelo);
    cadena1 = aMinuscula(modelo);
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            cadena2 = aMinuscula(reg.getModelo());
            if (cadena2 == cadena1) {
                resultado.push_back(reg);
            }
        }
    }
    if (resultado.empty() == true) {
        std::cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        std::cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    std::cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorAnio() {
    int anio, cantReg;
    Fecha año;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    while (true) {
        std::cout << "- Ingrese el Año de Fabricacion: ";
        anio = validarInt();
        if (anio > año.obtenerAnioActual()) {
            std::cout << "* El Año de Fabricacion No puede ser Mayor al Año Actual *" << endl;
        }
        if (anio < 2000) {
            std::cout << "* El Año de Fabricacion No puede ser Menor a 2000 *" << endl;
        }
        if (anio <= año.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }
    system("cls");
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            if (reg.getAnioFabricacion() == anio) {
                resultado.push_back(reg);
            }
        }
    }
    if (resultado.empty() == true) {
        std::cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        std::cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    std::cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorColor() {
    int cantReg;
    string color, cadena1, cadena2;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    std::cout << "- Ingrese el Color: ";
    color = validarStr();
    system("cls");
    cadena1 = aMinuscula(color);
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            cadena2 = aMinuscula(reg.getColor());
            if (cadena2 == cadena1) {
                resultado.push_back(reg);
            }
        }
    }
    if (resultado.empty() == true) {
        std::cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        std::cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    std::cout << endl;
    system("pause");
}

void VehiculosManager::editarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        std::cout << endl << "* Error de Archivo *" << endl << endl;
    }
    if (cantReg == 0) {
        std::cout << endl << "* No Hay Registros para Editar *" << endl << endl;
    }
    if (cantReg > 0) {
        int id, opc, pos;
        Vehiculo reg;
        std::cout << "- Ingrese el ID del Vehiculo que desea Editar: ";
        id = validarInt();
        std::cout << endl;
        pos = _vehiculosArchivo.buscarRegistro(id);
        if (pos == -1) {
            std::cout << "* No Existe ese ID de Vehiculo *" << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == true) {
                tituloVehiculo();
                mostrarVehiculo(reg);
                std::cout << endl << "- Que desea Editar? -" << endl;
                std::cout << "1) Marca " << endl;
                std::cout << "2) Modelo " << endl;
                std::cout << "3) Version " << endl;
                std::cout << "4) Color " << endl;
                std::cout << "5) Anio " << endl;
                std::cout << "6) Stock " << endl;
                std::cout << "7) Precio " << endl;
                std::cout << "8) Todo " << endl;
                std::cout << "0) Salir " << endl;
                std::cout << "Seleccion una Opcion: ";
                opc = validarInt();
                switch (opc) {
                case 1: {
                    string nuevaMarca;
                    cout << "- Ingrese Nueva Marca: ";
                    getline(cin, nuevaMarca);
                    reg.setMarca(nuevaMarca);
                    break;
                }
                case 2: {
                    string nuevoModelo;
                    cout << "- Ingrese Nuevo Modelo: ";
                    getline(cin, nuevoModelo);
                    reg.setModelo(nuevoModelo);
                    break;
                }
                case 3: {
                    string nuevaVersion;
                    cout << "- Ingrese Nueva Version: ";
                    getline(cin, nuevaVersion);
                    reg.setVersion(nuevaVersion);
                    break;
                }
                case 4: {
                    string nuevoColor;
                    cout << "- Ingrese Nuevo Color: ";
                    nuevoColor = validarStr();
                    reg.setColor(nuevoColor);
                    break;
                }
                case 5: {
                    int nuevoAnio;
                    cout << "- Ingrese Nuevo Anio: ";
                    nuevoAnio = validarInt();
                    reg.setAnioFabricacion(nuevoAnio);
                    break;
                }
                case 6: {
                    int nuevoStock;
                    cout << "-Ingrese Nuevo Stock: ";
                    nuevoStock = validarInt();
                    reg.setStock(nuevoStock);
                    break;
                }
                case 7: {
                    float nuevoPrecio;
                    cout << "-Ingrese Nuevo Precio: ";
                    nuevoPrecio = validarInt();
                    reg.setPrecioUnidad(nuevoPrecio);
                    break;
                }
                case 8: {
                    string nuevaMarca, nuevoModelo, nuevaVersion, nuevoColor;
                    int nuevoAnio, nuevoStock;
                    float nuevoPrecio;
                    cout << "- Nueva Marca: ";
                    getline(cin, nuevaMarca);
                    cout << "- Nuevo Modelo: ";
                    getline(cin, nuevoModelo);
                    cout << "- Nueva Version: ";
                    getline(cin, nuevaVersion);
                    cout << "- Nuevo Color: ";
                    nuevoColor = validarStr();
                    cout << "- Nuevo Año: ";
                    nuevoAnio = validarInt();
                    cout << "- Nuevo Stock: ";
                    nuevoStock = validarInt();
                    cout << "- Precio: ";
                    nuevoPrecio = validarInt();
                    reg.setMarca(nuevaMarca);
                    reg.setModelo(nuevoModelo);
                    reg.setVersion(nuevaVersion);
                    reg.setColor(nuevoColor);
                    reg.setAnioFabricacion(nuevoAnio);
                    reg.setStock(nuevoStock);
                    reg.setPrecioUnidad(nuevoPrecio);
                    break;
                }
                case 0:
                    return;
                default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
                bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
                if (modifico == true) cout << endl << "* Registro Modificado con Exito *" << endl;
                else cout << endl << "* No se Pudo Modificar el Registro *" << endl;
            }
            else {
                cout << "* El Registro se Encuentra Eliminado *" << endl;
            }
        }
    }
    cout << endl;
    system("pause");
}

void VehiculosManager::eliminarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl << endl;
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Eliminar *" << endl << endl;
    }
    if (cantReg > 0) {
        int id, pos, opc;
        cout << "- Ingrese el ID del Vehiculo: ";
        id = validarInt();
        system("cls");
        pos = _vehiculosArchivo.buscarRegistro(id);
        if (pos == -1) {
            cout << endl << "* No Existe ese ID de Vehiculo *" << endl << endl;
        }
        if (pos == -2) {
            cout << endl << "* Error de Archivo *" << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == true) {
                cout << endl;
                tituloVehiculo();
                mostrarVehiculo(reg);
                cout << endl;
                cout << "- Desea Eliminar el Registro? (1)Si (2)NO " << endl;
                cout << "- Seleccione una Opcion: ";
                opc = validarInt();
                switch (opc) {
                case 1: {
                    reg.setEstado(false);
                    bool elimino = _vehiculosArchivo.modificarRegistro(reg, pos);
                    if (elimino == true) cout << endl << "* Registro Eliminado con Exito *" << endl << endl;
                    else cout << "* No se Pudo Eliminar el Registro *" << endl;
                    break;
                }
                case 2:
                    break;
                default:cout << "* Opcion Incorrecta! *" << endl;
                }
            }
            else {
                cout << endl << "* El Registro ya se Encuentra Eliminado *" << endl << endl;
            }
        }
    }
    cout << endl;
}

void VehiculosManager::resturarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl << endl;
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Restaurar *" << endl << endl;
    }
    if (cantReg > 0) {
        int id, pos, opc;
        cout << "- Ingrese el ID del Vehiculo: ";
        id = validarInt();
        system("cls");
        pos = _vehiculosArchivo.buscarRegistro(id);
        if (pos == -1) {
            cout << endl << "* No Existe ese ID de Vehiculo *" << endl << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == false) {
                cout << "- Desea Restaurar el Registro? (1)Si (2)NO " << endl;
                cout << "- Seleccione una Opcion: ";
                opc = validarInt();
                system("cls");
                switch (opc) {
                case 1: {
                    reg.setEstado(true);
                    cout << endl;
                    tituloVehiculo();
                    mostrarVehiculo(reg);
                    bool restaurar = _vehiculosArchivo.modificarRegistro(reg, pos);
                    if (restaurar == true) cout << endl << setw(25) << " " << "* Registro Restaurado con Exito *" << endl << endl;
                    else cout << endl << "* No se Pudo Restaurar el Registro *" << endl;
                }
                case 2:
                    break;
                default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
            }
            else {
                cout << endl << "* El Registro ya Se Encuentra Disponible *" << endl << endl;
            }
        }
    }
    cout << endl;
}

enum OpcionesBkVh {
    Opcion1BkVh = 0,
    Opcion2BkVh = 1,
};


void VehiculosManager::realizarBackup() {
    
    bool resultado = system("copy Vehiculos.dat Vehiculos.bkp");
    if (resultado == 0) {
        std::cout << "* Backup Realizado con Exito! *" << std::endl;
    }
    else {
        std::cout << "* Hubo un error al copiar el archivo *" << std::endl;
    }
}

enum OpcionesRbVh {
	Opcion1RbVh = 0,
	Opcion2RbVh = 1,
};

void VehiculosManager::restaurarBackup() {
    
    bool resultado = system("copy Vehiculos.bkp Vehiculos.dat");
    if (resultado == 0) {
        std::cout << "* Restauracion Realizada con Exito! *" << std::endl;
    }
    else {
        std::cout << "* Hubo un error al copiar el archivo *" << std::endl;
    }
}

