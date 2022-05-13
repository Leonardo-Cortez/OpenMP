#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Prototipo de función

void mergeSort(int L[], int n);
void interchange(int L[], int a, int b);
void oddEvenSplit(int L[], int odd[], int even[], int n);
void oddEvenMerge(int L[], int n);

int main()
{
    int L[] = {16, 22, 35, 40, 53, 66, 70, 85, 15, 18, 23, 55, 60, 69, 72, 78};
    int a = 16;
    printf("\n***********************************************\n");
    printf("                  Ordenamiento EREW\n");
    printf("***********************************************\n");
    printf("MIEMBROS DE EQUIPO:\nJose Juan Garcia Romero\nJose Angel Romero Rios\nLeonardo Cortez Gomez");
    printf("\n");

    printf("\nArreglo Original: ");
    for (int i = 0; i < a; i++)
    {
        printf("[%d]", L[i]);
    }

    mergeSort(L, a);
    printf("\nArreglo acomodado: ");
    for (int i = 0; i < a; i++)
    {
        printf("[%d]", L[i]);
    }

    return 0;
}

void mergeSort(int L[], int n)
{
    if (n >= 2)
    {
        int m = (int)n / 2;

        int B[m];
        for (int i = 0; i < m; i++)
        {
            B[i] = L[2 * i];
        }

        int C[m];
        for (int i = m; i < n; i++)
        {
            C[i - m] = L[2 * (i - m) + 1];
        }

#pragma omp critical // Especifica que sólo se ejecuta en un hilo a la vez. Parareliza las funciones recursivas.
        {
            mergeSort(B, m);
            mergeSort(C, m);
        }

        oddEvenMerge(L, n);
    }
}

void interchange(int L[], int a, int b)
{
    int aux;
    aux = L[a];
    L[a] = L[b];
    L[b] = aux;
}

void oddEvenSplit(int L[], int odd[], int even[], int n)
{
#pragma omp parallel for
    for (int i = 0; i < (int)n / 2; i++)
    {
        odd[i] = L[2 * i];
        even[i] = L[2 * i + 1];
    }
}

void oddEvenMerge(int L[], int n)
{

    if (n == 2)
    {
        if (L[0] > L[1])
        {
            interchange(L, 0, 1);
        }
    }
    else
    {
        int m = (int)n / 2;
        int odd[m];
        int even[m];

        oddEvenSplit(L, odd, even, n);

#pragma omp critical // Especifica que sólo se ejecuta en un hilo a la vez. Parareliza las funciones recursivas.
        {
            oddEvenMerge(odd, m);
            oddEvenMerge(even, m);
        }

#pragma omp parallel for
        for (int i = 0; i < (int)n / 2; i++)
        {
            L[2 * i] = odd[i];
            L[2 * i + 1] = even[i];
        }
#pragma omp parallel for
        for (int i = 0; i < n - 1; i++)
        {

            if ((L[i]) > (L[i + 1]))
            {
                interchange(L, i, i + 1);
            }
        }
    }
}
