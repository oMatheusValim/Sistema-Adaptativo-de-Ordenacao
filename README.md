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

Este projeto implementa um **sistema adaptativo de ordenação** em linguagem C. Em vez de aplicar sempre o mesmo algoritmo, o sistema analisa características da entrada — tamanho, grau de desordem e amplitude — e seleciona automaticamente o algoritmo de ordenação mais adequado para aquele cenário.

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
```
## Estrutura do Projeto
├── docs/
│   ├── relatório.pdf           # Relatório técnico do trabalho
│   └── instruções.pdf          # Instruções para a realização do projeto
|
├── experiments/
│   ├── datasets/               # Entradas geradas para os experimentos
|   |   └── entrada.csv
│   ├── config.txt
│   └── run_all.sh              # Script de execução automatizada
|
├── results/                    # Saída dos experimentos
│   ├── resultados.txt
│   └── valgrind_report.txt
|
├── src/
│   ├── headers/
│   ├── utils/
│   │   ├── headers/
│   │   ├── config.c
│   │   ├── input_generator.c   # Gerador de entradas para experimentos
│   │   ├── io.c                # Leitura/escrita de arquivos
│   │   └── utils.c
|   |   
│   ├── adaptive.c              # Lógica do sistema adaptativo
│   ├── algoritmos.c            # Algoritmos de ordanação
│   ├── entry_analysis.c        # Análise de características da entrada
│   ├── main.c                  # Ponto de entrada e parsing de argumentos
│   └── method_compare.c        # Prepara o vetor para ser ordenado por vaŕios algoritmos de sorting
|
├── .gitignore
├── Makefile
└── README.md
```

---

## Compilação e execução

### Pré-requisitos

- GCC (versão 11 ou superior recomendada)
- Make
- Sistema operacional: Linux ou macOS *(scripts `.sh`)*
- Valgrind (opcional)

### Compilar

Caso não queira usar o Valgrind, o comando de compilação é ```make```

Caso queira usar o Valgrind, o comando de compilação é ```make val```

Obs: Uma vez que o Valgrind intercepta cada etapa da execução com o intuito de achar vazamentos de memória, além de outros erros, **a execução com ele é muito mais lenta do que sem**. Entretanto, para um projeto desse vigor, que aloca muito memória dinamicamente, o seu uso foi essencial ao longo do desenvolvimento do código para se assegurar o correto tratamento da pilha de memória, e recomendamos ao usuário que o utilize para também se certificar que o progama roda sem vazar memória e sem gerar erros que muitas vezes passam despercebidos ao utilizar apenas o gcc.

### Limpar

```bash
make clean
```

---

## Executar

O sistema possui um arquivo texto de configuração ([experiments/config.txt](experiments/config.txt)) que simula um .env. Nele, estão contidos os parâmetros de execução padrão. Se o usuário providenciar, por linha de comando, qualquer um dos parâmetros dispostos no config na hora de executar, o sistema **sempre dará preferência para o que estiver definido na linha de comando** antes de utilizar os valores default do config.

Para mudar vários parâmetros a cada execução, recomenda-se que o usuário modifique o config.txt para incluir as suas preferências e assim evitar um comando de execução muito longo. Para mudar poucos parâmetros por execução, os comandos de linha tendem a ser mais práticos.

### Resumo dos parâmetros disponíveis

| Parâmetro | Descrição |
|-----------|-----------|
| `<método>=<bool>` | Ativa (bool=1) ou desativa (bool=0) um método de ordenação (`A`, `C`, `H`, `I`, `M`, `S`) específico|
| `QUANT=<n>` | `n` vetores devem ser ordenados ao longo da execução |
| `MAX_SIZE=<n>` | Cada vetor pode ter ate `n` elementos |
| `MAX_NUM=<n>` | Todos os números presentes nos vetores serão menor ou iguais a `n` |
| `NEGATIVE=<n>` | `n` a cada 100 dos vetores terão números negativos |
| `ADV=<n>` | `n` a cada 100 dos vetores serão casos adversariais|
| `SRT=<n>` | `n` a cada 100 dos vetores já estarão ordenados |
| `R_SRT=<n>` | `n` a cada 100 dos vetores estarão ordenados de maneira decresente |
| `EQUAL=<n>` | `n` a cada 100 dos vetores serão preenchidos com o mesmo número |
| `VERBOSE=<bool>` | Ativa (`bool`=1) ou desativa (`bool`=0) os prints no terminal que caracterizam a execução |
| `OUT_TXT=<bool>` | Ativa (`bool`=1) ou desativa (`bool`=0) o arquivo txt de resultados no fim da execução |

Observação: todos os exemplos à frente de como usar as linhas de comando usam o `make run`, que não utiliza o Valgrind, para rodar o executável. Se o usuário compilar com o Valgrind, da maneira que foi descrita acima, use o comando `make run_val` para incluir o relatório do Valgrind na saída.

### Parâmetros de escolha de algoritmo

Há 6 maneiras de se ordenar os vetores de entrada usando o nosso algoritmo:
- Usar o sistema adaptativo (A), que irá escolher qual o melhor algoritmo de sorting a depender do vetor de entrada
- Usar sempre o Counting Sort (C)
- Usar sempre o Heap Sort (H)
- Usar sempre o Insertion Sort (I)
- Usar sempre o Merge Sort (M)
- Usar sempre o Selection Sort (S)

