#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagen.h"
#include "listaimagen.h"

static dbconector b;
static ListaImagen *listImgs = new ListaImagen();
MainWindow::MainWindow(QString id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->paginas->setCurrentIndex(0);
    ui->cerarSesion->hide();//bloqueo del boton
    setWindowTitle("RENTA FACIL");//titulo de la aplicacion
    //-------------------------------------------------------------------------------------------

    //base de datos
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("RentaFacil");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    //--------------------------------------------------------------------------------

    //imagen de iniciar sesion
    QPixmap logo(":/ /imagen/seguridad.png");
    int widWidth = this->ui->imagenLogin->width();
    int widHeight = this->ui->imagenLogin->height();
    ui->imagenLogin->setPixmap(logo.scaled(widWidth, widHeight, Qt::KeepAspectRatioByExpanding));
    //---------------------------------------------------------------------------------------------
    id_client="0";

}


MainWindow::~MainWindow()
{
    delete ui;


}
void MainWindow::mostrarActividades(QString idcasa){

    //tabla para mostar actividades
    ui->tablaActividades->setContextMenuPolicy(Qt::ActionsContextMenu);
    mostarActividades = new QSqlTableModel;
    ui->tablaActividades->setModel(mostarActividades);
    QSqlQuery query;
    QString consulta,user,contra;
    consulta.append("select *from actividades where  idCasa='"+idcasa+"'");
    query.prepare(consulta);
    query.exec();
    agregarActividad->setQuery(query);
    ui->tablaActividades->hideColumn(0);
    ui->tablaActividades->hideColumn(3);
}


void MainWindow::mostrarEstados(){
    ui->zona->addItem("Cancun");ui->zona->addItem("Chiapas");ui->zona->addItem("Chihuahua");
    ui->zona->addItem("Ciudad de Mexico");ui->zona->addItem("Jalisco");ui->zona->addItem("Michoacan");
    ui->zona->addItem("Nayarit");ui->zona->addItem("Oaxaca");ui->zona->addItem("San Luis Potosi");
    ui->zona->addItem("Puebla");ui->zona->addItem("Veracruz");ui->zona->addItem("Yucatan");

}


//tabla donde se agregan las actividades al registrar una casa
void MainWindow::tablaRegistrarActividades(){

   ui->tablaRegistrarActividades->setContextMenuPolicy(Qt::ActionsContextMenu);
   agregarActividad= new QSqlTableModel;
   ui->tablaRegistrarActividades->setModel(agregarActividad);
   QSqlQuery query;
   QString consulta,user,contra,id;
   id=idCasa();
   qDebug()<<"id"<<"tabla registrar actividades";;
   consulta.append("select *from actividades where  idCasa='"+id+"'");
   query.prepare(consulta);
   query.exec();
   agregarActividad->setQuery(query);
   ui->tablaRegistrarActividades->setModel(agregarActividad);
   ui->tablaRegistrarActividades->hideColumn(0);
   ui->tablaRegistrarActividades->hideColumn(3);

}

//tabla donde se agregan las imagnes al registrar una casa

void MainWindow::tablaRegistrarImagenes(){

  ui->tablaImagenes->setContextMenuPolicy(Qt::ActionsContextMenu);
    agergarImagen =new QSqlQueryModel();
    QSqlQuery query;
    QString consulta,user,contra,id;
    id=idCasa();
    qDebug()<<"id"<<"tabla registar imagen";
    consulta.append("select *from imagenes where  idCasa='"+id+"'");
    query.prepare(consulta);
    query.exec();
    agergarImagen->setQuery(query);
    ui->tablaImagenes->setModel(agergarImagen);
    //ui->tablaImagenes->addAction(ui->actionEliminar_Imagen);
    ui->tablaImagenes->hideColumn(0);
    ui->tablaImagenes->hideColumn(1);
    ui->tablaImagenes->hideColumn(3);

}

void MainWindow::muestraImagen(){

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("Casa");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
   // db.close();
   //ui->tablaCatalogo->hideColumn(0);
    //ui->tabla->hideColumn(2);

}


