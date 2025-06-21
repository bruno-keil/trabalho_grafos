#include "Grafo.h"
#include "includes.h"
#include <cmath>
#include <queue>
#include <limits>
#include <unordered_set> 


Grafo::Grafo() {
    this->ordem = 0;
    this->in_direcionado = false;
    this->in_ponderado_aresta = true;
    this->in_ponderado_vertice = false;
}

Grafo::Grafo(const string& filePath) {
    this->ordem = 0;
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filePath << endl;
        return;
    }

    cout << "Lendo grafo do arquivo: " << filePath << endl;
    // Lê as propriedades do Grafo
    if (getline(file, line)) {
        stringstream ss(line);
        int dir, pond_aresta, pond_vertice;
        ss >> dir >> pond_aresta >> pond_vertice;
        this->in_direcionado = (dir == 1);
        this->in_ponderado_aresta = (pond_aresta == 1);
        this->in_ponderado_vertice = (pond_vertice == 1);
    }

    // Lê o número de vértices
    int num_vertices = 0;
    if (getline(file, line)) {
        stringstream ss(line);
        ss >> num_vertices;
    }

    // Lê os vértices
    for (int i = 0; i < num_vertices; ++i) {
        if (getline(file, line)) {
            stringstream ss(line);
            char id;
            int peso = 0;
            ss >> id;
            if (this->in_ponderado_vertice) {
                ss >> peso;
            }
            adicionarNo(id, peso);
        }
    }

    // Lê as arestas
    while (getline(file, line)) {
        stringstream ss(line);
        char id_origem, id_destino;
        int peso = 0;
        ss >> id_origem >> id_destino;
        if (this->in_ponderado_aresta) {
            ss >> peso;
        }
        adicionarAresta(id_origem, id_destino, peso);
    }

    file.close();
}

Grafo::~Grafo() {
}

void Grafo::adicionarNo(char id_no, int peso) {
    No* novo_no = new No();
    novo_no->id = id_no;
    novo_no->peso = peso;
    lista_adj.push_back(novo_no);
    this->ordem++;
}

void Grafo::removerNo(char id_no) {
    auto it = remove_if(lista_adj.begin(), lista_adj.end(), [id_no](No* no) {
        if (no->id == id_no) {
            delete no;
            return true;
        }
        return false;
    });

    if(it != lista_adj.end()) {
        lista_adj.erase(it,lista_adj.end());
        this->ordem--;

        for (No* no : lista_adj) {
            no->arestas.erase(
                std::remove_if(no->arestas.begin(), no->arestas.end(), [id_no](Aresta* aresta) {
                    if (aresta->id_no_alvo == id_no) {
                        delete aresta; // Deallocate the memory for the edge.
                        return true;
                    }
                    return false;
                }),
                no->arestas.end()
            );
        }
    }
}

void Grafo::adicionarAresta(char id_origem, char id_destino, int peso) {
    No* origem = nullptr;
    No* destino = nullptr;

    for (No* no : lista_adj) {
        if (no->id == id_origem) {
            origem = no;
        }
        if(no->id == id_destino) {
            destino = no;
        }
        if(origem && destino) {
            break; // Ambos os nós foram encontrados
        }
    }

    if (origem) {
        Aresta* nova_aresta = new Aresta();
        nova_aresta->id_no_origem = id_destino;
        nova_aresta->id_no_alvo = id_destino;
        nova_aresta->peso = peso;
        origem->arestas.push_back(nova_aresta);
    }

    if (!this->in_direcionado && origem && destino) {
        Aresta* aresta_inversa = new Aresta();
        aresta_inversa->id_no_origem  = id_destino;    // invertido
        aresta_inversa->id_no_alvo = id_origem;     // invertido
        aresta_inversa->peso       = peso;
        destino->arestas.push_back(aresta_inversa);
    }

    // if (!this->in_direcionado) {
    //     No* destino = nullptr;
    //     for (No* no : lista_adj) {
    //         if (no->id == id_destino) {
    //             destino = no;
    //             break;
    //         }
    //     }
    //     if(destino) {
    //         Aresta* aresta_inversa = new Aresta();
    //         aresta_inversa->id_no_alvo = id_origem;
    //         aresta_inversa->peso = peso;
    //         destino->arestas.push_back(aresta_inversa);
    //     }
    // }
}

void Grafo::removerAresta(char id_origem, char id_destino, int peso) {
    for (No* no : lista_adj) {
        if (no->id == id_origem) {
            auto it = std::find_if(no->arestas.begin(), no->arestas.end(), [&](Aresta* aresta) {
                bool target_match = aresta->id_no_alvo == id_destino;
                if (!target_match) {
                    return false;
                }
                if (this->in_ponderado_aresta) {
                    return aresta->peso == peso;
                }
                return true;
            });

            if (it != no->arestas.end()) {
                delete *it;
                no->arestas.erase(it);
            }
            break;
        }
    }

    if (!this->in_direcionado) {
        for (No* no : lista_adj) {
            if (no->id == id_destino) {
                auto it = std::find_if(no->arestas.begin(), no->arestas.end(), [id_origem](Aresta* aresta) {
                    return aresta->id_no_alvo == id_origem;
                });

                if (it != no->arestas.end()) {
                    delete *it;
                    no->arestas.erase(it);
                }
                break;
            }
        }
    }
}


