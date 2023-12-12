#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cine{
    char Nome[20];
    int sala; 
    int hora;
    int min;
    int lotacao;
    int LOTMAX;
    struct cine *proxno;
} NO;

typedef struct cliente{
    char nome[20];
    struct cine *ingresso;
} USU;

NO *primeiro_no = NULL;
USU *primeiro_cliente = NULL;

void cadastra_cliente(USU *c, char *nome) {
    strcpy(c->nome, nome);
}



void adiciona_filme(NO **p, char nome[20], int sala, int hora, int min){
    NO *aux, *p1 = malloc(sizeof(NO));

    if (p1) {
        //p1->Nome = nome; Em C, você não pode atribuir diretamente um array a outro. Você precisa copiar cada elemento individualmente.
        strcpy(p1->Nome, nome);
        p1->sala = sala;
        p1->hora = hora;
        p1->min = min;
        p1->LOTMAX = 50;
        p1->lotacao = 0;
        p1->proxno = NULL;
        printf("|   Inclusao bem sucedida!   | \n");
        if (*p == NULL) {
            *p = p1; 
        } 
        else {
            aux = *p;
            while(aux->proxno){
                aux = aux->proxno;
            }
            aux->proxno = p1;
        }   
    } else {
        printf("| Erro ao alocar memoria! |");
    }
}

void remove_filme(NO **p, char nome[20], int sala){
    NO *aux = *p;
    NO *prev = NULL;

    // Procura o filme na lista
    while (aux != NULL) {
        if (strcmp(aux->Nome, nome) == 0 && aux->sala == sala) {
            break;
        }
        prev = aux;
        aux = aux->proxno;
    }

    // Se o filme não foi encontrado
    if (aux == NULL) {
        printf("Filme não encontrado!\n");
        return;
    }

    // Se o filme é o primeiro da lista
    if (prev == NULL) {
        *p = aux->proxno;
        free(aux); // Libera a memória alocada para o nó removido
    } else {
        prev->proxno = aux->proxno;
        free(aux); // Libera a memória alocada para o nó removido
    }
    free(aux);
    printf("Filme removido com sucesso!\n");

}


void lista_salas(NO *p) {   
            printf(" ____________________________\n");
            printf("|         Cine SyStem        |\n");
            printf("|----------------------------|\n");
            printf("|          Catalogo          |\n");
            printf("|____________________________|\n");
    while (p != NULL) {

        if (p->sala != NULL) {

            printf("| %s\n | Sala: %d | Sessao: %d:%d\n| Lotacao (%d/%d)\n",p->Nome,p->sala,p->hora,p->min, p->lotacao, p->LOTMAX);
            printf("_____________________________\n");
        }
        p = p->proxno;
    }
}

void lista_filmes ( NO *p ) {
        printf(" ____________________________\n");
        printf("|         Cine SyStem        |\n");
        printf("|----------------------------|\n");
        printf("|          Catalogo          |\n");
        printf("|____________________________|\n");
    while (p != NULL) {
        
        if (p->sala != NULL) {
        
        printf("|-%s          \n", p->Nome);
        printf("|____________________________\n");
        }
        p = p->proxno;
    } 
}

void compra_ingresso(NO **p, char nome[20], int sala) {
    NO *aux = *p;

    while (aux != NULL) {
        if (strcmp(aux->Nome, nome) == 0 && aux->sala == sala) {
            if (aux->lotacao < aux->LOTMAX) {
                primeiro_cliente->ingresso = aux;
                printf("Ingresso associado ao cliente\n"); // Mensagem de depuração
                aux->lotacao++;
                imprimir_ingresso(primeiro_cliente);
            } else {
                printf("Desculpe, a sala para %s está lotada!\n", aux->Nome);
            }
            return;
        }
        aux = aux->proxno;
    }

    printf("Sessao nao encontrada!\n");
}

void imprimir_ingresso(USU *c) {
    printf("Nome: %s\nSala: %d\nHora: %02d:%02d\nLotacao: %d/%d\n", c->ingresso->Nome, c->ingresso->sala, c->ingresso->hora, c->ingresso->min, c->ingresso->lotacao, c->ingresso->LOTMAX);
}
void pause() {
    printf("Pressione Enter para continuar...");
    getchar(); // Aguarda a entrada do usuário
}