//login buscamos el usuario dentro de la base de datos
void MainWindow::on_iniciarSesion_clicked()
{
    QMessageBox informacion;
    QSqlQuery query,query2,query3;
    QString user1=ui->nombreUsuario->text();
    QString clave1=ui->contrasena->text();
    QString consulta,user,contra,id;

    if(ui->nombreUsuario->text()==""||ui->contrasena->text()==""){
        informacion.setWindowTitle("Informacion");
        informacion.setText ("Campos incompletos, verifique");
        informacion.setStandardButtons( QMessageBox::Ok) ;
        informacion.setDefaultButton (QMessageBox ::Ok ) ;
        informacion.setButtonText( QMessageBox::Ok,"Aceptar");
        informacion.exec();
    }
            if(ui->propietario->isChecked()){
            consulta.append("SELECT  idPropietario,nombreUsuario,contrasena FROM propietario where nombreUsuario='"+user1+"' ");
            query.prepare(consulta);
            query.exec();
            query.next();
            id=query.value(0).toString();
            qDebug()<<"idpropietario: "<<id;
            user=query.value(1).toString();
            qDebug()<<user;
            contra=query.value(2).toString();
            qDebug()<<contra;
                     if(user==user1 && contra==clave1){
                         ui->iniciarSession->hide();
                         ui->resgistrar->hide();
                         ui->cerarSesion->show();
                         ui->paginas->setCurrentIndex(5);
                      }else {
                         informacion.setWindowTitle("Informacion");
                         informacion.setText ("Usuario o clave incorrectos, intente de nuevo");
                         informacion.setStandardButtons( QMessageBox::Ok) ;
                         informacion.setDefaultButton (QMessageBox ::Ok ) ;
                         informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                         informacion.exec();
                      }
                }

                if(ui->cliente->isChecked()){
                     consulta.append("SELECT  idcliente, nombreUsuario,contrasena FROM cliente where nombreUsuario='"+user1+"' ");
                     query.prepare(consulta);
                     query.exec();
                     query.next();
                     user=query.value(1).toString();
                     qDebug()<<user;
//      Obtenemos el id del cliente para realizar una reserva posterior al logeo del cliente
                     id_client=query.value(0).toString();
                     contra=query.value(2).toString();
                     qDebug()<<contra;
                     if(user==user1 && contra==clave1){
                         ui->resgistrar->hide();
                         ui->iniciarSession->hide();
                         ui->cerarSesion->show();
                         ui->paginas->setCurrentIndex(0);
                     }else {
                         informacion.setWindowTitle("Informacion");
                         informacion.setText ("Usuario o clave incorrectos, intente de nuevo");
                         informacion.setStandardButtons( QMessageBox::Ok) ;
                         informacion.setDefaultButton (QMessageBox ::Ok ) ;
                         informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                         informacion.exec();
                           }

                       }
                //LOGIN ADMIN ROBS
                    if(ui->administrador->isChecked()){
                    consulta.append("SELECT  usuario,contrasena FROM administrador where usuario='"+user1+"' ");
                    query.prepare(consulta);
                    query.exec();
                    query.next();
                    user=query.value(0).toString();
                    qDebug()<<user;
                    contra=query.value(1).toString();
                     qDebug()<<contra;

                         if(user==user1 && contra==clave1){
                          ui->resgistrar->hide();
                          ui->iniciarSession->hide();
                          ui->cerarSesion->show();
                          ui->paginas->setCurrentIndex(5);
                     } else{
                             informacion.setWindowTitle("Informacion");
                             informacion.setText ("Usuario o clave incorrectos, intente de nuevo");
                             informacion.setStandardButtons( QMessageBox::Ok) ;
                             informacion.setDefaultButton (QMessageBox ::Ok ) ;
                             informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                             informacion.exec();
                               }
               }

}


//moton que te envia donde inicias sesion
void MainWindow::on_iniciarSession_clicked()
{
     ui->paginas->setCurrentIndex(1);
}

//boton para registrarse como nuevo cliente o propietario
void MainWindow::on_resgistrar_clicked()
{
ui->paginas->setCurrentIndex(4);
}

void MainWindow::on_btnSigImg03_clicked()
{
    if(listImgs->next()){
        ui->lbImagen03->setPixmap(listImgs->getAux()->getPixMap()->scaled(ui->lbImagen03->width(), ui->lbImagen03->height(), Qt::KeepAspectRatioByExpanding));
    }
}

