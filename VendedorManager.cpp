#include <iostream>
#include <cstring>
#include <iomanip>
#include "VendedorManager.h"
#include "FuncionesGenerales.h"
#include "Sistema.h"
#include "rlutil.h"


VendedorManager::VendedorManager(): _archivo("Vendedores.dat"){

}

void VendedorManager::PlanillaVendedor(){
    std::cout<<std::left;
    std::cout<<std::setw(14)<<"DNI ";
    std::cout<<std::setw(20)<< "NOMBRE";
    std::cout<<std::setw(20)<<"APELLIDO ";
    std::cout<<std::setw(23)<<"FECHA NACIMIENTO ";
    std::cout<<std::setw(10)<<"LEGAJO ";
    std::cout<<std::setw(20)<<"FECHA INGRESO ";
    std::cout<<std::setw(10)<<"ANTIGUEDAD ";
    std::cout<<std::endl;
}

Vendedor VendedorManager::CrearVendedor(){
    int numLegajo, anioAntiguedad;
    Fecha fechaI;
    Vendedor vendedor;
    int opc;

    std::cout << std::left;
    std::cout<<std::setw(60)<<"--- AGREGAR VENDEDOR ---"<<std::endl;
    std::cout<<std::endl;

    regreso:
    vendedor.CargarPersona();
    bool resultado = DniRepetido(vendedor.getDni());
    if (resultado) {
        opc = validarInt("Vendedor ya existente.Desea cargar un nuevo vendedor? (1)Si - (2)No: ");

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

    numLegajo = validarInt("NUMERO DE LEGAJO: ");
    vendedor.setNroLegajo(numLegajo);
    std::cout<<"FECHA INGRESO: "<<std::endl;
    fechaI.Cargar();
    vendedor.setFechaIngreso(fechaI);
    std::cout<<"ANTIGUEDAD: ";
    anioAntiguedad=vendedor.calcularAntiguedad();
    std::cout << anioAntiguedad << " años" << std::endl;
    vendedor.setAntiguedad(anioAntiguedad);
    vendedor.setEliminado(false);
    std::cout<<std::endl;

    return vendedor;
}

void VendedorManager::MostrarVendedor(Vendedor vendedor){

    vendedor.MostrarPersonaEnLinea();

    std::cout<<std::left;
    std::cout<<std::setw(10)<<vendedor.getNroLegajo();
    std::cout<<std::setw(20)<<vendedor.getFechaIngreso().toString();
    std::cout << std::setw(0) << vendedor.getAntiguedad() << " años"; 
}

void VendedorManager::AgregarVendedor(){
    if(_archivo.GuardarRegistro(CrearVendedor())){
        std::cout<<"El vendedor se guardo correctamente!!!"<<std::endl;
    }else{
        std::cout<<"No se pudo guardar el vendedor!!!"<<std::endl;
    }
}

void VendedorManager::ListarVendedor()
{
    std::cout << std::left;
    std::cout<<std::setw(60)<<"--- LISTAR TODOS LOS VENDEDORES ---"<<std::endl;
    std::cout<<std::endl;

    PlanillaVendedor();

    int cantidad=_archivo.ContarRegistro();
    Vendedor reg;

    for(int i = 0; i < cantidad; i++){
        reg=_archivo.leerRegistro(i);

        if(reg.getEliminado()==false){
            MostrarVendedor(reg);
            std::cout<<std::endl;
        }
    }
    std::cout<<std::endl;
}

void VendedorManager::BuscarVendedor()
{
    int numLegajo, indice;
    Vendedor vendedor;

    std::cout << std::left;
    std::cout<<std::setw(60)<<"--- BUSCAR VENDEDOR ---"<<std::endl;
    std::cout<<std::endl;

    numLegajo = validarInt("Ingrese el numero de legajo del vendedor que desea buscar: ");
    std::cout<<std::endl;
    system("cls");

    indice=_archivo.BuscarId(numLegajo);

    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);

        std::cout<<"LEGAJO: "<<vendedor.getNroLegajo();
        std::cout<<std::endl<<std::endl;

        PlanillaVendedor();

        MostrarVendedor(vendedor);
    }else{
        std::cout<<"No se encuentra ningun vendedor con ese numero de legajo!!!"<<std::endl;
    }
    std::cout<<std::endl<<std::endl;
}

void showItemVendedor(const char* text, int posx, int posy, bool selected)
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

