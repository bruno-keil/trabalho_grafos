#include "Grafo.h"
#include "includes.h"
#include "climits"

Grafo::Grafo()
{
    this->ordem = 0;
    this->in_direcionado = false;
    this->in_ponderado_aresta = true;
    this->in_ponderado_vertice = false;
}

Grafo::Grafo(const string &filePath)
{
    this->ordem = 0;
    ifstream file(filePath);
    string line;

    if (!file.is_open())
    {
        cerr << "Erro ao abrir o arquivo: " << filePath << endl;
        return;
    }

    cout << "Lendo grafo do arquivo: " << filePath << endl;
    // Lê as propriedades do Grafo
    if (getline(file, line))
    {
        stringstream ss(line);
        int dir, pond_aresta, pond_vertice;
        ss >> dir >> pond_aresta >> pond_vertice;
        this->in_direcionado = (dir == 1);
        this->in_ponderado_aresta = (pond_aresta == 1);
        this->in_ponderado_vertice = (pond_vertice == 1);
    }

    // Lê o número de vértices
    int num_vertices = 0;
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> num_vertices;
    }

    // Lê os vértices
    for (int i = 0; i < num_vertices; ++i)
    {
        if (getline(file, line))
        {
            stringstream ss(line);
            char id;
            int peso = 0;
            ss >> id;
            if (this->in_ponderado_vertice)
            {
                ss >> peso;
            }
            adicionarNo(id, peso);
        }
    }

    // Lê as arestas
    while (getline(file, line))
    {
        stringstream ss(line);
        char id_origem, id_destino;
        int peso = 0;
        ss >> id_origem >> id_destino;
        if (this->in_ponderado_aresta)
        {
            ss >> peso;
        }
        adicionarAresta(id_origem, id_destino, peso);
    }

    file.close();
}

Grafo::~Grafo()
{
    for (No *no : lista_adj)
    {
        delete no;
    }
}

void Grafo::adicionarNo(char id_no, int peso)
{
    No *novo_no = new No();
    novo_no->id = id_no;
    novo_no->peso = peso;
    lista_adj.push_back(novo_no);
    this->ordem++;
}

void Grafo::removerNo(char id_no)
{
    auto it = remove_if(lista_adj.begin(), lista_adj.end(), [id_no](No *no)
                        {
        if (no->id == id_no) {
            delete no;
            return true;
        }
        return false; });

    if (it != lista_adj.end())
    {
        lista_adj.erase(it, lista_adj.end());
        this->ordem--;

        for (No *no : lista_adj)
        {
            no->arestas.erase(
                std::remove_if(no->arestas.begin(), no->arestas.end(), [id_no](Aresta *aresta)
                               {
                    if (aresta->id_no_alvo == id_no) {
                        delete aresta; // Deallocate the memory for the edge.
                        return true;
                    }
                    return false; }),
                no->arestas.end());
        }
    }
}

// Função Grafo::adicionarAresta CORRIGIDA

void Grafo::adicionarAresta(char id_origem, char id_destino, int peso)
{
    No *origem = nullptr;
    No *destino = nullptr;

    for (No *no : lista_adj)
    {
        if (no->id == id_origem)
        {
            origem = no;
        }
        if (no->id == id_destino)
        {
            destino = no;
        }
        if (origem && destino)
        {
            break;
        }
    }

    if (origem)
    {
        Aresta *nova_aresta = new Aresta();
        nova_aresta->id_no_origem = id_origem;
        nova_aresta->id_no_alvo = id_destino;
        nova_aresta->peso = peso;
        origem->arestas.push_back(nova_aresta);
    }

    if (!this->in_direcionado && origem && destino)
    {
        Aresta *aresta_inversa = new Aresta();
        aresta_inversa->id_no_origem = id_destino;
        aresta_inversa->id_no_alvo = id_origem;
        aresta_inversa->peso = peso;
        destino->arestas.push_back(aresta_inversa);
    }
}

void Grafo::removerAresta(char id_origem, char id_destino, int peso)
{
    for (No *no : lista_adj)
    {
        if (no->id == id_origem)
        {
            auto it = std::find_if(no->arestas.begin(), no->arestas.end(), [&](Aresta *aresta)
                                   {
                bool target_match = aresta->id_no_alvo == id_destino;
                if (!target_match) {
                    return false;
                }
                if (this->in_ponderado_aresta) {
                    return aresta->peso == peso;
                }
                return true; });

            if (it != no->arestas.end())
            {
                delete *it;
                no->arestas.erase(it);
            }
            break;
        }
    }

    if (!this->in_direcionado)
    {
        for (No *no : lista_adj)
        {
            if (no->id == id_destino)
            {
                auto it = std::find_if(no->arestas.begin(), no->arestas.end(), [id_origem](Aresta *aresta)
                                       { return aresta->id_no_alvo == id_origem; });

                if (it != no->arestas.end())
                {
                    delete *it;
                    no->arestas.erase(it);
                }
                break;
            }
        }
    }
}

