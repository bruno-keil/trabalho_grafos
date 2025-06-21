#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include "includes.h"
#include <unordered_map>

class Grafo {
public:
    Grafo();
    Grafo(const string& filePath);
    ~Grafo();

    void adicionarNo(char id_no, int peso = 0);
    void removerNo(char id_no);
    void adicionarAresta(char id_origem, char id_destino, int peso = 0);
    void removerAresta(char id_origem, char id_destino, int peso = 0);
    void imprimirNoTerminal() const;
    void imprimirEmArquivo(const string& nomeArquivo) const;
    void imprimirEmArquivoDot(const string& nomeArquivo) const;

    vector<char> fecho_transitivo_direto(int id_no); // a
    vector<char> fecho_transitivo_indireto(int id_no); // b
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b); // c
    vector<char> caminho_minimo_floyd(int id_no, int id_no_b); // d
    Grafo* arvore_geradora_minima_prim(vector<char> ids_nos); // e
    Grafo* arvore_geradora_minima_kruskal(vector<char> ids_nos); // f
    Grafo* arvore_caminhamento_profundidade(int id_no); // g
    int raio(); // h 1
    int diametro(); // h 2
    vector<char> centro(); // h 3
    vector<char> periferia(); // h 4
    vector<char> vertices_de_articulacao(); // i


    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No*> lista_adj;
    unordered_map<int, std::vector<int>> adjacencias;

    private:
    void gerarSaida(ostream& out) const;
};



#endif //GRAFO_H
