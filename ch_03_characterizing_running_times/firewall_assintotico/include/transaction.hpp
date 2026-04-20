#pragma once  // <-- ISSO É OBRIGATÓRIO
#include <string>

struct Transaction {
    std::string id;       // UUID ou lixo malformado
    double amount;        // Valor da transação
    long timestamp;       // Unix Epoch
    bool is_corrupt;      // Flag para entradas "sujas" do mundo real
};