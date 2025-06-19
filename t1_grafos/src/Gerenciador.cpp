#include "Gerenciador.h"
#include "includes.h"
#include <vector>
#include <string>

void Gerenciador::menu_principal(Grafo* grafo) {
    char resp;
    do {
        cout << "--- Menu Principal ---" << endl;
        cout << "(1) Funcoes Basicas" << endl;
        cout << "(2) Algoritmos em Grafos" << endl;
        cout << "(0) Sair" << endl;
        cin >> resp;

        switch (resp) {
            case '1':
                menu_basico(grafo);
                break;
            case '2':
                menu_algoritmos(grafo);
                break;
            case '0':
                cout << "Saindo..." << endl;
                exit(0);
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    } while (resp != '0');
}

void Gerenciador::menu_basico(Grafo* grafo) {
    char resp;
    do {
        cout << "--- Funcoes Basicas ---" << endl;
        cout << "(1) Adicionar No" << endl;
        cout << "(2) Remover No" << endl;
        cout << "(3) Adicionar Aresta" << endl;
        cout << "(4) Remover Aresta" << endl;
        cout << "(5) Imprimir Grafo" << endl;
        cout << "(6) Imprimir Grafo em Arquivo." << endl;
        cout << "(7) Imprimir Grafo em Arquivo DOT." << endl;
        cout << "(0) Voltar ao Menu Principal" << endl;
        cin >> resp;

        switch (resp) {
            case '1': {
                char id;
                int peso = 0;
                cout << "Digite o id do no: ";
                cin >> id;
                if (grafo->in_ponderado_vertice) {
                    cout << "Digite o peso do no: ";
                    cin >> peso;
                }
                grafo->adicionarNo(id, peso);
                break;
            }
            case '2': {
                char id = get_id_entrada();
                grafo->removerNo(id);
                break;
            }
            case '3': {
                char id_origem, id_destino;
                int peso = 0;
                cout << "Digite o id do no de origem: ";
                cin >> id_origem;
                cout << "Digite o id do no de destino: ";
                cin >> id_destino;
                if (grafo->in_ponderado_aresta) {
                    cout << "Digite o peso da aresta: ";
                    cin >> peso;
                }
                grafo->adicionarAresta(id_origem, id_destino, peso);
                break;
            }
            case '4': {
                char id_origem, id_destino;
                int peso = 0;
                cout << "Digite o id do no de origem: ";
                cin >> id_origem;
                cout << "Digite o id do no de destino: ";
                cin >> id_destino;
                if (grafo->in_ponderado_aresta) {
                    cout << "Digite o peso da aresta: ";
                    cin >> peso;
                }
                grafo->removerAresta(id_origem, id_destino, peso);
                break;
            }
            case '5':
                grafo->imprimirNoTerminal();
                break;
            case '6':{
                string file;
                cout << "Digite o nome do arquivo: ";
                cin >> file;
                grafo->imprimirEmArquivo(file);
                break;
            }
            case '7':{
                string file;
                cout << "Digite o nome do arquivo: ";
                cin >> file;
                grafo->imprimirEmArquivoDot(file);
                break;
            }
            case '0':
                return;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    } while (resp != '0');
}

void Gerenciador::menu_algoritmos(Grafo* grafo) {
    char resp;
    do {
    cout<<"Digite uma das opcoes abaixo e pressione enter:"<<endl<<endl;
    cout<<"(a) Fecho transitivo direto de um no;"<<endl;
    cout<<"(b) Fecho transitivo indireto de um no;"<<endl;
    cout<<"(c) Caminho minimo (Djikstra);"<<endl;
    cout<<"(d) Caminho minimo (Floyd);"<<endl;
    cout<<"(e) Arvore Geradora Minima (Algoritmo de Prim);"<<endl;
    cout<<"(f) Arvore Geradora Minima (Algoritmo de Kruskal);"<<endl;
    cout<<"(g) Arvore de caminhamento em profundidade;"<<endl;
    cout<<"(h) Raio, diametro, centro e periferia do grafo;"<<endl;
    cout<<"(0) Sair;"<<endl<<endl;
    cin >> resp;
    
    switch (resp) {
        case 'a': {

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_direto = grafo->fecho_transitivo_direto(id_no);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("fecho_trans_dir.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl<<endl;
            }


            break;
        }

        case 'b':{

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_indireto = grafo->fecho_transitivo_indireto(id_no);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("fecho_trans_indir.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

;
            break;
        }

        case 'c': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_dijkstra = grafo->caminho_minimo_dijkstra(id_no_1,id_no_2);
            cout << "Caminho minimo entre " << id_no_1 << " e " << id_no_2 << ": ";
            if(caminho_minimo_dijkstra.empty()) {
                cout << "Nao existe caminho entre os nos." << endl;
            } else {
                for(char id : caminho_minimo_dijkstra) {
                cout << id << "Vasco ";
            }
            cout << endl;
            }

            if(pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }


            break;
        }

        case 'd': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_floyd = grafo->caminho_minimo_floyd(id_no_1,id_no_2);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }


            break;
        }
        case 'e': {

            int tam;
            cout<<"Digite o tamanho do subconjunto: ";
            cin>>tam;

            if(tam > 0 && tam <= grafo->ordem) {

                vector<char> ids = get_conjunto_ids(grafo,tam);
                Grafo* arvore_geradora_minima_prim = grafo->arvore_geradora_minima_prim(ids);
                cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

                if(pergunta_imprimir_arquivo("agm_prim.txt")) {
                    cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
                }

                delete arvore_geradora_minima_prim;

            }else {
                cout<<"Valor invalido"<<endl;
            }

            break;
        }

        case 'f': {

            int tam;
            cout<<"Digite o tamanho do subconjunto: ";
            cin>>tam;

            if(tam > 0 && tam <= grafo->ordem) {

                vector<char> ids = get_conjunto_ids(grafo,tam);
                Grafo* arvore_geradora_minima_kruskal = grafo->arvore_geradora_minima_kruskal(ids);
                cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

                if(pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                    cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
                }

                delete arvore_geradora_minima_kruskal;

            }else {
                cout<<"Valor invalido"<<endl;
            }

            break;
        }

        case 'g': {

            char id_no = get_id_entrada();
            Grafo* arvore_caminhamento_profundidade = grafo->arvore_caminhamento_profundidade(id_no);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

            delete arvore_caminhamento_profundidade;
            break;
        }

        case 'h': {
            vector<char> articulacao = grafo->vertices_de_articulacao();
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

            break;
        }
        case 'i': {

            vector<char> articulacao = grafo->vertices_de_articulacao();
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

            break;
        }

        case '0': {
            menu_principal(grafo);
        }
        default: {
            cout<<"Opção inválida"<<endl;
        }
        }
    } while (resp != '0');
}

