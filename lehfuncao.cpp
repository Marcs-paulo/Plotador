#include "lehfuncao.h"
#include "ui_lehfuncao.h"
#include <QColor>

LehFuncao::LehFuncao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LehFuncao)
    , cor(0,0,255) // inicializacao do dado membro cor, com o valor correspondente a cor azul:
{
    ui->setupUi(this);
}

LehFuncao::~LehFuncao()
{
    delete ui;
}

void LehFuncao::clear()
{
    ui->lineEdit->clear();
}
void LehFuncao::on_radioAzul_clicked()
{
    cor = QColor(0,0,255);
}


void LehFuncao::on_radioVermelho_clicked()
{
    cor = QColor(255,0,0);
}


void LehFuncao::on_radioVerde_clicked()
{
    cor = QColor(0,255,0);
}


void LehFuncao::on_radioPreto_clicked()
{
    cor = QColor(0,0,0);
}


void LehFuncao::on_buttonBox_accepted()
{
    emit signIncluirFuncao(ui->lineEdit->text(), cor); //emita o sinal que indica que uma nova funcao foi digitada
}

