#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define infinity 100000

int temp[17], i, j, n, valbuscado; // Variables globales

// Prototipo de función

void Broadcast(int A[], int valbuscado, int tamA);
int minimo(int A[], int tamA);
int busqueda(int A[], int valbuscado, int tamA);

int main()
{
    printf("\n***********************************************\n");
    printf("                  Busqueda EREW\n");
    printf("***********************************************\n");
    printf("MIEMBROS DE EQUIPO:\nJose Juan Garcia Romero\nJose Angel Romero Rios\nLeonardo Cortez Gomez");
    printf("\n");

    int A[20], h, tamA, m, i1 = 1;
    A[0] = 0;

    printf("\nIngrese la longitud del arreglo: ");
    scanf("%d", &tamA);
    m = tamA + 1;

    for (i1; i1 < m; i1++)
    {
        printf("Valor : ");
        scanf("%d", &h);
        A[i1] = h;
    }

    printf("\nValor a buscar: ");
    scanf("%d", &valbuscado);

    printf("\nPosicion encontrada: ");
    printf("%i", busqueda(A, valbuscado, tamA));
    return 0;
}

// Definición de función

void Broadcast(int temp[], int valbuscado, int tamA) // Define la función para difusión.
{
    temp[1] = valbuscado;
    for (i = 1; i <= (log2(tamA)); i++)
    {
#pragma omp parallel for shared(j, i) // Shared: Especifica que una o más variables deben ser compartidas entre todos los hilos.
        for (j = (int)((pow(2, i - 1) + 1)); j <= (int)(pow(2, i)); j++)
        {
            temp[j] = temp[(j) - ((int)(pow(2, i - 1)))];
        }
    }
}

int minimo(int A[], int tamA) // Define la función para elemento mínimo.
{

    for (j = 1; j <= (log2(tamA)); j++)
    {
#pragma omp parallel for
        for (i = 1; i <= tamA / ((int)(pow(2, j))); i = i + 1)
        {
            if (A[(int)(pow(2, i - 1))] > A[(int)(pow(2, i))])
            {
                A[i] = A[(int)(pow(2, i))];
            }
            else
                A[i] = A[(int)(pow(2, i - 1))];
        }
    }
    n = temp[1];
    for (i = 1; i <= tamA; i++)
    {
        if (n > temp[i])
        {
            n = temp[i];
        }
    }
    temp[1] = n;
    return temp[1];
}

int busqueda(int A[], int valbuscado, int tamA) // Define la función para comparación
{
    Broadcast(temp, valbuscado, tamA);
#pragma omp parallel for
    for (i = 1; i <= tamA; i = i + 1)
    {
        if (A[i] == temp[i])
        {
            temp[i] = i;
        }
        else
        {
            temp[i] = infinity;
        }
    }
    return (minimo(A, tamA));
}