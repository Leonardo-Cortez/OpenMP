#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    printf("\n***********************************************\n");
    printf("                  Suma EREW\n");
    printf("***********************************************\n");
    printf("MIEMBROS DE EQUIPO:\nJose Juan Garcia Romero\nJose Angel Romero Rios\nLeonardo Cortez Gomez");
    printf("\n");

    int a[20], h, g, m;
    int indice = 1;
    a[0] = 0;
    printf("\nIngrese la longitud del arreglo: ");
    scanf("%d", &g);
    m = g + 1;
    for (indice; indice < m; indice++)
    {
        printf("Valor: ");
        scanf("%d", &h);
        a[indice] = h;
    }
    int i, j, k;
    for (i = 1; i <= (log2(g)); i++)
    {
#pragma omp parallel for
        for (j = 1; j <= (g / 2); j++)
        {
            if (((2 * j) % (int)(pow(2, i))) == 0)
            {
                a[2 * j] = a[2 * j] + a[(2 * j) - ((int)(pow(2, (i - 1))))];
            }
        }
        // time.sleep(3);
        printf("\n");
        for (k = 1; k <= g; k++)
        {

            printf(" %d ", a[k]); // aquí se define si se desea el espacio para los resultados finales " %d ", o sin espacios "%d"
        }
        printf("\n");
    }
}
