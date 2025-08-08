#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "includes.h"
#include "Grafo.h"

using namespace std;
class Gerenciador
{
public:
    static void menu_principal(Grafo *grafo,const string &instanceName);
    static void menu_basico(Grafo *grafo);
    static void menu_algoritmos(Grafo *grafo);
    static void menu_heuristics(Grafo *grafo,const string &instanceName);
    static char get_id_entrada();
    static vector<char> get_conjunto_ids(Grafo *grafo, int tam);
    static bool pergunta_imprimir_arquivo(string nome_arquivo);
    static void run_all_heuristics(Grafo *grafo, const string &instanceName);
    static void run_all_heuristics_one_time(Grafo *grafo, const string &instanceName);
};

#endif // GERENCIADOR_H
