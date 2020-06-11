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
        bool isUnbounded;
    public:
        Simplex(std::vector <std::vector<float> > matrix,std::vector<float> b ,std::vector<float> c,Ui::SimplexProblem *ui)
        {
            this->ui = ui;
            maximum = 0;
            isUnbounded = false;
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

        bool Simplex_Calculataion()
        {
            if(checkOptimality() == true)
            {
                        return true;
            }
            int pivotColumn = find_PivotColumn();
            if(isUnbounded == true)
            {
                ui->simplexOutputTextBrowser->insertPlainText("Error: It is unbounded\n");
                //cout<<"Error: It is unbounded"<<endl;                       //display error message
                            return true;
            }
            int pivotRow = find_PivotRow(pivotColumn);
            doPivotting(pivotRow, pivotColumn);
            return false;
        }

        bool checkOptimality()
        {
            bool isOptimal = false;
            int positveValueCount = 0;
            for(int i=0; i<C.size(); i++)
            {
                float value = C[i];
                if(value >= 0)
                {
                    positveValueCount++;
                }
            }
            if(positveValueCount == C.size())
            {
                isOptimal = true;
                print();
            }
            return isOptimal;
        }

        void doPivotting(int pivot_Row, int pivotColumn)
        {
            float pivotValue = A[pivot_Row][pivotColumn];
            float pivotRowVals[cols];
            float pivotColVals[rows];
            float rowNew[cols];
            maximum = maximum - (C[pivotColumn]*(B[pivot_Row]/pivotValue));
            for(int i=0;i<cols;i++)
            {
               pivotRowVals[i] = A[pivot_Row][i];
            }
            for(int j=0;j<rows;j++)
            {
               pivotColVals[j] = A[j][pivotColumn];
            }
            for(int k=0;k<cols;k++)
            {
               rowNew[k] = pivotRowVals[k]/pivotValue;
            }
            B[pivot_Row] = B[pivot_Row]/pivotValue;
            for(int m=0;m<rows;m++)
            {
               if(m != pivot_Row)
               {
                   for(int p=0; p<cols; p++)
                   {
                       float multiplyValue = pivotColVals[m];
                       A[m][p] = A[m][p] - (multiplyValue*rowNew[p]);
                   }
               }
             }
            for(int i=0;i<B.size();i++)
            {
                if(i != pivot_Row)
                {
                        float multiplyValue = pivotColVals[i];
                        B[i] = B[i] - (multiplyValue*B[pivot_Row]);
                }
            }
                float multiplyValue = C[pivotColumn];
                 for(int i=0;i<C.size();i++)
                {
                    C[i] = C[i] - (multiplyValue*rowNew[i]);
                }
             for(int i=0;i<cols;i++)
            {
                A[pivot_Row][i] = rowNew[i];
             }
        }

        void print()
        {
            for(int i=0; i<rows;i++)
            {
                for(int j=0;j<cols;j++)
                {
                    ui->simplexOutputTextBrowser->insertPlainText("\t" + QString::number(A[i][j]));                                       //print matrix*********
                }
                ui->simplexOutputTextBrowser->insertPlainText("\n");
                //cout<<""<<endl;                                                 //print space
            }
            ui->simplexOutputTextBrowser->insertPlainText(" ");
            //cout<<""<<endl;                                                     //print space
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

        int find_PivotRow(int pivotColumn)
        {
            float positiveValues[rows];
            std::vector<float> result(rows,0);
            int negativeValueCount = 0;
            for(int i=0;i<rows;i++)
            {
                if(A[i][pivotColumn]>0)
                {
                    positiveValues[i] = A[i][pivotColumn];
                }
                else{
                    positiveValues[i]=0;
                    negativeValueCount+=1;
                }
            }
            if(negativeValueCount==rows)
            {
                isUnbounded = true;
            }
            else
            {
                for(int i=0;i<rows;i++)
                    {
                    float value = positiveValues[i];
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

        void CalculateSimplex()
        {
            bool end = false;
            ui->simplexOutputTextBrowser->insertPlainText("\nInitial matrix:\n");
            //cout<<"\n\nInitial matrix"<<endl;                                                             //print heading
            print();
            ui->simplexOutputTextBrowser->insertPlainText(" \n");
            //cout<<" "<<endl;                                                                            //print space
            ui->simplexOutputTextBrowser->insertPlainText("Final matrix (Optimal solution)\n");
            //cout<<"Final matrix (Optimal solution)"<<endl;                                              //print final matrix heading
            while(!end)
            {
                bool result = Simplex_Calculataion();
                if(result==true)
                {
                    end = true;
                }
            }
            ui->simplexOutputTextBrowser->insertPlainText("\nAnswers for the Constraints of variables \n");
            //cout<<"Answers for the Constraints of variables"<<endl;                             //print heading
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
                    //cout << "variable" << index+1 << ": " << B[index] << endl;                  //print variable
                    ui->simplexOutputTextBrowser->insertPlainText("variable" + QString::number(index+1) + ": " + QString::number(B[index]) + "\n");
                }
                else
                {
                    //cout << "variable" << index+1 << ": " << 0 << endl;                         //print variable
                    ui->simplexOutputTextBrowser->insertPlainText("variable" + QString::number(index+1) + ": " + "0" + "\n");
                }
            }
            ui->simplexOutputTextBrowser->insertPlainText(" \n");
            //cout << "  " << endl;                                                                //print space
            ui->simplexOutputTextBrowser->insertPlainText("maximum value: " + QString::number(maximum) + "\n");
            //cout << "maximum value: " << maximum << endl;                                        //print maximum value
        }
};




#endif // SIMPLEXSOLVER_H
