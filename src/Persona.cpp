#include "Persona.h"
#include <stdio.h>
#include <string.h>

Persona::Persona()
{
}

///Setters
void Persona::setNombre(char* nombre)
{
    strcpy(_nombre, nombre);
}
void Persona::setApellido(char* apellido)
{
    strcpy(_apellido, apellido);
}
void Persona::setMail(char* direcionDeMail)
{
    strcpy(_direccionDeMail, direcionDeMail);
}
void Persona::setNumTelefono(char* num)
{
    strcpy(_numTelefono, num);
}
void Persona::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}
///Getters
char* Persona::getNombre()
{
    return _nombre;
}
char* Persona::getApellido()
{
    return _apellido;
}
char* Persona::getMail()
{
    return _direccionDeMail;
}
char* Persona::getNumTelefono()
{
    return _numTelefono;
}
bool Persona::getEliminado()
{
    return _eliminado;
}
