#include "Informes.h"
#include "VentasManager.h"
#include "VehiculosManager.h"
#include "SucursalManager.h"
#include "VendedorManager.h"
#include "FuncionesGenerales.h"
#include "Sistema.h"
#include <iostream>
#include <iomanip>
#include "rlutil.h"
using namespace std;

void showItemInf(const char* text, int posx, int posy, bool selected)
{

    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::GREEN);
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
    Opcion8 = 7
};


void Informes::Menu()
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

        showItemInf("--- INFORMES ---", 50, 2, false);

        showItemInf("Informe del Inventario", 53, 4, y == Opcion1);
        showItemInf("Informe de Recaudación Anual", 53, 5, y == Opcion2);
        showItemInf("Informe Anual de Ventas por Vendedor ", 53, 6, y == Opcion3);
        showItemInf("Informe Mensual de Ventas para todos los Vendedores ", 53, 7, y == Opcion4);
        showItemInf("Informe Anual de Ventas por Sucursal ", 53, 8, y == Opcion5);
        showItemInf("Informe Ventas en todas las Sucursales (mensual o anual) ", 53, 9, y == Opcion6);
        showItemInf("Ranking Anual de Ventas por Modelo ", 53, 10, y == Opcion7);
        showItemInf("Regresar al Menu Principal ", 53, 13, y == Opcion8);


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
                y = 6;
            }
            break;
        case 1: // ENTER
            switch (y) {
            case Opcion1:
                rlutil::cls();
                Inventario();
                system("pause");
                break;
            case Opcion2:
                rlutil::cls();
                recaudacionAnual();
                system("pause");
                break;
            case Opcion3:
                rlutil::cls();
                ventasXVendedorAnual();
                system("pause");
                break;
            case Opcion4:
                rlutil::cls();
                ventasXVendedoresMensual();
                system("pause");
                break;
            case Opcion5:
                rlutil::cls();
                ventasXSucursalAnual();
                system("pause");
                break;
            case Opcion6:
                rlutil::cls();
                int op;
                cout << "1. Ventas en todas las sucursales (mensual)" << endl;
                cout << "2. Ventas en todas las sucursales (anual)" << endl;
                op = validarInt("Ingrese una opcion: ");
                system("cls");
                if (op == 1) {
                    ventasTodasLasSucursalesMensual();
                }
                else if (op == 2) {
                    ventasTodasLasSucursalesAnual();
                }
                system("pause");
                break;
            case Opcion7:
                rlutil::cls();
                rankingVentasXModelo();
                system("pause");
                break;
            case Opcion8:
                programa.Menu();
            }
        }
    } while (op != 0);
}

//1
void Informes::Inventario()
{
    VehiculosArchivo archiV;
    Vehiculo regVeh;
    int cantReg, contDisp = 0, contAgo = 0;
    cantReg = archiV.contarRegistros();
    cout << left;
    cout << "--- Informe de Inventario ---" << endl;
    cout << "-------- Disponibles --------" << endl;
    cout << setw(9) << "Marca";
    cout << setw(15) << "Modelo";
    cout << setw(6) << "Stock";
    cout << endl;
    for (int i = 0; i < cantReg; i++) {
        regVeh = archiV.leerRegistro(i);
        if (regVeh.getEstado() == true) {
            if (regVeh.getStock() != 0) {
                cout << setw(9) << regVeh.getMarca();
                cout << setw(15) << regVeh.getModelo();
                cout << setw(6) << regVeh.getStock();
                cout << endl;
                contDisp += regVeh.getStock();
            }
        }
    }
    cout << endl;
    cout << "--------- Agotados ----------" << endl;
    cout << setw(9) << "Marca";
    cout << setw(15) << "Modelo";
    cout << setw(6) << "Stock";
    cout << endl;
    for (int j = 0; j < cantReg; j++) {
        regVeh = archiV.leerRegistro(j);
        if (regVeh.getEstado() == true) {
            if (regVeh.getStock() == 0) {
                cout << setw(9) << regVeh.getMarca();
                cout << setw(15) << regVeh.getModelo();
                cout << setw(6) << regVeh.getStock();
                cout << endl;
                contAgo++;
            }
        }
    }
    cout << endl;
    cout << "-----------------------------" << endl;
    cout << "---------- Totales ----------" << endl;
    cout << "- Autos Disponibles:    " << contDisp << endl;
    cout << "- Autos Agotados:       " << contAgo << endl;
    cout << endl;

}

