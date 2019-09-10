#include "dbconector.h"

dbconector::dbconector(){
db = QSqlDatabase::addDatabase("QMYSQL");
db.setHostName("localhost");
db.setPort(3306);
db.setDatabaseName("imagenes");
db.setUserName("root");
db.setPassword("");
db.open();
}

dbconector::dbconector(QString hostName, int port, QString dbName, QString userName, QString pass){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(pass);
    db.open();
}

QSqlQuery dbconector::buscaCasaPorZona(QString zona){
db.open();
q.exec("SELECT direccion, tarifa FROM casa WHERE zona='"+zona+"';");
//db.close();
return q;
}

QSqlQuery dbconector::buscaCasaPorId(QString id){
    db.open();
    q.exec("SELECT * FROM casa WHERE idCasa='"+id+"';");
    db.close();
    return q;
}

void dbconector::registroPropietario(QString nombre, QString apellidoP, QString apellidoM, QString domicilio, QString telefono, QString correo, QString cuentabancaria, QString nombreUsuario, QString contrasena){
    //query de insertado
    QSqlQuery insertar;
    insertar.exec("insert into propietario(nombre,apellidoP,apellidoM,domicilio,telefono,correo,cuentabancaria,nombreUsuario,contrasena)values('"+ nombre +"','"+ apellidoP +"','"+ apellidoM +"','"+ domicilio +"','"+ telefono +"','"+ correo +"','"+ cuentabancaria +"','"+ nombreUsuario +"','"+ contrasena +"')");
    insertar.next();

}


void dbconector::insertarImagenes(QString nombreImagen, QString imagenNOmbre,QString idCasa){

    //falta hacer un query que busque el id de la casa nueva para que lo pase como parametro
    QSqlQuery insertar;
   insertar.exec("insert into imagenes(mapaBit,nombre, idCasa)values(LOAD_FILE('"+nombreImagen+"'),'"+imagenNOmbre+"','"+idCasa+"')");
   insertar.next();

/*
     QSqlQuery insertar;
    insertar.exec("insert into imagenes(nombreImagen,imagen)values(LOAD_FILE('"+nombreImagen +"','"+    +"'))");
    insertar.next();
    */

}


void dbconector::registrarActividda(QString actividad ,QString distancia ,QString idcasa){

    QSqlQuery insertar;
    insertar.exec("insert into actividades(actividad,distancia,idCasa)values('"+actividad+"','"+distancia+"','"+ idcasa+"')");

}

void dbconector::registrarCasa(QString direccion,QString personas, QString numcuartos,QString tarifa,QString animales,QString colonia,QString zona,QString descripcion,QString idPropietario){

    QSqlQuery insertar;
    insertar.exec("insert into casa(direccion,personas,num_cuartos,tarifa,animales,colonia,zona,descripcion,idPropietario)values('"+ direccion +"','"+ personas +"','"+ numcuartos +"','"+ tarifa +"','"+ animales +"','"+colonia +"','"+ zona+"','"+descripcion+"','"+idPropietario+"')");

}



