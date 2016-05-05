/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejoDatos.h
 * Author: bintu
 *
 * Created on 4 de mayo de 2016, 13:11
 */

#ifndef MANEJODATOS_H
#define MANEJODATOS_H
#include <iostream>
#include <vector>

using namespace std;
struct usuario{
    string idUsuario;
    string password;
    string tipoAcceso;
};

struct horario{
    string id;
    string materia;
    string filaHora;
    string columnaDia;
    string aula;
};
struct alumno{
    string cedula;
    string materia;
};

struct aula{
    string codigoAula;
    string capacidad;
    
};

struct materia{
    string nombre;
    string creditos;
    string idDocente;
};


struct docente{
    string cedula;
    string nombre;
    
};


vector<string> split(string palabraAnalizar, char separador);
void escribirDatos(string aula,materia materia, int filaHora, int columnaDia);
void escribirHorarioEstudiante(alumno estudiante,horario horarioEstuduiante);
vector<usuario> obetnerIngreso();
vector<horario> obtenerHorario();
vector<alumno> obtenerEstudiantes();
vector<materia> obetnerMaterias();
vector<aula> obtenerAulas();





#endif /* MANEJODATOS_H */