//crear cuenta usuarion
void MainWindow::on_crearSesion_clicked()
{
     QMessageBox informacion;
     QMessageBox msgBox(QMessageBox::Question,"Confimacion","¿Estas seguro de guardar los datos?",QMessageBox::Yes|QMessageBox::No);
     msgBox.setButtonText(QMessageBox::Yes,"Sí");
     msgBox.setButtonText(QMessageBox::No,"No");
     QString contrasena1=ui->contrasena_1->text();
     if(!ui->propietario_2->isChecked()){
            if(ui->nombre->text()==""||ui->apellidoP->text()==""||ui->apellidoM->text()==""||ui->domicilio->text()==""||ui->telefono->text()==""||ui->correo->text()==""||ui->cuentabancaria->text()==""||ui->nombreUsuario_2->text()==""||ui->contrasena_1->text()==""){
                informacion.setWindowTitle("Informacion");
                informacion.setText ("Campos incompletos,verifique");
                informacion.setStandardButtons( QMessageBox::Ok) ;
                informacion.setDefaultButton (QMessageBox ::Ok ) ;
                informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                informacion.exec();
            }
     }else if(ui->cliente_2->isChecked()){
                if(ui->nombre->text()==""||ui->apellidoP->text()==""||ui->apellidoM->text()==""||ui->domicilio->text()==""||ui->telefono->text()==""||ui->nombreUsuario_2->text()==""||ui->contrasena_1->text()==""){
                informacion.setWindowTitle("Informacion");
                informacion.setText ("Campos incompletos,verifique");
                informacion.setStandardButtons( QMessageBox::Ok) ;
                informacion.setDefaultButton (QMessageBox ::Ok ) ;
                informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                informacion.exec();
            }
     } else
            {
                if(ui->contrasena_1->text() == ui->contrasena_2->text()){ //Si la contraseña coincide
                    if(msgBox.exec()==QMessageBox::Yes){
                        if(ui->cliente_2->isChecked()){
                            b.registro_cliente(ui->nombre->text(),ui->apellidoP->text(),ui->apellidoM->text(),ui->domicilio->text(),ui->telefono->text(),ui->nombreUsuario_2->text(),ui->contrasena_1->text());
                            ui->paginas->setCurrentIndex(0);
                        }else
                        {
                            b.registroPropietario(ui->nombre->text(),ui->apellidoP->text(),ui->apellidoM->text(),ui->domicilio->text(),ui->telefono->text(),ui->correo->text(),ui->cuentabancaria->text(),ui->nombreUsuario_2->text(),ui->contrasena_1->text());
                            ui->paginas->setCurrentIndex(1);
                        }
                    }
                }else{
                    QMessageBox wrongPass;
                    wrongPass.setWindowTitle("Contraseña no coincide");
                    wrongPass.setText ("La contraseña no coincide con la confirmación");
                    wrongPass.setStandardButtons( QMessageBox::Ok) ;
                    wrongPass.setDefaultButton (QMessageBox ::Ok ) ;
                    wrongPass.setButtonText( QMessageBox::Ok,"Aceptar");
                    wrongPass.exec();

                }

            }

}


//cancela la creacion de la cuenta
void MainWindow::on_cancelarCreacion_clicked()
{
     ui->paginas->setCurrentIndex(0);
}

void MainWindow::on_cerarSesion_clicked()
{
 ui->paginas->setCurrentIndex(0);
 ui->iniciarSession->show();
 ui->resgistrar->show();
 ui->cerarSesion->hide();

}


//buscar imagenes en el escritorio del propietario
void MainWindow::on_buscarImagen_clicked()
{
    auto nombreArchivo=QFileDialog::getOpenFileName(this,"Abrir imagen",QDir::rootPath(),
               "Imagenes (*.png *.jpg *.jpeg);;cualquier archivo(*.*)");
       ui->nombreImagen->setText(nombreArchivo);
}

