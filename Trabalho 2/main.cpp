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
        int pivo;
        int desl;

        if (ini >= fim)
            return 0;

        // Escolhendo pivô aleatório
        desl = rand() % (fim - ini);
        Quick::troca(arr, ini + desl, ini);

        pivo = Quick::Particiona(arr, ini, fim);

        if (pivo == k)
            return arr[pivo];
        else if (pivo > k)
            return Quick::Seleciona(arr, ini, pivo, k);
        else
            return Quick::Seleciona(arr, pivo + 1, fim, k);        
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
        int pivo = ini;
        int i = ini + 1;
        int j = fim - 1;

        while (i < j)
        {
            while (i < fim && arr[i] <= pivo)
                i++;
            while (arr[j] > pivo)
                j--;

            if (i < j)
                Quick::troca(arr, i, j);
        }

        Quick::troca(arr, pivo, j);

        return pivo;
    }
};

int detecta_outliers(double **matriz, int n, int k, double limite)
{
    int outliers = 0;

    for (int i = 0; i < n; i++)
    {
        double dist = Quick::Seleciona(matriz[i], 0, n, k + 1);
        if (dist > limite)
            outliers++;
    }

    return outliers;
}

int main()
{
    srand(time(NULL));

    int outliers; // Número de outliers
    int N;       // Tamanho da matriz
    int k;       // k-ésimo vizinho mais próximo a ser comparado
    double L;    // Limitante inferior para detectar outlier
    double **matriz = NULL;

    scanf("%d %d %lf ", &N, &k, &L);

    // Alocando espaço da matriz
    matriz = (double **) malloc((N) * sizeof(double *));
    for (int i = 0; i < N; i++)
        matriz[i] = (double *) malloc((N) * sizeof(double));

    // Lendo matriz de input
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%lf ", &matriz[i][j]);

    outliers = detecta_outliers(matriz, N, k, L);
    printf("%d\n", outliers);

    // Liberando a matriz
    for (int i = 0; i < N; i++)
        free(matriz[i]);
    free(matriz);

    return 0;
}
