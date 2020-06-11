#include "simplexproblem.h"
#include "ui_simplexproblem.h"
#include "SimplexSolver.h"
#include <iostream>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <bits/stdc++.h>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QtDebug>
#include <string>
#include <QTextBrowser>
using namespace std;

SimplexProblem::SimplexProblem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimplexProblem)
{
    ui->setupUi(this);
}

SimplexProblem::~SimplexProblem()
{
    delete ui;
}

void SimplexProblem::on_genrerateMatrixButton_clicked()
{
    int colSize = ui->columnSpinBox->text().toInt();
    int rowSize = ui->rowSpinBox->text().toInt();
    int variableSize = ui->variablesSpinBox->text().toInt();
    int constraintSize = ui->constraintsSpinBox->text().toInt();

    ui->objectiveTableWidget->setColumnCount(variableSize);
    ui->constraintsTableWidget->setRowCount(constraintSize);
    ui->simplexTableWidget->setColumnCount(colSize);
    ui->simplexTableWidget->setRowCount(rowSize);
}

void SimplexProblem::on_SimplexSolveButton_clicked()
{
    int colSize = ui->columnSpinBox->text().toInt();
    int rowSize = ui->rowSpinBox->text().toInt();
    int variableSize = ui->variablesSpinBox->text().toInt();
    int constraintSize = ui->constraintsSpinBox->text().toInt();

    int i;
    int j;

    float objective[variableSize];
    for(j=0; j < variableSize; j++)
    {
        objective[j] = ui->objectiveTableWidget->item(0,j)->text().toFloat();
        objective[j] = objective[j]*-1;
    }
    ui->simplexOutputTextBrowser->insertPlainText("Objective Function:\n");
    for(j=0; j < variableSize; j++)
    {
        ui->simplexOutputTextBrowser->insertPlainText(QString::number(objective[j]) + "\t");
    }



    float constraints[constraintSize];
    for(i=0; i < constraintSize; i++)
    {
         constraints[i] = ui->constraintsTableWidget->item(i,0)->text().toFloat();
    }
    ui->simplexOutputTextBrowser->insertPlainText("\n\nProblem Constraints:\n");
    for(i=0; i < constraintSize; i++)
    {
         ui->simplexOutputTextBrowser->insertPlainText(QString::number(constraints[i]) + "\n");
    }



    float matrix[rowSize][colSize];
    for(i=0; i < rowSize; i++)
    {
        for(j=0; j < colSize; j++)
        {
            matrix[i][j] = ui->simplexTableWidget->item(i,j)->text().toFloat();
        }
    }
    ui->simplexOutputTextBrowser->insertPlainText("\n\nInitialMatrix:\n");
    for(i=0; i < rowSize; i++)
    {
        for(j=0; j < colSize; j++)
        {
            ui->simplexOutputTextBrowser->insertPlainText("\t" + QString::number(matrix[i][j]));
        }
        ui->simplexOutputTextBrowser->insertPlainText("\n");
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector <std::vector<float> > vec2D(rowSize, std::vector<float>(colSize, 0));
    std::vector<float> b(constraintSize,0);
    std::vector<float> c(variableSize,0);

    for(int i=0;i<rowSize;i++)
    {
         for(int j=0; j<colSize;j++)
         {
             vec2D[i][j] = matrix[i][j];
         }
    }

    for(int i=0;i<constraintSize;i++)
    {
         b[i] = constraints[i];
    }

     for(int i=0;i<variableSize;i++)
    {
         c[i] = objective[i];
    }

     Simplex simplex(vec2D,b,c,ui);
     simplex.CalculateSimplex();
 }












