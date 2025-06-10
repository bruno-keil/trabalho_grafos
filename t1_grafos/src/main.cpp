#include "includes.h"
#include "Gerenciador.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Uso: ./main <arquivo_entrada>" << endl;
        return 1; // Return an error code
    }

    Grafo* grafo = new Grafo(argv[1]);

    Gerenciador::menu_principal(grafo);

    delete grafo;
    return 0;
}
