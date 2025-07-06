#include "No.h"

No::No()
{
    this->id = '\0';
    this->peso = 0;
}

No::~No()
{
    for (Aresta *aresta : arestas)
    {
        delete aresta;
    }
}