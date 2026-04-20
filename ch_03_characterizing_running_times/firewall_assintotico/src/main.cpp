#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono> // Para telemetria de alta precisão
#include "../include/engine.hpp"
#include "../include/transaction.hpp"


// Função auxiliar para carregar o "Pântano de Dados" (CSV) para a Memória
std::vector<Transaction> load_csv(const std::string& filename) {
    std::vector<Transaction> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, amount_str;
        
        if (std::getline(ss, id, ',') && std::getline(ss, amount_str, ',')) {
            // Criando a struct baseada no contrato definido em transaction.hpp
            Transaction tx;
            tx.id = id;
            tx.amount = std::stod(amount_str);
            tx.is_corrupt = (id == "CORRUPT_DATA_#@!");
            data.push_back(tx);
        }
    }
    return data;
}

int main() {
    std::cout << "--- Carregando Dados dos Logs ---" << std::endl;
    auto ledger = load_csv("data/bank_ledger.csv");
    auto network = load_csv("data/card_network.csv");
    
    std::cout << "Ledger: " << ledger.size() << " | Network: " << network.size() << std::endl;

    NaiveEngine naive;
    FastEngine fast;

    // --- Benchmark: Motor Naive Theta(n^2) ---
    std::cout << "\n--- Executando Motor Naive (Quadrático) ---" << std::endl;
    auto s1 = std::chrono::high_resolution_clock::now();
    std::vector<std::string> o_naive = naive.reconcile(ledger, network);
    auto e1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d1 = e1 - s1;
    std::cout << "Tempo Naive: " << d1.count() << "s | Órfãos: " << o_naive.size() << std::endl;

    // --- Benchmark: Motor Fast Theta(n lg n) ---
    std::cout << "\n--- Executando Motor Fast (Log-Linear) ---" << std::endl;
    auto s2 = std::chrono::high_resolution_clock::now();
    std::vector<std::string> o_fast = fast.reconcile(ledger, network);
    auto e2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d2 = e2 - s2;
    std::cout << "Tempo Fast: " << d2.count() << "s | Órfãos: " << o_fast.size() << std::endl;

    return 0;
}