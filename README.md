# Jogo-da-Nave-C-Ncurses
Um jogo clássico da nave implementado em C usando a biblioteca ncurses para interface de texto. O objetivo é desviar das letras que caem e acumular pontos, com a dificuldade aumentando gradualmente.
# Jogo da Nave em C com ncurses

Este é um jogo simples da nave implementado em C, utilizando a biblioteca ncurses para criar uma interface de texto no terminal.

## Como Jogar

* Use as teclas A e D para mover a nave para a esquerda e direita.
* Use a barra de espaço para atirar nas letras que caem.
* Evite ser atingido pelas letras.
* A cada 100 pontos, a velocidade das letras aumenta.
* O jogo termina quando você atingir 1000 pontos ou for atingido por uma letra.

## Compilação

1. Certifique-se de ter a biblioteca ncurses instalada:
   ```bash
   sudo apt-get install libncurses5-dev libncursesw5-dev
   
   gcc -o jogoLetra jogodeLetra.c -lncurses

   ./jogoLetra

Contribuições
Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novas funcionalidades. Basta abrir um pull request!

Autor
rafaellmak

