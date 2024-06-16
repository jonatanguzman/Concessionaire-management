#include "VehiculosManager.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

VehiculosManager::VehiculosManager() : _vehiculosArchivo("Vehiculos.dat")
{
    
}

void VehiculosManager::tituloVehiculo() {
    cout << left;
    cout << setw(26) << " " << "- Datos del Vehiculo -" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << setw(4) << "ID ";
    cout << setw(10) << "Marca ";
    cout << setw(14) << "Modelo ";
    cout << setw(12) << "Version ";
    cout << setw(10) << "Color ";
    cout << setw(8) << "Anio ";
    cout << setw(8) << "Stock ";
    cout << setw(20) << "Precio por Unidad ";
    cout << endl;

}

void VehiculosManager::Menu() {
    int opc;
    do {
        system("cls");
        cout << "--- Menu Vehiculos ---" << endl;
        cout << "----------------------" << endl;
        cout << "1) Cargar " << endl;
        cout << "2) Listar " << endl;
        cout << "3) Buscar " << endl;
        cout << "4) Editar " << endl;
        cout << "5) Eliminar " << endl;
        cout << "6) Restaurar " << endl;
        cout << "7) Realizar Backup " << endl;
        cout << "8) Restaurar Backup " << endl;
        cout << "0) Regresar al menu anterior " << endl;
        cout << "----------------------" << endl;
        cout << "Selecione una Opcion: ";
        cin >> opc;
        switch (opc) {
        case 1: system("cls");
            agregarVehiculo();
            system("pause");
            break;
        case 2: system("cls");
            listarVehiculos();
            system("pause");
            break;
        case 3: system("cls"); 
            buscarVehiculo();
            system("pause");
            break;
        case 4: system("cls"); 
            editarVehiculo();
            system("pause");
            break;
        case 5: system("cls");
            eliminarVehiculo();
            system("pause");
            break;
        case 6: system("cls"); 
            resturarVehiculo();
            system("pause");
            break;
        case 7: system("cls"); 
            realizarBackup();
            system("pause");
            break;
        case 8: system("cls"); 
            restaurarBackup();
            system("pause");
            break;
        case 0:
            break;
        default:cout << endl << "* Selecione una Opcion Correcta! *" << endl << endl;
            system("pause");
        }
    } while (opc != 0);

}

void VehiculosManager::agregarVehiculo() {
    if (_vehiculosArchivo.guardarRegistro(cargarVehiculo())) {
        cout << "* Registro Agregado! *" << endl;
    }
    else {
        cout << "* No se Pudo Agregar el Registro *" << endl;
    }
}

Vehiculo VehiculosManager::cargarVehiculo() {
    string marca, modelo, version, color;
    int id, anio, stock;
    float precio;
    VehiculosArchivo archivo;
    int cantReg = archivo.contarRegistros();
    if (cantReg == -1) {
        cantReg = 0;
        cout << "* Archivo Nuevo *" << endl;
    }
    Vehiculo reg;
    id = ++cantReg;
    cout << "- Ingrese Los Datos del Vehiculo -" << endl;
    cout << "- ID: ";
    cout << id << endl;
    reg.setIdVehiculo(id);
    cin.ignore();
    cout << "- Marca: ";
    getline(cin, marca);
    reg.setMarca(marca);
    cout << "- Modelo: ";
    getline(cin, modelo);
    reg.setModelo(modelo);
    cout << "- Version: ";
    getline(cin, version);
    reg.setVersion(version);
    cout << "- Color: ";
    getline(cin, color);
    reg.setColor(color);
    cout << "- Anio de Fabricacion: ";
    cin >> anio;
    reg.setAnioFabricacion(anio);
    cout << "- Stock: ";
    cin >> stock;
    reg.setStock(stock);
    cout << "- Precio por Unidad: $ ";
    cin >> precio;
    reg.setPrecioUnidad(precio);
    reg.setEstado(true);
    return reg;
}

string formatearNumero(float numero);

void VehiculosManager::mostrarVehiculo(Vehiculo reg) {
    if (reg.getEstado() == true) {
        cout << left;
        cout << setw(4) << reg.getIdVehiculo();
        cout << setw(10) << reg.getMarca();
        cout << setw(14) << reg.getModelo();
        cout << setw(12) << reg.getVersion();
        cout << setw(10) << reg.getColor();
        cout << setw(8) << reg.getAnioFabricacion();
        cout << setw(8) << reg.getStock();
        string numeroFormateado = formatearNumero(reg.getPrecioUnidad());
        cout << setw(2) << "$ " << setw(18) << numeroFormateado;
        cout << endl;
    }
    else {
        cout << reg.getIdVehiculo() << "   Este Registro se Encuentra Eliminado! " << endl;
    }
}

