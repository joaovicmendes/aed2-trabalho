/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001490 - Algoritmos e Estruturas de Dados 2 – Trabalho 2
    Prof. Dr. Diego Furtado Silva

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>
#include <cstdlib>

class Quick
{
    public:
    static double Seleciona(double *arr, int ini, int fim, int k)
    {
        int pivo = Quick::Particiona(arr, ini, fim);

        if (pivo == k)
            return arr[pivo];
        else if (pivo > k)
            return Quick::Seleciona(arr, ini, pivo, k);
        else
            return Quick::Seleciona(arr, pivo + 1, fim, k);        
    }

    static void Sort(double *arr, int ini, int fim)
    {
        if (ini < fim)
        {
            int pivo = Quick::Particiona(arr, ini, fim);
            Quick::Sort(arr, ini, pivo);
            Quick::Sort(arr, pivo + 1, fim);
        }
    }

    private:
    // Troca o valor de dois indices de um vetor, não verifica tamanho
    static void troca(double *arr, int a, int b)
    {
        double aux = arr[a];
        arr[a] = arr[b];
        arr[b] = aux;
    }
    // Partição do QuickSort
    static int Particiona(double *arr, int ini, int fim)
    {
        int pivo = (ini + fim) / 2;
        Quick::troca(arr, ini, pivo);

        pivo = ini;
        int i = ini + 1;
        int j = fim - 1;

        while (i <= j)
        {
            while (i < fim && arr[i] <= arr[pivo])
                i++;
            while (arr[j] > arr[pivo])
                j--;

            if (i < j)
                Quick::troca(arr, i, j);
        }

        Quick::troca(arr, pivo, j);

        return j;
    }
};

int detecta_outliers(double **matriz, int n, int k, double limite)
{
    int outliers = 0;

    // Para cada linha, seleciona o k+1-ésimo
    for (int i = 0; i < n; i++)
    {
        double dist = Quick::Seleciona(matriz[i], 0, n, k + 1); 
        if (dist > limite)
            outliers++;
    }

    return outliers;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    char file_name[100];
    int outliers;            // Número de outliers
    int N;                   // Tamanho da matriz
    int k;                   // k-ésimo vizinho mais próximo a ser comparado
    double L;                // Limitante inferior para detectar outlier
    double **matriz = NULL;
    FILE *entrada;

    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    // Lendo N, k, L e alocando o espaço para a matriz
    fscanf(entrada, "%d %d %lf", &N, &k, &L);
    matriz = (double **) malloc((N) * sizeof(double *));

    for (int i = 0; i < N; i++)
        matriz[i] = (double *) malloc((N) * sizeof(double));

    // Preenchendo a matriz de dados
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fscanf(entrada, "%lf", &matriz[i][j]);
    }
    fclose(entrada);

    // Detectando outliers
    outliers = detecta_outliers(matriz, N, k, L);
    printf("%d\n", outliers);

    for (int i = 0; i < N; i++)
        free(matriz[i]);
    free(matriz);

    return 0;
}
