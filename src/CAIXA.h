#ifndef CAIXA_H
#define CAIXA_H

#include "CLIENTE.h"

using namespace std;
struct caixa
{
    cliente* filaClientes; // Ponteiro para o primeiro cliente na fila
    uint32_t ID;
    // status indica se o caixa se encontra aberto ou fechado;
    string status; 
    int n_clientes = 0;

    // Construtor
    caixa(uint32_t id, string status, int n_clientes) : filaClientes(nullptr), ID(id), status(status), n_clientes(n_clientes){}
    void ClienteEntrandoNaFilaDoCaixa(cliente *novoCliente);
    bool FilaVazia() const;
    cliente* RemoverClienteDaFrente();
    void FecharCaixa(uint32_t id, vector<caixa>& caixas);
    void VisualizarFilas(const vector<caixa>& caixas) const;
    void VisualizarFila() const;

};

#endif