void Grafo::imprimirNoTerminal() const
{
    cout << "--- Exibindo Grafo no Terminal ---" << endl;
    gerarSaida(cout);
}

void Grafo::imprimirEmArquivo(const string &nomeArquivo) const
{
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }
    cout << "Imprimindo grafo no arquivo: " << nomeArquivo << endl
         << endl;
    outFile << "--- Exibindo Grafo no Arquivo ---" << endl;
    gerarSaida(outFile);
    outFile.close();
}

void Grafo::imprimirEmArquivoDot(const string &nomeArquivo) const
{
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }

    cout << "Imprimindo grafo no formato DOT em: " << nomeArquivo << endl
         << endl;

    if (in_direcionado)
    {
        outFile << "digraph G {" << endl;
    }
    else
    {
        outFile << "graph G {" << endl;
    }

    // Define os nós
    for (const auto &no : lista_adj)
    {
        outFile << "    " << no->id;
        if (in_ponderado_vertice)
        {
            outFile << " [label=\"" << no->id << " (" << no->peso << ")\"]";
        }
        outFile << ";" << endl;
    }

    // Define as arestas
    for (const auto &no_origem : lista_adj)
    {
        for (const auto &aresta : no_origem->arestas)
        {
            // Em grafos não direcionados, evita duplicar arestas
            if (!in_direcionado && no_origem->id > aresta->id_no_alvo)
            {
                continue;
            }

            outFile << "    " << no_origem->id;
            if (in_direcionado)
            {
                outFile << " -> ";
            }
            else
            {
                outFile << " -- ";
            }
            outFile << aresta->id_no_alvo;

            if (in_ponderado_aresta)
            {
                outFile << " [label=\"" << aresta->peso << "\"]";
            }
            outFile << ";" << endl;
        }
    }

    outFile << "}" << endl;
    outFile.close();
}

void Grafo::printTreeToDOT(const string &nomeArquivo, const vector<pair<char, char>> &back_edges) const
{
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }

    cout << "Imprimindo arvore no formato DOT em: " << nomeArquivo << endl
         << endl;

    if (in_direcionado)
    {
        outFile << "digraph G {" << endl;
    }
    else
    {
        outFile << "graph G {" << endl;
    }

    // Define os nós
    for (const auto &no : lista_adj)
    {
        outFile << "    " << no->id;
        if (in_ponderado_vertice)
        {
            outFile << " [label=\"" << no->id << " (" << no->peso << ")\"]";
        }
        outFile << ";" << endl;
    }

    // Define as arestas
    for (const auto &no_origem : lista_adj)
    {
        for (const auto &aresta : no_origem->arestas)
        {
            if (!in_direcionado && no_origem->id > aresta->id_no_alvo)
            {
                continue;
            }

            outFile << "    " << no_origem->id;
            if (in_direcionado)
            {
                outFile << " -> ";
            }
            else
            {
                outFile << " -- ";
            }
            outFile << aresta->id_no_alvo;

            bool is_back_edge = false;
            for (const auto &back_edge : back_edges)
            {
                if ((back_edge.first == no_origem->id && back_edge.second == aresta->id_no_alvo) ||
                    (!in_direcionado && back_edge.first == aresta->id_no_alvo && back_edge.second == no_origem->id))
                {
                    is_back_edge = true;
                    break;
                }
            }

            if (is_back_edge)
            {
                outFile << " [label=\"-1\"]";
            }

            outFile << ";" << endl;
        }
    }

    outFile << "}" << endl;
    outFile.close();
}

void Grafo::imprimirEmArquivoCsAcademy(const string &nomeArquivo) const
{
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }
    cout << "Imprimindo grafo no formato CSAcademy em: " << nomeArquivo << endl
         << endl;

    for (const auto &no_origem : lista_adj)
    {
        for (const auto &aresta : no_origem->arestas)
        {
            if (!in_direcionado && no_origem->id > aresta->id_no_alvo)
            {
                continue;
            }
            outFile << no_origem->id << " " << aresta->id_no_alvo;
            if (in_ponderado_aresta)
            {
                outFile << " " << aresta->peso;
            }
            outFile << endl;
        }
    }
    outFile.close();
}

