#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main()
{

    printf("\n***********************************************\n");
    printf("                  Suma CREW\n");
    printf("***********************************************\n");
    printf("MIEMBROS DE EQUIPO:\nJose Juan Garcia Romero\nJose Angel Romero Rios\nLeonardo Cortez Gomez");
    printf("\n");
    int num[20];
    int i, j, k, g;

    printf("\nIngrese la longitud del arreglo: ");
    scanf("%d", &g);

    for (i = 1; i <= g; i++) // para hacer el llenado de la columna
    {
        printf("Valor %d: ", i);
        scanf("%d", &num[i]);
    }

    printf("\n Arreglo original \n"); // esto va a mostrar la columna inicial
    printf("[");

    for (k = 1; k <= g; k++)
    {

        printf(" %d ", num[k]);
    }
    printf("]");

    // printf ( "\n\n" );

    for (i = 1; i <= (log2(g)); i++) // aquí se especifican el numero de procesos

    {
#pragma omp parallel for // shared (j, i)
        // for (j=8;j>=(int)((pow(2,i-1)+1));j--)
        for (j = 8; j >= (int)((pow(2, i - 1) + 1)); j--)

        {
            // num[j]=(num[j]-1)+num[(j)-(int)(pow(2,i-1))];
            num[j] = num[j] + num[(j) - (int)(pow(2, i - 1))];
        }

        printf("\n\n");
        printf("\n Arreglos paso por paso: \n\n");
        printf("[");

        for (k = 1; k <= g; k++)
        {
            printf(" %d ", num[k]);
        }

        printf(" ]");
    }
    printf("\n\n\n\n");
}