//guardar la imagen en la base de datos
void MainWindow::on_guardarImagen_clicked()
{
    QMessageBox informacion;
    QFile archivo(ui->nombreImagen->text());
    qDebug()<<ui->nombreImagen->text();
    QString nombreImagen,imagenNombre,idcasa;
    nombreImagen = ui->nombreImagen->text();
    imagenNombre = ui->imagenNombre->text();
    idcasa=idCasa();//metodo que regresa el id de la ultima casa insertada
    QMessageBox msgBox(QMessageBox::Question,"Confimacion","¿Estas seguro de guardar la imagen?",QMessageBox::Yes|QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,"Sí");
    msgBox.setButtonText(QMessageBox::No,"No");

    if(ui->imagenNombre->text()==""){
        informacion.setWindowTitle("Informacion");
        informacion.setText ("Campos incompletos");
        informacion.setStandardButtons( QMessageBox::Ok) ;
        informacion.setDefaultButton (QMessageBox ::Ok ) ;
        informacion.setButtonText( QMessageBox::Ok,"Aceptar");
        informacion.exec();
        return;
    }
      if(!archivo.open(QIODevice::ReadOnly)){
        informacion.setWindowTitle("Informacion");
        informacion.setText ("verifique direccion de imagen");
        informacion.setStandardButtons( QMessageBox::Ok) ;
        informacion.setDefaultButton (QMessageBox ::Ok ) ;
        informacion.setButtonText( QMessageBox::Ok,"Aceptar");
        informacion.exec();
        return;
    }
        if( msgBox.exec()==QMessageBox::Yes){
         b.insertarImagenes(nombreImagen,imagenNombre,idcasa);
         tablaRegistrarImagenes();
         archivo.close();
         ui->nombreImagen->clear();
         ui->imagenNombre->clear();
         ui->imagen->setText("Agrege imagenes de su casa");
       }
}

void MainWindow::on_btnAtrImg03_clicked()
{
    if(listImgs->previous()){
        ui->lbImagen03->setPixmap(listImgs->getAux()->getPixMap()->scaled(ui->lbImagen03->width(), ui->lbImagen03->height(), Qt::KeepAspectRatioByExpanding));
    }else {
        //ui->lbDireccion03->setText("Olovorgo");

    }
}

/*
//eliminar las imagenes registradas
void MainWindow::on_actionEliminar_Imagen_triggered()
{
    agergarImagen->removeRow(ui->tablaImagenes->currentIndex().row());
}
*/


//registrar casa------------------------------------------------------------------
void MainWindow::on_siguiente_clicked()
{
    ui->imagen->setText("imagen de la casa");
    QString direccion = ui->direccion->text();
    QString numPersona= ui->numPersona->text();
    QString colonia= ui->colonia->text();
    QString habitacion= ui->habitaciones->text();
    QString tarifa = ui->tarifa->text();
    QString zona = ui->zona->currentText();
    QString descripcion=ui->descripcion->text();
    QString idpropiedad=idPropientario();
    qDebug()<<"idpropietario: "<<idpropiedad;
     QMessageBox informacion;
     QMessageBox msgBox(QMessageBox::Question,"Confimacion","¿Estas seguro de guardar la informacion de su casa?",QMessageBox::Yes|QMessageBox::No);
     msgBox.setButtonText(QMessageBox::Yes,"Sí");
     msgBox.setButtonText(QMessageBox::No,"No");
   if(ui->direccion->text()==""||ui->numPersona->text()==""||ui->colonia->text()==""||ui->habitaciones->text()==""||ui->tarifa->text()==""||ui->zona->currentText()==""||ui->descripcion->text()==""){
       informacion.setWindowTitle("Informacion");
       informacion.setText ("Campos incompletos,verifique");
       informacion.setStandardButtons( QMessageBox::Ok) ;
       informacion.setDefaultButton (QMessageBox ::Ok ) ;
       informacion.setButtonText( QMessageBox::Ok,"Aceptar");
       informacion.exec();
   }if(ui->animalSi->isChecked()){
        if( msgBox.exec()==QMessageBox::Yes){
        ui->direccion->clear();ui->numPersona->clear();ui->colonia->clear();
       ui->habitaciones->clear();ui->tarifa->clear();ui->zona->clear();ui->descripcion->clear();
    b.registrarCasa(direccion,numPersona,habitacion,tarifa,"si",colonia,zona,descripcion,idpropiedad);
    qDebug()<<"entre al metodo ---si---- aceptan mascotas";
      ui->paginas->setCurrentIndex(7);
      QString idcasa=idCasa();
      qDebug()<<"idcasa: "<<idcasa;
      tablaRegistrarActividades();
      tablaRegistrarImagenes();
      }
        }if(ui->animalNo->isChecked()){
        if( msgBox.exec()==QMessageBox::Yes){
         ui->direccion->clear();ui->numPersona->clear();ui->colonia->clear();
        ui->habitaciones->clear();ui->tarifa->clear();ui->zona->clear();ui->descripcion->clear();
    b.registrarCasa(direccion,numPersona,habitacion,tarifa,"no",colonia,zona,descripcion,idpropiedad);
    qDebug()<<"entre al metodo --no---  aceptan mascotas";
      ui->paginas->setCurrentIndex(7);
      QString idcasa=idCasa();
      qDebug()<<"idcasa: "<<idcasa;
      tablaRegistrarActividades();
      tablaRegistrarImagenes();
    }
   }
}


