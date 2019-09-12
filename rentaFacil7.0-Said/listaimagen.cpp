#include "listaimagen.h"
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDatabase>

ListaImagen::ListaImagen()
{
    Imagen *newNode = new Imagen();
    aux = newNode;
    inicio = aux;
}

void ListaImagen::llenarImagenes(QSqlQuery *q){
    Imagen *aux2 = aux, *aux3;
    QPixmap *pix;
    while (q->next()){
        //aux = aux2;
        pix = new QPixmap();
        pix->loadFromData(q->value(0).toByteArray());
        aux2->pix = pix;
        Imagen *newNode= new Imagen(pix);
        aux2->next = newNode;
        Imagen *aux4 = newNode;
        aux3 = aux4;
        aux3->prev = aux2;
        aux2 = aux3;
    }

    //Queda un nodo sin imagen al final de la lista, y se elimina
        aux2 = aux3->prev;
        fin = aux2;
        fin->next = nullptr;
}

Imagen *ListaImagen::next()
{
    if(aux->next){
        aux = aux->next;
        return aux;
    }
    else {
        return nullptr;
    }
}

Imagen *ListaImagen::previous()
{
    if(aux->prev){
        aux = aux->prev;
        return aux;
    }
    else {
        return nullptr;
    }
}
