#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
 *
 */
void logoPrint() {
    printf("crazyshell@ufes:~$ ");
    return;
}

int main(int argc, char** argv) {
    char entrada[500], comando[50], *token;
    char p1[20] = "", p2[20] = "", p3[20] = "", p4[20] = "", p5[20] = "";
    char* argvv[6] = {comando, p1, p2, p3, p4, p5};
    char waitt[] = "wait", exitt[] = "exit";
    int aux;
    pid_t pai, filho, neto = -1;

    pai = getpid();

    if(fork() == 0){
    	execlp("clear","clear",NULL);
    }
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
                        strcpy(argvv[i], token);
                        i++;
                    }
                }
                for (; i < 6; i++) {
                    argvv[i] = NULL;
                }

                if (strcmp(comando, waitt) == 0) {
                    //ainda faz nada
                    exit(1);
                }
                if (strcmp(comando, exitt) == 0) {
                    //ainda faz nada
                    exit(1);
                }
                filho = fork();
            }
        }

        if(getpid() == pai){
          aux = wait(&aux);
        }

        if (filho == 0) {
            //neto = fork();
            int a = execvp(comando, argvv);
            if (a < 0)return 0;
        }
        if(neto == 0){
          daemon(0,0);
          int a = execvp(comando, argvv);
          if (a < 0)return 0;
        }
    }
    return (EXIT_SUCCESS);
}
