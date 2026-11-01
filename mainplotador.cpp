#include "mainplotador.h"
#include "ui_mainplotador.h"
//POR SEGURANÇA COMO FOI UTILIZADO O POW IREI INCLUIR A <CMATH>
#include <cmath>
#include <QMessageBox>
#include <QPen>
#include <QPainter>
#include <QLineF>
#include <QString>

MainPlotador::MainPlotador(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPlotador)
    , lehFuncao(new LehFuncao(this))
    , eval()
    , cor()
    , largura(0)
    , altura(0)
    , minX(0.0), maxX(0.0)
    , minY(0.0), maxY(0.0)
    , nMarcX(0), nMarcY(0)
{
    ui->setupUi(this);

    connect(lehFuncao, &LehFuncao::signIncluirFuncao, this, &MainPlotador::slotIncluirFuncao);

    connect(ui->grafico, &Grafico::signGraficoClicked, this, &MainPlotador::slotGraficoClicked);

    //Mude a cor de fundo do cabeçalho horizontal
    ui->tableFuncoes->setStyleSheet("QHeaderView::section{background-color:lightgray}");

    //Mude a política de redimensionamento das colunas
    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    //Fixe o texto do cabeçalho das 2 colunas como sendo “COR” E “FUNCAO”:
    ui->tableFuncoes->setHorizontalHeaderLabels(QStringList() << "COR" << "FUNCAO");

    //Atribua os valores atuais da interface aos limites do grafico
    minX = ui->spinMinX->value() * pow(10.0, ui->spinExpX->value());
    maxX = ui->spinMaxX->value() * pow(10.0, ui->spinExpX->value());
    minY = ui->spinMinY->value() * pow(10.0, ui->spinExpY->value());
    maxY = ui->spinMaxY->value() * pow(10.0, ui->spinExpY->value());

    //Atribua os valores atuais da interface ao numero de marcadores do gráfico:
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();
    //Ao final do construtor, chame a função desenharGrafico
    desenharGrafico();
}

MainPlotador::~MainPlotador()
{
    delete ui;
}

void MainPlotador::slotIncluirFuncao(QString Funcao, QColor Cor)
{
    try{
        //Crie um objeto da classe Evaluator, denominado new_eval
        Evaluator new_eval;

        //fixe a funcao a ser evaluada por new_eval como sendo o parametro Funcao
        new_eval.set(Funcao.toStdString());

        // Insira o objeto new_eval no dado membro eval, com push_back.
        eval.push_back(new_eval);

        //Insira o parametro Cor no dado membro cor, com push_back.
        cor.push_back(Cor);

        //Chame a funcao exibirFuncoes
        exibirFuncoes();

        //chame a funcao desenharGrafico
        desenharGrafico();
    } catch (const std::exception &E){
        //Em caso de erro Exiba uma janela QMessageBox::critical com título "Funcao invalida" e texto igual a "Erro na funcao: " mais o E.what()
        QMessageBox::critical(this, "Funcao invalida", QString("Erro na funcao: ") + E.what());
    }
}

void MainPlotador::on_actionFun_o_triggered()
{
    //limpa eventual conteudo anterior da janela de digitacao de funcao
    lehFuncao->clear();

    //exibe o objeto para o qual lehFuncao aponta, usando a funcao show dos widgets Qt
    lehFuncao->show();

}


void MainPlotador::on_actionApagar_triggered()
{
    // mesma coisa que o botao Apagar. Portanto, apenaschama a funcao/slot
    on_pushApagar_clicked();
}


void MainPlotador::on_actionSair_triggered()
{
    //on_actionSair_triggered – chama QCoreApplication::quit().
    QCoreApplication::quit();
}


void MainPlotador::on_spinMinX_valueChanged(int arg1)
{
    //Recalcula o novo valor dos dados membro minX e nMarcX:
    minX = arg1 * pow(10.0,ui->spinExpX->value());
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();

    //O valor maximo do eixo X tem que ser maior que o valor minimo
    ui->spinMaxX->setMinimum(arg1+1);

    //Redesenha o grafico
    desenharGrafico();
}