void Grafo::printTreeToCsAcademy(const string &nomeArquivo, const vector<pair<char, char>> &back_edges) const
{
    ofstream outFile(nomeArquivo);
    if (!outFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }
    cout << "Imprimindo arvore no formato CSAcademy em: " << nomeArquivo << endl
         << endl;

    for (const auto &no_origem : lista_adj)
    {
        for (const auto &aresta : no_origem->arestas)
        {
            if (!in_direcionado && no_origem->id > aresta->id_no_alvo)
            {
                continue;
            }

            outFile << no_origem->id << " " << aresta->id_no_alvo << " " << aresta->peso;
            outFile << endl;
        }
    }
    outFile.close();
}

void Grafo::gerarSaida(ostream &out) const
{

    for (const auto &no : lista_adj)
    {
        out << no->id;

        if (in_ponderado_vertice)
        {
            out << " (Peso: " << no->peso << ")";
        }

        out << " ---> ";

        for (auto it = no->arestas.begin(); it != no->arestas.end(); ++it)
        {
            out << (*it)->id_no_alvo;
            if (in_ponderado_aresta)
            {
                out << "(" << (*it)->peso << ")";
            }
            if (next(it) != no->arestas.end())
            {
                out << ", ";
            }
        }
        out << endl;
    }

    out << "---------------------------------" << endl << endl;
}

vector<char> Grafo::fecho_transitivo_direto(char id_no)
{
    // Busca BFS para encontrar todos os nós alcançáveis a partir do nó dado
    set<char> fecho; // Usa set para evitar repetição e manter ordenado
    queue<char> fila;

    fila.push(id_no);
    set<char> visitados;
    visitados.insert(id_no);

    while (!fila.empty())
    {
        char atual = fila.front();
        fila.pop();

        // Procura o nó atual na lista de adjacências
        No *no_atual = nullptr;
        for (No *no : lista_adj)
        {
            if (no->id == atual)
            {
                no_atual = no;
                break;
            }
        }

        if (!no_atual)
            continue;

        // Visita todos os vizinhos do nó atual
        for (const auto &aresta : no_atual->arestas)
        {
            char vizinho = aresta->id_no_alvo;

            // Adiciona o vizinho ao fecho (exceto o próprio nó inicial)
            if (vizinho != id_no)
            {
                fecho.insert(vizinho);
            }

            // Se o vizinho ainda não foi visitado, adiciona à fila
            if (visitados.find(vizinho) == visitados.end())
            {
                visitados.insert(vizinho);
                fila.push(vizinho);
            }
        }
    }

    // Converte o set para vector e retorna
    vector<char> resultado(fecho.begin(), fecho.end());
    return resultado;
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no)
{
    char alvo = static_cast<char>(id_no);

    // Criar o grafo reverso
    map<char, vector<char>> grafo_reverso; // A chave é o nó de destino, e o valor é uma lista de nós de origem.
    for (const auto &no_origem : lista_adj)
    {
        for (const auto &aresta : no_origem->arestas)
        {
            grafo_reverso[aresta->id_no_alvo].push_back(no_origem->id);
        }
    }

    // Busca BFS no grafo reverso
    set<char> fecho; // Usa set para evitar repetição e manter ordenado
    queue<char> fila;

    fila.push(alvo);
    set<char> visitados;
    visitados.insert(alvo);

    while (!fila.empty())
    {
        char atual = fila.front();
        fila.pop();

        // Adiciona o nó atual, exceto o próprio nó
        if (atual != alvo)
        {
            fecho.insert(atual);
        }

        // Se o nó atual existe como chave no grafo reverso, visita os vizinhos
        if (grafo_reverso.count(atual))
        {
            for (char vizinho_reverso : grafo_reverso[atual])
            {
                if (visitados.find(vizinho_reverso) == visitados.end())
                {
                    visitados.insert(vizinho_reverso);
                    fila.push(vizinho_reverso);
                }
            }
        }
    }

    vector<char> resultado(fecho.begin(), fecho.end());
    return resultado;
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b)
{
    map<char, int> id_to_index;
    map<int, char> index_to_id;
    int index = 0;
    for (const auto &no : lista_adj)
    {
        id_to_index[no->id] = index;
        index_to_id[index] = no->id;
        index++;
    }

    int inicio_idx = id_to_index.count(id_no_a) ? id_to_index[id_no_a] : -1;
    int destino_idx = id_to_index.count(id_no_b) ? id_to_index[id_no_b] : -1;

    // Verificação de limites
    if (inicio_idx == -1 || destino_idx == -1)
    {
        cout << "ERRO: Nós inválidos! Recebido: " << id_no_a << " e " << id_no_b << endl;
        return vector<char>();
    }

    const int INF = std::numeric_limits<int>::max();
    vector<int> dist(ordem, INF);
    vector<bool> visited(ordem, false);
    vector<int> pai(ordem, -1);

    dist[inicio_idx] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.emplace(0, inicio_idx);

    int dist_total = 0;

    while (!fila.empty())
    {
        int u_idx = fila.top().second;
        fila.pop();

        if (visited[u_idx])
            continue;
        visited[u_idx] = true;

        if (u_idx == destino_idx)
        {
            dist_total = dist[u_idx];
            break;
        }

        No *no_atual = lista_adj[u_idx];

        for (Aresta *a : no_atual->arestas)
        {
            if (id_to_index.count(a->id_no_alvo))
            {
                int v_idx = id_to_index[a->id_no_alvo];
                int w = in_ponderado_aresta ? a->peso : 1;

                if (dist[u_idx] != INF && dist[u_idx] + w < dist[v_idx])
                {
                    dist[v_idx] = dist[u_idx] + w;
                    pai[v_idx] = u_idx;
                    fila.emplace(dist[v_idx], v_idx);
                }
            }
        }
    }

    // Reconstrução do caminho
    vector<char> caminho;
    int atual_idx = destino_idx;

    if (dist[atual_idx] == INF)
    { // Caminho não encontrado
        return vector<char>();
    }

    while (atual_idx != -1)
    {
        caminho.push_back(index_to_id[atual_idx]);
        atual_idx = pai[atual_idx];
    }

    reverse(caminho.begin(), caminho.end());

    cout << "Distância total do caminho: " << dist_total << endl;
    return caminho;
}

