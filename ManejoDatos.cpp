/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ManejoDatos.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


vector<string> split(string palabraAnalizar, char separador){
    vector<string> alterno;
    stringstream analizador(palabraAnalizar);
    string tok;

    while(getline(analizador, tok, separador)) {
      alterno.push_back(tok);
    }

    return alterno;
}
void escribirDatos(string aula,materia materia, int filaHora, int columnaDia){
    ofstream archivoGuardar;
    archivoGuardar.open("horario.csv",ios::app);
    archivoGuardar <<aula<<","<<materia.idDocente<<","<< materia.nombre <<"," << filaHora<<","<< columnaDia<< endl;
    archivoGuardar.close();
}
void escribirHorarioEstudiante(alumno estudiante,horario horarioEstuduiante){
    ofstream archivoGuardar;
    archivoGuardar.open("horarioEstudiantes/"+estudiante.cedula+".cvs",ios::app);
    archivoGuardar <<horarioEstuduiante.aula<<","<<horarioEstuduiante.materia<<","<< horarioEstuduiante.filaHora
            <<"," << horarioEstuduiante.columnaDia<< endl;
    archivoGuardar.close();
}
vector<usuario> obetnerIngreso(){
    fstream acceso;
    string fraseIngreso;
    acceso.open("usuarios.csv",ios::in);
    vector<usuario> arregloUsuarios;
    vector<string> alterno;

    
    while(!acceso.eof()){
        
        getline (acceso,fraseIngreso);
        if(fraseIngreso.size()>1){
            alterno=split(fraseIngreso, ',');
            struct usuario *usuarioTem=new usuario();

            usuarioTem->idUsuario=alterno[0];
            usuarioTem->password=alterno[1];
            usuarioTem->tipoAcceso=alterno[2];
            arregloUsuarios.push_back(*usuarioTem);
            delete usuarioTem;
            usuarioTem = nullptr;
        }
        
    }
    acceso.close();
    return arregloUsuarios;
}
vector<horario> obtenerHorario(){
    fstream horarios;
    string frase;
    horarios.open("horario.csv",ios::in);
    vector<horario> arregloHorario;
    vector<string> alterno;
    while(!horarios.eof()){
        
        getline (horarios,frase);
        
        if(frase.size()>1){
            alterno=split(frase, ',');
            struct horario *horarioTem=new horario();

            horarioTem->aula=alterno[0];
            horarioTem->id=alterno[1];
            horarioTem->materia=alterno[2]; 
            horarioTem->filaHora=alterno[3];
            horarioTem->columnaDia=alterno[4];
            arregloHorario.push_back(*horarioTem);
            delete horarioTem;
            horarioTem = nullptr;
            alterno.clear();
        }
        
    }
    horarios.close();
    return arregloHorario;
}
vector<alumno> obtenerEstudiantes(){
    fstream estudiantes;
    string frase;
    estudiantes.open("alumnos.csv",ios::in);
    vector<alumno> arregloEstudiantes;
    vector<string> alterno;
    while(!estudiantes.eof()){
        
        getline (estudiantes,frase);
        if(frase.size()>1){
            alterno=split(frase, ',');
            struct alumno *estudiante=new alumno();

            estudiante->cedula=alterno[0];
            estudiante->materia=alterno[1];
            arregloEstudiantes.push_back(*estudiante);
            delete estudiante;
            estudiante = nullptr;
            alterno.clear();
        }
        
    }
    estudiantes.close();
    alterno.clear();
    return arregloEstudiantes;
}
vector<materia> obetnerMaterias(){
    fstream materias;
    string fraseMaterias;
    materias.open("materias.csv",ios::in);
    vector<materia> arregloMaterias;
    vector<string> alterno;

    while(!materias.eof()){
        
        getline (materias,fraseMaterias);
        if(fraseMaterias.size()>1){
            alterno=split(fraseMaterias, ',');
            struct materia *materiaTem=new materia();
            materiaTem->nombre=alterno[0];
            materiaTem->creditos=alterno[1];
            materiaTem->idDocente=alterno[2];

            arregloMaterias.push_back(*materiaTem);
            delete materiaTem;
            materiaTem = nullptr;
        }
        
    }
    cout<<"hola mundo"<<endl;
    materias.close();
    alterno.clear();
    return arregloMaterias;
}
vector<aula> obtenerAulas(){
    fstream aulas;
    string fraseAula;
    aulas.open("aulas.csv",ios::in);
    vector<aula> arregloAulas;
    vector<string> alterno;

    
    while(!aulas.eof()){
        
        getline (aulas,fraseAula);
        if(fraseAula.size()>1){
            alterno=split(fraseAula, ',');
            struct aula *aulaTem=new aula();
            aulaTem->codigoAula=alterno[0];
            aulaTem->capacidad=alterno[1];
            arregloAulas.push_back(*aulaTem);
            delete aulaTem;
            aulaTem = nullptr;  
        }
              
    }
    aulas.close();
    alterno.clear();
    return arregloAulas;
}
