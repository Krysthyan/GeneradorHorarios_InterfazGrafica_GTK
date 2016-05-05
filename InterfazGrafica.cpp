/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "InterfazGrafica.h"
#include "ManejoDatos.h"
#include <vector>
#include <cstdlib>
using namespace std;

enum {
    COL_LUNES,
    COL_MARTES,
    COL_MIERCOLES,
    COL_JUEVES,
    COL_VIERNES,
    COL_TOTAL
};

GtkTreeViewColumn *lunes;
GtkTreeViewColumn *martes;
GtkTreeViewColumn *miercoles;
GtkTreeViewColumn *jueves;
GtkTreeViewColumn *viernes;

GtkTreeStore *model;
GtkTreeIter top;
GtkTreeIter child;
GtkCellRenderer *renderer;

GtkBuilder *constructor;
GtkWindow *ventana1;
GtkTreeView *tabla;
GtkLabel *horario;
GtkButton *boton;

void destruir(GtkWidget *ventana){
     gtk_widget_destroy(ventana);
}






void ingreso(GtkButton *ingresar, ventana *ventanaPrincipal){
    // solo copiado del proyecto acterior toda realizar toda la adapacion
    
    const gchar *cedulaString;
    const gchar *passwordString;
    int comprobar=1;
    vector <struct horario> horarios=obtenerHorario();
    vector<struct horario> horarioTem;

    ventanaPrincipal->cedula=GTK_ENTRY(gtk_builder_get_object(ventanaPrincipal->constructor,"entryCedula"));
    ventanaPrincipal->password=GTK_ENTRY(gtk_builder_get_object(ventanaPrincipal->constructor,"entryCedula"));
    cedulaString=gtk_entry_get_text(ventanaPrincipal->cedula);
    passwordString=gtk_entry_get_text(ventanaPrincipal->password);
    
    gtk_widget_destroy(ventanaPrincipal->ventana);
    delete ventanaPrincipal;
    
    
    
    constructor = gtk_builder_new();
    GError *err = NULL; /* It is mandatory to initialize to NULL */

    //gtk_builder_add_from_file(constructor, "tabla.glade", NULL);

    if(0 == gtk_builder_add_from_file (constructor, "admin.glade", &err))
    {
        /* Print out the error. You can use GLib's message logging */
        fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);
        /* Your error handling code goes here */
    }
    
    ventana1 = GTK_WINDOW(gtk_builder_get_object(constructor,"ventana"));
    tabla = GTK_TREE_VIEW(gtk_builder_get_object(constructor,"tablaHorario"));

    lunes = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(constructor,"columLunes"));
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_column_pack_start (lunes, renderer, TRUE);
    gtk_tree_view_column_add_attribute  (lunes, renderer, "text",COL_LUNES);
    martes = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(constructor,"columMartes"));
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_column_pack_start (martes, renderer, TRUE);
    gtk_tree_view_column_add_attribute  (martes, renderer, "text",COL_MARTES);
    miercoles = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(constructor,"columMiercoles"));
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_column_pack_start (miercoles, renderer, TRUE);
    gtk_tree_view_column_add_attribute  (miercoles, renderer, "text",COL_MIERCOLES);
    jueves=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(constructor,"columJueves"));
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_column_pack_start (jueves, renderer, TRUE);
    gtk_tree_view_column_add_attribute  (jueves, renderer, "text",COL_JUEVES);
    viernes=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(constructor,"columViernes"));
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_column_pack_start (viernes, renderer, TRUE);
    gtk_tree_view_column_add_attribute  (viernes, renderer, "text",COL_VIERNES);

    model = gtk_tree_store_new (COL_TOTAL, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    
    
    gtk_tree_store_append (model, &top, NULL);
    for(struct horario elemento : horarios){
        if(comprobar==atoi(elemento.filaHora.c_str())){
            for(struct horario materiaHora : horarioTem){
                gtk_tree_store_set (model, &top,atoi(materiaHora.columnaDia.c_str()),materiaHora.materia.substr(0,18).c_str(),-1);
                
            }
            gtk_tree_store_append (model, &top, NULL);
            horarioTem.clear();
            horarioTem.push_back(elemento);
            comprobar+=1;
            
        }else{
            horarioTem.push_back(elemento);
        }
         
        
    }
    for(struct horario materiaHora : horarioTem){
        gtk_tree_store_set (model, &top,atoi(materiaHora.columnaDia.c_str()),materiaHora.materia.substr(0,18).c_str(),-1);
                
    }
    horarioTem.clear();
  

    gtk_tree_view_set_model (GTK_TREE_VIEW(tabla), GTK_TREE_MODEL (model));
    
    
    gtk_tree_store_set (model, &top,2,"hola mundo",-1);
    gtk_tree_view_set_model (GTK_TREE_VIEW(tabla), GTK_TREE_MODEL (model));

    gtk_widget_show(GTK_WIDGET(ventana1));
    gtk_main();
    
    
    
    
    
    
}
void ventanaPrincipal(){
    
    // TODO falta poder enviar la estructra ventana principal por la funcion
    
    ventana *ventanaPrincipal=new ventana();
    ventanaPrincipal->constructor=gtk_builder_new();
    gtk_builder_add_from_file(ventanaPrincipal->constructor,"ventana.glade",NULL);
    ventanaPrincipal->ventana=GTK_WIDGET(gtk_builder_get_object(ventanaPrincipal->constructor,"ventana"));
    gtk_window_set_title(GTK_WINDOW(ventanaPrincipal->ventana),"GENERADOR DE HORARIOS");
    ventanaPrincipal->ingresar=GTK_BUTTON(gtk_builder_get_object(ventanaPrincipal->constructor,"ingresar"));
    g_signal_connect(ventanaPrincipal->ingresar,"clicked",G_CALLBACK(ingreso),ventanaPrincipal);
    gtk_widget_show (ventanaPrincipal->ventana);
    gtk_main ();
}
