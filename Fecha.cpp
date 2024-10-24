#include "Fecha.h"
Fecha::Fecha(int dia, int mes, int anio)
{
    _dia = dia;
    _mes = mes;
    _anio = anio;
    validarFecha();
}

Fecha::Fecha()
{
    fechaPorDefecto();
}

void Fecha::fechaPorDefecto()
{
    _dia = 01;
    _mes = 01;
    _anio = 2023;
}

void Fecha::AnioBiscieto()
{
    if (_anio % 400 == 0 || (_anio % 100 != 0 && _anio % 4 == 0))
    {
        _vecMeses[1] = 29;
    }
}

bool Fecha::validarDia(){
    return _dia > 0 && _dia <= _vecMeses[_mes];
    }

bool Fecha::validarMes(){
    return _mes > 0 && _mes <= 12;
    }

bool Fecha::validarAnio(){
    return _anio > 0;
    }


void Fecha::validarFecha()
{
    AnioBiscieto();
    if (!(validarDia() && (validarMes()) && validarAnio()))
    {
        fechaPorDefecto();
    }
}

void Fecha::agregarDia()
{
    _dia += 1;

    if (_dia > _vecMeses[_mes])
    {
        _dia -= _vecMeses[_mes];
        _mes += +1;
        if (_mes == 13)
        {
            _mes -= 12;
            _anio += 1;
        }
    }
}

void Fecha::restarDia()
{
    _dia -= 1;
    if (_dia == 0)
    {
        _mes -= 1;
        if (_mes == 0)
        {
            _mes = 12;
            _anio -= 1;
            _dia = 31;
        }
        else
        {
            _dia = _vecMeses[_mes];
        }
    }
}

int Fecha::getDia()
{
    return _dia;
}
int Fecha::getMes()
{
    return _mes;
}
int Fecha::getAnio()
{
    return _anio;
}

void Fecha::agregarDias(int dias)
{
    _dia += dias;
    while (_dia > _vecMeses[_mes - 1])
    {
        if (_dia > _vecMeses[_mes - 1])
        {
            _dia -= _vecMeses[_mes - 1];
            _mes += +1;
            if (_mes == 13)
            {
                _mes -= 12;
                _anio += 1;
            }
        }
    }
}
std::string Fecha::toString()
{
    std::string fechaToString = std::to_string(getDia())+"/"+std::to_string(getMes())+"/"+std::to_string(getAnio());
    return fechaToString;
}