void MainPlotador::on_spinMaxX_valueChanged(int arg1)
{
    //Recalcula o novo valor dos dados membro maxX e nMarcX:
    maxX = arg1 * pow(10.0,ui->spinExpX->value());
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();

    //O valor minimo do eixo X tem que ser menor que o valor maximo
    ui->spinMinX->setMaximum(arg1-1);

    //Redesenha o grafico
    desenharGrafico();
}


void MainPlotador::on_spinExpX_valueChanged(int arg1)
{
    //Recalcula o novo valor dos dados membro maxX e minX:
    maxX = ui->spinMaxX->value() * pow(10.0, arg1);
    minX = ui->spinMinX->value() * pow(10.0, arg1);

    //Redesenha o grafico
    desenharGrafico();
}


void MainPlotador::on_spinMinY_valueChanged(int arg1)
{
    //Recalcula o novo valor dos dados membro minX e nMarcX:
    minY = arg1 * pow(10.0,ui->spinExpY->value());
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    //O valor maximo do eixo X tem que ser maior que o valor minimo
    ui->spinMaxY->setMinimum(arg1+1);

    //Redesenha o grafico
    desenharGrafico();
}


void MainPlotador::on_spinMaxY_valueChanged(int arg1)
{
    //Recalcula o novo valor dos dados membro maxX e nMarcX:
    maxY = arg1 * pow(10.0,ui->spinExpY->value());
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    //O valor minimo do eixo X tem que ser menor que o valor maximo
    ui->spinMinY->setMaximum(arg1-1);

    //Redesenha o grafico
    desenharGrafico();
}


void MainPlotador::on_spinExpY_valueChanged(int arg1)
{
    //Recalcula o novo valor dos dados membro maxX e minX:
    maxY = ui->spinMaxY->value() * pow(10.0, arg1);
    minY = ui->spinMinY->value() * pow(10.0, arg1);

    //Redesenha o grafico
    desenharGrafico();
}


void MainPlotador::on_pushApagar_clicked()
{
    //Limpe as funcoes a serem tracadas
    eval.clear();

    //Limpe as cores de tracagem
    cor.clear();

    //Reexiba a lista de funcoes
    exibirFuncoes();

    //Redesenha o grafico
    desenharGrafico();
}

void MainPlotador::exibirFuncoes()
{
    //Apague o conteudo anterior (clearContents) da tabela de funcoes (tableFuncoes)
    ui->tableFuncoes->clearContents();
    // Fixe o numero de linhas (setRowCount) da tabela de funcoes (tableFuncoes) como sendo igual ao numero de funcoes a serem plotadas (eval.size()).
    ui->tableFuncoes->setRowCount(eval.size());

    //Crie dois objetos:

    //Um ponteiro
    QLabel* prov;

    //Uma imagem pixmap de tamanho 20x20
    QPixmap img(20,20);

    //Percorra os indices de todas as funcoes, fazendo k variar de 0 a eval.size()-1:
    //O compilador estava reclamando do tipo de comparacao que estava sendo feita... pesquisei um pouco e vi a necessidade de utilizar o static_cast<int>
    for(int k=0; k < static_cast<int>(eval.size()); ++k){

        //Preencha (fill) a imagem (img) com a k-esima cor (cor.at(k)).
        img.fill(cor.at(k));

        //Aloque dinamicamente (new) um novo QLabel e armazene no ponteiro prov.
        prov = new QLabel(this);

        //Altere o alinhamento (setAlignment) do QLabel para o qual prov aponta
        prov->setAlignment(Qt::AlignCenter);

        //Altere a imagem (setPixmap) do QLabel para o qual prov aponta para ser img
        prov->setPixmap(img);

        //Fixe o widget (setCellWidget) da linha k, coluna 0 da tabela de funcoes (tableFuncoes) para ser prov.
        ui->tableFuncoes->setCellWidget(k, 0, prov);

        //Aloque dinamicamente (new) um novo QLabel e armazene no mesmo ponteiro prov
        prov = new QLabel(this);

        //Altere o alinhamento (setAlignment) do QLabel para o qual prov aponta
        prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

        //Altere o QLabel para quebrar linhas grandes: prov->setWordWrap(true);
        prov->setWordWrap(true);

        //Altere o texto (setText) do QLabel para o qual prov aponta
        prov->setText(QString::fromStdString(eval.at(k).getText()));

        //Fixe o widget (setCellWidget) da linha k, coluna 1 da tabela de funções (tableFuncoes) para ser prov.
        ui->tableFuncoes->setCellWidget(k, 1, prov);
    }
}

