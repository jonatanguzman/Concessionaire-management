#pragma once
#include "ClienteArchivo.h"

class ClienteManager
{
private:
	ClienteArchivo _archivo;
public:
	ClienteManager();
	void Menu();
	Cliente crearCliente();
	Cliente crearCliente(long long dni);
	void mostrarCliente(Cliente reg);
	void mostrarClienteEnLinea(Cliente reg);
	void agregarCliente();
	void encabezadoClientes();
	void menuListado();
	void listarClientes();
	void listarClientesXApellido();
	void ordenar(std::vector <Cliente>& vec, int cant);
	int buscarCliente(long dni);
	void editarCliente();
	void backupArchivo();
	void restaurarBackup();
	void borrarCliente();
	void buscadorDeClientes();
	bool DniRepetido(long long idPersona);
};

