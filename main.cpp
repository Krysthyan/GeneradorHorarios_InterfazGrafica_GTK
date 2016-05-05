/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bintu
 *
 * Created on 30 de abril de 2016, 11:57
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <gtk/gtk.h>
#include "ManejoDatos.h"
#include "InterfazGrafica.h"



using namespace std;


/*
 * estructuras de la interfaz grafica 
 */

struct posicion{
    int filaHora;
    int columnaDia;
    int verficarSalto;
    int numMateria;
    string aulaIngreso;
};

vector<materia> arregloMaterias;

void recursividadAsignacionMateria(posicion *datosPos, materia materia);
void recursividadMateria(posicion *datosPos);


void generarHorarioEstudiante(string cedulaIngresada){
    vector<alumno> arregloEstudiantes=obtenerEstudiantes();
    vector <horario> arregloHorario=obtenerHorario();
    
    for (alumno estudiante : arregloEstudiantes) {
        if(estudiante.cedula==cedulaIngresada){
            for (horario horario : arregloHorario) {
                if(horario.materia==estudiante.materia){
                    escribirHorarioEstudiante(estudiante,horario);
                }
                
            }

        }
            

    } 
}

/// CODIGO PARA GENERAR EL HORARIO RECURSIVAMENTE
void retocederUnpaso(posicion *datosPos, materia materia){
    if(datosPos->columnaDia==6){
        datosPos->filaHora++;
        datosPos->columnaDia=0;
    }
    if(!(datosPos->filaHora==5 && datosPos->columnaDia>=3)){
        escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,datosPos->columnaDia);
        if(datosPos->columnaDia+2>=5){
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora+1,1);
            datosPos->verficarSalto=1;
            datosPos->filaHora+=1;
            datosPos->columnaDia=0;
            datosPos->numMateria+=1;
            recursividadMateria(datosPos);
        }else{
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,datosPos->columnaDia+2);
            datosPos->verficarSalto=1;
            datosPos->columnaDia+=1;
            datosPos->numMateria+=1;
            recursividadMateria(datosPos);
        }
    }
}
void avanzarUnPaso(posicion *datosPos, materia materia){
    if(datosPos->columnaDia==5){
        datosPos->filaHora++;
        datosPos->columnaDia=0;
    }
     if(!(datosPos->filaHora==5 && datosPos->columnaDia>=3)){
         escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,datosPos->columnaDia);
        if(datosPos->columnaDia+2>=5){
            datosPos->filaHora++; 
            datosPos->columnaDia=0;
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,datosPos->columnaDia+1);                
            datosPos->columnaDia+=2;
        }else{
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,datosPos->columnaDia+2);
            datosPos->columnaDia+=3;
        }
        datosPos->verficarSalto=0;
        datosPos->numMateria+=1;
        recursividadMateria(datosPos);
     }
}
void creditosCuatro(posicion *datosPos, materia materia){
    if(datosPos->verficarSalto==0){          
        retocederUnpaso(datosPos, materia);
    }else{
    avanzarUnPaso(datosPos, materia);
    }
}
void creditosSeis(posicion *datosPos, materia materia){
    if(datosPos->filaHora<5){
        if(datosPos->columnaDia==0){
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,0);
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,2);
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,4);
        }else{
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora+1,0);
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora+1,2);
            escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora+1,4);
        }
        
        datosPos->filaHora+=2;
        datosPos->columnaDia=0;
        datosPos->numMateria+=1;
        recursividadMateria(datosPos);
    }else{
        datosPos->filaHora+=1;
        datosPos->columnaDia=0;
        recursividadMateria(datosPos);
    }
    
}
void creditosDos(posicion *datosPos, materia materia){
    escribirDatos(datosPos->aulaIngreso,materia,datosPos->filaHora,datosPos->columnaDia);
    if(datosPos->verficarSalto==0){ 
        datosPos->columnaDia+=2;
        datosPos->numMateria+=1;
        recursividadMateria(datosPos);
    }else{
        datosPos->columnaDia+=1;
        datosPos->numMateria+=1;
        recursividadMateria(datosPos);
    } 
}

void recursividadMateria(posicion *datosPos){
    if(datosPos->filaHora==6 )
        return;
    
    if(datosPos->numMateria >= arregloMaterias.size())
        return;

    recursividadAsignacionMateria(datosPos, arregloMaterias.at(datosPos->numMateria));
}

void recursividadAsignacionMateria(posicion *datosPos, materia materia){
    cout<<materia.nombre<<endl;
    if(materia.creditos=="4" ){
        creditosCuatro(datosPos, materia);
    }else if(materia.creditos=="6"){
        creditosSeis(datosPos, materia);    
    }else if(materia.creditos=="2"){
        creditosDos(datosPos, materia); 
    }
}



void generadorHorario(){
    int numeroAvanceMateria=0;
    arregloMaterias=obetnerMaterias();
    cout<<"hola mundo"<<endl;
    vector<aula> arregloAulas=obtenerAulas();
    
    for (aula elem : arregloAulas){
        posicion *pos=new posicion();
        pos->filaHora=0;
        pos->columnaDia=0;
        pos->verficarSalto=0;
        pos->aulaIngreso=elem.codigoAula;
        pos->numMateria=numeroAvanceMateria; 
        recursividadMateria(pos);
        numeroAvanceMateria=pos->numMateria;
        delete pos;
        pos = nullptr;
    }
    arregloMaterias.clear();
    arregloAulas.clear();
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);
    //generadorHorario();
    generarHorarioEstudiante("0104645676");
    ventanaPrincipal();
    
    
    
    return 0;
}

