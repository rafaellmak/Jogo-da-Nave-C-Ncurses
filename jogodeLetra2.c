#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define MAX_WIDTH 80
#define MAX_HEIGHT 24
#define NUM_LETRAS 5
#define DELAY_INICIAL 80
#define PONTUACAO_MAXIMA 1000

typedef struct {
    int x, y;
} Ponto;

typedef struct {
    Ponto posicao;
    char letra;
} Jogador;

typedef struct {
    Ponto posicao;
    char letra;
} Letra;

typedef struct {
    Ponto posicao;
    int ativo;
} Tiro;

void desenha(Jogador jogador, Letra letras[], Tiro tiros[]) {
    clear();
    mvaddch(jogador.posicao.y, jogador.posicao.x, jogador.letra);

    for (int i = 0; i < NUM_LETRAS; i++) {
        mvaddch(letras[i].posicao.y, letras[i].posicao.x, letras[i].letra);
    }

    for (int i = 0; i < NUM_LETRAS; i++) { 
        if (tiros[i].ativo) {
            mvaddch(tiros[i].posicao.y, tiros[i].posicao.x, '|');
        }
    }
}

int kbhit(void) {
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void Sleep(int ms) {
    usleep(ms * 1000);
}

void desenhaMensagem(const char *mensagem, int y, int x) {
    const char *letrasDisponiveis = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int len = strlen(mensagem);

    for (int i = 0; i < len; i++) {
        int letraIndex = rand() % strlen(letrasDisponiveis);
        mvaddch(y, x + i, letrasDisponiveis[letraIndex]);
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    Jogador jogador = { {MAX_WIDTH / 2, MAX_HEIGHT - 1}, '^' };
    Letra letras[NUM_LETRAS];
    Tiro tiros[NUM_LETRAS];
    int pontuacao = 0;
    int delay = DELAY_INICIAL;

    for (int i = 0; i < NUM_LETRAS; i++) {
        letras[i].posicao.x = rand() % MAX_WIDTH;
        letras[i].posicao.y = 0;
        letras[i].letra = 'a' + (rand() % 26);
        tiros[i].ativo = 0; 
    }

    while (pontuacao < PONTUACAO_MAXIMA) {
        desenha(jogador, letras, tiros); 
        mvprintw(0, 0, "Pontuacao: %d", pontuacao);

        if (kbhit()) {
            char tecla = getch();
            if (tecla == 'a' && jogador.posicao.x > 0) jogador.posicao.x--;
            if (tecla == 'd' && jogador.posicao.x < MAX_WIDTH - 1) jogador.posicao.x++;
            if (tecla == 'q') break;
            if (tecla == ' ') { 
                for (int i = 0; i < NUM_LETRAS; i++) {
                    if (!tiros[i].ativo) { 
                        tiros[i].posicao = jogador.posicao; 
                        tiros[i].ativo = 1; 
                        break; 
                    }
                }
            }
        }

        // Move as letras
        for (int i = 0; i < NUM_LETRAS; i++) {
            letras[i].posicao.y++;

            if (letras[i].posicao.y > MAX_HEIGHT) {
                letras[i].posicao.x = rand() % MAX_WIDTH;
                letras[i].posicao.y = 0;
                letras[i].letra = 'a' + (rand() % 26);
            }
        }
        
        // Move os tiros
        for (int i = 0; i < NUM_LETRAS; i++) {
            if (tiros[i].ativo) {
                tiros[i].posicao.y--;
                if (tiros[i].posicao.y < 0) {
                    tiros[i].ativo = 0; 
                }
            }
        }

        // Verifica colisões
        for (int i = 0; i < NUM_LETRAS; i++) {
            if (letras[i].posicao.x == jogador.posicao.x && letras[i].posicao.y == jogador.posicao.y) {
                clear();
                desenhaMensagem("GAME OVER", MAX_HEIGHT / 2 - 2, MAX_WIDTH / 2 - 6);
                mvprintw(MAX_HEIGHT / 2 + 1, MAX_WIDTH / 2 - 7, "Pontuacao final: %d", pontuacao);
                getch();
                endwin();
                return 0;
            }

            // Verifica colisão entre tiros e letras
            for (int j = 0; j < NUM_LETRAS; j++) {
                if (tiros[j].ativo && letras[i].posicao.x == tiros[j].posicao.x && letras[i].posicao.y == tiros[j].posicao.y) {
                    letras[i].posicao.x = rand() % MAX_WIDTH;
                    letras[i].posicao.y = 0;
                    letras[i].letra = 'a' + (rand() % 26);
                    tiros[j].ativo = 0;
                    pontuacao += 10; 
                    break; 
                }
            }
        }

        pontuacao++;

        if (pontuacao % 100 == 0 && delay > 10) { 
            delay -= 10; 
        }

        Sleep(delay);
    }

    clear();
    desenhaMensagem("CHAMPION", MAX_HEIGHT / 2 - 2, MAX_WIDTH / 2 - 7);
    mvprintw(MAX_HEIGHT / 2 + 1, MAX_WIDTH / 2 - 7, "Pontuacao final: %d", pontuacao);
    getch();

    endwin();
    return 0;
}
