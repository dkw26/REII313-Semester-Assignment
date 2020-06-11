#ifndef BNBSOLVER_H
#define BNBSOLVER_H

#include<stdio.h>

namespace Ui {
    class Knapsack;
}

class Knapsack
{

public:

    int max(int a, int b)
    {
       if(a>b)
       {
          return a;
       }
       else
       {
          return b;
       }
    }

    int knapsack_Calculation(int W, int weight[], int value[], int n)
    {
       int i;
       int w;
       int knap[n+1][W+1];

       for (i=0; i<=n; i++)
        {
          for (w=0; w<=W; w++)
          {
             if (i==0 || w==0)
             {
                  knap[i][w] = 0;
             }
             else if (weight[i-1] <= w)
             {
                  knap[i][w] = max(value[i-1] + knap[i-1][w-weight[i-1]], knap[i-1][w]);
             }
             else
             {
                  knap[i][w] = knap[i-1][w];
             }
          }
       }
       return knap[n][W];
    }
};

#endif // BNBSOLVER_H
