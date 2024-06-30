#pragma once
#include "VendedorArchivo.h"

class VendedorManager {
private:
    VendedorArchivo _archivo;
public:
    VendedorManager();

    void PlanillaVendedor();

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

    void OrdenarPorAntiguedad(Vendedor* obj, int cantidad, bool criterio(int, int));
    void ListarAntiguedad();
    void OrdenarPorApellido(Vendedor* obj, int cantidad, bool criterio(std::string, std::string));
    void ListarApellido();
    void menuListar();
    void MostrarPantalla();
};
