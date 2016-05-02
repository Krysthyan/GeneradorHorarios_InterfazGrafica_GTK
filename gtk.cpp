#include <stdlib.h>
#include <gtk/gtk.h>
#include <iostream>
void ingreso();
using namespace std;

GtkBuilder *constructor;
GtkWidget *ventana;
GtkButton *ingresar;
GtkEntry *cedula;
GtkEntry *password;

void destroy( GtkWidget *widget, gpointer   data )
{
    gtk_widget_destroy(ventana);
    constructor=gtk_builder_new();

    gtk_builder_add_from_file(constructor,"ventana.glade",NULL);

    ventana=GTK_WIDGET(gtk_builder_get_object(constructor,"ventana"));

    gtk_window_set_title(GTK_WINDOW(ventana),"GENERADOR DE HORARIOS");
    //gtk_widget_set_size_request(ventana,420,230);

    ingresar=GTK_BUTTON(gtk_builder_get_object(constructor,"ingresar"));
    g_signal_connect(ingresar,"clicked",G_CALLBACK(ingreso),NULL);


    gtk_widget_show (ventana);

}

void ingreso(){
    const gchar *cedulaString;
    const gchar *passwordString;

    cedula=GTK_ENTRY(gtk_builder_get_object(constructor,"entryCedula"));
    cedulaString=gtk_entry_get_text(cedula);
    passwordString=gtk_entry_get_text(password);


    gtk_widget_destroy(ventana);

    constructor=gtk_builder_new();

    gtk_builder_add_from_file(constructor,"estudiante.glade",NULL);

    ventana=GTK_WIDGET(gtk_builder_get_object(constructor,"ventana"));


    gtk_window_set_title(GTK_WINDOW(ventana),"GENERADOR DE HORARIOS");

    g_signal_connect (G_OBJECT (ventana), "destroy", G_CALLBACK (destroy), NULL);
    gtk_widget_show (ventana);
    gtk_main ();





}

int main (int argc, char *argv[]){



  gtk_init(&argc, &argv);
  constructor=gtk_builder_new();

  gtk_builder_add_from_file(constructor,"ventana.glade",NULL);

  ventana=GTK_WIDGET(gtk_builder_get_object(constructor,"ventana"));


  gtk_window_set_title(GTK_WINDOW(ventana),"GENERADOR DE HORARIOS");
  //gtk_widget_set_size_request(ventana,420,230);

  ingresar=GTK_BUTTON(gtk_builder_get_object(constructor,"ingresar"));
  g_signal_connect(ingresar,"clicked",G_CALLBACK(ingreso),NULL);


    gtk_widget_show (ventana);
    gtk_main ();
  return 0;
}