vector<char> Grafo::caminho_minimo_floyd(char id_no_a, char id_no_b)
{
    // Criar mapeamentos de ID para índices
    map<char, int> id_to_index;
    map<int, char> index_to_id;
    int index = 0;
    for (const auto &no : lista_adj)
    {
        id_to_index[no->id] = index;
        index_to_id[index] = no->id;
        index++;
    }

    int inicio_idx = id_to_index.count(id_no_a) ? id_to_index[id_no_a] : -1;
    int destino_idx = id_to_index.count(id_no_b) ? id_to_index[id_no_b] : -1;

    // Verificação de nós válidos
    if (inicio_idx == -1 || destino_idx == -1)
    {
        cout << "ERRO: Nós inválidos! Recebido: " << id_no_a << " e " << id_no_b << endl;
        return vector<char>();
    }

    const int INF = std::numeric_limits<int>::max();
    int n = ordem;

    // Inicializar matrizes de distância e predecessor
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> next(n, vector<int>(n, -1));

    // Inicializar distâncias para o próprio nó como 0
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }

    // Preencher a matriz de distâncias com as arestas do grafo
    for (int i = 0; i < n; i++)
    {
        No *no_atual = lista_adj[i];
        for (const auto &aresta : no_atual->arestas)
        {
            if (id_to_index.count(aresta->id_no_alvo))
            {
                int j = id_to_index[aresta->id_no_alvo];
                int peso = in_ponderado_aresta ? aresta->peso : 1;
                dist[i][j] = peso;
                next[i][j] = j;
            }
        }
    }

    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }

    // Verificar se existe caminho
    if (dist[inicio_idx][destino_idx] == INF)
    {
        cout << "Não existe caminho entre " << id_no_a << " e " << id_no_b << endl;
        return vector<char>();
    }

    // Reconstruir o caminho
    vector<char> caminho;
    int atual = inicio_idx;

    while (atual != destino_idx)
    {
        caminho.push_back(index_to_id[atual]);
        atual = next[atual][destino_idx];

        if (atual == -1)
        {
            // Erro na reconstrução do caminho
            cout << "Erro na reconstrução do caminho" << endl;
            return vector<char>();
        }
    }

    // Adicionar o nó de destino
    caminho.push_back(index_to_id[destino_idx]);

    cout << "Distância total do caminho: " << dist[inicio_idx][destino_idx] << endl;
    return caminho;
}

