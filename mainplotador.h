#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QColor>
#include <vector>
#include "lehfuncao.h"
#include "evaluator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPlotador;
}
QT_END_NAMESPACE

class MainPlotador : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPlotador(QWidget *parent = nullptr);
    ~MainPlotador() override;

private slots:
    void slotIncluirFuncao(QString Funcao, QColor Cor);

    void on_actionFun_o_triggered();

    void on_actionApagar_triggered();

    void on_actionSair_triggered();

    void on_spinMinX_valueChanged(int arg1);

    void on_spinMaxX_valueChanged(int arg1);

    void on_spinExpX_valueChanged(int arg1);

    void on_spinMinY_valueChanged(int arg1);

    void on_spinMaxY_valueChanged(int arg1);

    void on_spinExpY_valueChanged(int arg1);

    void on_pushApagar_clicked();

    void slotGraficoClicked(QPointF point);

private:
    Ui::MainPlotador *ui;

    //novas funcoes membro privadas
    void exibirFuncoes();
    double convXtoJ(double X) const;
    double convYtoI(double Y) const;
    double convJtoX(double J) const;
    double convItoY(double I) const;
    void desenharGrafico();

    // novos dados membro privados:
    LehFuncao* lehFuncao;
    std::vector<Evaluator> eval;
    std::vector<QColor> cor;
    int largura,altura;
    double minX,maxX,minY,maxY;
    int nMarcX,nMarcY;

    //Para auto ajuste do grafico
    void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINPLOTADOR_H
