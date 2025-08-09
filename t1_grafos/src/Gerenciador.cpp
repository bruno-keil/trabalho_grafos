#include "Gerenciador.h"
#include "includes.h"

void Gerenciador::menu_principal(Grafo *grafo, const string &instanceName)
{
    char resp;
    do
    {
        cout << "--- Menu Principal ---" << endl;
        cout << "(1) Funcoes Basicas" << endl;
        cout << "(2) Algoritmos em Grafos" << endl;
        cout << "(3) 2-distance dominating set (Heuristicas)" << endl;
        cout << "(0) Sair" << endl;
        cin >> resp;

        switch (resp)
        {
        case '1':
            menu_basico(grafo);
            break;
        case '2':
            menu_algoritmos(grafo);
            break;
        case '3':
            menu_heuristics(grafo, instanceName);
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

void Gerenciador::menu_basico(Grafo *grafo)
{
    char resp;
    do
    {
        cout << "--- Funcoes Basicas ---" << endl;
        cout << "(1) Adicionar No" << endl;
        cout << "(2) Remover No" << endl;
        cout << "(3) Adicionar Aresta" << endl;
        cout << "(4) Remover Aresta" << endl;
        cout << "(5) Imprimir Grafo" << endl;
        cout << "(6) Imprimir Grafo em Arquivo." << endl;
        cout << "(7) Imprimir Grafo em Arquivo DOT." << endl;
        cout << "(8) Imprimir Grafo em Arquivo CSAcademy." << endl;
        cout << "(0) Voltar ao Menu Principal" << endl;
        cin >> resp;

        switch (resp)
        {
        case '1':
        {
            char id;
            int peso = 0;
            cout << "Digite o id do no: ";
            cin >> id;
            if (grafo->in_ponderado_vertice)
            {
                cout << "Digite o peso do no: ";
                cin >> peso;
            }
            grafo->adicionarNo(id, peso);
            break;
        }
        case '2':
        {
            char id = get_id_entrada();
            grafo->removerNo(id);
            break;
        }
        case '3':
        {
            char id_origem, id_destino;
            int peso = 0;
            cout << "Digite o id do no de origem: ";
            cin >> id_origem;
            cout << "Digite o id do no de destino: ";
            cin >> id_destino;
            if (grafo->in_ponderado_aresta)
            {
                cout << "Digite o peso da aresta: ";
                cin >> peso;
            }
            grafo->adicionarAresta(id_origem, id_destino, peso);
            break;
        }
        case '4':
        {
            char id_origem, id_destino;
            int peso = 0;
            cout << "Digite o id do no de origem: ";
            cin >> id_origem;
            cout << "Digite o id do no de destino: ";
            cin >> id_destino;
            if (grafo->in_ponderado_aresta)
            {
                cout << "Digite o peso da aresta: ";
                cin >> peso;
            }
            grafo->removerAresta(id_origem, id_destino, peso);
            break;
        }
        case '5':
            grafo->imprimirNoTerminal();
            break;
        case '6':
        {
            string file;
            cout << "Digite o nome do arquivo: ";
            cin >> file;
            grafo->imprimirEmArquivo(file);
            break;
        }
        case '7':
        {
            string file;
            cout << "Digite o nome do arquivo: ";
            cin >> file;
            grafo->imprimirEmArquivoDot(file);
            break;
        }
        case '8':
        {
            string file;
            cout << "Digite o nome do arquivo: ";
            cin >> file;
            grafo->imprimirEmArquivoCsAcademy(file);
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

void Gerenciador::menu_algoritmos(Grafo *grafo)
{
    char resp;
    do
    {
        cout << "Digite uma das opcoes abaixo e pressione enter:" << endl
             << endl;
        cout << "(a) Fecho transitivo direto de um no;" << endl;
        cout << "(b) Fecho transitivo indireto de um no;" << endl;
        cout << "(c) Caminho minimo (Djikstra);" << endl;
        cout << "(d) Caminho minimo (Floyd);" << endl;
        cout << "(e) Arvore Geradora Minima (Algoritmo de Prim);" << endl;
        cout << "(f) Arvore Geradora Minima (Algoritmo de Kruskal);" << endl;
        cout << "(g) Arvore de caminhamento em profundidade;" << endl;
        cout << "(h) Raio, diametro, centro e periferia do grafo;" << endl;
        cout << "(i) Vertices de Articulacao;" << endl;
        cout << "(0) Sair;" << endl
             << endl;
        cin >> resp;

        switch (resp)
        {
        case 'a':
        {

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_direto = grafo->fecho_transitivo_direto(id_no);

            // Impressão em tela do fecho transitivo direto
            cout << "Fecho transitivo direto do no " << id_no << ": ";
            if (fecho_transitivo_direto.empty())
            {
                cout << "Nenhum no alcanca " << id_no << ".";
            }
            else
            {
                for (size_t i = 0; i < fecho_transitivo_direto.size(); ++i)
                {
                    cout << fecho_transitivo_direto[i];
                    if (i != fecho_transitivo_direto.size() - 1)
                        cout << ", ";
                }
            }
            cout << endl
                 << endl;
            // Impressão em arquivo do fecho transitivo direto
            if (pergunta_imprimir_arquivo("fecho_trans_dir.txt"))
            {
                ofstream out("fecho_trans_dir.txt");
                if (!out.is_open())
                {
                    cout << "Erro ao abrir o arquivo para escrita." << endl;
                }
                else
                {
                    out << "Fecho transitivo direto do no " << id_no << ": ";
                    if (fecho_transitivo_direto.empty())
                    {
                        out << "Nenhum no alcanca " << id_no << ".";
                    }
                    else
                    {
                        for (size_t i = 0; i < fecho_transitivo_direto.size(); ++i)
                        {
                            out << fecho_transitivo_direto[i];
                            if (i != fecho_transitivo_direto.size() - 1)
                                out << ", ";
                        }
                    }
                    out << endl;
                    out.close();
                    cout << "Fecho transitivo direto salvo em fecho_trans_dir.txt" << endl;
                }
            }

            break;
        }

        case 'b':
        {

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_indireto = grafo->fecho_transitivo_indireto(id_no);

            // Impressão em tela do fecho transitivo indireto
            cout << "Fecho transitivo indireto do no " << id_no << ": ";
            if (fecho_transitivo_indireto.empty())
            {
                cout << "Nenhum no alcanca " << id_no << ".";
            }
            else
            {
                for (size_t i = 0; i < fecho_transitivo_indireto.size(); ++i)
                {
                    cout << fecho_transitivo_indireto[i];
                    if (i != fecho_transitivo_indireto.size() - 1)
                        cout << ", ";
                }
            }
            cout << endl
                 << endl;

            if (pergunta_imprimir_arquivo("fecho_trans_indir.txt"))
            {
                ofstream out("fecho_trans_indir.txt");
                if (!out.is_open())
                {
                    cout << "Erro ao abrir o arquivo para escrita." << endl;
                }
                else
                {
                    out << "Fecho transitivo indireto do no " << id_no << ": ";
                    if (fecho_transitivo_indireto.empty())
                    {
                        out << "Nenhum no alcanca " << id_no << ".";
                    }
                    else
                    {
                        for (size_t i = 0; i < fecho_transitivo_indireto.size(); ++i)
                        {
                            out << fecho_transitivo_indireto[i];
                            if (i != fecho_transitivo_indireto.size() - 1)
                                out << ", ";
                        }
                    }
                    out << endl;
                    out.close();
                    cout << "Fecho transitivo indireto salvo em fecho_trans_indir.txt" << endl;
                }
            }

            break;
        }

        case 'c':
        {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_dijkstra = grafo->caminho_minimo_dijkstra(id_no_1, id_no_2);
            cout << "Caminho minimo entre " << id_no_1 << " e " << id_no_2 << ": ";
            if (caminho_minimo_dijkstra.empty())
            {
                cout << "Nao existe caminho entre os nos." << endl;
            }
            else
            {
                for (char c : caminho_minimo_dijkstra)
                {
                    cout << c << " ";
                }
                cout << endl;

                cout << endl;
            }

            if (pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt"))
            {
                ofstream outFile("caminho_minimo_dijkstra.txt");
                if (outFile.is_open())
                {
                    if (caminho_minimo_dijkstra.empty())
                    {
                        outFile << "Nao existe caminho entre " << id_no_1 << " e " << id_no_2 << "." << endl;
                    }
                    else
                    {
                        for (size_t i = 0; i < caminho_minimo_dijkstra.size(); ++i)
                        {
                            outFile << caminho_minimo_dijkstra[i] << (i == caminho_minimo_dijkstra.size() - 1 ? "" : " -> ");
                        }
                        outFile << endl;
                    }
                    cout << "Caminho minimo salvo em caminho_minimo_dijkstra.txt" << endl;
                    outFile.close();
                }
                else
                {
                    cout << "Erro ao abrir o arquivo para escrita." << endl;
                }
            }
            break;
        }

        case 'd':
        {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_floyd = grafo->caminho_minimo_floyd(id_no_1, id_no_2);

            cout << "Caminho minimo entre " << id_no_1 << " e " << id_no_2 << ": ";
            if (caminho_minimo_floyd.empty())
            {
                cout << "Nao existe caminho entre os nos." << endl;
            }
            else
            {
                for (char c : caminho_minimo_floyd)
                {
                    cout << c << " ";
                }
                cout << endl;

                cout << endl;
            }

            if (pergunta_imprimir_arquivo("caminho_minimo_floyd.txt"))
            {
                ofstream outFile("caminho_minimo_floyd.txt");
                if (outFile.is_open())
                {
                    if (caminho_minimo_floyd.empty())
                    {
                        outFile << "Nao existe caminho entre " << id_no_1 << " e " << id_no_2 << "." << endl;
                    }
                    else
                    {
                        for (size_t i = 0; i < caminho_minimo_floyd.size(); ++i)
                        {
                            outFile << caminho_minimo_floyd[i] << (i == caminho_minimo_floyd.size() - 1 ? "" : " -> ");
                        }
                        outFile << endl;
                    }
                    cout << "Caminho minimo salvo em caminho_minimo_floyd.txt" << endl;
                    outFile.close();
                }
                else
                {
                    cout << "Erro ao abrir o arquivo para escrita." << endl;
                }
            }

            break;
        }
        case 'e':
        {

            int tam;
            cout << "Digite o tamanho do subconjunto: ";
            cin >> tam;

            if (tam > 0 && tam <= grafo->ordem)
            {

                vector<char> ids = get_conjunto_ids(grafo, tam);
                Grafo *arvore_geradora_minima_prim = grafo->arvore_geradora_minima_prim(ids);

                if (arvore_geradora_minima_prim)
                {
                    // Impressão em tela da AGM de Prim
                    cout << "Subgrafo AGM (Prim) formado com os nós: ";
                    for (const auto &id : ids)
                    {
                        cout << id << " ";
                    }
                    cout << endl;
                    arvore_geradora_minima_prim->imprimirNoTerminal();

                    if (pergunta_imprimir_arquivo("agm_prim.txt"))
                    {
                        arvore_geradora_minima_prim->imprimirEmArquivo("agm_prim.txt");
                        cout << "AGM (Prim) salva em agm_prim.txt" << endl;
                    }
                    delete arvore_geradora_minima_prim;
                }
                else
                {
                }
            }
            else
            {
                cout << "Valor invalido" << endl;
            }

            break;
        }

        case 'f':
        {

            int tam;
            cout << "Digite o tamanho do subconjunto: ";
            cin >> tam;

            if (tam > 0 && tam <= grafo->ordem)
            {

                vector<char> ids = get_conjunto_ids(grafo, tam);
                Grafo *arvore_geradora_minima_kruskal = grafo->arvore_geradora_minima_kruskal(ids);

                // Imprime o subgrafo AGM
                cout << "Subgrafo AGM formado com os nós: ";
                for (const auto &id : ids)
                {
                    cout << id << " ";
                }
                cout << endl;

                arvore_geradora_minima_kruskal->imprimirNoTerminal();

                if (pergunta_imprimir_arquivo("../agm_kruskal.txt"))
                {
                    arvore_geradora_minima_kruskal->imprimirEmArquivo("../agm_kruskal.txt");
                }

                delete arvore_geradora_minima_kruskal;
            }
            else
            {
                cout << "Valor invalido" << endl;
            }

            break;
        }

        case 'g':
        {
            char id_no = get_id_entrada();
            pair<Grafo *, vector<pair<char, char>>> result = grafo->arvore_caminhamento_profundidade(id_no);

            Grafo *arvore = result.first;
            vector<pair<char, char>> back_edges = result.second;

            if (arvore)
            {
                if (pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt"))
                {
                    arvore->printTreeToArquivo("arvore_caminhamento_profundidade.txt", back_edges);
                }
                delete arvore;
            }
            break;
        }

        case 'h':
        {
            int r = grafo->raio();
            if (r != -1)
            {
                int d = grafo->diametro();
                vector<char> c = grafo->centro();
                vector<char> p = grafo->periferia();

                cout << endl
                     << "--- Propriedades do Grafo ---" << endl;
                cout << "Raio: " << r << endl;
                cout << "Diametro: " << d << endl;

                cout << "Centro: ";
                for (size_t i = 0; i < c.size(); ++i)
                {
                    cout << c[i] << (i == c.size() - 1 ? "" : ", ");
                }
                cout << endl;

                cout << "Periferia: ";
                for (size_t i = 0; i < p.size(); ++i)
                {
                    cout << p[i] << (i == p.size() - 1 ? "" : ", ");
                }
                cout << endl
                     << endl;

                if (pergunta_imprimir_arquivo("propriedades_grafo.txt"))
                {
                    ofstream outFile("propriedades_grafo.txt");
                    if (outFile.is_open())
                    {
                        outFile << "--- Propriedades do Grafo ---" << endl;
                        outFile << "Raio: " << r << endl;
                        outFile << "Diametro: " << d << endl;
                        outFile << "Centro: ";
                        for (size_t i = 0; i < c.size(); ++i)
                        {
                            outFile << c[i] << (i == c.size() - 1 ? "" : ", ");
                        }
                        outFile << endl;
                        outFile << "Periferia: ";
                        for (size_t i = 0; i < p.size(); ++i)
                        {
                            outFile << p[i] << (i == p.size() - 1 ? "" : ", ");
                        }
                        outFile << endl;
                        outFile.close();
                        cout << "Propriedades do grafo salvas em propriedades_grafo.txt" << endl;
                    }
                    else
                    {
                        cout << "Erro ao abrir o arquivo para escrita." << endl;
                    }
                }
            }
            break;
        }
        case 'i':
        {
            vector<char> articulacao = grafo->vertices_de_articulacao();
            cout << endl
                 << "--- Vertices de Articulacao ---" << endl;
            if (articulacao.empty())
            {
                cout << "O grafo nao possui vertices de articulacao." << endl;
            }
            else
            {
                for (size_t i = 0; i < articulacao.size(); ++i)
                {
                    cout << articulacao[i] << (i == articulacao.size() - 1 ? "" : ", ");
                }
            }
            cout << endl
                 << endl;

            if (pergunta_imprimir_arquivo("vertices_articulacao.txt"))
            {
                ofstream outFile("vertices_articulacao.txt");
                if (outFile.is_open())
                {
                    outFile << "--- Vertices de Articulacao ---" << endl;
                    if (articulacao.empty())
                    {
                        outFile << "O grafo nao possui vertices de articulacao." << endl;
                    }
                    else
                    {
                        for (size_t i = 0; i < articulacao.size(); ++i)
                        {
                            outFile << articulacao[i] << (i == articulacao.size() - 1 ? "" : ", ");
                        }
                    }
                    outFile << endl;
                    outFile.close();
                    cout << "Vertices de articulacao salvos em vertices_articulacao.txt" << endl;
                }
                else
                {
                    cout << "Erro ao abrir o arquivo para escrita." << endl;
                }
            }
            break;
        }
        case '0':
        {
            return;
        }
        default:
        {
            cout << "Opção inválida" << endl;
            break;
        }
        }
    } while (resp != '0');
}

void Gerenciador::menu_heuristics(Grafo *grafo, const string &instanceName)
{
    char resp;
    do
    {
        cout << "--- Heurísticas ---" << endl;
        cout << "(1) 2-distance Dominating Set (Guloso)" << endl;
        cout << "(2) 2-distance Dominating Set (Guloso Randomizado)" << endl;
        cout << "(3) 2-distance Dominating Set (Guloso Randomizado Reativo)" << endl;
        cout << "(4) Experimento para todas as heuristicas" << endl;
        cout << "(5) Experimento para todas as heuristicas, uma unica vez." << endl;
        cout << "(0) Voltar ao Menu" << endl;
        cin >> resp;

        switch (resp)
        {
            case '1':
            {
                vector<char> resultado = grafo->ds_2_greedy();
                cout << "Conjunto Dominante a 2-distancia (Guloso): ";
                for (size_t i = 0; i < resultado.size(); ++i)
                {
                    cout << resultado[i] << (i == resultado.size() - 1 ? "" : ", ");
                }
                cout << endl
                     << endl;
    
                if (pergunta_imprimir_arquivo("ds_2_greedy.txt"))
                {
                    ofstream outFile("ds_2_greedy.txt");
                    if (outFile.is_open())
                    {
                        outFile << "Conjunto Dominante a 2-distancia (Guloso): ";
                        for (size_t i = 0; i < resultado.size(); ++i)
                        {
                            outFile << resultado[i] << (i == resultado.size() - 1 ? "" : ", ");
                        }
                        outFile << endl;
                        outFile.close();
                        cout << "Resultado salvo em ds_2_greedy.txt" << endl;
                    }
                    else
                    {
                        cout << "Erro ao abrir o arquivo para escrita." << endl;
                    }
                }
                break;
            }
            case '2':
            {
                int max_iter;
                float alpha;
                unsigned int seed;
    
                cout << "Digite o numero maximo de iteracoes: ";
                cin >> max_iter;
                cout << "Digite o valor de alfa (entre 0 e 1): ";
                cin >> alpha;
                cout << "Digite a seed (0 se quiser seed aleatoria): ";
                cin >> seed;
    
                vector<char> resultado = grafo->ds_2_randomized_greedy(max_iter, alpha, seed);
                cout << "Conjunto Dominante a 2-distancia (Randomizado): ";
                for (size_t i = 0; i < resultado.size(); ++i)
                {
                    cout << resultado[i] << (i == resultado.size() - 1 ? "" : ", ");
                }
                cout << endl
                     << endl;
    
                if (pergunta_imprimir_arquivo("ds_2_randomized_greedy.txt"))
                {
                    ofstream outFile("ds_2_randomized_greedy.txt");
                    if (outFile.is_open())
                    {
                        outFile << "Conjunto Dominante a 2-distancia (Randomizado): ";
                        for (size_t i = 0; i < resultado.size(); ++i)
                        {
                            outFile << resultado[i] << (i == resultado.size() - 1 ? "" : ", ");
                        }
                        outFile << endl;
                        outFile.close();
                        cout << "Resultado salvo em ds_2_randomized_greedy.txt" << endl;
                    }
                    else
                    {
                        cout << "Erro ao abrir o arquivo para escrita." << endl;
                    }
                }
                break;
            }
            case '3':
            {
                int numIter;
                int bloco;
                int numAlfas;
                unsigned int seed;
    
                cout << "Digite o numero maximo de iteracoes: ";
                cin >> numIter;
                cout << "Digite o tamanho do bloco: ";
                cin >> bloco;
                cout << "Digite a seed (0 se quiser seed aleatoria): ";
                cin >> seed;
                cout << "Digite o numero de alfas a serem testados: ";
                cin >> numAlfas;
    
                vector<float> alfaVet(numAlfas);
                cout << "Digite os " << numAlfas << " valores de alfa (entre 0 e 1):" << endl;
                for (int i = 0; i < numAlfas; ++i) {
                    cout << "Alfa " << i + 1 << ": ";
                    cin >> alfaVet[i];
                }
    
                vector<char> resultado = grafo->ds_2_reactive_randomized_greedy(alfaVet, numIter, bloco, seed);
                cout << "Conjunto Dominante a 2-distancia (Reativo): ";
                for (size_t i = 0; i < resultado.size(); ++i)
                {
                    cout << resultado[i] << (i == resultado.size() - 1 ? "" : ", ");
                }
                cout << endl
                     << endl;
                if (pergunta_imprimir_arquivo("ds_2_reactive_randomized_greedy.txt"))
                {
                    ofstream outFile("ds_2_reactive_randomized_greedy.txt");
                    if (outFile.is_open())
                    {
                        outFile << "Conjunto Dominante a 2-distancia (Reativo): ";
                        for (size_t i = 0; i < resultado.size(); ++i)
                        {
                            outFile << resultado[i] << (i == resultado.size() - 1 ? "" : ", ");
                        }
                        outFile << endl;
                        outFile.close();
                        cout << "Resultado salvo em ds_2_reactive_randomized_greedy.txt" << endl;
                    }
                    else
                    {
                        cout << "Erro ao abrir o arquivo para escrita." << endl;
                    }
                }
                break;
            }
        case '4':
        {
            run_all_heuristics(grafo, instanceName);
            break;
        }
        case '5':
        {
            run_all_heuristics_one_time(grafo, instanceName);
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

void Gerenciador::run_all_heuristics(Grafo *grafo, const string &instanceName)
{

    // --- Algoritmo Guloso ---
    cout << "Executando o algoritmo guloso 30 vezes..." << endl;
    string greedy_filename = "resultados/" + instanceName + "_greedy_all_runs.txt";
    ofstream greedy_outFile(greedy_filename);
    streambuf *coutbuf = cout.rdbuf(); // Salva o buffer antigo

    for (int i = 0; i < 30; ++i)
    {
        cout.rdbuf(greedy_outFile.rdbuf()); // Redireciona o cout para o arquivo

        greedy_outFile << "--- Execucao " << i + 1 << " ---" << endl;
        unsigned int seed = time(0) + i;
        srand(seed);
        greedy_outFile << "Seed: " << seed << endl;

        vector<char> resultado = grafo->ds_2_greedy();
        greedy_outFile << "Conjunto Dominante a 2-distancia (Guloso): ";
        for (size_t j = 0; j < resultado.size(); ++j)
        {
            greedy_outFile << resultado[j] << (j == resultado.size() - 1 ? "" : ", ");
        }
        greedy_outFile << endl;
        greedy_outFile << "---------------------------\n"
                       << endl;
    }
    cout.rdbuf(coutbuf); // Restaura o cout
    greedy_outFile.close();
    cout << "Resultados do Guloso salvos em: " << greedy_filename << endl;

    // --- Algoritmo Guloso Randomizado ---
    vector<float> alphas = {0.3, 0.6, 0.9};
    cout << "Executando o algoritmo guloso randomizado 30 vezes para cada alfa..." << endl;
    string randomized_filename = "resultados/" + instanceName + "_randomized_all_runs.txt";
    ofstream randomized_outFile(randomized_filename);

    for (float alpha : alphas)
    {
        for (int i = 0; i < 30; ++i)
        {
            cout.rdbuf(randomized_outFile.rdbuf());

            randomized_outFile << "--- Execucao " << i + 1 << " para o alpha " << alpha << " ---" << endl;
            unsigned int seed = time(0) + 30 + (int)(alpha * 100);
            srand(seed);
            randomized_outFile << "Seed: " << seed << endl;
            randomized_outFile << "Alpha: " << alpha << endl;

            vector<char> resultado = grafo->ds_2_randomized_greedy(150, alpha, seed);
            randomized_outFile << "Conjunto Dominante a 2-distancia (Randomizado): ";
            for (size_t j = 0; j < resultado.size(); ++j)
            {
                randomized_outFile << resultado[j] << (j == resultado.size() - 1 ? "" : ", ");
            }
            randomized_outFile << endl;
            randomized_outFile << "--------------------------------------------------\n"
                               << endl;
        }
    }
    cout.rdbuf(coutbuf);
    randomized_outFile.close();
    cout << "Resultados do Guloso Randomizado salvos em: " << randomized_filename << endl;

    // --- Algoritmo Guloso Randomizado Reativo ---
    cout << "Executando o algoritmo guloso randomizado reativo 30 vezes..." << endl;
    string reactive_filename = "resultados/" + instanceName + "_reactive_all_runs.txt";
    ofstream reactive_outFile(reactive_filename);
    for (int i = 0; i < 30; ++i)
    {
        cout.rdbuf(reactive_outFile.rdbuf());

        reactive_outFile << "--- Execucao " << i + 1 << " ---" << endl;
        unsigned int seed = time(0) + 30 + 1000;
        srand(seed);
        reactive_outFile << "Seed: " << seed << endl;
        vector<float> reactive_alphas = {0.3, 0.6, 0.9};

        vector<char> resultado = grafo->ds_2_reactive_randomized_greedy(reactive_alphas, 150, 30, seed);
        reactive_outFile << "Conjunto Dominante a 2-distancia (Reativo): ";
        for (size_t j = 0; j < resultado.size(); ++j)
        {
            reactive_outFile << resultado[j] << (j == resultado.size() - 1 ? "" : ", ");
        }
        reactive_outFile << endl;
        reactive_outFile << "---------------------------\n"
                         << endl;
    }
    cout.rdbuf(coutbuf);
    reactive_outFile.close();
    cout << "Resultados do Guloso Reativo salvos em: " << reactive_filename << endl;

    cout << "\nTodas as heuristicas foram executadas. Os resultados estao na pasta 'resultados'." << endl;
}

void Gerenciador::run_all_heuristics_one_time(Grafo *grafo, const string &instanceName)
{

    // --- Algoritmo Guloso ---
    cout << "Executando o algoritmo guloso 1 vez..." << endl;
    string greedy_filename = "resultados/" + instanceName + "_greedy_all_runs.txt";
    ofstream greedy_outFile(greedy_filename);
    streambuf *coutbuf = cout.rdbuf(); // Salva o buffer antigo

    for (int i = 0; i < 1; ++i)
    {
        cout.rdbuf(greedy_outFile.rdbuf()); // Redireciona o cout para o arquivo

        greedy_outFile << "--- Execucao " << i + 1 << " ---" << endl;
        unsigned int seed = time(0) + i;
        srand(seed);
        greedy_outFile << "Seed: " << seed << endl;

        vector<char> resultado = grafo->ds_2_greedy();
        greedy_outFile << "Conjunto Dominante a 2-distancia (Guloso): ";
        for (size_t j = 0; j < resultado.size(); ++j)
        {
            greedy_outFile << resultado[j] << (j == resultado.size() - 1 ? "" : ", ");
        }
        greedy_outFile << endl;
        greedy_outFile << "---------------------------\n"
                       << endl;
    }
    cout.rdbuf(coutbuf); // Restaura o cout
    greedy_outFile.close();
    cout << "Resultados do Guloso salvos em: " << greedy_filename << endl;

    // --- Algoritmo Guloso Randomizado ---
    vector<float> alphas = {0.3, 0.6, 0.9};
    cout << "Executando o algoritmo guloso randomizado 1 vez para cada alfa..." << endl;
    string randomized_filename = "resultados/" + instanceName + "_randomized_all_runs.txt";
    ofstream randomized_outFile(randomized_filename);

    for (float alpha : alphas)
    {
        for (int i = 0; i < 1; ++i)
        {
            cout.rdbuf(randomized_outFile.rdbuf());

            randomized_outFile << "--- Execucao " << i + 1 << " para o alpha " << alpha << " ---" << endl;
            unsigned int seed = time(0) + 30 + (int)(alpha * 100);
            srand(seed);
            randomized_outFile << "Seed: " << seed << endl;
            randomized_outFile << "Alpha: " << alpha << endl;

            vector<char> resultado = grafo->ds_2_randomized_greedy(150, alpha, seed);
            randomized_outFile << "Conjunto Dominante a 2-distancia (Randomizado): ";
            for (size_t j = 0; j < resultado.size(); ++j)
            {
                randomized_outFile << resultado[j] << (j == resultado.size() - 1 ? "" : ", ");
            }
            randomized_outFile << endl;
            randomized_outFile << "--------------------------------------------------\n"
                               << endl;
        }
    }
    cout.rdbuf(coutbuf);
    randomized_outFile.close();
    cout << "Resultados do Guloso Randomizado salvos em: " << randomized_filename << endl;

    // --- Algoritmo Guloso Randomizado Reativo ---
    cout << "Executando o algoritmo guloso randomizado reativo 1 vez..." << endl;
    string reactive_filename = "resultados/" + instanceName + "_reactive_all_runs.txt";
    ofstream reactive_outFile(reactive_filename);
    for (int i = 0; i < 1; ++i)
    {
        cout.rdbuf(reactive_outFile.rdbuf());

        reactive_outFile << "--- Execucao " << i + 1 << " ---" << endl;
        unsigned int seed = time(0) + 30 + 1000;
        srand(seed);
        reactive_outFile << "Seed: " << seed << endl;
        vector<float> reactive_alphas = {0.3, 0.6, 0.9};

        vector<char> resultado = grafo->ds_2_reactive_randomized_greedy(reactive_alphas, 150, 30, seed);
        reactive_outFile << "Conjunto Dominante a 2-distancia (Reativo): ";
        for (size_t j = 0; j < resultado.size(); ++j)
        {
            reactive_outFile << resultado[j] << (j == resultado.size() - 1 ? "" : ", ");
        }
        reactive_outFile << endl;
        reactive_outFile << "---------------------------\n"
                         << endl;
    }
    cout.rdbuf(coutbuf);
    reactive_outFile.close();
    cout << "Resultados do Guloso Reativo salvos em: " << reactive_filename << endl;

    cout << "\nTodas as heuristicas foram executadas. Os resultados estao na pasta 'resultados'." << endl;
}

char Gerenciador::get_id_entrada()
{
    cout << "Digite o id de um no: ";
    char id;
    cin >> id;
    cout << endl;
    return id;
}

vector<char> Gerenciador::get_conjunto_ids(Grafo *grafo, int tam)
{
    vector<char> ids = {};
    while ((int)ids.size() < tam)
    {
        char id_no = get_id_entrada();
        bool existe = false;
        for (No *no : grafo->lista_adj)
        {
            if (no->id == id_no)
            {
                existe = true;
                break;
            }
        }

        if (!existe)
        {
            cout << "Vertice nao existe" << endl;
        }
        else
        {
            bool repetido = find(ids.begin(), ids.end(), id_no) != ids.end();
            if (repetido)
            {
                cout << "Valor repetido" << endl;
            }
            else
            {
                ids.push_back(id_no);
            }
        }
    }

    return ids;
}

bool Gerenciador::pergunta_imprimir_arquivo(string nome_arquivo)
{

    cout << "Imprimir em arquivo externo? (" << nome_arquivo << ")" << endl;
    cout << "(1) Sim;" << endl;
    cout << "(2) Nao." << endl;
    int resp;
    cin >> resp;
    cout << endl;

    switch (resp)
    {
    case 1:
        return true;
    case 2:
        return false;
    default:
        cout << "Resposta invalida" << endl;
        return pergunta_imprimir_arquivo(nome_arquivo);
    }
}