Grafo *Grafo::arvore_geradora_minima_prim(vector<char> ids_nos)
{
    if (ids_nos.empty())
        return nullptr;

    unordered_set<char> subconjunto(ids_nos.begin(), ids_nos.end());
    unordered_set<char> visitados;
    vector<Aresta *> arestas_possiveis;

    // Cria o subgrafo AGM
    Grafo *agm = new Grafo();
    agm->in_direcionado = this->in_direcionado;
    agm->in_ponderado_aresta = this->in_ponderado_aresta;
    agm->in_ponderado_vertice = this->in_ponderado_vertice;

    // Adiciona os nós do subconjunto ao subgrafo AGM
    for (char id : ids_nos)
    {
        // Procura o nó original para copiar o peso, se houver
        int peso = 0;
        for (No *no : lista_adj)
        {
            if (no->id == id)
            {
                peso = no->peso;
                break;
            }
        }
        agm->adicionarNo(id, peso);
    }

    // Começa por qualquer nó do subconjunto
    char inicial = ids_nos[0];
    visitados.insert(inicial);

    // Adiciona as arestas do nó inicial à lista de possíveis arestas
    auto adicionar_arestas = [&](char no_id)
    {
        No *no = nullptr;
        for (No *n : lista_adj)
        {
            if (n->id == no_id)
            {
                no = n;
                break;
            }
        }
        if (!no)
            return;
        for (Aresta *aresta : no->arestas)
        {
            char vizinho = aresta->id_no_alvo;
            if (subconjunto.count(vizinho) && !visitados.count(vizinho))
            {
                arestas_possiveis.push_back(aresta);
            }
        }
    };

    adicionar_arestas(inicial);

    while (visitados.size() < subconjunto.size() && !arestas_possiveis.empty())
    {
        // Encontra a aresta de menor peso que conecta um nó visitado a um não visitado
        auto it = min_element(arestas_possiveis.begin(), arestas_possiveis.end(),
                              [](Aresta *a, Aresta *b)
                              { return a->peso < b->peso; });

        Aresta *menor = *it;
        arestas_possiveis.erase(it);

        char u = menor->id_no_origem;
        char v = menor->id_no_alvo;

        // Garante que v é o nó ainda não visitado
        if (visitados.count(v))
            std::swap(u, v);
        if (visitados.count(v))
            continue; // Se ambos já visitados, ignora

        agm->adicionarAresta(u, v, menor->peso);
        visitados.insert(v);

        adicionar_arestas(v);
    }

    // Se não foi possível conectar todos os nós do subconjunto, retorna nullptr
    if (visitados.size() < subconjunto.size())
    {
        cout << "ERRO: Não foi possível formar uma árvore geradora mínima com os nós fornecidos.\n"
             << endl;
        delete agm;
        return nullptr;
    }

    return agm;
}

Grafo *Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos)
{

    unordered_set<char> subconjunto_nos(ids_nos.begin(), ids_nos.end());
    vector<Aresta *> arestas_subgrafo;

    // Incialmente pegar todos as arestas dos nós do subgrafo
    for (const auto &no : lista_adj)
    {
        char u = no->id;
        if (subconjunto_nos.find(u) == subconjunto_nos.end())
            continue; // Ignora nós que não estão no subconjunto

        // Pegar as arestas do nó atual
        for (const auto &aresta : no->arestas)
        {
            char v = aresta->id_no_alvo;
            int peso = aresta->peso;

            if (subconjunto_nos.find(v) == subconjunto_nos.end())
                continue; // Ignora arestas que não estão no subconjunto

            if (!in_direcionado && u > v)
                continue; // Evita arestas duplicadas em grafos não direcionados

            Aresta *nova_aresta = new Aresta();
            nova_aresta->peso = peso;
            nova_aresta->id_no_origem = u;
            nova_aresta->id_no_alvo = v;
            arestas_subgrafo.push_back(nova_aresta);
        }
    }

    // Ordenar as arestas por peso
    sort(arestas_subgrafo.begin(), arestas_subgrafo.end(), [](const Aresta *a, const Aresta *b)
         { return a->peso > b->peso; });

    Grafo *subgrafoAGM = new Grafo();

    // Adiciona os nós do subconjunto ao subgrafo AGM
    for (const auto &id : ids_nos)
    {
        subgrafoAGM->adicionarNo(id);
    }

    // Estrutura Union-Find para detectar ciclos
    unordered_map<char, char> parent;
    for (const auto &id : ids_nos)
    {
        parent[id] = id;
    }

    auto find = [&parent](char node)
    {
        while (parent[node] != node)
        {
            node = parent[node];
        }
        return node;
    };

    auto union_sets = [&parent, &find](char u, char v)
    {
        char root_u = find(u);
        char root_v = find(v);
        if (root_u != root_v)
        {
            parent[root_v] = root_u;
            return true;
        }
        return false;
    };

    int cont = 0;

    while (cont < subconjunto_nos.size() - 1 && !arestas_subgrafo.empty())
    {
        Aresta *aresta = arestas_subgrafo.back();
        arestas_subgrafo.pop_back();

        char u = aresta->id_no_origem;
        char v = aresta->id_no_alvo;

        // Verifica se u e v estão no mesmo subconjunto
        if (union_sets(u, v))
        {
            subgrafoAGM->adicionarAresta(u, v, aresta->peso); // Adiciona a aresta ao subgrafo AGM
            cont++;
        }
    }

    // Liberação de memória das arestas
    for (auto &aresta : arestas_subgrafo)
    {
        delete aresta; // Libera memória das arestas que não foram usadas
    }

    if (cont < subconjunto_nos.size() - 1)
    {
        cout << "ERRO: Não foi possível formar uma árvore geradora mínima com os nós fornecidos." << endl;
        delete subgrafoAGM; // Libera memória se não for possível formar a árvore
        return nullptr;
    }
    return subgrafoAGM;
}

