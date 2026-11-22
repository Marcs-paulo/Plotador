# Plotador — gráficos de funções com Qt

Projeto da disciplina **Programação Avançada** do Departamento de Engenharia de Computação e Automação (DCA) da **UFRN**, com o professor Adelardo Adelino Dantas de Medeiros.

A disciplina teve três projetos práticos, um por unidade:

| Unidade | Projeto | Assunto principal |
| :-- | :-- | :-- |
| 1 | [BigInt](https://github.com/Marcs-paulo/BigInt) | classes, ponteiros e memória dinâmica |
| 2 | [Planejador](https://github.com/Marcs-paulo/Planejador) | exceções, arquivos e STL (algoritmo A*) |
| 3 | **Plotador** (este) | interface gráfica com Qt |

## O que é

Um programa de janela, feito com **Qt 6 e C++**, que desenha o gráfico de uma ou mais funções digitadas pelo usuário (por exemplo `sin(x)` ou `x^2-3`), cada uma com sua cor.

- O menu **Plotagem → Função...** abre uma janela para digitar a função e escolher a cor.
- A tabela ao lado lista as funções que estão no gráfico.
- Os campos **Min**, **Max** e **Exp** mudam os limites dos eixos X e Y (o valor mostrado é multiplicado por 10 elevado a Exp).
- O gráfico se redesenha quando a janela muda de tamanho.
- Clicar num ponto do gráfico mostra as coordenadas (x, y) daquele ponto na barra de status.

## Foco do projeto e o que buscamos aprender

- **Montar uma interface no Qt Designer**: `QMainWindow`, `QFrame`, `QTableWidget`, `QSpinBox`, menus e layouts que se ajustam quando a janela é redimensionada.
- **Sinais e slots**: os slots automáticos do Designer ("Go to slot...") e um sinal próprio (`signIncluirFuncao`) que leva a função digitada da janela de diálogo para a janela principal.
- **Janela de diálogo** (`QDialog`) separada da janela principal, para ler a função e a cor.
- **Desenhar** o gráfico num `QPixmap` exibido num `QLabel`, convertendo coordenadas da função (x, y) para pixels da tela e vice-versa.
- **Herdar de uma classe do Qt e tratar eventos**: a classe `Grafico` herda de `QLabel` e reimplementa o clique do mouse; a janela principal reimplementa o evento de redimensionamento.
- **Usar uma classe pronta sem modificá-la**: a `Evaluator`, fornecida pelo professor, que interpreta e calcula a expressão digitada.

## O que foi pedido

O enunciado completo está em [`docs/plotador-especificacao.pdf`](docs/plotador-especificacao.pdf). Ele descreve passo a passo a interface que deveria ser construída (nomes, tamanhos e propriedades de cada widget) e a lógica de cada parte:

- janela principal `MainPlotador` de 850×600, com a área do gráfico à esquerda e o painel de controle à direita;
- classe de diálogo `LehFuncao` para digitar a função e escolher a cor;
- slots para o menu, para os limites dos eixos e para o botão **APAGAR**;
- funções de conversão de unidades e de desenho do gráfico;
- redimensionamento automático e a classe `Grafico` para mostrar as coordenadas do clique.

## Como compilar e rodar

Precisa do **Qt 6** (testado com o Qt 6.12, kit `gcc_64`).

Pelo **Qt Creator**: abra `Plotador.pro`, escolha o kit e clique em executar.

Pelo terminal (troque o caminho pelo da sua instalação do Qt):

```bash
mkdir build && cd build
~/Qt/6.12.0/gcc_64/bin/qmake ../Plotador.pro
make
./Plotador
```

## Arquivos

| Arquivo | Origem |
| :-- | :-- |
| `mainplotador.*` | janela principal, implementada por mim |
| `lehfuncao.*` | janela de diálogo para ler a função, implementada por mim |
| `grafico.*` | `QLabel` que reage ao clique, implementado por mim |
| `evaluator.h`, `evaluator.cpp` | classe que calcula a expressão, fornecida pelo professor (sem alterações) |
| `main.cpp`, `Plotador.pro` | ponto de entrada e projeto do Qt |
| `docs/plotador-especificacao.pdf` | enunciado do projeto |