void VendedorManager::EditarVendedor()
{
    int legajo;
    int opcion;

    std::cout << std::left;
    std::cout<<std::setw(60)<<"--- EDITAR VENDEDOR ---"<<std::endl;
    std::cout<<std::endl;

    legajo = validarInt("Ingrese Legajo del Vendedor a editar: ");
    std::cout << std::endl;
    system("cls");

    int indice = _archivo.BuscarId(legajo);

    Vendedor vendedor;
    vendedor = _archivo.leerRegistro(indice);

    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);

        PlanillaVendedor();
        MostrarVendedor(vendedor);

        std::cout << std::endl<<std::endl;
        std::cout << "¿Desea editar la Fecha de Ingreso? (1)Si - (2)No: " << std::endl;
        opcion = validarInt("Opcion: ");
        system("cls");

        if(opcion == 1){
            std::cout<<std::endl;
            Fecha f;
            std::cout << "Ingrese nueva fecha: "<<std::endl;
            f.Cargar();
            system("cls");
            vendedor.setFechaIngreso(f);
            int newA=vendedor.calcularAntiguedad();
            vendedor.setAntiguedad(newA);

            bool result = _archivo.Sobreescribir(indice, vendedor);

            if (result == true) {
                std::cout<<"Se edito correctamente el vendedor."<<std::endl;
            }

        }else{
            std::cout<<"Cancelo el modificar del vendedor."<<std::endl;
        }
    }else{
        std::cout<<"Numero de Legajo inexistente."<<std::endl;
    }

}

void VendedorManager::EliminarVendedor()
{
    int numLegajo, indice;
    Vendedor vendedor;
    int opcion;

    std::cout << std::left;
    std::cout<<std::setw(60)<<"--- ELIMINAR VENDEDOR ---"<<std::endl;
    std::cout<<std::endl;

    numLegajo = validarInt("Ingrese el numero de Legajo: ");

    indice=_archivo.BuscarId(numLegajo);

    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);

        std::cout<<std::endl;
        PlanillaVendedor();
        MostrarVendedor(vendedor);
        std::cout<<std::endl<<std::endl;

        std::cout<< "Desea eliminar este vendedor? (1)Si - (2)No: " << std::endl;
        opcion = validarInt("Opcion: ");
        system("cls");

        if(opcion == 1){ 
            vendedor.setEliminado(true);

            if(_archivo.Sobreescribir(indice, vendedor)){
                std::cout<<"Se elimino con exito."<<std::endl;
            }else{
                std::cout<<"No se pudo eliminar."<<std::endl;
            }
        }else{
            std::cout<<"Cancelo el eliminado del vendedor."<<std::endl;
        }
    }else{
        std::cout<<"Numero de Legajo inexistente."<<std::endl;
    }
}

void VendedorManager::realizarBackupVendedores()
{
    bool resultado = system("copy Vendedores.dat Vendedores.bkp");
    if (resultado == 0) {
        std::cout << "* Backup Realizado con Exito! *" << std::endl;
    }
    else {
        std::cout << "* Hubo un error al copiar el archivo *" << std::endl;
    }
}

void VendedorManager::restaurarBackupVendedores() 
{
    bool resultado = system("copy Vendedores.bkp Vendedores.dat");
    if (resultado == 0) {
        std::cout << "* Restauracion Realizado con Exito! *" << std::endl;
    }
    else {
        std::cout << "* Hubo un error al copiar el archivo *" << std::endl;
    }
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

void VendedorManager::Menu() {
    Sistema programa;
    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    do {

        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemVendedor("--- MENU VENDEDORES ---", 50, 2, false);
        showItemVendedor("Agregar ", 53, 4, y == Opcion1);
        showItemVendedor("Listar ", 53, 5, y == Opcion2);
        showItemVendedor("Buscar ", 53, 6, y == Opcion3);
        showItemVendedor("Editar ", 53, 7, y == Opcion4);
        showItemVendedor("Eliminar ", 53, 8, y == Opcion5);
        showItemVendedor("Crear Backup ", 53, 9, y == Opcion6);
        showItemVendedor("Restaurar Backup ", 53, 10, y == Opcion7);
        showItemVendedor("Regresar al Menu Principal ", 53, 13, y == Opcion8);


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
                AgregarVendedor();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                menuListar();
                system("pause");
                break;
            case Opcion3:
                rlutil::cls();
                BuscarVendedor();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                EditarVendedor();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                EliminarVendedor();
                system("pause");
                break;
            case Opcion6:
                rlutil::cls();
                realizarBackupVendedores();
                system("pause");
                break;
            case Opcion7:
                rlutil::cls();
                restaurarBackupVendedores();
                system("pause");
                break;
            case Opcion8:
                programa.Menu();
                break;
            }
        }
    } while (op != 0);
}
  
