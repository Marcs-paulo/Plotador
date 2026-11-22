#ifndef LEHFUNCAO_H
#define LEHFUNCAO_H

#include <QDialog>
#include <QColor>
#include <QString>

namespace Ui {
class LehFuncao;
}

class LehFuncao : public QDialog
{
    Q_OBJECT

public:
    explicit LehFuncao(QWidget *parent = nullptr);
    ~LehFuncao();

    void clear(); // Nova funcao membro publica, clear (sem parâmetros)

signals:
    void signIncluirFuncao(QString Funcao, QColor Cor);

private slots:
    void on_radioAzul_clicked();

    void on_radioVermelho_clicked();

    void on_radioVerde_clicked();

    void on_radioPreto_clicked();

    void on_buttonBox_accepted();

private:
    Ui::LehFuncao *ui;
    QColor cor; // Novo dado membro privado, cor, do tipo QColor.
};

#endif // LEHFUNCAO_H
