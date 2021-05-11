#include <stdlib.h>
#include <string.h>
#include "nummeths.h"

int interpol(const double *x, const double *fx, int n, double *z, double *pz, int m)
{
    double term, *table, *coeff;
    int i, j, k;

    if((table = (double *)malloc(sizeof(double) * n)) == NULL)
    {
        return -1;
    }
    
    if((coeff = (double *)malloc(sizeof(double) * n)) == NULL)
    {
        free(table);
        return -1;
    }

    /* 把x坐标对应的值放到变量中，因为需要对y坐标的值进行修改 */
    memcpy(table, fx, sizeof(double) * n);


    /* 当i == j的时候系数就是f(x[i]) */
    coeff[0] = table[0];

    /* 计算系数其中k是行的概念，table每一行的头对应i-j */
    for(k = 1; k < n; k++)
    {
        for(i = 0; i < n-k; i++)
        {
            j = i + k;
            table[i] = (table[i + 1] - table[i]) / (x[j] - x[i]);
        }
        coeff[k] = table[0];
    }

    /* 系数已经算出来，多项式已经有了，下一步是计算结果 */
    for(k = 0; k < m; k++)
    {
        pz[k] = coeff[0];
        for(j = 1; j < n; j++)
        {
            term = coeff[i];
            for(i = 0; i < j; i++)
                term = term * (z[k] - x[i]);
            pz[k] = pz[k] + term;
        }
    }
    free(coeff);
    free(table);
    return 0;

}
