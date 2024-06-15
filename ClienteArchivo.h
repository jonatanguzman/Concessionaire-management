#pragma once
#include "Cliente.h" 
#include <string> 

class ClienteArchivo
{
private:
	char _nombreArchivo[40];
public:
	ClienteArchivo();
	ClienteArchivo(std::string n);
	std::string getNombreArchivo();
	Cliente leerCliente(int pos);
	int contarClientes();
	bool guardarCliente(Cliente reg);
	bool sobreescribirCliente(Cliente reg, int pos);
};