char Gerenciador::get_id_entrada() {
    cout<<"Digite o id de um no: ";
    char id;
    cin>>id;
    cout<<endl;
    return id;
}

vector<char> Gerenciador::get_conjunto_ids(Grafo *grafo, int tam) {
    vector<char> ids = {};
    while((int)ids.size() < tam) {
        char id_no =get_id_entrada();
        bool existe = false;
        for(No* no: grafo->lista_adj){
            if(no->id == id_no){
                existe = true;
                break;
            }
        }

        if(!existe){
            cout<<"Vertice nao existe"<<endl;
        }else{
            bool repetido = find(ids.begin(), ids.end(),id_no) != ids.end();
            if(repetido) {
                    cout<<"Valor repetido"<<endl;
            }else {
                ids.push_back(id_no);
            }
        }

    }

    return ids;
}


bool Gerenciador::pergunta_imprimir_arquivo(string nome_arquivo) {

    cout<<"Imprimir em arquivo externo? ("<<nome_arquivo<<")"<<endl;
    cout<<"(1) Sim;"<<endl;
    cout<<"(2) Nao."<<endl;
    int resp;
    cin>>resp;
    cout<<endl;

    switch (resp) {
        case 1:
            return true;
        case 2:
            return false;
        default:
            cout<<"Resposta invalida"<<endl;
            return pergunta_imprimir_arquivo(nome_arquivo);
    }
}