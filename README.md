# Sistema Adaptativo de Ordenação

> **SCC0606 – Estruturas de Dados II**  
> Prof. Dr. Renato Moraes Silva — ICMC/USP

---

## Integrantes

| Nome | Nº USP |
|------|--------|
| *Arthur Silva de Albuquerque* | *17078155* |
| *Cecília Luis de Queiroz* | *16817870* |
| *Julia Vitoriano Silva e Silva* | *16879240* |
| *Matheus Valim Nogueira* | *15746323* |
| *Thaís Batista da Paixão* | *17015724* |
| *Thaís Rodrigues Lindquist* | *16813796* |


---

## Descrição do Projeto

Este projeto implementa um **sistema adaptativo de ordenação** em linguagem C. Em vez de aplicar sempre o mesmo algoritmo, o sistema analisa características da entrada — como tamanho, grau de desordem, presença de duplicatas e distribuição dos valores — e seleciona automaticamente o algoritmo de ordenação mais adequado para aquele cenário.

O objetivo central não é apenas implementar os algoritmos, mas investigar seu comportamento experimental, construir heurísticas de seleção bem justificadas e avaliar criticamente as decisões do sistema.

---

## Algoritmos Implementados

### O(n²)
- **Insertion Sort**
- **Selection Sort** *(ou Bubble Sort — a definir)*

### O(n log n)
- **Merge Sort**
- **Quick Sort** *(ou Heap Sort — a definir)*

### Alternativo
- **Counting Sort** *(algoritmo não-comparativo, linear para inteiros com amplitude reduzida)*

> ℹ️ A justificativa detalhada para a escolha de cada algoritmo, bem como as heurísticas de seleção, está disponível no relatório do projeto.

---

## Estrutura do Projeto

```
.
├── src/
│   ├── main.c                  # Ponto de entrada e parsing de argumentos
│   ├── adaptive.c / .h         # Lógica do sistema adaptativo
│   ├── characterizer.c / .h    # Análise de características da entrada
│   ├── metrics.c / .h          # Coleta de métricas de execução
│   ├── algorithms/
│   │   ├── insertion_sort.c
│   │   ├── selection_sort.c
│   │   ├── merge_sort.c
│   │   ├── quick_sort.c
│   │   └── counting_sort.c
│   └── utils/
│       ├── input_generator.c   # Gerador de entradas para experimentos
│       └── io.c                # Leitura/escrita de arquivos
├── experiments/
│   ├── run_all.sh              # Script de execução automatizada
│   └── datasets/               # Entradas geradas para os experimentos
├── results/                    # Saída dos experimentos (CSVs, logs)
├── report/                     # Relatório em PDF
├── Makefile
└── README.md
```

---

## Compilação

### Pré-requisitos

- GCC (versão 11 ou superior recomendada)
- Make
- Sistema operacional: Linux ou macOS *(scripts `.sh`)*

### Compilar

```bash
make
```

O executável será gerado como `./programa`.

### Limpar

```bash
make clean
```

---

## Execução

O sistema aceita parâmetros por linha de comando.

### Modo adaptativo com arquivo de entrada

```bash
./programa --modo adaptativo --input dados.txt
```

### Modo fixo (algoritmo específico)

```bash
./programa --algoritmo quick --tamanho 10000
./programa --algoritmo merge --input dados.txt
./programa --algoritmo heap  --tamanho 50000
```

### Parâmetros disponíveis

| Parâmetro | Descrição |
|-----------|-----------|
| `--modo adaptativo` | Ativa o sistema adaptativo |
| `--algoritmo <nome>` | Força um algoritmo específico (`insertion`, `selection`, `merge`, `quick`, `counting`) |
| `--tamanho <n>` | Gera uma entrada aleatória de tamanho `n` |
| `--input <arquivo>` | Lê a entrada a partir de um arquivo |
| `--tipo <tipo>` | Define o tipo da entrada gerada: `aleatorio`, `quase_ordenado`, `reverso`, `repetidos` |
| `--seed <valor>` | Define a semente para reprodutibilidade |
| `--output <arquivo>` | Redireciona as métricas para um arquivo CSV |
| `--verbose` | Exibe métricas detalhadas no terminal |

---

## Métricas Coletadas

Para cada execução, o sistema registra:

- Tempo de execução (em milissegundos)
- Número de comparações
- Número de trocas/movimentações
- Profundidade máxima de recursão
- Número de chamadas recursivas
- Uso estimado de memória auxiliar

---

## Heurísticas Adaptativas

O sistema classifica a entrada e escolhe o algoritmo com base nas seguintes regras:

| Característica detectada | Algoritmo escolhido |
|--------------------------|---------------------|
| Entrada pequena (n ≤ ?) | Insertion Sort |
| Entrada quase ordenada | Insertion Sort |
| Muitos valores repetidos | Merge Sort |
| Inteiros com amplitude pequena | Counting Sort |
| Entrada grande e aleatória | Quick Sort / Heap Sort |

> ℹ️ Os limiares exatos e a justificativa experimental para cada regra estão detalhados no relatório.

---

## Experimentos

Para reproduzir todos os experimentos automaticamente:

```bash
cd experiments/
chmod +x run_all.sh
./run_all.sh
```

O script irá:
1. Compilar o projeto
2. Gerar as entradas de teste (aleatória, quase ordenada, reversa, repetidos, adversarial)
3. Executar o sistema adaptativo e os algoritmos fixos de referência
4. Salvar os resultados em `results/`

### Tipos de entrada testados

- Aleatória
- Quase ordenada
- Reversamente ordenada
- Muitos elementos repetidos
- Entradas pequenas e grandes
- **Entradas adversariais** (casos que exploram limitações do sistema adaptativo)

---

## Vídeo de Apresentação

> 🎬 Link: *(a ser adicionado)*

---

## Relatório

O relatório completo em PDF está disponível em `report/relatorio.pdf` e contém:

- Introdução e descrição do sistema
- Arquitetura e heurísticas
- Metodologia experimental
- Resultados com gráficos e análise crítica
- Reflexão sobre uso de ferramentas de IA
- Conclusões

---

## Observações

- É permitido o uso de trechos de código disponibilizados pelo professor no e-Disciplinas.
- Qualquer uso de ferramentas de IA está devidamente documentado na seção de reflexão do relatório.
- Todos os experimentos podem ser reproduzidos integralmente com os scripts fornecidos e a seed documentada.