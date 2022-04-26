#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QProcess>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
int nv=88;
using namespace std;

std::string com1()
{
    string cmd="envycontrol -q";
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
      while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
      pclose(stream);
    }
  cout << "LS: " << data << endl;

    const std::string s = data;
    return s;
}

std::string com2()
{
    string cmd="envycontrol -v";
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
      while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
      pclose(stream);
    }
  cout << "LS: " << data << endl;

    const std::string s = data;
    return s;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> lcdNumber ->display(nv);
    const QString s1 = QString::fromStdString( com1() );
    ui -> textBrowser_2->append(s1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_2_pressed()
{
    nv=1;
    ui -> lcdNumber ->display(nv);

}


void MainWindow::on_radioButton_3_pressed()
{
    nv=2;
    ui -> lcdNumber ->display(nv);
}


void MainWindow::on_radioButton_pressed()
{
    nv=0;
    ui -> lcdNumber ->display(nv);
}


void MainWindow::on_pushButton_3_clicked()
{

    const QString s="";
    ui -> textBrowser_2 -> setText(s);
    const QString s1 = QString::fromStdString( com1() );
    system("notify-send 'Title' \"Test msg\"");
    ui -> textBrowser_2->append(s1);
}


void MainWindow::on_pushButton_4_clicked()
{
    system("reboot");
}


void MainWindow::on_pushButton_5_clicked()
{
    const QString s="";
    ui -> textBrowser_2 -> setText(s);
    const QString s2 = QString::fromStdString( com2() );
    ui -> textBrowser_2->append(s2);
    const QString s1 = QString::fromStdString( com1() );
    ui -> textBrowser_2->append(s1);
}


void MainWindow::on_pushButton_6_clicked()
{
      system("poweroff");
}


void MainWindow::on_pushButton_clicked()
{
    if(nv==2)
    {
        QProcess p;
        p.QProcess::start("pkexec envycontrol -s hybrid");
        p.waitForFinished(-1);
        ui->textBrowser_2->setText(p.readAllStandardOutput());

    }
    if(nv==0)
    {
        QProcess p;
        p.QProcess::start("pkexec envycontrol -s integrated");
        p.waitForFinished(-1);
        ui->textBrowser_2->setText(p.readAllStandardOutput());

    }
    if(nv==1)
    {
        QProcess p;
        p.QProcess::start("pkexec envycontrol -s nvidia");
        p.waitForFinished(-1);
        ui->textBrowser_2->setText(p.readAllStandardOutput());

    }
    if(nv=88)
    {
        const QString sts="Select a mode before pressing Set...";
        ui ->statusbar->showMessage(sts,2000);
    }
}

