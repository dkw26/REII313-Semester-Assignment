#ifndef SIMPLEXSOLVER_H
#define SIMPLEXSOLVER_H

#include "simplexproblem.h"
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

namespace Ui {
    class Simplex;
}


class Simplex
{
    private:
        Ui::SimplexProblem *ui;
        int rows, cols;
        std::vector <std::vector<float> > A;
        std::vector<float> B;
        std::vector<float> C;
        float maximum;
        bool is_Unbounded;
    public:
        Simplex(std::vector <std::vector<float> > matrix,std::vector<float> b ,std::vector<float> c,Ui::SimplexProblem *ui)
        {
            this->ui = ui;
            maximum = 0;
            is_Unbounded = false;
            rows = matrix.size();
            cols = matrix[0].size();
            A.resize(rows, vector<float> (cols,0));
            B.resize(b.size());
            C.resize(c.size());
            for(int i=0; i<rows; i++)
            {
                for(int j=0; j<cols; j++)
                {
                    A[i][j] = matrix[i][j];
                }
            }
            for(int i=0; i<c.size(); i++)
            {
                C[i] = c[i] ;
            }
            for(int i=0; i<b.size(); i++)
            {
                B[i] = b[i];
            }
        }

        bool check_Optimality()
        {
            bool is_Optimal = false;
            int positve_ValueCount = 0;
            for(int i=0; i<C.size(); i++)
            {
                float value = C[i];
                if(value >= 0)
                {
                    positve_ValueCount++;
                }
            }
            if(positve_ValueCount == C.size())
            {
                is_Optimal = true;
                print();
            }
            return is_Optimal;
        }

        bool Simplex_Calculataion()
        {
            if(check_Optimality() == true)
            {
                        return true;
            }
            int pivot_Column = find_PivotColumn();
            if(is_Unbounded == true)
            {
                ui->simplexOutputTextBrowser->insertPlainText("Error: It is unbounded\n");

                            return true;
            }
            int pivot_Row = find_PivotRow(pivot_Column);
            do_Pivotting(pivot_Row, pivot_Column);
            return false;
        }

        void do_Pivotting(int pivot_Row, int pivot_Column)
        {
            float pivot_Value = A[pivot_Row][pivot_Column];
            float pivot_RowVals[cols];
            float pivot_ColVals[rows];
            float row_New[cols];
            maximum = maximum - (C[pivot_Column]*(B[pivot_Row]/pivot_Value));
            for(int i=0;i<cols;i++)
            {
               pivot_RowVals[i] = A[pivot_Row][i];
            }
            for(int j=0;j<rows;j++)
            {
               pivot_ColVals[j] = A[j][pivot_Column];
            }
            for(int k=0;k<cols;k++)
            {
               row_New[k] = pivot_RowVals[k]/pivot_Value;
            }

            B[pivot_Row] = B[pivot_Row]/pivot_Value;
            for(int m=0;m<rows;m++)
            {
               if(m != pivot_Row)
               {
                   for(int p=0; p<cols; p++)
                   {
                       float multiply_Value = pivot_ColVals[m];
                       A[m][p] = A[m][p] - (multiply_Value*row_New[p]);
                   }
               }
             }
            for(int i=0;i<B.size();i++)
            {
                if(i != pivot_Row)
                {
                        float multiply_Value = pivot_ColVals[i];
                        B[i] = B[i] - (multiply_Value*B[pivot_Row]);
                }
            }
                float multiply_Value = C[pivot_Column];
                 for(int i=0;i<C.size();i++)
                {
                    C[i] = C[i] - (multiply_Value*row_New[i]);
                }
             for(int i=0;i<cols;i++)
            {
                A[pivot_Row][i] = row_New[i];
             }
        }

        void print()
        {
            for(int i=0; i<rows;i++)
            {
                for(int j=0;j<cols;j++)
                {
                    ui->simplexOutputTextBrowser->insertPlainText("\t" + QString::number(A[i][j]));
                }
                ui->simplexOutputTextBrowser->insertPlainText("\n");                                               
            }
            ui->simplexOutputTextBrowser->insertPlainText(" ");
        }

        int find_PivotColumn()
        {
            int location = 0;
            float minm = C[0];
            for(int i=1; i<C.size(); i++)
            {
                if(C[i] < minm)
                {
                    minm = C[i];
                    location = i;
                }
            }
            return location;
        }

        int find_PivotRow(int pivot_Column)
        {
            float positive_Values[rows];
            std::vector<float> result(rows,0);
            int negative_ValueCount = 0;
            for(int i=0;i<rows;i++)
            {
                if(A[i][pivot_Column]>0)
                {
                    positive_Values[i] = A[i][pivot_Column];
                }
                else{
                    positive_Values[i]=0;
                    negative_ValueCount+=1;
                }
            }
            if(negative_ValueCount==rows)
            {
                is_Unbounded = true;
            }
            else
            {
                for(int i=0;i<rows;i++)
                    {
                    float value = positive_Values[i];
                    if(value>0)
                    {
                        result[i] = B[i]/value;
                    }
                    else
                    {
                        result[i] = 0;
                    }
                }
            }
            float minimum = 99999999;
            int location = 0;
            for(int i=0; i<sizeof(result)/sizeof(result[0]); i++)
            {
                if(result[i] > 0)
                {
                    if(result[i] < minimum)
                    {
                        minimum = result[i];
                        location = i;
                    }
                }
            }
            return location;
        }

        void Calculate_Simplex()
        {
            bool end = false;
            ui->simplexOutputTextBrowser->insertPlainText(" \n");
            ui->simplexOutputTextBrowser->insertPlainText("Final matrix (Optimal solution)\n");

            while(!end)
            {
                bool result = Simplex_Calculataion();
                if(result==true)
                {
                    end = true;
                }
            }
            ui->simplexOutputTextBrowser->insertPlainText("\nAnswers for the Constraints of variables \n");

            for(int i=0; i<A.size(); i++)
                {
                int count0 = 0;
                int index = 0;
                for(int j=0; j<rows; j++)
                {
                    if(A[j][i] == 0.0)
                    {
                        count0 += 1;
                    }
                    else if(A[j][i] == 1)
                    {
                        index = j;
                    }
                }
                if(count0 == rows -1)
                {

                    ui->simplexOutputTextBrowser->insertPlainText("variable" + QString::number(index+1) + ": " + QString::number(B[index]) + "\n");
                }
                else
                {

                    ui->simplexOutputTextBrowser->insertPlainText("variable" + QString::number(index+1) + ": " + "0" + "\n");
                }
            }
            ui->simplexOutputTextBrowser->insertPlainText(" \n");

            ui->simplexOutputTextBrowser->insertPlainText("maximum value: " + QString::number(maximum) + "\n");

        }
};




#endif // SIMPLEXSOLVER_H