//2
void Informes::recaudacionAnual()
{
    VentasManager vm;
    VentasArchivo va;
    Fecha f;
    int i;
    double recaudacion[13] = {0};
    string meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

    int anio;

	cout << "** INFORME DE RECAUDACION ANUAL ** " << endl;
    do {
        anio = validarInt("Ingrese año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            cout << "Año no valido." << endl << endl;
        }

    } while (anio > f.obtenerAnioActual());

	system("cls");

	int cantidad = va.contarVentas();
	for (i = 0; i < cantidad; i++) {
		Venta reg = va.leerVenta(i);
		if (reg.getFechaVenta().getAnio() == anio) {
			recaudacion[reg.getFechaVenta().getMes() - 1] += reg.getTotalVenta();
			recaudacion[12] += reg.getTotalVenta();
		}

	}

	cout << "** INFORME DE RECAUDACION ANUAL ** " << endl << endl;
	cout << "Año: " << anio << endl << endl;

	cout << left;
	cout << setw(12) << "MES";
	cout << setw(20) << "RECAUDACION" << endl;
	cout << "------------------------------------------------------------" << endl;

	for (i = 0; i < 12; i++) {

		cout << setw(12) << meses[i];
		cout << "$ " << setw(20) << vm.formatearNumero(recaudacion[i]);
		cout << endl;

	}
	cout << endl << endl;

	cout << "** Total Anual : $" << vm.formatearNumero(recaudacion[12]) << " **" << endl << endl;
	
}

//3
void Informes::ventasXVendedorAnual()
{
     int numLegajo, anio, id = 0;
    Vendedor vendedor;
    Venta venta;
    VendedorArchivo va;
    VentasArchivo vs;
    VentasManager vm;
    Fecha f;

    int cantidadVendedor = va.ContarRegistro();
    int cantidadVentas = vs.contarVentas();

    string meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };
    double recaudacion[13] = {};

    numLegajo = validarInt("Ingrese el numero de legajo del vendedor: ");
    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            cout << "Año no valido." << endl << endl;
        }

    } while (anio > f.obtenerAnioActual());
    
    system("cls");

    for (int i = 0; i < cantidadVendedor; i++)
    {
        vendedor = va.leerRegistro(i);
        id = va.BuscarId(numLegajo);

    }

    if (id > -1)
    {
        for (int i = 0; i < cantidadVentas; i++)
        {
             venta = vs.leerVenta(i);
             if (venta.getFechaVenta().getAnio() == anio && venta.getNroLegajo() == numLegajo) {

                recaudacion[venta.getFechaVenta().getMes() - 1] += venta.getTotalVenta();
                recaudacion[12] += venta.getTotalVenta();

             }
        }
        cout << "** INFORME ANUAL DE VENTAS POR VENDEDOR ** " << endl << endl;
        cout << "Vendedor: " << vm.mostrarNombreVendedor(id) << endl;
        cout << "Nro Legajo: " << numLegajo << endl;
        cout << "Año: " << anio << endl << endl;

        cout << left;
        cout << setw(12) << "MES";
        cout << setw(20) << "RECAUDACION" << endl;
        cout << "------------------------------------------------------------" << endl;

        for (int i = 0; i < 12; i++) {

            cout << setw(12) << meses[i];
            cout << "$ " << setw(20) << vm.formatearNumero(recaudacion[i]);
            cout << endl;

        }
        cout << endl << endl;

        cout << "** Total Anual : $" << vm.formatearNumero(recaudacion[12]) << " **" << endl << endl;

    }
    else {
            cout << "No se encontro el vendedor" << endl;
    }
}

