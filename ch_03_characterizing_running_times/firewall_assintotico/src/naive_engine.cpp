#include "../include/engine.hpp"

std::vector<std::string> NaiveEngine::reconcile(
    const std::vector<Transaction>& ledger, 
    const std::vector<Transaction>& network) 
{
    // 1. Crie o container de retorno (orphans) 
    std::vector<std::string> orphans;
    // 2. Implemente o loop aninhado (O "para cada item em A, varre B") 
    int ledge_size = ledger.size();
    int network_size = network.size();

    bool found;

    for (int i = 0; i < ledge_size; i++) {
        found = false;
        for (int j = 0; j < network_size; j++) {
            if (ledger[i].id == network[j].id) {
                found = true;
                break;
            } 
        }
        if (!found) {
            orphans.push_back(ledger[i].id);
        }
    }
    // 3. Retorne o container
    return orphans;
}