void menu_Funcionario(){
        int in;
        char nome[20];
        int sala, hora, min;
    
        do{
            printf(" ____________________________\n");
            printf("| Cine SyStem - Funcionario  |\n");
            printf("|----------------------------|\n");
            printf("| 1 - Adicionar Filme        |\n");
            printf("| 2 - Remover Filme          |\n");
            printf("| 3 - Listar Salas           |\n");
            printf("| 4 - Listar Filmes          |\n");
            printf("| 5 - Sair                   |\n");
            printf("|____________________________|\n");
            scanf("%d", &in);
            getchar();
            switch(in){
                case 1: printf(" ____________________________\n");
                        printf("| Cine SyStem - Funcionario  |\n");
                        printf("|----------------------------|\n");
                        printf("| 1 - Adicionar Filme        |\n");

                        printf("|Filme: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = 0;  
                        printf("|Sala: ");
                        scanf("%d", &sala);
                        getchar();
                        printf("|Hora:");
                        scanf("%d", &hora);
                        getchar();
                        printf("|Minuto:");
                        scanf("%d", &min);
                        getchar();                        
                        adiciona_filme(&primeiro_no,nome,sala,hora,min);
                        pause();
                        break;
                
                case 2: 

                        printf(" ____________________________\n");
                        printf("| Cine SyStem - Funcionario  |\n");
                        printf("|----------------------------|\n");
                        printf("| 2 - Remover Filme          |\n");
                        printf("| Filme: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = 0;  
                        getchar(); // Limpa o buffer do teclado
                        printf("| Sala: ");
                        scanf("%d", &sala);
                        getchar(); // Limpa o buffer do teclado
                        printf("|____________________________|\n");
                        remove_filme(&primeiro_no, nome, sala);
                        pause();
                        break;
               
                case 3: 
                        printf(" ____________________________\n");
                        printf("| Cine SyStem - Funcionario  |\n");
                        printf("|----------------------------|\n");
                        printf("| 3 - Listar Salas           |\n");
                        lista_salas(primeiro_no);
                        pause();
                        break;
                
                case 4: 
                        printf(" ____________________________\n");
                        printf("| Cine SyStem - Funcionario  |\n");
                        printf("|----------------------------|\n");
                        printf("| 4 - Listar Filmes          |\n");
                        lista_filmes(primeiro_no);
                        pause();
                        break;
            }

        } while(in != 5);
        
        
}

void menu_Cliente(){
    int in, sala;
    char nome[20];
    char nome_cliente[20];

    USU *primeiro_cliente = (USU*) malloc(sizeof(USU));
    printf(" _______________________________\n");
    printf("| Nome Cliente:");
    fgets(nome_cliente, sizeof(nome_cliente), stdin);
    strcpy(primeiro_cliente->nome, nome_cliente);
        printf("| Bem vindo(a), %s!", primeiro_cliente->nome);
    do{
        printf(" ____________________________\n");
        printf("|   Cine SyStem - Cliente    |\n");
        printf("|----------------------------|\n");
        printf("| 1 - Comprar Ingressos      |\n");
        printf("| 2 - Comprovante Ingresso   |\n");
        printf("| 3 - Listar Salas           |\n");
        printf("| 4 - Listar Filmes          |\n");
        printf("| 5 - Sair                   |\n");
        printf("|____________________________|\n");
        scanf("%d", &in);
        getchar();
        switch(in){
            case 1:
                printf(" ____________________________\n");
                printf("|   Cine SyStem - Cliente    |\n");
                printf("|----------------------------|\n");
                printf("| 1 - Comprar Ingressos      |\n");
                printf("| Filme:");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;  
                printf("|Sala: ");
                scanf("%d", &sala);
                getchar();
                compra_ingresso(&primeiro_no, nome, sala);
                pause();
                break;
            case 2:
                printf(" ____________________________\n");
                printf("|   Cine SyStem - Cliente    |\n");
                printf("|----------------------------|\n");
                printf("| 2 - Comprovante Ingresso   |\n");
                compra_ingresso(&primeiro_no, nome, sala);
                printf("|____________________________|\n");
                pause();
                break;
            case 3: 
                printf(" __________________________\n");
                printf("| Cine SyStem - Cliente    |\n");
                printf("|--------------------------|\n");
                printf("| 3 - Listar Salas         |\n");
                lista_salas(primeiro_no);
                pause();
                break;
            case 4: 
                printf(" __________________________\n");
                printf("| Cine SyStem - Cliente    |\n");
                printf("|--------------------------|\n");
                printf("| 4 - Listar Filmes        |\n");
                lista_filmes(primeiro_no);
                pause();
                break;
        }

    } while(in != 5);
}

main(){

    primeiro_cliente = (USU*)malloc(sizeof(USU));
    int in;
    do{
    printf(" ____________________\n");
    printf("|    Cine SyStem     |\n");
    printf("|--------------------|\n");
    printf("| 1 - Cliente        |\n");
    printf("| 2 - Funcionario    |\n");
    printf("| 3 - Sair           |\n");
    printf("|____________________|\n");
    scanf("%i", &in);
    getchar();
        switch(in){
            case 1:
                menu_Cliente();
                break;
            case 2:
                menu_Funcionario();
                break;
        }   
    } while(in != 3);
}
