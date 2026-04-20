#include "../include/engine.hpp"

// Dica de Arquiteto: Você pode criar funções de ajuda (como o merge) 
// aqui em cima antes da função principal.

void merge(std::vector<Transaction>& A, int p, int q, int r) {
    int nL = q - p + 1;
    int nR = r - q;

    std::vector<Transaction> L(nL);
    std::vector<Transaction> R(nR);

    for (int i = 0; i < nL; i++) { L[i] = A[p + i]; }
    for (int j = 0; j < nR; j++) { R[j] = A[q + j + 1]; }

    int i = 0, j = 0, k = p;
    
    while (i < nL && j < nR) {
        if (L[i].id <= R[j].id) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        } 
        k++;
    }

    while (i < nL) {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < nR) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Transaction>& A, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

std::vector<std::string> FastEngine::reconcile(
    const std::vector<Transaction>& ledger, 
    const std::vector<Transaction>& network) 
{
    // 1. Ordene os dados (Merge Sort manual) [cite: 4, 98]
    std::vector<Transaction> s_ledger = ledger;
    std::vector<Transaction> s_network = network;

    mergeSort(s_ledger, 0, s_ledger.size() - 1);
    mergeSort(s_network, 0, s_network.size() - 1);

    // 2. Implemente a lógica de busca eficiente (Zíper/Dois ponteiros)
    std::vector<std::string> orphans;
    size_t i = 0, j = 0;

    while (i < s_ledger.size() && j < s_network.size()) {
        if (s_ledger[i].id == s_network[j].id) {
            i++; j++;
        } else if (s_ledger[i].id < s_network[j].id) {
            orphans.push_back(s_ledger[i].id);
            i++;
        } else {
            j++;
        }
    }

    while (i < s_ledger.size()) {
        orphans.push_back(s_ledger[i].id);
        i++;
    }

    // 3. Retorne os órfãos
    return orphans;
}
