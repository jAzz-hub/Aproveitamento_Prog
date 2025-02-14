#include "CAIXA.h"


void caixa::ClienteEntrandoNaFilaDoCaixa(cliente* novoCliente)
{
    if (!novoCliente) return; // Verifica se o cliente é válido

    this->n_clientes++;
    // Se a fila estiver vazia, insere no início
    if (!filaClientes)
    {
        filaClientes = novoCliente;
        novoCliente->next = nullptr; // Ensure the new client is the last in the queue
        return;
    }

    cliente* atual = filaClientes;

    // Se o novo cliente tem prioridade maior que o primeiro, insere no início
    if (novoCliente->Prioridade > atual->Prioridade)
    {
        novoCliente->next = atual;
        filaClientes = novoCliente;
        return;
    }

    // Percorre a fila até encontrar a posição correta
    while (atual->next && atual->next->Prioridade >= novoCliente->Prioridade)
    {
        atual = atual->next;
    }

    // Insere o novo cliente na posição correta
    novoCliente->next = atual->next;
    atual->next = novoCliente;
    novoCliente->next = nullptr; // Ensure the new client is the last in the queue
}

bool caixa::FilaVazia() const {
    return filaClientes == nullptr;
}

cliente* caixa::RemoverClienteDaFrente()
{
    if (FilaVazia()) return nullptr; // Verifica se a fila está vazia

    cliente* clienteRemovido = filaClientes;
    filaClientes = filaClientes->next;
    clienteRemovido->next = nullptr; // Desconecta o cliente removido da fila

    this->n_clientes--;

    if(this->n_clientes < 1) this->n_clientes = 0;
    
    return clienteRemovido;
}



void caixa::FecharCaixa(uint32_t id, vector<caixa>& caixas)
{
    // Verifica se há outros caixas abertos
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
        cout<<"Não é possível fechar o caixa" << id << "afinal não há outros caixas abertos!"<<endl;
        return; // Não fecha se não houver outros caixas abertos
    }

    // Transfere os clientes para o próximo caixa aberto
    for (auto& c : caixas)
    {
        if (c.status == "aberto" && c.ID != id)
        {
            cliente* atual = filaClientes;
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
    filaClientes = nullptr;
    status = "fechado";
}



void caixa::VisualizarFila() const {
    cout << "Caixa ID: " << ID << endl;
    cliente* atual = this->filaClientes;
    if (!atual)
    {
        cout << "  Fila vazia" << endl;
    } 
    else
    {
        while (atual != nullptr)
        {
            cout << "  Cliente: " << atual->Nome << "PRIORIDADE:"<< atual->Prioridade <<endl;
            atual = atual->next;
        }
    }
}
