#pragma once
#include <string>

class Fecha
{

private:
    int _dia;
    int _mes;
    int _anio;
    int _vecMeses[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    void agregarDia();
    void restarDia();
    void validarFecha();
    void fechaPorDefecto();
    void AnioBiscieto();
    bool validarDia();
    bool validarMes();
    bool validarAnio();

public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();
    void agregarDias(int dias);
    std::string toString();

};
