import random, csv, sys

def generate_logs(n):
    # Simula a "Barreira do n" [cite: 1, 4]
    ids = [f"TXN-{i:08d}" for i in range(n)]
    
    def write_ledger(filename, dataset):
        with open(filename, 'w') as f:
            writer = csv.writer(f)
            for tx_id in dataset:
                # Ruído: 5% de chance de ID malformado ou lixo
                record = tx_id if random.random() > 0.05 else "CORRUPT_DATA_#@!"
                writer.writerow([record, round(random.uniform(10, 1000), 2)])

    # Gera conjuntos com intersecção parcial para reconciliação
    sample_a = random.sample(ids, int(n * 0.95))
    sample_b = random.sample(ids, int(n * 0.95))
    
    write_ledger('data/bank_ledger.csv', sample_a)
    write_ledger('data/card_network.csv', sample_b)

if __name__ == "__main__":
    generate_logs(int(sys.argv[1]))