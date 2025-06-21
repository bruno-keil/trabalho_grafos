#ifndef ARESTA_H
#define ARESTA_H
#include "includes.h"
class Aresta {
public:
    Aresta();
    ~Aresta();

    //Adição desse nó de origem tanto aqui quanto no cpp e nas adições de arestas no Grafo.cpp
    char id_no_origem;
    char id_no_alvo;
    int peso;
    
};



#endif //ARESTA_H