//4
void Informes::ventasXVendedoresMensual()
{
    int anio, mes, pos = 0;
    int ventaRealizada = 0;
    Vendedor vendedor;
    Venta venta, * vecVenta;
    VendedorArchivo va;
    VentasArchivo vs;
    VentasManager vm;
    Fecha f;

    int cantidadVendedor = va.ContarRegistro();
    int cantidadVentas = vs.contarVentas();

    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            cout << "Año no valido." << endl << endl;
        }

    } while (anio > f.obtenerAnioActual());

    do {
        mes = validarInt("Ingrese el mes a revisar: ");

        if (mes < 1 || mes > 12) {
            cout << "Mes no valido." << endl << endl;
        }

    } while (mes < 1 || mes > 12);

    system("cls");

    for (int i = 0; i < cantidadVentas; i++)
    {
        venta = vs.leerVenta(i);
        if (venta.getFechaVenta().getAnio() == anio && venta.getFechaVenta().getMes() == mes)
        {
            ventaRealizada++;
        }
    }

    if (ventaRealizada > 0)
    {
        vecVenta = new Venta[ventaRealizada];
        if (vecVenta == nullptr)
        {
            return;
        }

        for (int i = 0; i < cantidadVentas; i++)
        {
            venta = vs.leerVenta(i);
            if (venta.getFechaVenta().getAnio() == anio && venta.getFechaVenta().getMes() == mes)
            {
                vecVenta[pos] = venta;
                pos++;
            }
        }

        Vendedor* vendedores = new Vendedor[cantidadVendedor];
        if (vendedores == nullptr)
        {
            return;
        }

        int* cantidades = new int[cantidadVendedor];
        if (cantidades == nullptr)
        {
            return;
        }

        double* recaudaciones = new double[cantidadVendedor];
        if (recaudaciones == nullptr)
        {
            return;
        }
        for (int i = 0; i < cantidadVendedor; i++)
        {
            vendedores[i] = va.leerRegistro(i);
            cantidades[i] = 0;
            recaudaciones[i] = 0.0;
        }

        for (int i = 0; i < cantidadVendedor; i++)
        {
            for (int j = 0; j < ventaRealizada; j++)
            {
                if (vecVenta[j].getNroLegajo() == vendedores[i].getNroLegajo())
                {
                    recaudaciones[i] += vecVenta[j].getTotalVenta();
                    cantidades[i]++;
                }
            }
        }

        for (int i = 0; i < cantidadVendedor - 1; i++)
        {
            for (int j = 0; j < cantidadVendedor - i - 1; j++)
            {
                if (cantidades[j] < cantidades[j + 1])
                {
                    // Intercambiar cantidades
                    int auxVenta = cantidades[j];
                    cantidades[j] = cantidades[j + 1];
                    cantidades[j + 1] = auxVenta;

                    // Intercambiar recaudaciones
                    double auxMonto = recaudaciones[j];
                    recaudaciones[j] = recaudaciones[j + 1];
                    recaudaciones[j + 1] = auxMonto;

                    // Intercambiar vendedores
                    Vendedor auxVendedor = vendedores[j];
                    vendedores[j] = vendedores[j + 1];
                    vendedores[j + 1] = auxVendedor;
                }
            }
        }

        cout << "** INFORME MENSUAL DE VENTAS POR VENDEDOR ** " << endl << endl;
        cout << "Año: " << anio << endl;
        cout << "Mes: " << mes << endl << endl;

        cout << left;
        cout << setw(20) << "VENDEDOR";
        cout << setw(14) << "CANTIDAD";
        cout << setw(20) << "RECAUDACION" << endl;
        cout << "------------------------------------------------------------" << endl;

        for (int i = 0; i < cantidadVendedor; i++)
        {
            if (cantidades[i] > 0)
            {
                cout << setw(22) << vendedores[i].getApellidoNombre();
                cout << setw(12) << cantidades[i];
                cout << "$ " << setw(20) << vm.formatearNumero(recaudaciones[i]);
                cout << endl;
            }
        }
        cout << endl << endl;

        delete[] vecVenta;
        delete[] vendedores;
        delete[] cantidades;
        delete[] recaudaciones;
    }
    else
    {
        cout << "No se encontraron ventas en el mes y año ingresado" << endl;
    }
}

