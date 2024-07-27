#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    g.save_results();
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "", tr("Text Files (*.txt)"));
    g.open_file(fileName.toStdString());
    ui->textEdit->setPlainText(QString(g.get_source().c_str()));
}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    QString what = ui->lineEdit->text();
    bool use_regex = ui->checkBox->isChecked();
    if(use_regex)
    {
        std::string output = g.search_regex(what.toStdString());
        ui->textEdit->setPlainText(output.c_str());
    }
    else
    {
        std::string output = g.search(what.toStdString());
        ui->textEdit->setPlainText(output.c_str());
    }
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    ui->textEdit->setPlainText(g.get_source().c_str());
}

