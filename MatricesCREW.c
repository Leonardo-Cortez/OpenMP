#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Prototipo de funciones

void MatMultCREW();
void Imprimir();

int n = 2;
int i, j, k;
int a[2][2]; // Matriz A
int b[2][2]; // Matriz B
int c[2][2][2];

int main()
{
    printf("\n***********************************************\n");
    printf("        Multiplicacion de Matrices CREW\n");
    printf("***********************************************\n");
    printf("MIEMBROS DE EQUIPO:\nJose Juan Garcia Romero\nJose Angel Romero Rios\nLeonardo Cortez Gomez");
    printf("\n");

    printf("\nVALORES DE MATRIZ A\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            printf("Valor A[%d][%d] ", i, j);
            scanf("%d", &a[i][j]);
        }
    printf("\nVALORES DE MATRIZ B\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            printf("Valor B[%d][%d] ", i, j);
            scanf("%d", &b[i][j]);
        }
    printf("\nMatriz A: \n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz B: \n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d\t", b[i][j]);
        }
        printf("\n");
    }

    MatMultCREW();
    Imprimir();
}

void MatMultCREW()
{

    // Paso 1
#pragma omp parallel for
    for (int i = 1; i <= n; i++)
    {
#pragma omp parallel for
        for (int j = 1; j <= n; j++)
        {
#pragma omp parallel for
            for (int k = 1; k <= n; k++)
            {
                c[i][j][k] = a[i][k] * b[k][j];
            }
        }
    }

    // Paso 2
    for (int L = 1; L <= (log2(n)); L++)
    {
#pragma omp parallel for
        for (int i = 1; i <= n; i++)
        {
#pragma omp parallel for
            for (int j = 1; j <= n; j++)
            {
#pragma omp parallel for
                for (int k = 1; k <= n / 2; k++)
                {
                    if (((int)(pow(2, (k))) % (int)(pow(2, (L)))) == 0)
                    {
                        c[i][j][2 * k] = c[i][j][2 * k] + c[i][j][2 * k - (int)(pow(2, (L - 1)))];
                    }
                }
            }
        }
    }
} // Finaliza función

// Ahora es necesario crear el metodo a llamar Imprimir

void Imprimir()
{
    printf("\n\nMatriz resultante de A*B\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf(" %d\t", c[i][j][n]);
        }
        printf("\n");
    }
}
