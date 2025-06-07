#ifndef LEHFUNCAO_H
#define LEHFUNCAO_H

#include <QDialog>
namespace Ui {
class LehFuncao;
}

class LehFuncao : public QDialog
{
    Q_OBJECT

public:
    explicit LehFuncao(QWidget *parent = nullptr);
    ~LehFuncao();
    void clear();

private slots:
    void on_buttonBox_accepted();

signals:
    void signDefinirFuncao(const QString &funcao);

private:
    Ui::LehFuncao *ui;
};

#endif // LEHFUNCAO_H
