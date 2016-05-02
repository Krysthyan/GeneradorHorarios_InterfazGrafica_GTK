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



using namespace std;
ofstream archivoGuardar;


/*
 * estructuras de la interfaz grafica 
 */
struct ventana{
    GtkBuilder *constructor;
    GtkWidget *ventana;
    GtkButton *ingresar;
    GtkEntry *cedula;
    GtkEntry *password;
};

struct usuario{
    string idUsuario;
    string password;
    string tipoAcceso;
};



/*
 Estructuras de logica del programa
 */



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

int variable=0;

vector<struct aula> arregloAulas;
vector<materia> arregloMaterias;
vector <struct usuario> arregloUsuarios;
void funcionRecursivaUno(int pos, int controlador,int indeX, int indeY,struct materia materiaInFuncion);
int funcionRecursivaDos(int controlador,int indeX, int indeY, int pos);
vector<string> split(string palabraAnalizar, char separador);
void obetnerMaterias();
void obtenerAulas();
void generadorHorario();

/*TRABAJO DE INTERFAZ GRAFICA*/

void ingreso(GtkButton *ingresar, ventana *ventanaPrincipal){
    // solo copiado del proyecto acterior toda realizar toda la adapacion
    
    const gchar *cedulaString;
    const gchar *passwordString;

    ventanaPrincipal->cedula=GTK_ENTRY(gtk_builder_get_object(ventanaPrincipal->constructor,"entryCedula"));
    ventanaPrincipal->password=GTK_ENTRY(gtk_builder_get_object(ventanaPrincipal->constructor,"entryCedula"));
    cedulaString=gtk_entry_get_text(ventanaPrincipal->cedula);
    passwordString=gtk_entry_get_text(ventanaPrincipal->password);
    
    gtk_widget_destroy(ventanaPrincipal->ventana);
    ventanaPrincipal->constructor=gtk_builder_new();
    gtk_builder_add_from_file(ventanaPrincipal->constructor,"admin.glade",NULL);
    ventanaPrincipal->ventana=GTK_WIDGET(gtk_builder_get_object(ventanaPrincipal->constructor,"ventana"));

    gtk_window_set_title(GTK_WINDOW(ventanaPrincipal->ventana),"GENERADOR DE HORARIOS");

    //g_signal_connect (G_OBJECT (ventanaPrincipal->ventana), "destroy", G_CALLBACK (destroy), NULL);
    gtk_widget_show (ventanaPrincipal->ventana);
    gtk_main ();
}
int ventanaPrincipal(){
    
    // TODO falta poder enviar la estructra ventana principal por la funcion
    
    ventana *ventanaPrincipal;
    ventanaPrincipal->constructor=gtk_builder_new();
    gtk_builder_add_from_file(ventanaPrincipal->constructor,"ventana.glade",NULL);
    ventanaPrincipal->ventana=GTK_WIDGET(gtk_builder_get_object(ventanaPrincipal->constructor,"ventana"));
    gtk_window_set_title(GTK_WINDOW(ventanaPrincipal->ventana),"GENERADOR DE HORARIOS");
    ventanaPrincipal->ingresar=GTK_BUTTON(gtk_builder_get_object(ventanaPrincipal->constructor,"ingresar"));
    g_signal_connect(ventanaPrincipal->ingresar,"clicked",G_CALLBACK(ingreso),ventanaPrincipal);
    gtk_widget_show (ventanaPrincipal->ventana);
    gtk_main ();
}

void obetnerIngreso(){
    fstream acceso;
    string fraseIngreso;
    acceso.open("usuarios.csv",ios::in);
     
    vector<string> alterno;

    
    while(!acceso.eof()){
        
        getline (acceso,fraseIngreso);
        alterno=split(fraseIngreso, ',');
        struct usuario *usuarioTem=new usuario();
        for(int i = 0; i < alterno.size(); ++i){
            
            usuarioTem->idUsuario=alterno[0];
            usuarioTem->password=alterno[1];
            usuarioTem->tipoAcceso=alterno[2];
            
            
        }
        arregloUsuarios.push_back(*usuarioTem);
        delete usuarioTem;
    }
    acceso.close();
    cout<<"USUARIOS"<<endl;
    for (usuario elem : arregloUsuarios) {
        
        cout<<elem.idUsuario<<"--"<<elem.password<<endl;
    }
}







vector<string> split(string palabraAnalizar, char separador) {
  vector<string> alterno;
  stringstream analizador(palabraAnalizar);
  string tok;
  
  while(getline(analizador, tok, separador)) {
    alterno.push_back(tok);
  }
  
  return alterno;
}

int funcionRecursivaDos(int controlador,int indeX, int indeY, int pos){
    if(indeX==5 ){
        return pos;
    }
    funcionRecursivaUno(pos,controlador,indeX,indeY,arregloMaterias.at(pos));
    variable++;
}