void Grafo::imprimirNoTerminal() const {
    cout << "--- Exibindo Grafo no Terminal ---" << endl;

    for (const auto& no : lista_adj) {
        cout << no->id;

        if (in_ponderado_vertice) {
            cout << " (Peso: " << no->peso << ")";
        }

        cout << " ---> ";

        for (auto it = no->arestas.begin(); it != no->arestas.end(); ++it) {
            cout << (*it)->id_no_alvo;
            if (next(it) != no->arestas.end()) {
                cout << ", ";
            }
        }

        cout << endl;
    }

    cout << "---------------------------------" << endl << endl;
}

void Grafo::imprimirEmArquivo(const string& nomeArquivo) const {
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }
    cout << "Imprimindo grafo no arquivo: " << nomeArquivo << endl << endl;
    gerarSaida(outFile);
    outFile.close();
}

void Grafo::imprimirEmArquivoDot(const string& nomeArquivo) const {
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }

    cout << "Imprimindo grafo no formato DOT em: " << nomeArquivo << endl << endl;

    if (in_direcionado) {
        outFile << "digraph G {" << endl;
    } else {
        outFile << "graph G {" << endl;
    }

    // Define os nós
    for (const auto& no : lista_adj) {
        outFile << "    " << no->id;
        if (in_ponderado_vertice) {
            outFile << " [label=\"" << no->id << " (" << no->peso << ")\"]";
        }
        outFile << ";" << endl;
    }

    // Define as arestas
    for (const auto& no_origem : lista_adj) {
        for (const auto& aresta : no_origem->arestas) {
            // Em grafos não direcionados, evita duplicar arestas
            if (!in_direcionado && no_origem->id > aresta->id_no_alvo) {
                continue;
            }

            outFile << "    " << no_origem->id;
            if (in_direcionado) {
                outFile << " -> ";
            } else {
                outFile << " -- ";
            }
            outFile << aresta->id_no_alvo;

            if (in_ponderado_aresta) {
                outFile << " [label=\"" << aresta->peso << "\"]";
            }
            outFile << ";" << endl;
        }
    }

    outFile << "}" << endl;
    outFile.close();
}

void Grafo::gerarSaida(ostream& out) const {
    out << in_direcionado << " " << in_ponderado_aresta << " " << in_ponderado_vertice << endl;
    out << ordem << endl;

    for (const auto& no : lista_adj) {
        out << no->id;
        if (in_ponderado_vertice) {
            out << " " << no->peso;
        }
        out << endl;
    }

    for (const auto& no_origem : lista_adj) {
        for (const auto& aresta : no_origem->arestas) {
            if (!in_direcionado && no_origem->id > aresta->id_no_alvo) {
                continue; // Avoids duplicate edges in non-directed graphs
            }
            out << no_origem->id << " " << aresta->id_no_alvo;
            if (in_ponderado_aresta) {
                out << " " << aresta->peso;
            }
            out << endl;
        }
    }
}