void Grafo::dfs_profundidade_helper(char id_no, char parent_id, set<char> &visitados, set<char> &recursion_stack, Grafo *arvore, vector<char> &insertion_sequence, vector<pair<char, char>> &back_edges)
{
    visitados.insert(id_no);
    recursion_stack.insert(id_no);
    insertion_sequence.push_back(id_no);

    No *no_origem = nullptr;
    for (No *no : this->lista_adj)
    {
        if (no->id == id_no)
        {
            no_origem = no;
            break;
        }
    }

    if (!no_origem)
        return;

    for (Aresta *aresta : no_origem->arestas)
    {
        char id_vizinho = aresta->id_no_alvo;
        if (id_vizinho == parent_id)
        {
            continue;
        }

        if (visitados.find(id_vizinho) == visitados.end())
        {
            int peso = this->in_ponderado_aresta ? aresta->peso : 1;
            arvore->adicionarAresta(id_no, id_vizinho, peso);
            dfs_profundidade_helper(id_vizinho, id_no, visitados, recursion_stack, arvore, insertion_sequence, back_edges);
        }
        else if (recursion_stack.count(id_vizinho))
        {
            back_edges.push_back({id_no, id_vizinho});
        }
    }

    recursion_stack.erase(id_no);
}

int Grafo::calcular_distancia(char id_origem, char id_destino)
{
    map<char, int> id_to_index;
    map<int, char> index_to_id;
    int index = 0;
    for (const auto &no : lista_adj)
    {
        id_to_index[no->id] = index;
        index_to_id[index] = no->id;
        index++;
    }

    int inicio_idx = id_to_index.count(id_origem) ? id_to_index[id_origem] : -1;
    int destino_idx = id_to_index.count(id_destino) ? id_to_index[id_destino] : -1;

    if (inicio_idx == -1 || destino_idx == -1)
    {
        return INT_MAX;
    }

    const int INF = std::numeric_limits<int>::max();
    vector<int> dist(ordem, INF);
    dist[inicio_idx] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.emplace(0, inicio_idx);

    while (!fila.empty())
    {
        int u_idx = fila.top().second;
        fila.pop();

        if (u_idx == destino_idx)
        {
            return dist[u_idx];
        }

        No *no_atual = lista_adj[u_idx];

        for (Aresta *a : no_atual->arestas)
        {
            if (id_to_index.count(a->id_no_alvo))
            {
                int v_idx = id_to_index[a->id_no_alvo];
                int w = in_ponderado_aresta ? a->peso : 1;

                if (dist[u_idx] != INF && dist[u_idx] + w < dist[v_idx])
                {
                    dist[v_idx] = dist[u_idx] + w;
                    fila.emplace(dist[v_idx], v_idx);
                }
            }
        }
    }

    return dist[destino_idx];
}

