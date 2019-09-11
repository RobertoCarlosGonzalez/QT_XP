#include "imagen.h"

Imagen::Imagen()
{
   //this->pix = new QPixmap();
    this->prev = nullptr;
    this->next = nullptr;
}

Imagen::Imagen(QPixmap *p){
    this->pix = p;
}