//para mostras las imagenes que has agregado a la casa
void MainWindow::on_tablaImagenes_clicked(const QModelIndex &index)
{
    if(!index.isValid()){
        return;
    }
    const int id = agergarImagen->index(index.row(),0).data().toInt();
    QSqlQuery p;
    p.exec(QString("select  *from imagenes where idImagen= %1").arg(id));
    p.next();
    QPixmap pix;
    if(!pix.loadFromData(p.value(1).toByteArray())){
        ui->imagen->setText("<b>Error de imagen</b>");
        return;
    }
    int widWidth = this->ui->imagen->width();
    int widHeight = this->ui->imagen->height();
    ui->imagen->setPixmap(pix.scaled(widWidth, widHeight, Qt::KeepAspectRatioByExpanding));

}

//boton que regresa la casa el a el lugar
void MainWindow::on_regresarLista_clicked()
{
     ui->paginas->setCurrentIndex(2);
}

//es para mostrar la informacion completa de la casa
void MainWindow::on_tablaCatalogo_doubleClicked(const QModelIndex &index)
{
    if(!index.isValid()){
        return;
    }


    QString idCasa = modelo->index(index.row(),0).data().toString();
    res = idCasa;
    QString consulta;

    //Registro de casa
    QSqlQuery q;
    q.exec("SELECT * FROM Casa WHERE idCasa="+idCasa+";");
    q.next();

    ui->lbDireccion03->setText(q.value(1).toString());
    ui->lbPersonas03->setText(q.value(2).toString());
    ui->lbHabitaciones03->setText(q.value(3).toString());
    ui->lbZona03->setText(q.value(7).toString());
    ui->lbDescripcion03->setText(q.value(8).toString());
    ui->lbTarifa03->setText(q.value(4).toString());
    ui->lbMascotas03->setText(q.value(5).toString());
    ui->lbColonia03->setText(q.value(6).toString());
    QSqlQuery query;
    agregarActividad= new QSqlTableModel;
    consulta.append("select actividad, distancia from actividades where idCasa='"+idCasa+"'");
    query.prepare(consulta);
    query.exec();
    agregarActividad->setQuery(query);
    ui->tablaActividades->setModel(agregarActividad);

    //IMAGENES
    QSqlQuery *q2 = new QSqlQuery();

    //Query que busca imagenes de la casa
    q2->exec("SELECT mapaBit FROM imagenes AS IM INNER JOIN Casa AS C ON IM.idCasa = C.idCasa WHERE C.idCasa="+idCasa+";");
    //Llenado de imagenes
    listImgs->llenarImagenes(q2);
    ui->lbImagen03->setPixmap(listImgs->getAux()->getPixMap()->scaled(ui->lbImagen03->width(), ui->lbImagen03->height(), Qt::KeepAspectRatioByExpanding));
    ui->paginas->setCurrentIndex(3);

}


//para regresa el menu del catalogo y poder elegir otro estado
void MainWindow::on_regresarMenu_clicked()
{
    ui->label_31->setText("imagen");
    ui->paginas->setCurrentIndex(0);
}


//para que muestre la casa antes de ir a la informacion completa de la casa elegida
void MainWindow::on_tablaCatalogo_clicked(const QModelIndex &index)
{
    listImgs = nullptr;
    listImgs = new ListaImagen();
    if(!index.isValid()){
        return;
    }
    const int id =modelo->index(index.row(),0).data().toInt();
    qDebug()<<id<<"primero";
    QSqlQuery p;
    p.exec(QString("select  * from imagenes where idImagen= %1").arg(id));
    p.next();

    QPixmap pix;
    if(!pix.loadFromData(p.value(1).toByteArray())){
        ui->label_31->setText("<b>Error de imagen</b>");
        return;
    }

    int widWidth = this->ui->label_31->width();
    int widHeight = this->ui->label_31->height();
    ui->label_31->setPixmap(pix.scaled(widWidth, widHeight, Qt::KeepAspectRatioByExpanding));

}



