#include "configuracion.h"
#include "ui_configuracion.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include<QMessageBox>
#include <QFile>
Configuracion::Configuracion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Configuracion)
{
    ui->setupUi(this);
}
Configuracion::~Configuracion()
{
    delete ui;
}
void Configuracion::on_btnGuardar_clicked()
{
    Configuracion::guardar();
    QMessageBox::information(this, tr("Aviso"),tr("Guardado Exitosamente"));
}
void Configuracion::on_btnAbrir_clicked()
{
    Configuracion::abrir();
}
void Configuracion::guardar()
{
    QString direccion=ui->InDirecion->text();
    int puerto=ui->InPuerto->value();
    bool caja1=ui->chkCaja1->isChecked();
    bool caja2=ui->chkCaja2->isChecked();
    bool caja3=ui->chkCaja3->isChecked();
    bool caja4=ui->chkCaja4->isChecked();
    QString temportal=QDir::home().absolutePath()+"/sin_titulo.cfg";
    qDebug()<<temportal;
    QString nombreArchivo = QFileDialog::getSaveFileName(this, ("Guardar Configuracion "),temportal,("Archivos de configuracion (*.cfg)"));

    QFile data(nombreArchivo);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out <<"Servidor ="<< direccion<<'\n';
        out <<"Puerto ="<< puerto<<'\n';
        out <<"Caja1 ="<<caja1<<'\n';
        out <<"Caja2 ="<<caja2<<'\n';
        out <<"Caja3 ="<<caja3<<'\n';
        out <<"Caja4 ="<<caja4<<'\n';
        qDebug() << "Archivo almacenado en:" << nombreArchivo;
        data.close();
    }
}
void Configuracion::abrir()
{
    QString temportal=QDir::home().absolutePath();
    qDebug()<<temportal;
    QString nombreArchivo = QFileDialog::getOpenFileName(this, ("Abrir Archivo"),temportal, ("Archivos de configuracion (*.cfg)"));
    QFile Archivo(nombreArchivo);
    if(!Archivo.open(QIODevice::ReadOnly| QIODevice::Text))
        return;
    QStringList documentos;
    QTextStream in(&Archivo);
    while(!in.atEnd()){
        QString parrafo=in.readLine();
        documentos<<parrafo;
    }
    QStringList seciones=documentos[0].split("=");
    ui->InDirecion->setText(seciones[1]);
    QStringList seciones1=documentos[1].split("Puerto =");
    ui->InPuerto->setValue(seciones1[1].toInt());
    QStringList seciones2=documentos[2].split("Caja1 =");
    ui->chkCaja1->setChecked(seciones2[1].toInt());
    QStringList seciones3=documentos[3].split("Caja2 =");
    ui->chkCaja2->setChecked(seciones3[1].toInt());
    QStringList seciones4=documentos[4].split("Caja3 =");
    ui->chkCaja3->setChecked(seciones4[1].toInt());
    QStringList seciones5=documentos[5].split("Caja4 =");
    ui->chkCaja4->setChecked(seciones5[1].toInt());
    qDebug()<<documentos;
}
