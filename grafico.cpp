#include "grafico.h"
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QResizeEvent>

Grafico::Grafico(QWidget *parent)
    : QLabel(parent)

    , eval()
    , img()
    , cor(0,0,255)
    , largura(0)
    , altura(0)
    , minX(0.0)
    , maxX(0.0)
    , minY(0.0)
    , maxY(0.0)
    , nMarcX(0)
    , nMarcY(0)
{

}

bool Grafico::empty()
{
    return eval.empty();
}

void Grafico::setLimites(int MinX, int MaxX, int MinY, int MaxY, int Expoente)
{
    minX = MinX * pow(10.0, Expoente);
    maxX = MaxX * pow(10.0, Expoente);
    minY = MinY * pow(10.0, Expoente);
    maxY = MaxY * pow(10.0, Expoente);
    nMarcX = 1+MaxX-MinX;
    nMarcY = 1+MaxY-MinY;
}

void Grafico::setFuncao(const std::string &S)
{
    eval.set(S);
}

void Grafico::clearFuncao()
{
    eval.clear();
}

void Grafico::setCor(int R, int G, int B)
{
    cor = QColor(R,G,B);
}

void Grafico::apagar()
{
    largura = width();
    altura = height();

    img = QPixmap(largura,altura);
    img.fill(Qt::white);

    QPainter painter(&img);
    QPen pen(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    int Izero = convYtoI(0.0);
    if (Izero >=0 && Izero < altura)
    {
        QLineF linhaX(0.0, (double)Izero, (double)(largura - 1), (double)Izero);
        painter.drawLine(linhaX);
        for (int i = 0; i < nMarcX; ++i)
        {
            int Jmarc = convXtoJ(minX + (maxX - minX) * i / (nMarcX - 1));
            QLineF marcaX(Jmarc, Izero - 3.0, Jmarc, Izero + 3.0);
            painter.drawLine(marcaX);
        }
    }

    int Jzero = convXtoJ(0.0);
    if (Jzero >=0 && Jzero < largura)
    {
        QLineF eixoY(Jzero, 0.0, Jzero, (double)(altura - 1));
        painter.drawLine(eixoY);
        for (int i = 0; i < nMarcX; ++i)
        {
            int Imarc = convYtoI(minY + (maxY - minY) * i / (nMarcY - 1));
            QLineF marcaY(Jzero - 3.0, Imarc, Jzero + 3.0, Imarc);
            painter.drawLine(marcaY);
        }
    }

    setPixmap(img);
}

void Grafico::plotar()
{

    QPainter painter(&img);
    QPen pen(cor);
    pen.setWidth(1);
    painter.setPen(pen);

    double Iant = -1.0;
    for (int J=0; J<largura; ++J)
    {
        double X = convJtoX(J);
        double Y = eval(X);
        double I = convYtoI(Y);
        if (I >= 0 && I < altura && Iant >= 0 && Iant < altura)
        {
            QLineF linha(J - 1.0, Iant, (double)J, I);
            painter.drawLine(linha);

        }
        Iant = I;
    }

    setPixmap(img);
}

double Grafico::convXtoJ(double X) const
{
    return (largura - 1) * (X - minX) / (maxX-minX);
}

double Grafico::convYtoI(double Y) const
{
    return (altura-1) * (maxY-Y) / (maxY-minY);
}

double Grafico::convJtoX(double J) const
{
    return minX + (maxX-minX)*J / (largura-1);
}

double Grafico::convItoY(double I) const
{
    return maxY - (maxY-minY) * I / (altura-1);
}

void Grafico::mouseReleaseEvent(QMouseEvent *event)
{

    emit signGraficoClicked(convJtoX(event->position().x()),convItoY(event->position().y()));

}

void Grafico::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize() != event->size())
    {
        this->apagar();
        if (!this->empty())
        {
            this->plotar();
        }

    }
}
