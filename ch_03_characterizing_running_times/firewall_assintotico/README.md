### 📄 LAB: Firewall Assintótico

#### 1. OVERVIEW
> O objetivo deste projeto foi demonstrar a superioridade prática da eficiência assintótica ao substituir um motor de reconciliação $\Theta(n^2)$ por um algoritmo de Divisão e Conquista $\Theta(n \lg n)$, resultando em uma redução de tempo de **31.6s** para **0.18s** para $n=95.000$.

#### 2. TECHNICAL CONTEXT
* **Core Concept:** Eficiência Assintótica, Divisão e Conquista (Merge Sort), e técnica de Dois Ponteiros (Zíper).
* **Tools Used:** C++ (GCC 11), Docker, Python 3 (gerador de massa), e Notação Assintótica ($\Theta, O, \Omega$).

#### 3. DEBUGGING & LEARNING
* **Issue:** Otimização agressiva do compilador (`-O3`) removendo a execução das funções por "dead code" e erros de limites de índices ($p, q, r$) na recursão do Merge Sort.
* **Solution:** Forçamos o uso do retorno das funções com `std::cout` e isolamos a lógica de fusão em uma função `merge` separada da lógica recursiva `mergeSort`.
* **Technical Learning:** Entendi que constantes multiplicativas são irrelevantes quando $n$ cresce o suficiente e que a correta definição de limites em algoritmos recursivos é crucial para evitar *Stack Overflow*.

#### 4. HOW TO REPRODUCE
1. `docker build -t firewall-lab .`
2. `docker run -it --name asymptotic_chamber firewall-lab`
3. `python3 scripts/generator.py 100000 && g++ -O3 -I./include src/*.cpp -o lab && ./lab`

---

## 🛡️ Documentação de Engenharia (Cenário fictício)

### 1. O Cenário de Trincheira
Nossa fintech sofria com um delay crítico. Para identificar transações órfãs (presentes em um log mas não no outro), o sistema original varria a lista inteira para cada item encontrado, uma abordagem puramente quadrática que não escalava para o volume real de mercado.

### 2. Arquitetura do Sistema
O projeto foi estruturado para isolar a lógica de comparação:
* `NaiveEngine`: Implementação de força bruta com loops aninhados ($\Theta(n^2)$).
* `FastEngine`: Implementação otimizada usando **Merge Sort** manual e busca por **Zíper** ($\Theta(n \lg n)$).

### 3. Resultados Obtidos (Benchmark)
| $n$ (Transações) | Motor Naive ($\Theta(n^2)$) | Motor Fast ($\Theta(n \lg n)$) | Speedup |
| :--- | :--- | :--- | :--- |
| 95.000 | 31.61 s | 0.18 s | ~175x |

### 4. Configuração do Ambiente Docker
Para garantir que o hardware não mascare a eficiência algorítmica, utilizamos um ambiente isolado:

**Dockerfile:**
```dockerfile
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y g++ python3 make
WORKDIR /app
COPY . .
CMD ["/bin/bash"]
```

**Comandos de Operação:**
```bash
# Subir o laboratório
docker compose up -d

# Entrar na câmara de vácuo assintótico
docker exec -it asymptotic_chamber bash

# Gerar massa de dados (100k registros)
python3 scripts/generator.py 100000

# Compilar e Rodar o Lab
g++ -O3 -I./include src/main.cpp src/naive_engine.cpp src/fast_engine.cpp -o reconciliation_lab
./reconciliation_lab
```

---

### 🔬 Check-point Acadêmico (Vereditos)

1.  **Diferenciação de Limites:** Sim, posso afirmar que o Motor Fast é $O(n^3)$. Tecnicamente, a Notação $O$ é um limite superior não estrito. Se algo cresce a $n \lg n$, ele também cresce **no máximo** a $n^3$. É uma afirmação correta, porém pouco informativa (pobre em termos de *tight bound*).
2.  **O Teorema da Unificação:** De acordo com o **Teorema 3.1**, se o algoritmo é $O(n \lg n)$ (limite superior) e $\Omega(n \lg n)$ (limite inferior), então ele é **estritamente** $\Theta(n \lg n)$.
3.  **Transitividade:** Pela transitividade, se a triagem é $O(n)$ e a reconciliação é $O(n \lg n)$, o sistema total é $O(n + n \lg n) = O(n \lg n)$. O termo de maior ordem sempre domina a taxa de crescimento.

---