void funcionRecursivaUno(int pos, int controlador,int indeX, int indeY, materia materiaInFuncion){
    if(materiaInFuncion.creditos=="4" || materiaInFuncion.creditos=="2"){
        if(controlador==0){
            
            if(indeY==5){
                indeX++;
                indeY=0;
            }
            if(!(indeX==4 && indeY>=3)){
                archivoGuardar.open("datos.txt",ios::app);
                archivoGuardar << materiaInFuncion.nombre <<"," << indeX<<","<< indeY<< endl;

                if(indeY+2>=5){
                    indeX++; 
                    indeY=0;
                    archivoGuardar << materiaInFuncion.nombre <<"," << indeX<<","<< indeY+1<< endl;           
                    archivoGuardar.close();
                    controlador=1;
                    funcionRecursivaDos(controlador,indeX,indeY,pos+1);
                }else{
                    archivoGuardar  << materiaInFuncion.nombre <<"," << indeX<<","<< indeY+2<< endl;           
                    archivoGuardar.close();
                    indeY++;
                    controlador=1;
                    funcionRecursivaDos(controlador,indeX,indeY,pos+1);
                }
            }   
        }else{
            archivoGuardar.open("datos.txt",ios::app);
            if(indeY==5){
                indeX++;
                indeY=0;
            }
             if(!(indeX==4 && indeY>=3)){
                 archivoGuardar << materiaInFuncion.nombre <<"," << indeX<<","<< indeY<< endl;

                if(indeY+2>=5){
                    indeX++; 
                    indeY=0;
                    archivoGuardar << materiaInFuncion.nombre <<"," << indeX<<","<< indeY+1<< endl;           
                    archivoGuardar.close();
                    indeY+=2;
                }else{
                    archivoGuardar << materiaInFuncion.nombre <<"," << indeX<<","<< indeY+2<< endl;           
                    archivoGuardar.close();
                    indeY+=3;
                }



                controlador=0;
                funcionRecursivaDos(controlador,indeX,indeY,pos+1);
             }
            
        }
    
    }else if(materiaInFuncion.creditos=="6"){
        archivoGuardar.open("datos.txt",ios::app);
        
        archivoGuardar << materiaInFuncion.nombre <<"," << indeX+1<<","<< 0<< endl;
        archivoGuardar << materiaInFuncion.nombre <<"," << indeX+1<<","<< 2<< endl;
        archivoGuardar << materiaInFuncion.nombre <<"," << indeX+1<<","<< 4<< endl;
        archivoGuardar.close();
        indeX++;
        funcionRecursivaDos(controlador,indeX,indeY,pos+1);
    }
}


void obetnerMaterias(){
    fstream materias;
    string fraseMaterias;
    materias.open("materias.csv",ios::in);
     
    vector<string> alterno;

    while(!materias.eof()){
        
        getline (materias,fraseMaterias);
        alterno=split(fraseMaterias, ',');
        struct materia *materiaTem=new materia();
        for(int i = 0; i < alterno.size(); ++i){
            
            materiaTem->nombre=alterno[0];
            materiaTem->creditos=alterno[1];
            materiaTem->idDocente=alterno[2];
            
            
        }
        arregloMaterias.push_back(*materiaTem);
        delete materiaTem;
    }
    materias.close();
    cout<<"MATERIAS"<<endl;
    for (materia elem : arregloMaterias) {
        
        cout<<elem.nombre<<"--"<<elem.creditos<<endl;
    }
}
void obtenerAulas(){
    fstream aulas;
    string fraseAula;
    aulas.open("aulas.csv",ios::in);
     
    vector<string> alterno;

    
    while(!aulas.eof()){
        
        getline (aulas,fraseAula);
        alterno=split(fraseAula, ',');
        struct aula *aulaTem=new aula();
        for(int i = 0; i < alterno.size(); ++i){
            
            aulaTem->codigoAula=alterno[0];
            aulaTem->capacidad=alterno[1]; 
            
        }
        arregloAulas.push_back(*aulaTem);
        delete aulaTem;
        
    }
    aulas.close();
     for (aula elem : arregloAulas) {
        cout<<elem.codigoAula<<"--"<<elem.capacidad<<endl;
    }

}
void generadorHorario(){
    
    obetnerMaterias();
    obtenerAulas();
    
    for (aula elem : arregloAulas){
        archivoGuardar.open("datos.txt",ios::app);       
        archivoGuardar << elem.codigoAula<< endl;
        archivoGuardar.close();
        funcionRecursivaDos(0,0,0,variable);       
    }
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);
    fstream archivo;
    string frase;
    archivo.open("alumnos.csv",ios::in);
    vector<alumno> arregloEstudiantes; 
    vector<string> alterno;
    while(!archivo.eof()){
        
        getline (archivo,frase);
        alterno=split(frase, ',');
        struct alumno *estudiante=new alumno();
        for(int i = 0; i < alterno.size(); ++i){
            
            estudiante->cedula=alterno[0];
            estudiante->materia=alterno[1];           
        }
        arregloEstudiantes.push_back(*estudiante);
        delete estudiante;
    }
    ventanaPrincipal();
    generadorHorario();
    return 0;
}

