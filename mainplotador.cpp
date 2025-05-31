#include "mainplotador.h"
#include "ui_mainplotador.h"
#include <QMessageBox>
#include <QPainter>
#include <QPen>


MainPlotador::MainPlotador(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPlotador)
    , lehFuncao(new LehFuncao(this))
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
    ui->setupUi(this);
    connect(lehFuncao, &LehFuncao::signDefinirFuncao,
            this, &::MainPlotador::slotDefinirFuncao);

    minX = ui->spinMinX->value() * pow(10.0, ui->spinExpoente->value());
    maxX = ui->spinMaxX->value() * pow(10.0, ui->spinExpoente->value());
    minY = ui->spinMinY->value() * pow(10.0, ui->spinExpoente->value());
    maxY = ui->spinMaxY->value() * pow(10.0, ui->spinExpoente->value());

    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    on_pushApagar_clicked();
}

MainPlotador::~MainPlotador()
{
    delete ui;
}

void MainPlotador::on_actionFun_o_triggered()
{
    lehFuncao->clear();
    lehFuncao->show();
}


void MainPlotador::on_actionPlotar_triggered()
{
    on_pushPlotar_clicked();
}


void MainPlotador::on_actionApagar_triggered()
{
    on_pushApagar_clicked();
}


void MainPlotador::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainPlotador::on_spinMinX_valueChanged(int arg1)
{
    minX = arg1 * pow(10.0,ui->spinExpoente->value());
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    ui->spinMaxX->setMinimum(1+arg1);
    on_pushApagar_clicked();

}


void MainPlotador::on_spinMaxX_valueChanged(int arg1)
{
    maxX = arg1 * pow(10.0, ui->spinExpoente->value());
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();

    on_pushApagar_clicked();
}


void MainPlotador::on_spinMinY_valueChanged(int arg1)
{
    minY = arg1 * pow(10.0, ui->spinExpoente->value());
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    ui->spinMaxY->setMinimum(1 + arg1);

    on_pushApagar_clicked();
}


void MainPlotador::on_spinMaxY_valueChanged(int arg1)
{
    maxY = arg1 * pow(10.0, ui->spinExpoente->value());
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    on_pushApagar_clicked();
}


void MainPlotador::on_spinExpoente_valueChanged(int arg1)
{
    minX = ui->spinMinX->value() * pow(10.0, arg1);
    maxX = ui->spinMinY->value() * pow(10.0, arg1);
    minY = ui->spinMinY->value() * pow(10.0, arg1);
    maxY = ui->spinMaxY->value() * pow(10.0, arg1);
}


void MainPlotador::on_radioAzul_clicked()
{
    this->cor = QColor(0,0,255);
}


void MainPlotador::on_radioVermelho_clicked()
{
    this->cor = QColor(255,0,0);
}


void MainPlotador::on_radioVerde_clicked()
{
    cor = QColor(0,255,0);
}


void MainPlotador::on_pushPlotar_clicked()
{
    if (eval.empty())
    {
        QMessageBox::warning(this, "Funcao indefinida" , "A funcao a ser plotada nao estah definida");
        return;
    }
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

    ui->grafico->setPixmap(img);

}


void MainPlotador::on_pushApagar_clicked()
{
    largura = ui->grafico->width();
    altura = ui->grafico->height();

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

    ui->grafico->setPixmap(img);
}

void MainPlotador::slotDefinirFuncao(QString &funcao)
{
    std::string func = funcao.toStdString();
    try {
        eval.set(func);
        ui->textoFuncao->setPlainText(funcao);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Funcao invalida", "Erro na funcao" + QString::fromStdString(e.what()));

        eval.clear();
        ui->textoFuncao->clear();

    }
}

double MainPlotador::convXtoJ(double X)
{
    return (largura - 1) * (X - minX) / (maxX-minX);
}

double MainPlotador::convYtoI(double Y)
{
    return (altura-1) * (maxY-Y) / (maxY-minY);

}

double MainPlotador::convJtoX(double J)
{
    return minX + (maxX-minX)*J / (largura-1);
}

double MainPlotador::convItoY(double I)
{
    return maxY - (maxY-minY) * I / (altura-1);

}

