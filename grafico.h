#ifndef GRAFICO_H
#define GRAFICO_H

#include "evaluator.h"
#include <QLabel>

class Grafico : public QLabel
{
    Q_OBJECT
public:
    explicit Grafico(QWidget *parent = nullptr);
    bool empty();
    void setLimites(int MinX, int MaxX, int MinY, int MaxY, int Expoente);
    void setFuncao(const std::string& S);
    void clearFuncao();
    void setCor(int R, int G, int B);
    void apagar();
    void plotar();
private:
    double convXtoJ(double X) const;
    double convYtoI(double Y) const;
    double convJtoX(double J) const;
    double convItoY(double I) const;
    void mouseReleaseEvent(QMouseEvent *event) override;
    Evaluator eval;
    QPixmap img;
    QColor cor;
    int largura, altura;
    double minX,maxX,minY,maxY;
    int nMarcX,nMarcY;
    void resizeEvent(QResizeEvent *event) override;
signals:
    void signGraficoClicked(double X, double Y);
};

#endif // GRAFICO_H
