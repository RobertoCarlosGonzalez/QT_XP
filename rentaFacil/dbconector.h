#ifndef DBCONECTOR_H
#define DBCONECTOR_H
#include <QtSql/QSqlQuery>

class dbconector
{
    private:
    QSqlQuery q;
    QSqlDatabase db;
public:
    dbconector();
    dbconector(QString, int, QString, QString, QString);
    QSqlQuery buscaCasaPorZona(QString);
    QSqlQuery buscaCasaPorId(QString);
     void registroPropietario(QString,QString,QString,QString,QString,QString,QString,QString,QString);
     void insertarImagenes(QString,QString,QString);
     void registrarActividda(QString,QString,QString);
     void registrarCasa(QString,QString,QString,QString,QString,QString,QString,QString,QString);

};


#endif // DBCONECTOR_H
