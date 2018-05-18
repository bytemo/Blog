#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmd = new QProcess(this);
    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
    connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));

    cmd->start("bash");
    cmd->waitForStarted();
}

MainWindow::~MainWindow()
{
        if(cmd)
        {
            cmd->terminate();
            cmd->waitForFinished();
        }
    delete ui;
}

void MainWindow::on_readoutput()
{
    ui->textEdit->append(cmd->readAllStandardOutput().data());
}

void MainWindow::on_readerror()
{
    QMessageBox::information(0, "Error", cmd->readAllStandardError().data());
}


void MainWindow::on_pushButton_clicked()
{
    cmd->write(ui->lineEdit->text().toLocal8Bit() + '\n');
}
