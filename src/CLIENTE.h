#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm> 
#include <cctype>
#include <vector>

using namespace std;

struct cliente
{
    string Nome;
    long long int cpf;
    uint32_t Prioridade;
    uint32_t itens;
    struct cliente* next;

    // Construtor
    cliente(string nome, long long int cpf, uint32_t prioridade, uint32_t itens)
        : Nome(nome), cpf(cpf), Prioridade(prioridade), itens(itens), next(nullptr)
    {
        VerificarNome(nome);
        // VerificarCPF(cpf);
    }

    // Funções
    bool VerificarNome(string nome);
    // bool VerificarCPF(long cpf);


};

#endif