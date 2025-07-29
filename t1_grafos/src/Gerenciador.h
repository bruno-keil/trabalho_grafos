#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "includes.h"
#include "Grafo.h"

using namespace std;
class Gerenciador
{
public:
    static void menu_principal(Grafo *grafo);
    static void menu_basico(Grafo *grafo);
    static void menu_algoritmos(Grafo *grafo);
    static void menu_heuristics(Grafo *grafo);
    static int get_id_entrada();
    static vector<int> get_conjunto_ids(Grafo *grafo, int tam);
    static bool pergunta_imprimir_arquivo(string nome_arquivo);
};

#endif // GERENCIADOR_H
