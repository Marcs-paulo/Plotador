#ifndef GRAFICO_H
#define GRAFICO_H

#include <QLabel>

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
