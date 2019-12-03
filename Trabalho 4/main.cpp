/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001490 - Algoritmos e Estruturas de Dados 2 – Trabalho 4
    Prof. Dr. Diego Furtado Silva

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define iPair std::pair<int, int>

class Grafo
{
public:
    Grafo(int n);

    ~Grafo();

    // Adiciona uma aresta de v à u com peso w
    void add_edge(int v, int u, int w) const;

    // Retorna o caminho mínimo de ori até dest, usando o algoritmo
    // de Dijkstra
    int Dijkstra(int ori, int dest) const;
private:
    int                    n; // No. de vértices
    std::vector<iPair > *adj; // Lista de adjacencias
};

int main()
{
    int m, n; // No. de arestas e vértices, respectivamente

    scanf("%d %d ", &n, &m);
    Grafo grafo(n);

    // Adicionando arestas
    for (int i = 0; i < m; i++)
    {
        int v, u, w;
        scanf("%d %d %d ", &v, &u, &w);
        grafo.add_edge(v, u, w);
    }

    std::cout << grafo.Dijkstra(0, n-1) << "\n";

    return 0;
}

Grafo::Grafo(int n)
{
    if (n <= 0)
    {
        std::cout << "Erro: número de índices negativo\n";
        exit(1);
    }

    this->n = n;
    this->adj = new std::vector<iPair >[n];
}

Grafo::~Grafo()
{
    delete [] adj;
}

void Grafo::add_edge(int v, int u, int w) const
{
    if (v < 0 || v >= n || u < 0 || u >= n)
    {
        std::cout << "Erro: índice inexistente\n";
        exit(1);
    }

    this->adj[v].push_back(std::make_pair(u, w));
}

int Grafo::Dijkstra(int ori, int dest) const
{
    std::priority_queue<iPair, std::vector<iPair >, std::greater<iPair > > pq;
    bool visitado[this->n];
    // int      prev[this->n]; // Para poder reconstruir o caminho
    int      dist[this->n];
    int u, v, w;

    // Inicializando com valores apropriados
    for (int i = 0; i < this->n; i++)
    {
        visitado[i] = false;
        // prev[i]     = -1;
        dist[i]     = INF;
    }

    // Colocando origem na pq
    dist[ori] = 0;
    pq.push(std::make_pair(0, ori));

    while (!visitado[dest] || pq.empty())
    {
        // Retirando o elemento com menor distância
        v = pq.top().second;
        pq.pop();
        visitado[v] = true;

        // Iterando sobre suas arestas
        for (unsigned int i = 0; i < this->adj[v].size(); i++)
        {
            u = this->adj[v].at(i).first;
            w = this->adj[v].at(i).second;

            if (!visitado[u])
                if (dist[u] > dist[v] + w)
                {
                    dist[u] = dist[v] + w;
                    pq.push(std::make_pair(dist[u], u));
                    // prev[u] = v;
                }
        }
    }

    return dist[dest];
}
