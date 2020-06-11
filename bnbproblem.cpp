#include "bnbSolver.h"
#include "ui_bnbproblem.h"
#include "bnbproblem.h"
#include <QString>

BnBProblem::BnBProblem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BnBProblem)
{
    ui->setupUi(this);
}

BnBProblem::~BnBProblem()
{
    delete ui;
}


void BnBProblem::on_bnbGenerateButton_clicked()
{
    int itemNum = ui->itemsSpinBox->text().toInt();

    ui->valuesTableWidget->setColumnCount(itemNum);
    ui->weightsTableWidget->setColumnCount(itemNum);
}

void BnBProblem::on_BnBSolveButton_clicked()
{
    int itemNum = ui->itemsSpinBox->text().toInt();
    int capacity = ui->capacitySpinBox->text().toInt();


    int i;

    int value[itemNum];
    for(i = 0; i < itemNum; i++)
    {
        value[i] = ui->valuesTableWidget->item(0,i)->text().toInt();
    }

    int weight[itemNum];
    for(i = 0; i < itemNum; i++)
    {
        weight[i] = ui->weightsTableWidget->item(0,i)->text().toInt();
    }

    int n = sizeof(value)/sizeof(value[0]);

    Knapsack solution;
    ui->bnbOutputTextBrowser->insertPlainText("\nThe optimal solution is: " + QString::number(solution.knapsack_Calculation(capacity, weight, value, n)));
}
