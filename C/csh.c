#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void logoPrint() {
    printf("crazyshell@ufes:~$ ");
    return;
}

void trata_c(){
     char resposta;
     printf("\n");
     logoPrint();
     printf("Não adianta me enviar um sinal por Ctrl-c, não vou morrer!\n");
     logoPrint();
     printf("Você quer suspender meu filho que está rodando em foreground? S/n: ");
     scanf("%c", &resposta);
     /*  if(resposta == 's' || resposta == 'S' ){

     }
     else if(resposta == 'n' || resposta == "N")*/
     return;
}

void limpa_Tela(){
  if(fork() == 0){
    execlp("clear","clear",NULL);
  }
  return;
}

int tamanhoPalavra(char* aux){
    int i = 0;
    int tam = 1;
    while(aux[i]!='\0'){
        tam++;i++;
    }
    return tam;
}

int main(int argc, char** argv) {
    char entrada[500], comando[50], *token, waitt[] = "wait", exitt[] = "exit";
    char* argvv[6];
    int aux;
    pid_t pai, filho, neto = -1;

    argvv[0] = comando;
    pai = getpid();
    limpa_Tela();
    aux = wait(&aux);

    while (1) {
        if (getpid() == pai) {
            logoPrint();
            fgets(entrada, 500, stdin);

            if (entrada[0] != '\n') {
                token = strtok(entrada, " \n");

                strcpy(comando, token);
                strcpy(argvv[0], token);
                int i = 1;
                while (token != NULL) {
                    token = strtok(NULL, " \n");
                    if (token != NULL) {
                        int tamanho = tamanhoPalavra(token);
                        argvv[i] = (char*)malloc((tamanho+1)*sizeof(char));
                        strcpy(argvv[i], token);
                        i++;
                    }
                }
                for (; i < 6; i++) {
                    argvv[i] = NULL;
                }

                if (strcmp(comando, waitt) == 0) {
                    printf("Tu entrou no wait\n");
                    exit(1);
                }
                if (strcmp(comando, exitt) == 0) {
                    printf("Tu entrou no exit\n");
                    exit(1);
                }
                filho = fork();
            }
        }

        if(getpid() == pai){
          aux = wait(&aux);
        }
        int a = 1;

        if (filho == 0) {
            neto = fork();
            if(neto == 0){
              daemon(0,0);
            }

            a = execvp(comando, argvv);
            if (a < 0){
                a = 1;
                a = execv(comando, argvv);
                if(a < 0){
                    printf("Opa isso não existe. Tente novamente...\n");
                    exit(1);
                }
            }
        }

        if(pai == getpid()){
            for(aux=1;aux<6;aux++){
              free(argvv[aux]);
            }
        }
    }
    return (EXIT_SUCCESS);
}
