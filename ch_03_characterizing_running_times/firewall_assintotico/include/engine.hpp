#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "transaction.hpp"
#include <vector>
#include <string>

class ReconciliationEngine {
public:
    virtual ~ReconciliationEngine() {}
    // Retorna IDs que estão em A mas não em B (Órfãs)
    virtual std::vector<std::string> reconcile(
        const std::vector<Transaction>& ledger, 
        const std::vector<Transaction>& network
    ) = 0;
};

// DECLARE AS FILHAS AQUI PARA O COMPILADOR CONHECÊ-LAS
class NaiveEngine : public ReconciliationEngine {
public:
    std::vector<std::string> reconcile(
        const std::vector<Transaction>& ledger, 
        const std::vector<Transaction>& network) override;
};

class FastEngine : public ReconciliationEngine {
public:
    std::vector<std::string> reconcile(
        const std::vector<Transaction>& ledger, 
        const std::vector<Transaction>& network) override;
};

#endif




