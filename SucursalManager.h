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
	void ordenarNombre(Sucursal obj[], int tam);
	void ordenarID(Sucursal obj[], int tam);
	void listarPorID();
	void listarPorNombre();
	void listarRegistros();
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
	void realizarBackupSucursal();
	void restaurarBackupSucursal();
};