void VehiculosManager::listarVehiculos() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1)cout << endl << "* Error de Archivo *" << endl;
    else {
        Vehiculo reg;
        cout << left;
        cout << setw(26) << " " << "- Datos de los Vehiculos -" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << setw(4) << "ID ";
        cout << setw(10) << "Marca ";
        cout << setw(14) << "Modelo ";
        cout << setw(12) << "Version ";
        cout << setw(10) << "Color ";
        cout << setw(8) << "Anio ";
        cout << setw(8) << "Stock ";
        cout << setw(20) << "Precio por Unidad ";
        cout << endl;
        for (int i = 0; i < cantReg; i++) {
            reg = _vehiculosArchivo.leerRegistro(i);
            if (reg.getEstado() == true) {

                mostrarVehiculo(reg);
            }
        }
    }
    cout << endl;
}

void VehiculosManager::buscarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int opc;
        cout << "- Buscar Vehiculo -" << endl;
        cout << "-------------------" << endl;
        cout << "1) Por ID " << endl;
        cout << "2) Por Modelo " << endl;
        cout << "3) Por Anio de Fabricacion " << endl;
        cout << "4) Por Color " << endl;
        cout << "0) Salir " << endl;
        cout << "Ingrese una Opcion: ";
        cin >> opc;
        system("cls");
        switch (opc) {
        case 1:buscarPorID();
            break;
        case 2:buscarPorModelo();
            break;
        case 3:buscarPorAnio();
            break;
        case 4:buscarPorColor();
            break;
        default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
            return;
        }
    }
    cout << endl;
}

void VehiculosManager::buscarPorID() {
    int id, pos;
    cout << "- Ingrese el ID: ";
    cin >> id;
    pos = _vehiculosArchivo.buscarRegistro(id);
    if (pos == -1) {
        cout << endl << "* No se Encontraron Registros *" << endl;
    }
    if (pos >= 0) {
        Vehiculo reg;
        reg = _vehiculosArchivo.leerRegistro(pos);
        if (reg.getEstado() == true) {
            tituloVehiculo();
            mostrarVehiculo(reg);
            cout << endl;
        }
        else {
            cout << "* El Registro se Encuentra Eliminado *" << endl;
        }
    }
    cout << endl;
}

string aMinuscula(string cadena);

void VehiculosManager::buscarPorModelo() {
    string modelo;
    string cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    cout << "- Ingrese el Modelo: ";
    cin.ignore();
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
}

void VehiculosManager::buscarPorAnio() {
    int anio, cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    cout << "- Ingrese el Anio: ";
    cin >> anio;
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
}

void VehiculosManager::buscarPorColor() {
    int cantReg;
    string color;
    string cadena1, cadena2;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    cout << "- Ingrese el Color: ";
    cin >> color;
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
}

void VehiculosManager::editarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int id, opc, pos;
        Vehiculo reg;
        cout << "- Ingrese el ID del Vehiculo que desea Editar: ";
        cin >> id;
        cout << endl;
        pos = _vehiculosArchivo.buscarRegistro(id);
        if (pos == -1) {
            cout << "* No Existe ese ID de Vehiculo *" << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == true) {
                tituloVehiculo();
                mostrarVehiculo(reg);
                cout << endl << "- Que desea Editar? -" << endl;
                cout << "1) Marca " << endl;
                cout << "2) Modelo " << endl;
                cout << "3) Version " << endl;
                cout << "4) Color " << endl;
                cout << "5) Anio " << endl;
                cout << "6) Stock " << endl;
                cout << "7) Precio " << endl;
                cout << "8) Todo " << endl;
                cout << "0) Salir " << endl;
                cout << "Seleccion una Opcion: ";
                cin >> opc;
                switch (opc) {
                case 1: {
                    string nuevaMarca;
                    cin.ignore();
                    cout << "- Ingrese la Nueva Marca: ";
                    getline(cin, nuevaMarca);
                    reg.setMarca(nuevaMarca);
                    break;
                }
                case 2: {
                    string nuevoModelo;
                    cin.ignore();
                    cout << "- Ingrese el Nuevo Modelo: ";
                    getline(cin, nuevoModelo);
                    reg.setModelo(nuevoModelo);
                    break;
                }
                case 3: {
                    string nuevaVersion;
                    cin.ignore();
                    cout << "- Ingrese la Nueva Version: ";
                    getline(cin, nuevaVersion);
                    reg.setVersion(nuevaVersion);
                    break;
                }
                case 4: {
                    string nuevoColor;
                    cin.ignore();
                    cout << "- Ingrese Nuevo Color: ";
                    getline(cin, nuevoColor);
                    reg.setColor(nuevoColor);
                    break;
                }
                case 5: {
                    int nuevoAnio;
                    cout << "- Ingrese Nuevo Anio: ";
                    cin >> nuevoAnio;
                    reg.setAnioFabricacion(nuevoAnio);
                    break;
                }
                case 6: {
                    int nuevoStock;
                    cout << "-Ingrese Nuevo Stock: ";
                    cin >> nuevoStock;
                    reg.setStock(nuevoStock);
                    break;
                }
                case 7: {
                    float nuevoPrecio;
                    cout << "-Ingrese Nuevo Precio: ";
                    cin >> nuevoPrecio;
                    reg.setPrecioUnidad(nuevoPrecio);
                    break;
                }
                case 8: {
                    string nuevaMarca, nuevoModelo, nuevaVersion, nuevoColor;
                    int nuevoAnio, nuevoStock;
                    float nuevoPrecio;
                    cin.ignore();
                    cout << "- Nueva Marca: ";
                    getline(cin, nuevaMarca);
                    cout << "- Nuevo Modelo: ";
                    getline(cin, nuevoModelo);
                    cout << "- Nueva Version: ";
                    getline(cin, nuevaVersion);
                    cout << "- Nuevo Color: ";
                    getline(cin, nuevoColor);
                    cout << "- Nuevo Anio: ";
                    cin >> nuevoAnio;
                    cout << "- Nuevo Stock: ";
                    cin >> nuevoStock;
                    cout << "- Precio: ";
                    cin >> nuevoPrecio;
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
                if (modifico == true) cout << "* Registro Modificado con Exito *" << endl;
                else cout << "* No se Pudo Modificar el Registro *" << endl;
            }
            else {
                cout << "* El Registro se Encuentra Eliminado *" << endl;
            }
        }
    }
    cout << endl;
}


