#ifndef IMAGEN_H
#define IMAGEN_H

#include <QPixmap>
//#include "listaimagen.h"

class Imagen
{
public:
    Imagen();
    Imagen(QPixmap*);
    QPixmap* getPixMap(){return pix;}
    Imagen* getPrev(){return prev;}
    Imagen* getNext(){return next;}
    void setPrev(Imagen *node){this->prev = node;}
    void setNext(Imagen *node){this->next = node;}


private:
    Imagen *prev, *next;
    QPixmap *pix;
    //ByteArray g;
    friend class ListaImagen;


};

#endif // IMAGEN_H
