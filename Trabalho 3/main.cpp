/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001490 - Algoritmos e Estruturas de Dados 2 – Trabalho 3
    Prof. Dr. Diego Furtado Silva

    Aluno: João Victor Mendes Freire
    RA: 758943

    Baseado do algoritmo apresentado em https://www.ime.usp.br/~pf/algoritmos/aulas/strma.html
*/

#include <iostream>
#include <vector>

std::vector<long> boyer_moore(const std::string& pattern, const std::string& text)
{
    int m = pattern.length();
    int n =    text.length();
    int             ult[256];
    int                *jump; 
    std::vector<long> occurs;

    // Pré-processamento do padrão (bad-char rule)
    for (int f = 0; f < 256; ++f)
        ult[f] = 0;
    for (int g = 0; g < m; ++g)
        ult[(int)pattern.at(g)] = g;

    // Pré-processamento do padrão (good-char rule)
    jump = (int *)malloc(m * sizeof(int));

    int h = m, k = m-1;
    int i = m, j = k;
    while (h >= 1)
    {
        while (i >= h && j >= 1)
            if (pattern.at(i - 1) == pattern.at(j - 1))
                --i, --j;
            else
                i = m, j = --k;
        jump[--h] = k;
    }

    // Busca do padrão no texto
    k = m;
    int bad_c, good_c;
    while (k <= n)
    {
        i = m, j = k;
        while (i >= 1 && pattern.at(i - 1) == text.at(j - 1)) 
            --i, --j;   
        if (i < 1)
            occurs.push_back(j);
        if (i == m) 
            k += 1;
        else 
        {
            good_c = m - jump[i];
            bad_c  = m - ult[(int)text.at(k)];
            k += (good_c > bad_c) ? good_c : bad_c;
        }
    }

    return occurs;
}

int main(int argc, char **argv)
{
    char       file_name[100];
    char                    c;
    long              ptrn_sz;
    long               txt_sz;
    FILE             *entrada;
    std::string          text;
    std::string       pattern;
    std::vector<long> results;


    // Lendo nome do arquivo da entrada padrão
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    // Lendo tamanho do texto e padrão, e alocando espaço adequado
    fscanf(entrada, "%ld %ld ", &txt_sz, &ptrn_sz);

    for (int i = 0; i < txt_sz; i++)
    {
        fscanf(entrada, "%c ", &c);
        text.append(1, c);
    }

    for (int i = 0; i < ptrn_sz; i++)
    {
        fscanf(entrada, "%c ", &c);
        pattern.append(1, c);
    }
    fclose(entrada);

    results = boyer_moore(pattern, text);
    
    for (unsigned int i = 0; i < results.size(); i++)
        std::cout << results.at(i) << '\n';

    return 0;
}