//boton que muetra la pestaña  de registro de casa
void MainWindow::on_registrarCasa_clicked()
{
    mostrarEstados();
    tablaRegistrarImagenes();//muetra los encabezados de la tabla registrar imagen
    tablaRegistrarActividades();//muetra los encabezados de la tabla registrar actividades
    ui->paginas->setCurrentIndex(6);
}

//boton que cancela el registro de la casa
void MainWindow::on_cancelarRegistro_clicked()
{
    ui->paginas->setCurrentIndex(5);
}

//boton que finaliza el registro de la casa
void MainWindow::on_finalizarRegistro_clicked()
{
    QMessageBox informacion;
    informacion.setWindowTitle("Informacion");
    informacion.setText ("No podras modificar la informacion de tu casa dentro de un 1 año");
    informacion.setStandardButtons( QMessageBox::Ok) ;
    informacion.setDefaultButton (QMessageBox ::Ok ) ;
    informacion.setButtonText( QMessageBox::Ok,"Aceptar");
    informacion.exec();

    QMessageBox msgBox(QMessageBox::Question,"Confimacion","¿Has terminado"
                                                           " de agregar imagenes y actividades a tu casa?",QMessageBox::Yes|QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,"Sí");
    msgBox.setButtonText(QMessageBox::No,"No");
    if(msgBox.exec()==QMessageBox::Yes){
    ui->paginas->setCurrentIndex(5);
    }
}


//registrar actividaes de la casa
void MainWindow::on_agergarActividad_clicked()
{
    QMessageBox informacion;
    QMessageBox msgBox(QMessageBox::Question,"Confimacion","¿Estas seguro de guardar la actividad?",QMessageBox::Yes|QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,"Sí");
    msgBox.setButtonText(QMessageBox::No,"No");
    if(ui->actividad->text()=="" || ui->distansiActividad->text()==""){
        informacion.setWindowTitle("Informacion");
        informacion.setText ("campos incompletos");
        informacion.setStandardButtons( QMessageBox::Ok) ;
        informacion.setDefaultButton (QMessageBox ::Ok ) ;
        informacion.setButtonText( QMessageBox::Ok,"Aceptar");
        informacion.exec();
        return;
    }
        if( msgBox.exec()==QMessageBox::Yes){
        QString  actividad=ui->actividad->text();
        QString  distancia=ui->distansiActividad->text();
        QString  idcasa=idCasa();
        ui->actividad->clear();
        ui->distansiActividad->clear();
        //---------------------------------------------------------------------------------
        //codigo para que la tabla de valla actualizando.
        //------------------------------------------------------------------------------
        b.registrarActividda(actividad,distancia,idcasa);
        tablaRegistrarActividades();
        }
}


//retorna el id de el propietario
QString MainWindow::idPropientario(){
    QSqlQuery query,query2,query3;
    QString user1=ui->nombreUsuario->text();
    QString clave1=ui->contrasena->text();
    QString consulta,user,contra,id;

    consulta.append("SELECT  idPropietario,nombreUsuario,contrasena FROM propietario where nombreUsuario='"+user1+"' ");
    query.prepare(consulta);
    query.exec();
    query.next();
    id=query.value(0).toString();
    qDebug()<<"metodo retorna el idpropietario"<<endl;
    qDebug()<<"idPropietario:"<<id;
    return id;

}

//retorna el id de la casa que se esta insertanndo
QString MainWindow::idCasa(){
    QSqlQuery query;
    QString user1=ui->nombreUsuario->text();
    QString consulta,user,contra,id;

    QString idpropietario=idPropientario();
    qDebug()<<idpropietario;
    consulta.append("select  c.idCasa  from  casa as c inner join propietario  on c.idPropietario = propietario.idPropietario where c.idPropietario='"+idpropietario+ "' order by c.idCasa desc limit 1 ");
    query.prepare(consulta);
    query.exec();
    query.next();
    id=query.value(0).toString();
    qDebug()<<"metodo retorna el idCasa"<<endl;
    qDebug()<<"idcasa"<<id;
    return id;

}