void VehiculosManager::eliminarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int id, pos, opc;
        cout << "- Ingrese el ID del Vehiculo: ";
        cin >> id;
        cout << endl;
        pos = _vehiculosArchivo.buscarRegistro(id);
        if (pos == -1) {
            cout << "* No Existe ese ID de Vehiculo *" << endl << endl;
        }
        if (pos == -2) {
            cout << "* Error de Archivo *" << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == true) {
                tituloVehiculo();
                mostrarVehiculo(reg);
                cout << endl;
                cout << "- Desea Eliminar el Registro? (1)Si (2)NO " << endl;
                cout << "- Seleccione una Opcion: ";
                cin >> opc;
                switch (opc) {
                case 1: {
                    reg.setEstado(false);
                    bool elimino = _vehiculosArchivo.modificarRegistro(reg, pos);
                    if (elimino == true) cout << "* Registro Eliminado *" << endl;
                    else cout << "* No se Pudo Eliminar el Registro *" << endl;
                    break;
                }
                case 2:
                    break;
                default:cout << "* Opcion Incorrecta! *" << endl;;
                }
            }
            else {
                cout << "* El Registro ya se Encuentra Eliminado *" << endl << endl;
            }
        }
    }
    cout << endl;
}

void VehiculosManager::resturarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int id, pos, opc;
        cout << "- Ingrese el ID del Vehiculo: ";
        cin >> id;
        cout << endl;
        pos = _vehiculosArchivo.buscarRegistro(id);
        if (pos == -1) {
            cout << "* No Existe ese ID de Vehiculo *" << endl << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == false) {
                cout << "- Desea Restaurar el Registro? (1)Si (2)NO " << endl;
                cout << "- Seleccione una Opcion: ";
                cin >> opc;
                switch (opc) {
                case 1:
                    reg.setEstado(true);
                    tituloVehiculo();
                    mostrarVehiculo(reg);
                case 2:
                    break;
                default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
                bool restaurar = _vehiculosArchivo.modificarRegistro(reg, pos);
                if (restaurar == true) cout << setw(25) << " " << "* Registro Restaurado con Exito *" << endl;
                else cout << "* No se Pudo Restaurar el Registro *" << endl;
            }
            else {
                cout << "* El Registro ya Se Encuentra Disponible *" << endl;
            }
        }
    }
    cout << endl;
}

void VehiculosManager::realizarBackup() {
    int opc;
    cout << "- Desea Relizar Backup del Archivo Vehiculo?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "- Selecione una Opcion: ";
    cin >> opc;
    switch (opc) {
    case 1: system("copy Vehiculos.dat Vehiculos.bkp");
        cout << "* Backup Realizado con Exito! *" << endl;
    case 2:
        break;
    default:cout << endl << "* Opcion Incorrecta! *" << endl;
    }
}

void VehiculosManager::restaurarBackup() {
    int opc;
    cout << "- Desea Restaurar del Archivo Vehiculo?" << endl;
    cout << " (1)SI (2)NO " << endl;
    cout << "- Selecione una Opcion: ";
    cin >> opc;
    switch (opc) {
    case 1: system("copy Vehiculos.bkp Vehiculos.dat");
        cout << "* Restauracion Realizado con Exito! *" << endl;
    case 2:
        break;
    default:cout << endl << "* Opcion Incorrecta! *" << endl;
    }
}

string formatearNumero(float numero) {
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

string aMinuscula(string cadena) {
    for (string::size_type i = 0; i < cadena.length(); i++)cadena[i] = tolower(cadena[i]);
    return cadena;
}