O usuário pode escolher quais destes ele quer utilizar simultâneamente para comparar as suas respectivas eficiências. Para selecionar as opções de algoritmo que ele deseja usar, use o comando de linha ```X=1``` onde X representa um algoritmo que o usuário queira incluir na execução, ou ```Y=0```, onde Y representa um algoritmo que o usuário queira excluir da execução. Exemplos de utilização:

```bash
# Usar o sistema adaptativo apenas
make run A=1 C=0 H=0 I=0 M=0 S=0

# Usar o sistema adaptativo, o counting e o insertion apenas
make run A=1 C=1 H=0 I=1 M=0 S=0

# Usar todos os os métodos
make run A=1 C=1 H=1 I=1 M=1 S=1

# Usar o heap e o insertion apenas
make run A=0 C=0 H=1 I=1 M=0 S=0

# Usar o sistema adaptativo, não usar o counting e o merge, a utilização dos outros irá depender do config
make run A=1 C=0 M=0

```

Observações:
- Pelo menos 1 método deve ser escolhido, seja pela linha de comando ou pelo config. **O caso ```make run A=0 C=0 H=0 I=0 M=0 S=0``` irá retornar um warning pro usuário**.

### Parâmetros de entrada de vetores

O nosso sistema adaptativo possui um módulo ([src/utils/input_generator.c](src/utils/input_generator.c)) capaz de gerar aleatoriamente os vetores a serem ordenados. Para controlar melhor estes vetores, é possível definir os seguintes parâmetros por linha de comando:

```bash
# Ordenar 300 vetores aleatórios, que podem ter até 4000 números inteiros, os quais que podem assumir qualquer valor de 0 a 5000
make run QUANT=300 MAX_SIZE=4000 MAX_NUM=5000

# 11% dos vetores irão conter números negativos
make run NEGATIVE=11

# Pelo menos 36% dos vetores serão casos adversariais, 7% estarão em ordem crescente, 9% estaram em ordem decrescente e 4% serão preenchidos inteiramente com o mesmo número
make run ADV=36 SRT=7 R_SRT=9 EQUAL=4
```

A cada execução, o conjunto de vetores utilizados é salvo na pasta experiments/datasets/ em um arquivo csv. Para reutilizar os vetores de uma execução passada, é necessário passar o nome do csv gerado naquela execução (```make run CSV_FILE=entradaX.csv```). 

Observações:
- Se tanto o CSV_FILE quanto os parâmetros de geração de entrada (QUANT, MAX_SIZE, MAX_NUM ...) estiverem definidos, o sistema sempre dá preferência para o CSV_FILE, e não irá gerar um novo conjunto de vetores;

- Se qualquer valor do trio (QUANT, MAX_SIZE, MAX_NUM) e o também CSV_FILE estiverem ausentes da linha de comando e do config, o sistema usará o arquivo padrão entrada.csv;

- Se algum dos valores (ADV, SRT, R_SRT, EQUAL, NEGATIVE) não for definido ou for inválido (menor que 0, ou maior que 100), o sistema irá considerar ele como zero;

- Se a soma ADV + SRT + R_SRT + EQUAL for maior do que 100, o sistema usará o padrão ADV=30, SRT=5, R_SRT=5, EQUAL=5.

### Parâmetros de logging

Para acompanhar a execução do programa, tão bem quantos os seus resultados, é possível definir 2 parâmetros: `VERBOSE` e `OUT_TXT`:

```bash
# Dar prints no terminal ao longo da execução para acompanhar em qual etapa o programa está
make run VERBOSE=1

# Dar gerar o arquivo resultados(time).txt para resumir as metricas dos algoritmos
make run OUT_TXT=1
```


## Métricas Coletadas

Para cada ordenação, o sistema registra:

- Tempo de execução
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
| Entrada com **amplitude pequena** (amp ≤ n) | Counting Sort | Complexidade de tempo O(n + k), linear quando k é pequeno |
| Entrada de **tamanho pequeno com alta desordem**| Selection Sort | Complexidade de tempo O(n^2) o torna lento demais para entradas maiores e o grau de desordem não impacta a sua execução|
| Entrada de **tamanho pequeno e média-baixa desordem** | Insertion Sort | Complexidade de tempo O(n^2) o torna lento demais para entradas maiores, mas ele aproveita quando a desordem não é tão alta|
| Entrada de **tamanho grande** | Heap Sort | Complexidade de espaço fixa O(1)|
| Entrada **com alta desordem** | Heap Sort | O grau de desordem não impacta a sua execução |
| Entrada de **tamanho médio com média desordem** | Merge Sort | O caso base que aproveita quando o vetor já está um pouco ordenado, e não tão grande |


> ℹ️ Os limiares exatos e a justificativa experimental para cada regra estão detalhados no relatório.

---

## Experimentos

Para reproduzir todos os experimentos automaticamente:

```bash
cd experiments/
chmod +x run_all.sh
bash run_all.sh
```

O script irá:
1. Escrever o config.txt de maneira padrão
2. Compilar o projeto (sem Valgrind)
3. Executar o programa
4. Salvar os resultados em `results/`

### Tipos de entrada testados

- Aleatória
- Ordenada
- Reversamente ordenada
- Todos elementos repetidos
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
