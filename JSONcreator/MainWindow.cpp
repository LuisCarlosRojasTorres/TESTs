#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cB_value4->addItem(QString("Male"));
    ui->cB_value4->addItem(QString("FeMale"));
    ui->cB_value4->addItem(QString("SheMale"));
    ui->cB_value4->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_OpenJson_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open JSON", "/","JSON (*.json)");

    if(fileName.isEmpty()){

    }else{
        QJsonDocument doc;
        QJsonObject obj;
        QByteArray data_json;
        QFile input(fileName);

        if(input.open(QIODevice::ReadOnly | QIODevice::Text)){
            data_json = input.readAll();
            doc = doc.fromJson(data_json);
            obj = doc.object();

            int value1 = obj["Value1"].toInt();
            double value2 = obj["Value2"].toDouble();
            QString value3 = obj["Value3"].toString();
            int value4 = obj["Value4"].toInt();

            ui->sB_value1->setValue(value1);
            ui->dSB_value2->setValue(value2);
            ui->lE_value3->setText(value3);
            ui->cB_value4->setCurrentIndex(value4);

        }
        else{

        }

    }
}


void MainWindow::on_pB_SaveJson_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save JSON","/","JSON (*.json)");

    if(fileName.isEmpty()){

    }else{
        //Get Data from GUI
        int value1 = ui->sB_value1->value();
        double value2 = ui->dSB_value2->value();
        QString value3 = ui->lE_value3->text();
        int value4 = ui->cB_value4->currentIndex();


        QJsonDocument doc;
        QJsonObject obj;
        obj["Value1"] = value1;
        obj["Value2"] = value2;
        obj["Value3"] = value3;
        obj["Value4"] = value4;

        doc.setObject(obj);

        QByteArray data_json = doc.toJson();
        QFile output(fileName);

        if(output.open(QIODevice::WriteOnly | QIODevice::Text)){
            output.write(data_json);
            output.close();
            std::cout << "Saved" << std::endl;
        }
        else{
            std::cout << "Error Saved" << std::endl;
        }


    }
}

