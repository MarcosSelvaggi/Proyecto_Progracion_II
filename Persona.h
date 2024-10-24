#pragma once


class Persona
{
    public:
        Persona();
        void setNombre(char* nombre);
        void setApellido(char* apellido);
        void setMail(char* direcionDeMail);
        void setNumTelefono(char* num);
        void setEliminado(bool eliminado);


        char* getNombre();
        char* getApellido();
        char* getMail();
        char* getNumTelefono();
        bool getEliminado();

    protected:
        char _nombre[25];
        char _apellido[25];
        char _direccionDeMail[100] = "";
        char _numTelefono[25];
        bool _eliminado = false;
};
