#ifndef UICATALOGO_H
#define UICATALOGO_H

#include <QDialog>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDatabase>

class uicatalogo
{
public:
    uicatalogo();
    void muestraImagen();
private:
    QSqlTableModel *modelo;
};

#endif // UICATALOGO_H
