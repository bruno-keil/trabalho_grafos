#ifndef NO_H
#define NO_H

#include "includes.h"
#include "Aresta.h"

using namespace std;
class No
{
public:
    No();
    ~No();

    char id;
    int peso;
    vector<Aresta *> arestas;
};

#endif // NO_H
