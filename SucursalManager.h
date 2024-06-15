#pragma once
#include "SucursalArchivo.h"

class SucursalManager
{
private:
	SucursalArchivo _archivo;
public:
	SucursalManager();
	
	bool validarIDUnico(int id);
	void agregarRegistro();
	void listarRegistros();
	void ordenarNombre(Sucursal obj[], int tam);
	void buscarSucursal();
	void buscarSucursalID();
	void buscarSucursalNombre();
	void Menu();
	void salidaEnPantalla();
	Sucursal crearRegistro();
	void mostrarRegistro(Sucursal reg);
	void editarRegistro();
	void bajaLogica();
	void backupArchivo();
	void restaurarBackup();
};