//5
void Informes::ventasXSucursalAnual()
{
    VentasManager vm; 
    VentasArchivo va; 
    SucursalArchivo sa;
    SucursalManager sm;
    Sucursal s;
    int i, cant;
    double recaudacion[13] = { 0 };
    string meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };
    Fecha f;
    bool existeSucursal = false;

    int anio, id;

    cout << "** INFORME ANUAL DE VENTAS POR SUCURSAL ** " << endl;
    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            cout << "Año no valido." << endl << endl;
        }

    } while (anio > f.obtenerAnioActual());
    
    id = validarInt("Ingrese Id de Sucursal: ");

    cant = sa.contarRegistro();
    for (i = 0; i < cant; i++) {
        s = sa.leerRegistro(i);
        if (s.getIdSucursal() == id) {
            existeSucursal = true;
        }
    }

    if(existeSucursal == true){

		int cantidad = va.contarVentas();
		for (i = 0; i < cantidad; i++) {
			Venta reg = va.leerVenta(i);
			if (reg.getFechaVenta().getAnio() == anio && reg.getIdSucursal() == id) {
				recaudacion[reg.getFechaVenta().getMes() - 1] += reg.getTotalVenta();
				recaudacion[12] += reg.getTotalVenta();

			}

		}

		system("cls");

		cout << "** INFORME ANUAL DE VENTAS POR SUCURSAL ** " << endl << endl;
		cout << "Año: " << anio << endl;
		cout << "Sucursal: " << vm.mostrarNombreSucursal(id) << endl;
		cout << endl;

		cout << left;
		cout << setw(12) << "MES";
		cout << setw(20) << "RECAUDACION" << endl;
		cout << "------------------------------------------------------------" << endl;

		for (i = 0; i < 12; i++) {

			cout << setw(12) << meses[i];
			cout << "$ " << setw(20) << vm.formatearNumero(recaudacion[i]);
			cout << endl;

		}
		cout << endl << endl;

		cout << "** TOTAL ANUAL : $" << vm.formatearNumero(recaudacion[12]) << " **" << endl << endl;

    }
    else {
        cout << "Sucursal no valida." << endl << endl;
    }

}

//6.1
void Informes::ventasTodasLasSucursalesMensual()
{
    int anio, mes, contVentas;
    double acuMes;
    Fecha f;

    Venta regV;
    VentasArchivo va;
    VentasManager vm;
    int cantV = va.contarVentas();

    Sucursal reg;
    SucursalArchivo sa;
    int cont = sa.contarRegistro();

    cout << " INFORME MENSUAL DE VENTAS POR SUCURSAL  " << endl;
    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) { 
            cout << "Año no valido." << endl << endl;
        } 

    } while (anio > f.obtenerAnioActual()); 

    do {
        mes = validarInt("Ingrese el mes a revisar: ");

        if (mes < 1 || mes > 12) {
            cout << "Mes no valido." << endl << endl;
        }

    } while (mes < 1 || mes > 12);
    system("cls");


    cout << " INFORME MENSUAL DE VENTAS POR SUCURSAL  " << endl << endl;
    cout << "Año: " << anio << endl;
    cout << "Mes: " << mes << endl;

    cout << endl;

    cout << left;
    cout << setw(25) << "SUCURSAL";
    cout << setw(20) << "CANTIDAD DE VENTAS";
    cout << setw(20) << "RECAUDACION" << endl;
    cout << "------------------------------------------------------------" << endl;

    double total = 0;
    int totalCantV = 0;
    for (int i = 0; i < cont; i++)
    {
        reg = sa.leerRegistro(i);
        acuMes = 0;
        contVentas = 0;

        for (int j = 0; j < cantV; j++)
        {
            regV = va.leerVenta(j);
            if (regV.getFechaVenta().getAnio() == anio && regV.getFechaVenta().getMes() == mes) {
                if (regV.getIdSucursal() == reg.getIdSucursal()) {
                    acuMes += regV.getTotalVenta();
                    contVentas++;
                }
            }
        }
        if (acuMes > 0) {
            cout << setw(25) << reg.getNombre();
            cout << setw(20) << contVentas;
            cout << "$ " << setw(20) << vm.formatearNumero(acuMes);
            cout << endl;
        }

        total += acuMes;
        totalCantV += contVentas;
    }
    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << setw(25) << "TOTAL : ";
    cout << setw(20) << totalCantV;
    cout << "$ " << setw(20) << vm.formatearNumero(total);
    cout << endl;

}

