#ifndef GRAFICO_H
#define GRAFICO_H

#include <QLabel>
#include <QPointF>
// Por seguranca vou adicionar o QMouseEvent
#include <QMouseEvent>

class Grafico : public QLabel
{
    Q_OBJECT

public:
    Grafico(QWidget *parent = nullptr);

signals:
    void signGraficoClicked(QPointF point);

private:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // GRAFICO_H
