#include "methodsdialog.h"
#include "ui_methodsdialog.h"

MethodsDialog::MethodsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodsDialog)
{
    ui->setupUi(this);
}

MethodsDialog::~MethodsDialog()
{
    delete ui;
}



void MethodsDialog::on_SimplexButton_clicked()
{
    hide();
    simplexProblem = new SimplexProblem(this);
    simplexProblem->show();
}


void MethodsDialog::on_BnBButton_clicked()
{
    hide();
    bnbProblem = new BnBProblem(this);
    bnbProblem->show();
}
