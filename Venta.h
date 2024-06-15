#pragma once
#include "Fecha.h"
class Venta
{
private:
	int _idVenta;
	Fecha _fechaVenta;
	long long _dniCliente;
	int _idSucursal;
	int _nroLegajo;
	int _idVehiculo;
	float _gastosAdm;
	double _totalVenta;
	bool _eliminado;

public:
	Venta();
	Venta(int idVenta, Fecha fechaVenta, long long dni, int idSucursal, int nroLegajo, int idVehiculo, float gastos, double total, bool eliminado);
	
	//getters
	int getIdVenta();
	Fecha getFechaVenta();
	long long getDniCliente();
	int getIdSucursal();
	int getNroLegajo();
	int getIdVehiculo();
	float getGastosAdm();
	double getTotalVenta();
	bool getEliminado();
	
	//setters
	void setIdVenta(int id);
	void setFechaVenta(Fecha f);
	void setDniCliente(long long dni);
	void setIdSucursal(int id); 
	void setNroLegajo(int nro);
	void setIdVehiculo(int id); 
	void setGastosAdm(float gastos);
	void setTotalVentas(double total);
	void setEliminado(bool e);

	int contarDigitos(long long num);
	bool validar(long long dni);


};