bool VendedorManager::LegajoRepetido(int idLegajo) {
    Vendedor registro;
    int cantidad = _archivo.ContarRegistro();

    for (int i = 0; i < cantidad; i++) {
        registro = _archivo.leerRegistro(i);

        if (registro.getNroLegajo() == idLegajo) {
            return true;
        }
    }
    return false;
}

bool VendedorManager::DniRepetido(long long idPersona) {
    VendedorArchivo va;
    Vendedor registro;
    int cantidad = va.ContarRegistro();

    for (int i = 0; i < cantidad; i++) {
        registro = va.leerRegistro(i);

        if (registro.getDni() == idPersona) {
            return true;
        }
    }
    return false;
}

void VendedorManager::OrdenarPorAntiguedad(Vendedor* obj, int cantidad, bool criterio(int, int)) {
    Vendedor aux;

    for (int i = 0; i < cantidad; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (criterio(obj[j].getAntiguedad(), obj[i].getAntiguedad())) {
                aux = obj[j];
                obj[j] = obj[i];
                obj[i] = aux;
            }
        }
    }
}

void VendedorManager::ListarAntiguedad() 
{
    int cantidad = _archivo.ContarRegistro();
    Vendedor* vec, reg;

    vec = new Vendedor[cantidad];
    if (vec == nullptr) {
        std::cout << "No hay memoria.";
    }

    if (cantidad == 0) {
        std::cout << "No hay Vendedores para mostrar." << std::endl;
    }
    else {
         MostrarPantalla(); 
        for (int i = 0; i < cantidad; i++) {
            reg = _archivo.leerRegistro(i);
            vec[i] = reg;
        }

        OrdenarPorAntiguedad(vec, cantidad, creciente);  

        for (int i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                MostrarVendedor(vec[i]);
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    delete[]vec;
}

void VendedorManager::OrdenarPorApellido(Vendedor* obj, int cantidad, bool criterio(std::string, std::string)) 
{
    Vendedor aux;

    for (int i = 0; i < cantidad; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (criterio(obj[j].getApellido(), obj[i].getApellido())) {
                aux = obj[j];
                obj[j] = obj[i];
                obj[i] = aux;
            }
        }
    }
}

void VendedorManager::ListarApellido() 
{
    int cantidad = _archivo.ContarRegistro();
    Vendedor* vec, reg;

    vec = new Vendedor[cantidad];
    if (vec == nullptr) {
        std::cout << "No hay memoria.";
    }

    if (cantidad == 0) {
        std::cout << "No hay Vendedores para mostrar." << std::endl;
    }
    else {
        MostrarPantalla();
        for (int i = 0; i < cantidad; i++) {
            reg = _archivo.leerRegistro(i);
            vec[i] = reg;
        }

        OrdenarPorApellido(vec, cantidad, creciente);

        for (int i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                MostrarVendedor(vec[i]);
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    delete[]vec;
}


enum OpcionesListar {
    Opcion1L = 0,
    Opcion2L = 1,
    Opcion3L = 2,
};

void VendedorManager::menuListar()
{
    int op = 1;
    int y = 0;
    rlutil::hidecursor();

    while (true) {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

        showItemVendedor("Como desea ordenar el listado de Vendedores?", 59, 8, false);

        showItemVendedor("Por Antiguedad", 60, 12, y == Opcion1L);
        showItemVendedor("Por Apellido ", 60, 14, y == Opcion2L);
        showItemVendedor("Volver al menu anterior ", 60, 16, y == Opcion3L);


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
            if (y > 3) {
                y = 3;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case Opcion1L:
                rlutil::cls();
                ListarAntiguedad();
                system("pause");
                break;
            case Opcion2L:
                rlutil::cls();
                ListarApellido();
                system("pause");
                break;
            case Opcion3L:
                rlutil::cls();
                Menu();
                break;
            }
        }
    }
    system("pause");

    return;
}

void VendedorManager::MostrarPantalla() 
{
    std::cout << std::left;
    std::cout << std::setw(14) << "DNI ";
    std::cout << std::setw(20) << "NOMBRE";
    std::cout << std::setw(20) << "APELLIDO ";
    std::cout << std::setw(23) << "FECHA NACIMIENTO ";
    std::cout << std::setw(10) << "LEGAJO ";
    std::cout << std::setw(20) << "FECHA INGRESO ";
    std::cout << std::setw(10) << "ANTIGUEDAD ";
    std::cout << std::endl;
}