void Grafo::dfs_articulacao_helper(char u, map<char, int> &desc, map<char, int> &low, map<char, char> &parent, set<char> &articulacoes, int &time, bool &is_root)
{
    // Define o tempo de descoberta e o low-link para o nó atual.
    desc[u] = low[u] = ++time;
    int children = 0; // Contador de filhos na árvore DFS.

    No *no_u = nullptr;
    for (No *no : lista_adj)
    {
        if (no->id == u)
        {
            no_u = no;
            break;
        }
    }
    if (!no_u)
        return;

    // Itera sobre os vizinhos do nó 'u'.
    for (Aresta *aresta : no_u->arestas)
    {
        char v = aresta->id_no_alvo;
        // Se 'v' é o pai de 'u' na árvore de busca, ignora.
        if (parent.count(u) && v == parent[u])
        {
            continue;
        }

        // Se 'v' já foi visitado, atualiza o low-link de 'u'.
        if (desc.count(v))
        {
            low[u] = min(low[u], desc[v]);
        }
        else
        {
            // Se 'v' não foi visitado, 'u' é seu pai e a recursão continua.
            children++;
            parent[v] = u;
            bool child_is_root = false;
            dfs_articulacao_helper(v, desc, low, parent, articulacoes, time, child_is_root);
            low[u] = min(low[u], low[v]);

            // Condição de articulação para a raiz da árvore DFS.
            if (is_root && children > 1)
            {
                articulacoes.insert(u);
            }
            // Condição de articulação para os demais nós.
            if (!is_root && low[v] >= desc[u])
            {
                articulacoes.insert(u);
            }
        }
    }
}

pair<Grafo *, vector<pair<char, char>>> Grafo::arvore_caminhamento_profundidade(char id_no)
{
    Grafo *arvore = new Grafo();
    arvore->in_direcionado = this->in_direcionado;
    arvore->in_ponderado_aresta = true;
    arvore->in_ponderado_vertice = this->in_ponderado_vertice;

    for (const auto &no : this->lista_adj)
    {
        arvore->adicionarNo(no->id, no->peso);
    }

    set<char> visitados;
    set<char> recursion_stack;
    vector<char> insertion_sequence;
    vector<pair<char, char>> back_edges;

    dfs_profundidade_helper(id_no, '\0', visitados, recursion_stack, arvore, insertion_sequence, back_edges);

    for (const auto &node : this->lista_adj)
    {
        if (visitados.find(node->id) == visitados.end())
        {
            dfs_profundidade_helper(node->id, '\0', visitados, recursion_stack, arvore, insertion_sequence, back_edges);
        }
    }

    for (const auto &edge : back_edges)
    {
        arvore->adicionarAresta(edge.first, edge.second, 0);
    }

    cout << "Arvore de caminhamento em profundidade gerada." << endl;
    cout << "Sequencia de insercao (ordem de visita): ";
    for (size_t i = 0; i < insertion_sequence.size(); ++i)
    {
        cout << insertion_sequence[i] << (i == insertion_sequence.size() - 1 ? "" : ", ");
    }
    cout << endl;
    cout << "Arestas de retorno (back edges): ";
    if (back_edges.empty())
    {
        cout << "Nenhuma.";
    }
    else
    {
        for (size_t i = 0; i < back_edges.size(); ++i)
        {
            cout << "(" << back_edges[i].first << ", " << back_edges[i].second << ")" << (i == back_edges.size() - 1 ? "" : "");
        }
    }
    cout << endl
         << endl;

    return {arvore, back_edges};
}

// Calcula o raio do grafo.
int Grafo::raio()
{
    int raio = INT_MAX;
    bool is_conexo = true;

    // Itera sobre cada nó para calcular sua excentricidade.
    for (const auto &no_origem : this->lista_adj)
    {
        int excentricidade = 0;
        // Encontra a maior distância deste nó para todos os outros.
        for (const auto &no_destino : this->lista_adj)
        {
            if (no_origem->id != no_destino->id)
            {
                int dist = calcular_distancia(no_origem->id, no_destino->id);
                // Se não houver caminho, o grafo é desconexo.
                if (dist == INT_MAX)
                {
                    is_conexo = false;
                    break;
                }
                if (dist > excentricidade)
                {
                    excentricidade = dist;
                }
            }
        }

        if (!is_conexo)
            break;

        // O raio é a menor de todas as excentricidades.
        if (excentricidade < raio)
        {
            raio = excentricidade;
        }
    }

    // Se o grafo for desconexo, o raio é considerado infinito.
    if (!is_conexo)
    {
        cout << "O grafo e desconexo, portanto o raio e o diametro sao infinitos." << endl;
        return -1;
    }

    return raio;
}

