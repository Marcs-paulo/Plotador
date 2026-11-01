#include "grafico.h"
#include <QMouseEvent>

Grafico::Grafico(QWidget *parent) : QLabel(parent)
{
}

void Grafico::mouseReleaseEvent(QMouseEvent *event){
    //Chame a funcao original da classe QLabel que reage a liberacao de um click
    QLabel::mouseReleaseEvent(event);

    // Emita o sinal signGraficoClicked com o valor de event->position().
    emit signGraficoClicked(event->position());
}
