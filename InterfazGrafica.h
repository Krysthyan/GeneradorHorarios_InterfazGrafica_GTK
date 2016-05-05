/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InterfazGrafica.h
 * Author: bintu
 *
 * Created on 4 de mayo de 2016, 10:53
 */

#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H
#include <gtk/gtk.h>
#include <iostream>


struct tablaDias{
    GtkTreeViewColumn *lunes;
    GtkTreeViewColumn *martes;
    GtkTreeViewColumn *miercoles;
    GtkTreeViewColumn *jueves;
    GtkTreeViewColumn *viernes;
};
struct ventana{
    GtkBuilder *constructor;
    GtkWidget *ventana;
    GtkButton *ingresar;
    GtkEntry *cedula;
    GtkEntry *password;
    GtkButton *generar;
    GtkTreeView *tabla;
    struct tablaDias *dias;
};



using namespace std;
void destruir(GtkWidget *ventana);
GtkTreeModel *create_model ();
void ventanaPrincipal();
void validacionIngreso(string cedula);
void ventanaEstudiante();
void ventanaAdministrador();

void ingreso(GtkButton *ingresar, ventana *ventanaPrincipal);
void construirHorario(GtkButton *boton, ventana *ventanaAdministrador);
#endif /* INTERFAZGRAFICA_H */

