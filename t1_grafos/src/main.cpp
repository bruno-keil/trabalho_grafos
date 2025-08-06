#include "includes.h"
#include "Gerenciador.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Uso: ./main <arquivo_entrada>" << endl;
        return 1; // Return an error code
    }

    Grafo *grafo = new Grafo(argv[1]);

    string path = argv[1];
    string instanceName = path.substr(path.find_last_of("/\\") + 1);
    size_t dot_pos = instanceName.find_last_of('.');
    if (dot_pos != string::npos) {
        instanceName = instanceName.substr(0, dot_pos);
    }


    Gerenciador::menu_principal(grafo, instanceName);

    delete grafo;
    return 0;
}