//6.2
void Informes::ventasTodasLasSucursalesAnual()
{
    int anio, cantAnual;
    double acuAnio;
    Fecha f;

    Venta regV;
    VentasArchivo va;
    VentasManager vm;
    int cantV = va.contarVentas();

    Sucursal reg;
    SucursalArchivo sa;
    int cont = sa.contarRegistro();

    cout << " INFORME ANUAL DE VENTAS POR SUCURSAL  " << endl;
    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            cout << "Año no valido." << endl << endl;
        }

    } while (anio > f.obtenerAnioActual());
    system("cls");

    cout << " INFORME ANUAL DE VENTAS POR SUCURSAL  " << endl << endl;
    cout << "Año: " << anio << endl;

    cout << endl;

    cout << left;
    cout << setw(20) << "SUCURSAL";
    cout << setw(27) << "CANTIDAD DE VENTAS";
    cout << setw(20) << "RECAUDACION" << endl;
    cout << "------------------------------------------------------------" << endl;

    double totalAnio = 0;
    int totalAnual = 0;

    for (int i = 0; i < cont; i++)
    {
        reg = sa.leerRegistro(i);
        cantAnual = 0;
        acuAnio = 0;

        for (int j = 0; j < cantV; j++)
        {
            regV = va.leerVenta(j);
            if (regV.getFechaVenta().getAnio() == anio) {
                if (regV.getIdSucursal() == reg.getIdSucursal()) {
                    acuAnio += regV.getTotalVenta();
                    cantAnual++;
                }
            }
        }
        if (acuAnio > 0) {
            cout << setw(25) << reg.getNombre();
            cout << setw(20) << cantAnual;
            cout << "$ " << setw(20) << vm.formatearNumero(acuAnio);
            cout << endl;
        }

        totalAnio += acuAnio;
        totalAnual += cantAnual;

    }
    if (totalAnio > 0) {
        cout << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << setw(25) << "TOTAL : ";
        cout << setw(20) << totalAnual;
        cout << "$ " << setw(20) << vm.formatearNumero(totalAnio);
        cout << endl;
    }
    else {
        cout << "No se encontraron ventas para el año " << anio << endl;
    }
}

//7
void Informes::rankingVentasXModelo()
{
    int anio, cantVen, cantVeh;
    bool sinVentas = true;
    Fecha f;

    VentasArchivo archiVen("Ventas.dat");
    Venta venReg;
    cantVen = archiVen.contarVentas();

    VehiculosArchivo archiVeh("Vehiculos.dat");
    Vehiculo vehReg;
    cantVeh = archiVeh.contarRegistros();

    vector<int> ventas(cantVeh, 0);
    vector<string> marca(cantVeh);
    vector<string> modelo(cantVeh);

    cout << "- Ranking Anual de Ventas por Modelo -" << endl;
    cout << "---------------------------------------" << endl;
    do {
        anio = validarInt("Ingrese el Año que desea Consultar: ");

        if (anio > f.obtenerAnioActual()) {
            cout << "Año no valido." << endl << endl;
        }

    } while (anio > f.obtenerAnioActual());

    for (int i = 0; i < cantVen; i++) {
        venReg = archiVen.leerVenta(i);
        if (venReg.getFechaVenta().getAnio() == anio) {
            ventas[venReg.getIdVehiculo() - 1] += 1;
            sinVentas = false;
            for (int j = 0; j < cantVeh; j++) {
                vehReg = archiVeh.leerRegistro(j);
                if (venReg.getIdVehiculo() == vehReg.getIdVehiculo()) {
                    marca[venReg.getIdVehiculo() - 1] = vehReg.getMarca();
                    modelo[venReg.getIdVehiculo() - 1] = vehReg.getModelo();
                }
            }
        }
    }
    if (sinVentas) {
        cout << endl << "* No existen Registros de Ventas para ese Año *" << endl;
    }
    else {
        for (int i = 0; i < cantVeh - 1; ++i) {
            for (int j = 0; j < cantVeh - i - 1; ++j) {
                if (ventas[j] < ventas[j + 1]) {
                    // Intercambiar ventas
                    int auxVentas = ventas[j];
                    ventas[j] = ventas[j + 1];
                    ventas[j + 1] = auxVentas;
                    // Intercambiar marca
                    string auxMarca = marca[j];
                    marca[j] = marca[j + 1];
                    marca[j + 1] = auxMarca;
                    // Intercambiar modelo
                    string auxModelo = modelo[j];
                    modelo[j] = modelo[j + 1];
                    modelo[j + 1] = auxModelo;
                }
            }
        }
        system("cls");
        cout << "- Ranking Anual de Ventas por Modelo -" << endl;
        cout << "--------------------------------------" << endl;
        cout << "------------- Año: " << anio << " --------------" << endl;
        cout << left;
        cout << setw(12) << "Marca";
        cout << setw(15) << "Modelo";
        cout << setw(10) << "Cantidad";
        cout << endl;
        for (int j = 0; j < cantVeh; j++) {
            if (ventas[j] > 0) {
                cout << setw(12) << marca[j];
                cout << setw(18) << modelo[j];
                cout << setw(10) << ventas[j];
                cout << endl;
            }
        }
    }
    cout << endl;
}