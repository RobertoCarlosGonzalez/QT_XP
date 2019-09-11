#ifndef LISTAIMAGEN_H
#define LISTAIMAGEN_H
#include "imagen.h"
#include <QtSql/QSqlQuery>
#include <QSqlDatabase>



class ListaImagen
{
public:
    ListaImagen();
    void llenarImagenes(QSqlQuery*);
    Imagen* next();
    Imagen* previous();
    Imagen* getAux(){return aux;}
    Imagen* getInicio(){return inicio;}


  private:
    Imagen *inicio, *fin, *aux;
};

#endif // LISTAIMAGEN_H
