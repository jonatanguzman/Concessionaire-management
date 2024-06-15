#pragma once
#include <string>
#include "Venta.h"
class VentasArchivo
{
private:
	char _nombreArchivo[40];
public:
	VentasArchivo();
	VentasArchivo(std::string n);
	std::string getNombreArchivo();
	Venta leerVenta(int pos);
	int contarVentas();
	bool guardarVenta(Venta reg);
	int leerUltimoId();
	bool sobreescribirVenta(Venta reg, int pos);

};