// Calcula o diâmetro do grafo.
int Grafo::diametro()
{
    int diametro = 0;
    bool is_conexo = true;

    // Itera sobre cada nó para calcular sua excentricidade.
    for (const auto &no_origem : this->lista_adj)
    {
        int excentricidade = 0;
        // Encontra a maior distância deste nó para todos os outros.
        for (const auto &no_destino : this->lista_adj)
        {
            if (no_origem->id != no_destino->id)
            {
                int dist = calcular_distancia(no_origem->id, no_destino->id);
                // Se não houver caminho, o grafo é desconexo.
                if (dist == INT_MAX)
                {
                    is_conexo = false;
                    break;
                }
                if (dist > excentricidade)
                {
                    excentricidade = dist;
                }
            }
        }

        if (!is_conexo)
            break;

        // O diâmetro é a maior de todas as excentricidades.
        if (excentricidade > diametro)
        {
            diametro = excentricidade;
        }
    }

    // Se o grafo for desconexo, o diâmetro é considerado infinito.
    if (!is_conexo)
    {
        return -1;
    }

    return diametro;
}

// Encontra o centro do grafo.
vector<char> Grafo::centro()
{
    vector<char> centro_nos;
    int r = raio();

    // Se o grafo for desconexo, não há centro.
    if (r == -1)
    {
        return centro_nos;
    }

    // Itera sobre cada nó para verificar se sua excentricidade é igual ao raio.
    for (const auto &no_origem : this->lista_adj)
    {
        int excentricidade = 0;
        for (const auto &no_destino : this->lista_adj)
        {
            int dist = calcular_distancia(no_origem->id, no_destino->id);
            if (dist > excentricidade)
            {
                excentricidade = dist;
            }
        }
        // Se a excentricidade for igual ao raio, o nó pertence ao centro.
        if (excentricidade == r)
        {
            centro_nos.push_back(no_origem->id);
        }
    }
    return centro_nos;
}

// Encontra a periferia do grafo.
vector<char> Grafo::periferia()
{
    vector<char> periferia_nos;
    int d = diametro();

    // Se o grafo for desconexo, não há periferia.
    if (d == -1)
    {
        return periferia_nos;
    }

    // Itera sobre cada nó para verificar se sua excentricidade é igual ao diâmetro.
    for (const auto &no_origem : this->lista_adj)
    {
        int excentricidade = 0;
        for (const auto &no_destino : this->lista_adj)
        {
            int dist = calcular_distancia(no_origem->id, no_destino->id);
            if (dist > excentricidade)
            {
                excentricidade = dist;
            }
        }
        // Se a excentricidade for igual ao diâmetro, o nó pertence à periferia.
        if (excentricidade == d)
        {
            periferia_nos.push_back(no_origem->id);
        }
    }
    return periferia_nos;
}

// Encontra todos os vértices de articulação (pontos de corte) do grafo.
vector<char> Grafo::vertices_de_articulacao()
{
    map<char, int> desc;
    map<char, int> low;
    map<char, char> parent;
    set<char> articulacoes;
    int time = 0;

    // Itera sobre todos os nós do grafo.
    for (const auto &no : this->lista_adj)
    {
        // Se o nó ainda não foi visitado, inicia uma nova busca DFS a partir dele.
        if (desc.find(no->id) == desc.end())
        {
            bool is_root = true;
            dfs_articulacao_helper(no->id, desc, low, parent, articulacoes, time, is_root);
        }
    }

    // Converte o conjunto de articulações para um vetor e o retorna.
    return vector<char>(articulacoes.begin(), articulacoes.end());
}

vector<char> Grafo::ds_2_greedy()
{
    vector<char> D;
    set<char> U;

    // Initialize U with all vertices
    for (const auto &no : lista_adj)
    {
        U.insert(no->id);
    }

    while (!U.empty())
    {
        char melhor_no = '\0';
        int max_cobertos = -1;
        set<char> melhores_cobertos;

        // Iterate over all nodes to find the best candidate
        for (const auto &candidato : lista_adj)
        {
            set<char> cobertos_pelo_candidato;
            // Check which uncovered vertices are covered by the current candidate
            for (char u_node : U)
            {
                if (calcular_distancia(candidato->id, u_node) <= 2)
                {
                    cobertos_pelo_candidato.insert(u_node);
                }
            }

            if ((int)cobertos_pelo_candidato.size() > max_cobertos)
            {
                max_cobertos = cobertos_pelo_candidato.size();
                melhor_no = candidato->id;
                melhores_cobertos = cobertos_pelo_candidato;
            }
        }

        // Add the best node to the dominating set
        D.push_back(melhor_no);
        cout << "Nó adicionado ao conjunto dominante: " << melhor_no << endl;


        // Remove the newly covered vertices from U
        for (char no_coberto : melhores_cobertos)
        {
            U.erase(no_coberto);
        }
    }
    return D;
}