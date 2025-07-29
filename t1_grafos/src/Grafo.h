#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include "includes.h"
#include <unordered_map>

class Grafo
{
public:
    Grafo();
    Grafo(const string &filePath);
    ~Grafo();

    void adicionarNo(int id_no, int peso = 0);
    void removerNo(int id_no);
    void adicionarAresta(int id_origem, int id_destino, int peso = 0);
    void removerAresta(int id_origem, int id_destino, int peso = 0);
    void imprimirNoTerminal() const;
    void imprimirEmArquivo(const string &nomeArquivo) const;
    void imprimirEmArquivoDot(const string &nomeArquivo) const;
    void printTreeToDOT(const string &nomeArquivo, const vector<pair<int, int>> &back_edges) const;
    void imprimirEmArquivoCsAcademy(const string &nomeArquivo) const;
    void printTreeToCsAcademy(const string &nomeArquivo, const vector<pair<int, int>> &back_edges) const;
    void printTreeToArquivo(const string &nomeArquivo, const vector<pair<int, int>> &back_edges) const;

    vector<int> fecho_transitivo_direto(int id_no);                                     // a
    vector<int> fecho_transitivo_indireto(int id_no);                                   // b
    vector<int> caminho_minimo_dijkstra(int id_no_a, int id_no_b);                     // c
    vector<int> caminho_minimo_floyd(int id_no, int id_no_b);                          // d
    Grafo *arvore_geradora_minima_prim(vector<int> ids_nos);                             // e
    Grafo *arvore_geradora_minima_kruskal(vector<int> ids_nos);                          // f
    pair<Grafo *, vector<pair<int, int>>> arvore_caminhamento_profundidade(int id_no); // g
    int raio();                                                                           // h 1
    int diametro();                                                                       // h 2
    vector<int> centro();                                                                // h 3
    vector<int> periferia();                                                             // h 4
    vector<int> vertices_de_articulacao();                                               // i
    vector<int> ds_2_greedy();
    vector<int> ds_2_randomized_greedy(int max_iter, float alpha);
    vector<int> ds_2_reactive_randomized_greedy();

    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No *> lista_adj;
    unordered_map<int, std::vector<int>> adjacencias;

private:
    void gerarSaida(ostream &out) const;
    void dfs_profundidade_helper(int id_no, int parent_id, set<int> &visitados, set<int> &recursion_stack, Grafo *arvore, vector<int> &insertion_sequence, vector<pair<int, int>> &back_edges);
    void dfs_articulacao_helper(int u, map<int, int> &desc, map<int, int> &low, map<int, int> &parent, set<int> &articulacoes, int &time, bool &is_root);
    int calcular_distancia(int id_origem, int id_destino);
};

#endif // GRAFO_H
