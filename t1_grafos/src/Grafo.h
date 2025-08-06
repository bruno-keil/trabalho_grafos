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

    void adicionarNo(char id_no, int peso = 0);
    void removerNo(char id_no);
    void adicionarAresta(char id_origem, char id_destino, int peso = 0);
    void removerAresta(char id_origem, char id_destino, int peso = 0);
    void imprimirNoTerminal() const;
    void imprimirEmArquivo(const string &nomeArquivo) const;
    void imprimirEmArquivoDot(const string &nomeArquivo) const;
    void printTreeToDOT(const string &nomeArquivo, const vector<pair<char, char>> &back_edges) const;
    void imprimirEmArquivoCsAcademy(const string &nomeArquivo) const;
    void printTreeToCsAcademy(const string &nomeArquivo, const vector<pair<char, char>> &back_edges) const;
    void printTreeToArquivo(const string &nomeArquivo, const vector<pair<char, char>> &back_edges) const;

    vector<char> fecho_transitivo_direto(char id_no);                                     // a
    vector<char> fecho_transitivo_indireto(char id_no);                                   // b
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b);                     // c
    vector<char> caminho_minimo_floyd(char id_no_a, char id_no_b);                          // d
    Grafo *arvore_geradora_minima_prim(vector<char> ids_nos);                             // e
    Grafo *arvore_geradora_minima_kruskal(vector<char> ids_nos);                          // f
    pair<Grafo *, vector<pair<char, char>>> arvore_caminhamento_profundidade(char id_no); // g
    int raio();                                                                           // h 1
    int diametro();                                                                       // h 2
    vector<char> centro();                                                                // h 3
    vector<char> periferia();                                                             // h 4
    vector<char> vertices_de_articulacao();                                               // i
    vector<char> ds_2_greedy();
    vector<char> ds_2_randomized_greedy(int max_iter, float alpha);
    vector<char> ds_2_reactive_randomized_greedy(vector<float> alfaVet, int numIter, int bloco);

    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No *> lista_adj;
    unordered_map<char, std::vector<char>> adjacencias;

private:
    void gerarSaida(ostream &out) const;
    void dfs_profundidade_helper(char id_no, char parent_id, set<char> &visitados, set<char> &recursion_stack, Grafo *arvore, vector<char> &insertion_sequence, vector<pair<char, char>> &back_edges);
    void dfs_articulacao_helper(char u, map<char, int> &desc, map<char, int> &low, map<char, char> &parent, set<char> &articulacoes, int &time, bool &is_root);
    int calcular_distancia(char id_origem, char id_destino);
};

#endif // GRAFO_H