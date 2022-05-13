#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

void sortCRCW(int L[], int n); // Procedimiento sortCRCW
void Imprimir(int L[], int n); // Procedimiento imprimir

int main()
{
    printf("\n***********************************************\n");
    printf("                  Ordenamiento CRCW\n");
    printf("***********************************************\n");
    printf("MIEMBROS DE EQUIPO:\nJose Juan Garcia Romero\nJose Angel Romero Rios\nLeonardo Cortez Gomez");
    printf("\n");

    // x delimita el tamaño
    // y define el guardado
    // z define el tamaño del arreglo

    int L[10], x, y, z;
    int Index = 1;
    L[0] = 0;

    printf("\nIngrese la longitud del arreglo: ");
    scanf("%d", &y);
    z = y + 1;

    for (Index; Index < z; Index++)
    {
        printf("Ingresa un valor: ");
        scanf("%d", &x);
        L[Index] = x; // el valor de Indice se establece en el arreglo de L para guardarse en h
    }

    printf("El arreglo original es:  ");
    Imprimir(L, z);
    sortCRCW(L, z);

    return 0;
}

// Se necesita ahora hacer un llamado del proceso que hará main. Main va a llamar a Imprimir y a SortCRCW

void sortCRCW(int L[], int n)
{
    int win[n], i, j; // el win[n] para guardarle al arreglo cualquier valor i, j
    int L2[n];        // auxiliar L2
    win[0] = 0;
#pragma omp parallel for
    for (i = 0; i <= n; i++)
    {
        win[i] = 0;
    }

#pragma omp parallel for
    for (i = 1; i <= n; i++) // Este es el arreglo win, permite calcular si un numero es mayor a otro "x" veces
    {
#pragma omp parallel for
        for (j = i + 1; j <= n; j++) // J tiene que iniciar en una posición x+1 (después de i)
        {
            if (L[i] > L[j])
            {
                win[i] = win[i] + 1;
            }
            else
            {
                win[j] = win[j] + 1;
            }
        }
    }

#pragma omp parallel for
    for (i = 1; i <= n; i++)
    {
        L2[win[i] + 1] = L[i];
    }

    printf("Arreglo win:  ");
    Imprimir(win, n);

    printf("Arreglo acomodado:  ");
    Imprimir(L2, n);

    printf("\n");
}

// Ahora es necesario crear el metodo a llamar Imprimir

void Imprimir(int L[], int n)
{
    printf("[");
    for (int i = 1; i < n; i++)
    {
        printf(" %d ", L[i]);
    }

    printf("]");
    printf("\n");
}
