#pragma once
#include <vector>
#include "VentasArchivo.h"

class VentasManager
{
private:
	VentasArchivo _archivo;
public:
	VentasManager();
	void Menu();

	Venta crearVenta();
	void mostrarVenta(Venta reg);
	void mostrarVentaEnLinea(Venta reg);
	void agregarVenta();
	void encabezadoListadoVentas();
	void menuListados();
	void listarVentas();
	void ordenar(std::vector<Venta>& vec, int cant);  
	void listarVentasXFecha();
	int buscarVenta(int idVenta);
	void editarVenta();
	void backupArchivo();
	void restaurarBackup();
	void borrarVenta();
	void restaurarVentaBorrada();
	
	int validarCliente(long long dni);
	void crearNuevoCliente(long long dni);
	void mostrarClienteAsociado(int pos);
	std::string mostrarNombreCliente(long long dni);
	
	int validarSucursal(int id);
	void mostrarSucursalAsociada(int pos);
	std::string mostrarNombreSucursal(int id);
	
	int validarVendedor(int nroLegajo);
	void mostrarVendedorAsociado(int pos);
	std::string mostrarNombreVendedor(int nrolegajo);
	
	bool validarVehiculo(int& id);
	void mostrarVehiculoAsociado(int id);
	std::string mostrarNombreVehiculo(int id);
	
	float obtenerPrecioVehiculo(int id);
	float calcularPrecioTotal(float gastos, float precio);
	
	std::string formatearNumero(double numero);

	void buscadorDeVentas();
	void buscarVentaPorID();
	void buscarVentaPorFecha();


};