double MainPlotador::convXtoJ(double X) const
{
    return (largura-1)*(X-minX)/(maxX-minX);
}

double MainPlotador::convYtoI(double Y) const
{
    return (altura-1)*(maxY-Y)/(maxY-minY);
}

double MainPlotador::convJtoX(double J) const
{
    return minX+(maxX-minX)*J/(largura-1);
}

double MainPlotador::convItoY(double I) const
{
    return maxY-(maxY-minY)*I/(altura-1);
}

void MainPlotador::desenharGrafico()
{
    //Crie uma caneta (QPen pen) e um desenhador (QPainter painter) para plotar os graficos.
    QPen pen;
    QPainter painter;

    //Faca os dados membro largura e altura serem iguais a largura width() e altura height()
    largura = ui->grafico->width();
    altura = ui->grafico->height();

    //Crie uma imagem pixmap (QPixmap img) de dimensoes largura e altura.
    QPixmap img(largura, altura);

    //Preencha img com a cor branca, usando a funcao fill da classe QPixmap.
    img.fill(Qt::white);

    //inicie o desenho1 na imagem com o desenhador: painter.begin(&img);
    painter.begin(&img);

    //Para desenhar os eixos, fixe a caneta (pen) para ter cor preta e largura da linha de 3px e associe a caneta ao desenhador (setPen).
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    // Para verificar se o eixo X esta visivel
    double Izero = convYtoI(0.0);

    // Se o eixo X estiver visivel (Izero entre 0.0 e altura-1.0):
    if (Izero >= 0.0 && Izero <= altura - 1.0) {
        // Trace uma linha de [0.0, Izero] ate [largura-1.0, Izero]
        painter.drawLine(QLineF(0.0, Izero, largura - 1.0, Izero));

        // Faca a variavel inteira i variar de 0 a nMarcX-1. Para cada valor, faca uma marcacao no eixo:
        for (int i = 0; i < nMarcX; ++i) {
            double Jmarc = convXtoJ(minX + (maxX - minX) * i / (nMarcX - 1.0));
            painter.drawLine(QLineF(Jmarc, Izero - 3.0, Jmarc, Izero + 3.0));
        }
    } // Se o eixo X nao estiver visivel, nao desenhe nada (nem o eixo, nem os marcadores)

    // Desenhe (ou nao, se nao estiver visivel) o eixo Y e seus marcadores, de forma similar ao eixo X.
    double Jzero = convXtoJ(0.0);

    // Se o eixo Y estiver visível (Jzero entre 0.0 e largura-1.0):
    if (Jzero >= 0.0 && Jzero <= largura - 1.0) {
        // Trace uma linha vertical de [Jzero, 0.0] ate [Jzero, altura - 1.0]
        painter.drawLine(QLineF(Jzero, 0.0, Jzero, altura - 1.0));

        // Faca a variável inteira i variar de 0 a nMarcY-1. Para cada valor, faca uma marcacao no eixo:
        for (int i = 0; i < nMarcY; ++i) {
            double Imarc = convYtoI(minY + (maxY - minY) * i / (nMarcY - 1.0));
            painter.drawLine(QLineF(Jzero - 3.0, Imarc, Jzero + 3.0, Imarc));
        }
    } // Se o eixo Y nao estiver visivel, nao desenhe nada (nem o eixo, nem os marcadores)

    //Se o vetor de funcaes (eval) estiver vazio (empty), ou seja, sem nenhuma funcao definida:
    if(eval.empty()){
        //Conclua o desenhador (funcao end da classe QPainter).
        painter.end();

        //Exiba o objeto img no QLabel grafico (ui->grafico), usando a funcao setPixmap.
        ui->grafico->setPixmap(img);

        // Encerre (return) a funcao desenharGrafico.
        return;
    }
    //Crie variaveis double para conter:
    //X,Y: valores dos pontos da funcao a serem plotados.
    double X, Y;

    //I, Iant: coordenada (linha) que corresponde ao valor Y do ponto atual e do anterior.
    double I, Iant;

    // Para desenhar as curvas das funcoes, fixe a caneta (pen) para ter largura da linha de 1px.
    pen.setWidth(1);

    //Percorra os indices de todas as funcoes, fazendo k variar de 0 a eval.size()-1:
    for (int k = 0; k < static_cast<int>(eval.size()); ++k) {
        //Fixe a caneta (pen) para ter a cor associada a essa k-esima funcao (cor.at(k)) e associe a caneta ao desenhador (setPen).
        pen.setColor(cor.at(k));
        painter.setPen(pen);

        //Atribua a coordenada linha do ponto anterior (Iant) um valor invalido (-1.0, por exemplo), ja que o primeiro ponto da curva nao tem ponto anterior
        Iant = -1.0;

        //Faca a coordenada coluna J (int) do ponto a ser tracado variar de 0 a largura-1:
        for (int J = 0; J < largura; ++J) {
            //Calcule o valor X correspondente a coordenada coluna J: X = convJtoX(J)
            X = convJtoX(J);

            //Calcule o valor Y correspondente ao valor X, evaluando a funcao atraves da chamada ao operator() da k-esima funcao: Y = eval.at(k)(X)
            Y = eval.at(k)(X);

            //Calcule a coordenada linha I correspondente ao valor Y: I = convYtoI(Y)
            I = convYtoI(Y);

            //Se tanto a coordenada linha do ponto atual (I) quanto a coordenada linha do ponto anterior (Iant) estiverem dentro dos limites (de 0 a altura-1),
            if (I >= 0.0 && I <= (altura - 1.0) && Iant >= 0.0 && Iant <= (altura - 1.0)) {
                //desenhe uma linha de [J1,Iant] ate [J,I], usando a funcao drawLine2 da classe QPainter.
                painter.drawLine(QLineF((J) - 1.0, Iant, (J), I));
            }

            //Faca Iant = I.
            Iant = I;
        }
    }
    //Conclua o desenhador (funcao end da classe QPainter).
    painter.end();

    //Exiba o objeto img no QLabel grafico (ui->grafico), usando a funcao setPixmap.
    ui->grafico->setPixmap(img);
}
// Para auto ajuste do grafico
void MainPlotador::resizeEvent(QResizeEvent *event)
{
    //Chame a função original de redimensionamento da classe QMainWindow:
    QMainWindow::resizeEvent(event);

    //Se o tamanho antigo, event->oldSize(), for diferente do novo, event->size() chame a função desenharGrafico
    if(event->oldSize() != event->size()){
        desenharGrafico();
    }
}
void MainPlotador::slotGraficoClicked(QPointF point)
{
    //Converta as coordenadas point.x() e point.y() para os valores X e Y
    double X = convJtoX(point.x());
    double Y = convItoY(point.y());

    //Forme uma QString com conteúdo “X=<X> Y=<Y>”
    QString texto = QString("X=%1 Y=%2").arg(X).arg(Y);

    //Exiba a QString na barra de status, que pode ser acessada via statusBar()
    statusBar()->showMessage(texto, 2000);
}

