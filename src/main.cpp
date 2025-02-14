#include<vector>
#include "CAIXA.h"

#define NUM_CAIXAS 4




bool CaixaAberto(uint32_t ID, vector<caixa> caixas)
{

    if(ID >= 0 || ID > NUM_CAIXAS)
    {
        if(caixas[ID].status == "aberto")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void FecharCaixa(uint32_t id, vector<caixa>& caixas)
{
    // Verifica se ha outros caixas abertos
    bool outrosCaixasAbertos = false;
    for (const auto& c : caixas)
    {
        if (c.status == "aberto" && c.ID != id)
        {
            outrosCaixasAbertos = true;
            break;
        }
    }

    if (!outrosCaixasAbertos)
    {
        cout << "Nao é possível fechar o caixa " << id << " afinal nao ha outros caixas abertos!" << endl;
        return; // Nao fecha se nao houver outros caixas abertos
    }

    // Transfere os clientes para o próximo caixa aberto
    for (auto& c : caixas)
    {
        if (c.status == "aberto" && c.ID != id)
        {
            cliente* atual = caixas[id].filaClientes;
            while (atual)
            {
                cliente* proximo = atual->next;
                c.ClienteEntrandoNaFilaDoCaixa(atual);
                atual = proximo;
            }
            break;
        }
    }

    // Fecha o caixa
    caixas[id].filaClientes = nullptr;
    caixas[id].status = "fechado";
}

void AbrirCaixa(vector <caixa>& caixas, uint32_t id)
{
    caixas.emplace_back(caixa(id, "aberto", 0));
}

void VisualizarFilas(const vector<caixa>& caixas)
{
    // caixas.front().next = nullptr;
    for (const auto& c : caixas)
    {
        cout << "Caixa ID " << c.ID << " - Estado: " << c.status << " - Numero de clientes em espera: ";
        cout << c.n_clientes << endl;
    }
}

void AbrirOuFecharCaixa(vector<caixa> caixas, int id)
{
    int request = 0;
    while(request!=3)
    {    
        int request;
        cout<<"\n\nDeseja abrir ou fechar um caixa?\n";
        cout<<"[1] -  abrir\n";
        cout<<"[2] - fechar\n";
        cout<<"[3] - sair\n";
        cin>>request;

        switch(request)
        {
            case 1:
            {
                if (CaixaAberto(id, caixas))
                {
                    cout<<"O caixa" << id << "ja esta aberto";    
                    return;
                }
                else
                    AbrirCaixa(caixas, id);
                
                break;
            }
            case 2:
            {
                if (!CaixaAberto(id, caixas))
                {
                    cout<<"O caixa" << id << "ja esta fechado";    
                    return;
                }
                else
                    FecharCaixa(id, caixas);
                break;
            }
            case 3:
            {
                printf("Saindo do menu de abertura e fechamento de caixas !\n\n\n");
                return;
            }
        }
    }
}


void limparTela()
{
    #ifdef _WIN32
        system("cls"); // Limpa a tela no Windows
    #else
        system("clear"); // Limpa a tela no Linux/Mac
    #endif
}

vector<caixa> abrindoCaixas(int numOfCaixas)
{
    vector <caixa> caixas;
    for(int i = 0; i<=numOfCaixas; i++)
    {
        caixas.emplace_back(caixa(i, "aberto", 0));
        caixas[i].ID = i;
        caixas[i].status = "aberto";
        caixas[i].n_clientes = 0;
    }        

    return caixas;
}



bool cpf_valido(const string& cpf)
{
    if (cpf.length() != 11)
    {
        cout << "TAMANHO DE CPF INVaLIDO!!" << endl;
        return false;
    }
    for (char c : cpf)
    {
        if (!isdigit(c))
        {
            cout << "INSIRA APENAS DIGITOS NUMÉRICOS PARA O SEU CPF!" << endl;
            return false;
        }
    }
    return true;
}

int main()
{

    vector<caixa> caixas;
    
    caixas = abrindoCaixas(NUM_CAIXAS);

    int op = 7;
    // setlocale(LC_ALL, "Portuguese");
    while (op != 0){
        
        cout << "\n=== MENU ===\n";
        cout << "1. Cadastrar Cliente\n";
        cout << "2. Atender Cliente\n";
        cout << "3. Abrir/Fechar Caixa\n";
        cout << "4. Imprimir Lista de Clientes em Espera\n";
        cout << "5. Imprimir Status dos Caixas\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> op;
        if(cin.fail())
        {
            cout<<"Para selecionar uma opcao do menu considere que apenas NuMEROS SaO VaLIDOS!";
            cout<<"REINICIE O PROGRAMA!";
            break;
        }

        switch (op){
        case 1:
        {
            string nome, cpf_str;
            long long int cpf;
            uint32_t Prioridade, itens, caixa_id;
            
            
            cout<<"ATENcaO: No cpf devem ser inseridos apenas numeros!! NaO INSIRA LETRAS"<<endl;
            cout<<"Digite seu cpf aqui:";
            cin>>cpf_str;
            
            if(!cpf_valido(cpf_str))
            {
                cout<<"\n\n~\t\t~~ERRO DE CADASTRO~~\n\n";
                break;
            }
            else
            {
                cpf = stoll(cpf_str);
                cout << "Digite o nome do cliente: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite a prioridade (1-Alta, 2-Media, 3-Baixa): ";
                cin >> Prioridade;
                cout << "Digite o numero de itens no carrinho: ";
                cin >> itens;
                cout << "Digite o ID do caixa (1-" << caixas.size() << "): ";
                cin >> caixa_id;

                cout<<CaixaAberto(caixa_id, caixas);

                if( CaixaAberto(caixa_id, caixas) )
                {
                    cliente Cliente = cliente(nome, cpf, Prioridade, itens);
                    caixas[caixa_id].ClienteEntrandoNaFilaDoCaixa(&Cliente);
                }
            } 
            break;
        }
        case 2:
        {
            uint32_t caixa_id_atendimento;
            cout<<"Escolha o ID do caixa onde deve haver um atendimento";
            cin >> caixa_id_atendimento;
            if(CaixaAberto(caixa_id_atendimento, caixas))
            {
                if(caixas[caixa_id_atendimento].FilaVazia())
                    cout<<"Nao é possível atender nenhum cliente, afinal a fila de clientes do caixa " << caixa_id_atendimento << "esta vazia";
                else
                {
                    cliente removido = *caixas[caixa_id_atendimento].RemoverClienteDaFrente();
                    cout<<"+1 Cliente satisfeito,"<< removido.Nome << "tinha prioridade: " << removido.Prioridade << " e foi atendido!";
                }
            }
            break;
        }
        case 3:{
            int caixa_id_request;
            cout<<"Escolha o ID do que você gostaria de abrir ou fechar";
            cin >> caixa_id_request;
            if(cin.fail())
            {
                cout<<"O id escolhido é representado apenas numeros!! NaO INSIRA LETRAS";
                cout<<"REINICIE O CADASTRO";
                break;
            }
            AbrirOuFecharCaixa(caixas, caixa_id_request);
            break;}
        case 4:{
            for (const auto& c : caixas) {
                cout << "Caixa ID: " << c.ID << endl;
                if (c.FilaVazia()) {
                    cout << "  Fila vazia" << endl;
                } else {
                    cliente* atual = c.filaClientes;
                    while (atual!=nullptr) {
                        cout << "  Cliente: " << atual->Nome << " - PRIORIDADE: " << atual->Prioridade << endl;
                        atual = atual->next;
                    }
                }
            }
            break;}
        case 5:{
            VisualizarFilas(caixas);
            break;}
        case 6:{
            // listar_livros();
            break;}
        case 7:{
            printf("Saindo . . . !\n\n\n");
            return 0;}
        }
        printf("\nTecle !");
        // getc();
    }
    return 0;
}
