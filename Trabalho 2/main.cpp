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

class Merge
{
    public:
    // Função que ordena um vetor [ini .. fim - 1] de doubles, dada uma posição 
    // inicial e final.
    static void Sort(double *arr, int ini, int fim)
    {
        if (ini + 1 < fim)
        {
            int m = ini + (fim - ini) / 2;

            Merge::Sort(arr, ini, m);
            Merge::Sort(arr, m, fim);

            Merge::merge(arr, ini, m, fim);
        }
    }

    private:
    // Função auxiliar da Sort(). Não deve ser usada por conta própria.
    static void merge(double *arr, int ini, int meio, int fim)
    {
        int i = ini;
        int j = meio;
        int k = 0;

        double *aux = (double *) malloc((fim - ini) * sizeof(double));

        while(i < meio && j < fim)
        {
            if (arr[i] < arr[j])
                aux[k++] = arr[i++];
            else
                aux[k++] = arr[j++];
        }

        while(i < meio)
            aux[k++] = arr[i++];
        while(j < fim)
            aux[k++] = arr[j++];

        for (k = 0; k < (fim - ini); k++)
            arr[ini + k] = aux[k];

        free(aux);
    }
};

int detecta_outliers(double **matriz, int n, int k, double limite)
{
    int outliers = 0;

    for (int i = 0; i < n; i++)
    {
        // double dist = Quick::Seleciona(matriz[i], 0, n, k + 1); 
        Merge::Sort(matriz[i], 0, n); 
        double dist = matriz[i][k + 1]; 
        if (dist > limite)
            outliers++;
    }

    return outliers;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    char file_name[100];
    int outliers; // Número de outliers
    int N;        // Tamanho da matriz
    int k;        // k-ésimo vizinho mais próximo a ser comparado
    double L;     // Limitante inferior para detectar outlier
    double **matriz = NULL;
    FILE *entrada;

    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    fscanf(entrada, "%d %d %lf", &N, &k, &L);

    // Alocando espaço da matriz
    matriz = (double **) malloc((N) * sizeof(double *));

    for (int i = 0; i < N; i++)
        matriz[i] = (double *) malloc((N) * sizeof(double));

    // Lendo matriz de input
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fscanf(entrada, "%lf", &matriz[i][j]);
    }
    fclose(entrada);

    // Detectando outliers
    outliers = detecta_outliers(matriz, N, k, L);
    printf("%d\n", outliers);

    // Liberando a matriz
    for (int i = 0; i < N; i++)
        free(matriz[i]);
    free(matriz);

    return 0;
}
