#pragma once
#include <string>

///ClaseVehiculo
class Vehiculo {
private:
    int _idVehiculo;
    char _marca[40];
    char _modelo[40];
    char _version[40];
    char _color[40];
    int _anioFabricacion;
    int _stock;
    float _precioUnidad;
    bool _estado;
public:
    ///Constructor
    Vehiculo();
    Vehiculo(int i, std::string m, std::string mo, std::string v, std::string c, int a, int s, float p, bool e);
    ///set`s
    void setIdVehiculo(int i);
    void setMarca(std::string m);
    void setModelo(std::string mo);
    void setVersion(std::string v);
    void setColor(std::string c);
    void setAnioFabricacion(int a);
    void setStock(int s);
    void setPrecioUnidad(float p);
    void setEstado(bool e);

    ///Get`s
    int getIdVehiculo();
    std::string getMarca();
    std::string getModelo();
    std::string getVersion();
    std::string getColor();
    int getAnioFabricacion();
    int getStock();
    float getPrecioUnidad();
    bool getEstado();
};