void MainWindow::on_cerrarSesionPropietario_clicked()
{
    ui->paginas->setCurrentIndex(0);
    ui->iniciarSession->show();
    ui->resgistrar->show();
    ui->cerarSesion->hide();
    ui->nombreUsuario->clear();
    ui->contrasena->clear();
    //para quitar el lleno del combo box
     ui->propietario->setAutoExclusive(false);
    ui->propietario->setChecked(false);
    //-------------------------------------------

}

//menu de imagenes de catalogo-------------------------------------
void MainWindow::on_imagen1_clicked()
{
    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_cancun");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);
}

void MainWindow::on_imagen2_clicked()
{

    //tabla de mostrar casa por zonas
    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_chiapas");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}


void MainWindow::on_imagen3_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Chihuahua");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen4_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Ciudad_de_Mexico");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen5_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Jalisco");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen6_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Michoacan");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen7_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Nayarit");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen8_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Oaxaca");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen9_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_San_luis_potosi");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen10_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Puebla");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen11_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Veracruz");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}

void MainWindow::on_imagen12_clicked()
{

    ui->tablaCatalogo->setContextMenuPolicy(Qt::ActionsContextMenu);
    modelo = new QSqlTableModel(this);
    modelo->setTable("casas_Yucatan");
    modelo->select();
    ui->tablaCatalogo->setModel(modelo);
    ui->tablaCatalogo->hideColumn(0);
    ui->tablaCatalogo->hideColumn(2);
    ui->tablaCatalogo->hideColumn(5);
    ui->tablaCatalogo->hideColumn(6);
    ui->tablaCatalogo->hideColumn(7);
    ui->tablaCatalogo->hideColumn(8);
    ui->tablaCatalogo->hideColumn(9);
    ui->paginas->setCurrentIndex(2);

}
//--------------------------------------------------------------------------------------

void MainWindow::on_verImagen_clicked()
{
    QPixmap logo(ui->nombreImagen->text());
    int widWidth = this->ui->imagen->width();
    int widHeight = this->ui->imagen->height();
    ui->imagen->setPixmap(logo.scaled(widWidth, widHeight, Qt::KeepAspectRatioByExpanding));
}

void MainWindow::on_crearUsuario_clicked()
{
   ui->paginas->setCurrentIndex(4);
}



void MainWindow::on_tablaCatalogo_activated(const QModelIndex &index)
{

}

void MainWindow::on_propietario_2_clicked()
{
    ui->cuentabancaria->show();
    ui->label_14->show();
}

void MainWindow::on_cliente_2_clicked()
{
    ui->label_14->hide();
    ui->cuentabancaria->hide();
    ui->label_13->hide();
    ui->correo->hide();
}

//------------------
// RESERVACIONES
void MainWindow::on_Btn_reservar_seleccion_clicked()
{
    QSqlQuery query;
    int n_huespedes;
    QString  /*insert,*/f_llegada,f_salida,deposito;
    f_llegada = ui->date_arrival->date().toString();
    f_salida = ui->date_derpature2->date().toString();
    n_huespedes = ui->sb_nhuespedes->value();
//    insert.append("insert into reservacion (idCliente,idCasa,f_llegada,f_salida,deposito) values('"+ id_client +"','"+ idCasa +"','"+ f_llegada +"','"+ f_salida +"','"+ deposito +"')");
    query.prepare("insert into reservacion(idCliente,idCasa,f_llegada,f_salida,deposito,huespedes) values('"+ id_client +"','"+ res +"','"+ f_llegada +"','"+ f_salida +"','"+ deposito +"','"+n_huespedes+"')");
    query.exec();
    if(!query.next()){
        qDebug()<<"BIEN HECHO";
    }else{
        qDebug()<<"FALLASTE CRACK!"<<id_client<<" "<<res<<" "<<deposito<<" "<<f_llegada<<" "<<f_salida<<" "<<n_huespedes;
    }

}

void MainWindow::on_date_arrival_dateChanged(const QDate &date)
{
    ui->date_derpature2->setDate(date);
    qDebug()<<date;
}
