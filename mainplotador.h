#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include "evaluator.h"
#include "lehfuncao.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPlotador;
}
QT_END_NAMESPACE

class MainPlotador : public QMainWindow
{
    Q_OBJECT

public:
    MainPlotador(QWidget *parent = nullptr);
    ~MainPlotador();

private slots:
    void on_actionFun_o_triggered();

    void on_actionPlotar_triggered();

    void on_actionApagar_triggered();

    void on_actionSair_triggered();

    void on_spinMinX_valueChanged(int arg1);

    void on_spinMaxX_valueChanged(int arg1);

    void on_spinMinY_valueChanged(int arg1);

    void on_spinMaxY_valueChanged(int arg1);

    void on_spinExpoente_valueChanged(int arg1);

    void on_radioAzul_clicked();

    void on_radioVermelho_clicked();

    void on_radioVerde_clicked();

    void on_pushPlotar_clicked();

    void on_pushApagar_clicked();

    void slotDefinirFuncao(QString &funcao);

private:
    Ui::MainPlotador *ui;
    double convXtoJ(double X);
    double convYtoI(double Y);
    double convJtoX(double J);
    double convItoY(double I);
    LehFuncao *lehFuncao;
    Evaluator eval;
    QPixmap img;
    QColor cor;
    int largura, altura;
    double minX,maxX,minY,maxY;
    int nMarcX,nMarcY;
};
#endif // MAINPLOTADOR_H
