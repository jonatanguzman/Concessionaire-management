#pragma once
#include <iostream>
#include<string>
#include "Direccion.h"
#include "Sucursal.h"
#include "VentasManager.h"
#include "VendedorManager.h"
#include "ClienteManager.h"
#include "VehiculosManager.h"
#include "SucursalManager.h"
#include "Informes.h"
#include "Configuracion.h"

class Sistema
{
private:
	VehiculosManager _vehiculos;
	VentasManager _ventas;
	ClienteManager _clientes;
	VendedorManager _vendedores;
	SucursalManager _sucursales;
	Informes _informes;
	Configuracion _configuracion;
	
public:
	Sistema();
	void Menu();
	void Creditos();
};

