#pragma once
#include "VendedorArchivo.h"

class VendedorManager {
private:
    VendedorArchivo _archivo;
public:
    VendedorManager();

    Vendedor CrearVendedor();
    void MostrarVendedor(Vendedor vendedor);
    void AgregarVendedor();
    void ListarVendedor();
    void BuscarVendedor();
    void EditarVendedor();
    void EliminarVendedor();
    void realizarBackupVendedores();
    void restaurarBackupVendedores();

    void Menu();
    bool LegajoRepetido(int idLegajo);
    bool DniRepetido(long long idPersona);
};
