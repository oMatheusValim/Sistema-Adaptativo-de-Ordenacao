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
- **Selection Sort** 

### O(n log n)
- **Merge Sort**
- **Heap Sort** 

### Alternativo
- **Counting Sort** *(algoritmo não-comparativo, linear para inteiros com amplitude reduzida)*

> ℹ️ A justificativa detalhada para a escolha de cada algoritmo, bem como as heurísticas de seleção, está disponível no relatório do projeto.

---

## Estrutura do Projeto

```
.
├── apps/
│   └── main.c                  # Ponto de entrada e parsing de argumentos 
├── include/
│   ├── adaptive.h              # Lógica do sistema adaptativo
│   ├── algoritmos.h 
│   ├── entry_analysis.h
│   ├── execution_analysis.h
│   └── input_generator.h       # Coleta de métricas de execução
├── src/
│   ├── adaptive.c
│   ├── algoritmos.c
│   ├── entry_analysis.c
│   ├── execution_analysis.c
│   ├── input_generator.c
│   └── io.c     
├── report/                     # Relatório em PDF
├── entrada.csv
├── instruções.pdf              # Instruções para a realização do projeto
├── Makefile
├── README.md
└── resultados.csv
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

Para deixar o seu `README.md` perfeitamente alinhado com a ferramenta profissional de linha de comando (CLI) que acabamos de construir, o ideal é padronizar o nome do executável (`./bin/run.exe`), adicionar os exemplos com as novas *flags* (como `--verbose` e `--tipo`) e listar todos os parâmetros disponíveis de forma clara.

Aqui está o formato ideal que você pode copiar e colar direto no seu `README.md`:

## Execução

O sistema foi construído para ser executado via linha de comando (CLI), permitindo alta flexibilidade na escolha de entradas, geração de dados e exportação de métricas.

O executável gerado pelo `make` fica na pasta `bin`. Para rodar, utilize:

### 1. Modo Adaptativo (Árvore de Decisão)

Lendo um lote de dados de um arquivo CSV existente:
```bash
./bin/run.exe --modo adaptativo --input entrada.csv --verbose

```

Gerando um vetor de tamanho específico na hora:

```bash
./bin/run.exe --modo adaptativo --tamanho 50000 --tipo quase_ordenado --verbose

```

### 2. Modo Fixo (Algoritmo Específico)

Testando um algoritmo com geração de dados aleatórios ou específicos:

```bash
./bin/run.exe --algoritmo insertion --tamanho 100000 --tipo reverso --verbose
./bin/run.exe --algoritmo heap --tamanho 50000 --tipo aleatorio --seed 99

```

Lendo um lote de dados e forçando um único algoritmo para todas as linhas:

```bash
./bin/run.exe --algoritmo merge --input entrada.csv --output resultados.csv

```

## Parâmetros Disponíveis

O sistema exige que você forneça **ou** um arquivo de entrada (`--input`) **ou** um tamanho para gerar os dados (`--tamanho`).

| Parâmetro | Descrição | Valores Aceitos / Exemplos |
| --- | --- | --- |
| `--modo adaptativo` | Ativa a árvore de decisão para escolher o melhor algoritmo automaticamente. | (Uso isolado) |
| `--algoritmo <nome>` | Força a execução de um algoritmo específico de ordenação. | `quick`, `merge`, `heap`, `selection`, `insertion`, `counting` |
| `--tamanho <n>` | Gera um array dinamicamente com `n` elementos. | Ex: `10000`, `50000` |
| `--input <arquivo>` | Lê lotes de dados a partir de um arquivo de texto/csv. | Ex: `entrada.csv` |
| `--tipo <tipo>` | Define a distribuição matemática dos dados gerados pelo `--tamanho`. | `aleatorio`, `quase_ordenado`, `reverso`, `repetidos` |
| `--seed <valor>` | Define a semente de aleatoriedade para reprodutibilidade dos testes. | Ex: `42`, `99` (Padrão: 42) |
| `--output <arquivo>` | Redireciona as métricas (algoritmo usado, tamanho, tempo) para um CSV. | Ex: `resultados.csv` |
| `--verbose` | Habilita a exibição detalhada de logs e métricas no terminal. | (Uso isolado) |

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

| Característica detectada | Algoritmo escolhido | Motivo |
|---|---|---|
| Entrada pequena e **quase ordenada** | Insertion Sort | O(n) no melhor caso; overhead mínimo |
| Entrada pequena com **custo de escrita alto** (poucas trocas desejadas) | Selection Sort | Faz **exatamente n−1 trocas**, independente da entrada |
| Entrada com **muitos valores repetidos** ou que exige **estabilidade** | Merge Sort | Estável; lida bem com duplicatas |
| Inteiros com **amplitude pequena** (range ≤ fator de n) | Counting Sort | O(n + k), linear quando k é pequeno |
| Entrada **grande e aleatória** / quando pior caso importa | Heap Sort | O(n log n) garantido, in-place |


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

[![Assista ao Vídeo](https://img.youtube.com)](https://youtu.be)

> Caso o vídeo acima não carregue, você pode assistir [diretamente no YouTube](https://youtu.be) ou baixar via [Google Drive](https://drive.google.com).

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