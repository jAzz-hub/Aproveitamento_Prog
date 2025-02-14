#include "CLIENTE.h"

// Verifica se o nome é válido (exemplo simples: verifica se não está vazio)
bool cliente::VerificarNome(string nome)
{
    if (nome.empty())
    {
        cerr << "Erro: Nome inválido!" << endl;
        return false;
    }
    return true;
}

// // Verifica se o CPF é válido (exemplo simples: verifica se tem 11 dígitos)
// bool cliente::VerificarCPF(long cpf)
// {
//     if (cpf < 10000000000 || cpf > 99999999999)
//     {
//         cerr << "Erro: CPF inválido!" << endl;
//         return false;
//     }
//     return true;
// }

