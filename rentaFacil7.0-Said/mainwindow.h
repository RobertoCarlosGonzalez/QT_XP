#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imagen.h>
#include <QDialog>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <dbconector.h>
#include <QDebug>
#include <qmessagebox.h>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QtDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString idCasa =nullptr,QWidget *parent = nullptr);
    ~MainWindow();
    void muestraImagen();
    QString idPropientario();
    QString idCasa();
    void tablaRegistrarImagenes();
    void tablaRegistrarActividades();
    void mostrarEstados();
    void mostrarActividades(QString idcasa);

private slots:
    void on_iniciarSesion_clicked();
    void on_iniciarSession_clicked();
    void on_resgistrar_clicked();
    void on_imagen1_clicked();
    void on_btnSigImg03_clicked();
    void on_crearSesion_clicked();
    void on_cancelarCreacion_clicked();
    void on_cerarSesion_clicked();
    void on_buscarImagen_clicked();
    void on_guardarImagen_clicked();
    void on_btnAtrImg03_clicked();
    //void on_actionEliminar_Imagen_triggered();
    void on_siguiente_clicked();
    void on_tablaImagenes_clicked(const QModelIndex &index);
    void on_regresarLista_clicked();
    void on_tablaCatalogo_doubleClicked(const QModelIndex &index);
    void on_regresarMenu_clicked();
    void on_tablaCatalogo_clicked(const QModelIndex &index);
    void on_registrarCasa_clicked();
    void on_cancelarRegistro_clicked();
    void on_finalizarRegistro_clicked();
    void on_agergarActividad_clicked();
    void on_cerrarSesionPropietario_clicked();
    void on_imagen2_clicked();
    void on_imagen3_clicked();
    void on_imagen4_clicked();
    void on_imagen5_clicked();
    void on_imagen6_clicked();
    void on_imagen7_clicked();
    void on_imagen8_clicked();
    void on_imagen9_clicked();
    void on_imagen10_clicked();
    void on_imagen11_clicked();
    void on_imagen12_clicked();
    void on_verImagen_clicked();
    void on_crearUsuario_clicked();
    void on_tablaCatalogo_activated(const QModelIndex &index);
    void on_propietario_2_clicked();
    void on_cliente_2_clicked();
    void on_Btn_reservar_seleccion_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *modelo;
    QSqlQueryModel *agergarImagen;
    QSqlQueryModel *agregarActividad;
    QSqlQueryModel *mostarActividades;
    QSqlDatabase db;
    QString res,id_client;
};

#endif // MAINWINDOW_H