vector<char> Grafo::fecho_transitivo_direto(int id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::fecho_transitivo_indireto(int id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    // Converte chars para índices inteiros (A=0, B=1, ...)
    int inicio = toupper(id_no_a) - 'A';
    int destino = toupper(id_no_b) - 'A';

    // Verificação de limites
    if (inicio < 0 || inicio >= ordem || destino < 0 || destino >= ordem) {
        cout << "ERRO: Nós inválidos! Deve ser entre A e " 
             << static_cast<char>('A' + ordem - 1) 
             << ". Recebido: " << id_no_a << " e " << id_no_b << endl;
        return vector<char>();
    }

    const int INF = std::numeric_limits<int>::max() - 1;
    vector<int> dist(ordem, INF);
    vector<bool> visited(ordem, false);
    vector<int> pai(ordem, -1);

    dist[inicio] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    fila.emplace(0, inicio);

    cout << "Iniciando Dijkstra de " << id_no_a << " (" << inicio 
         << ") para " << id_no_b << " (" << destino << ")" << endl;

    while (!fila.empty()) {
        int u_id = fila.top().second;
        int u_dist = fila.top().first;
        fila.pop();

        if (visited[u_id]) continue;
        visited[u_id] = true;

        cout << "\nProcessando no " << static_cast<char>(u_id + 'A') 
             << " (" << u_id << "), dist: " << u_dist;
        
        if (u_id == destino) {
            cout << "\nDestino " << id_no_b << " alcancado!" << endl;
            break;
        }

        No* no_atual = lista_adj[u_id];
        if (!no_atual) {
            cout << "ERRO: Nó " << static_cast<char>(u_id + 'A') 
                 << " não existe!" << endl;
            continue;
        }

        cout << "\nVizinhos:";
        for (Aresta* a : no_atual->arestas) {
            int v_id = toupper(a->id_no_alvo) - 'A';
            int w = in_ponderado_aresta ? a->peso : 1;

            cout << "\n  " << static_cast<char>(u_id + 'A') << " -> " 
                 << static_cast<char>(v_id + 'A') << " (peso: " << w << ")";

            if (dist[u_id] != INF && dist[u_id] + w < dist[v_id]) {
                dist[v_id] = dist[u_id] + w;
                pai[v_id] = u_id;
                fila.emplace(dist[v_id], v_id);
                cout << " | Distancia atualizada: " << dist[v_id];
            }
        }
    }

    // Reconstrução do caminho
    vector<char> caminho;
    int atual = destino;
    
    while (atual != -1) {
        caminho.push_back(static_cast<char>(atual + 'A'));
        atual = pai[atual];
    }
    
    reverse(caminho.begin(), caminho.end());

    if (caminho.empty() || caminho[0] != id_no_a) {
        return vector<char>();
    }

    

    return caminho;
}

vector<char> Grafo::caminho_minimo_floyd(int id_no, int id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

Grafo * Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos) {

    unordered_set<char> subconjunto_nos(ids_nos.begin(), ids_nos.end());
    vector<Aresta*> arestas_subgrafo;

    //Incialmente pegar todos as arestas dos nós do subgrafo
    for(const auto& no : lista_adj){
        char u = no->id;
        if(subconjunto_nos.find(u) == subconjunto_nos.end()) continue; // Ignora nós que não estão no subconjunto

        //Pegar as arestas do nó atual
        for(const auto& aresta : no->arestas){
            char v = aresta->id_no_alvo;
            int peso = aresta->peso;
            
            if(subconjunto_nos.find(v) == subconjunto_nos.end()) continue; // Ignora arestas que não estão no subconjunto

            if(!in_direcionado && u > v) continue; // Evita arestas duplicadas em grafos não direcionados

            Aresta* nova_aresta = new Aresta();
            nova_aresta->peso = peso;
            nova_aresta->id_no_origem = u;
            nova_aresta->id_no_alvo = v;
            arestas_subgrafo.push_back(nova_aresta);
        }
    }

    //Ordenar as arestas por peso
    sort(arestas_subgrafo.begin(), arestas_subgrafo.end(), [](const Aresta* a, const Aresta* b) {
        return a->peso < b->peso;
    });

    
    Grafo* subgrafoAGM = new Grafo();

    //Adiciona os nós do subconjunto ao subgrafo AGM
    for(const auto& id : ids_nos) {
        subgrafoAGM->adicionarNo(id);
    }

    // Estrutura Union-Find para detectar ciclos
    unordered_map<char, char> parent;
    for(const auto& id : ids_nos) {
        parent[id] = id;
    }

    auto find = [&parent](char node) {
        while(parent[node] != node) {
            node = parent[node];
        }
        return node;
    };

    auto union_sets = [&parent, &find](char u, char v) {
        char root_u = find(u);
        char root_v = find(v);
        if(root_u != root_v) {
            parent[root_v] = root_u;
            return true;
        }
        return false;
    };

    int cont = 0;

    while(cont < subconjunto_nos.size() - 1 && !arestas_subgrafo.empty()) {
        Aresta* aresta = arestas_subgrafo.back();
        arestas_subgrafo.pop_back();

        char u = aresta->id_no_origem; 
        char v = aresta->id_no_alvo;


        // Verifica se u e v estão no mesmo subconjunto
        if(union_sets(u, v)) {
            subgrafoAGM->adicionarAresta(u, v, aresta->peso);
            cont++;
        }
    }

    //Liberação de memória das arestas
    for(auto& aresta : arestas_subgrafo) {
        delete aresta; // Libera memória das arestas que não foram usadas
    }


    if(cont < subconjunto_nos.size() - 1) {
        cout << "ERRO: Não foi possível formar uma árvore geradora mínima com os nós fornecidos." << endl;
        delete subgrafoAGM; // Libera memória se não for possível formar a árvore
        return nullptr;
    }

    //Imprime o subgrafo AGM
    cout << "Subgrafo AGM formado com os nós: ";
    for(const auto& id : ids_nos) {
        cout << id << " ";
    }
    cout << endl;

    subgrafoAGM->imprimirNoTerminal();

    return subgrafoAGM;
}

Grafo * Grafo::arvore_caminhamento_profundidade(int id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

int Grafo::raio() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

int Grafo::diametro() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

vector<char> Grafo::centro() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::periferia() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::vertices_de_articulacao() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}
