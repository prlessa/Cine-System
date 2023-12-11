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
        printf("| Inclusao bem sucedida! | \n");
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
    } else {
        prev->proxno = aux->proxno;
    }

    free(aux);
    printf("Filme removido com sucesso!\n");
}

void lista_salas(NO *p) {
    while (p != NULL) {
        if (p->sala != NULL) {
        printf("_____________________________\n");
        printf("  %s\n Sala: %d | Sessao: %d:%d\n Lotacao (%d/%d)\n",p->Nome,p->sala,p->hora,p->min, p->lotacao, p->LOTMAX);
        printf("_____________________________\n");
        }
        p = p->proxno;
    }
}

void lista_filmes ( NO *p ) {
        printf(" CATALOGO DE FILMES \n");
        printf("____________________\n");
    while (p != NULL) {
        
        if (p->sala != NULL) {
        
        printf("|-%s          \n", p->Nome);
        printf("____________________\n");
        }

        p = p->proxno;
    } 
}

void compra_ingresso(NO **p, char nome[20], int sala){
    NO *aux = *p;

    while(aux != NULL){
        if (encontra_sessao(aux,strcmp(aux->Nome, nome), sala)){
        primeiro_cliente->ingresso = aux;
        } else {
                aux = aux->proxno;
            }
    }
}
/*int compra_ingresso(NO *p, USU *c, char nome[20], int sala){
    NO *aux = malloc(sizeof(NO));
    aux = p;
    if (aux == NULL){
        return 0;
    } else {
        while (aux != NULL) {
            if (strcmp(aux->Nome, nome) == 0 && aux->sala == sala){
                c->ingresso = aux;
               // aux->lotacao += 1;
            } else{
                aux = aux->proxno;
            }
        }
    }
    return 0;
}*/
/*void compra_ingresso(NO *p, char nome[20], int sala) {
    NO *aux = NULL;
    aux = p;
    USU *primeiro_cliente = NULL;
    while(aux != NULL) {
        if (strcmp(aux->Nome, nome) == 0 && aux->sala == sala) {
            primeiro_cliente->ingresso = aux;
        } else{
            aux = aux->proxno;
        }
    }
}*/

int encontra_sessao(NO *p, char nome[20], int sala) {
    if ( p == NULL){
       return(0); 
    } else {
            do {
                if (strcmp(p->Nome, nome) == 0 && p->sala == sala) {
                primeiro_cliente->ingresso = p;
                return(1);
                }
            } while ( p != NULL );
        } 
} 



void imprimir_ingresso(USU *c) {
    printf("Nome: %s\nSala: %d\nHora: %02d:%02d\nLotacao: %d/%d\n", c->ingresso->Nome, c->ingresso->sala, c->ingresso->hora, c->ingresso->min, c->ingresso->lotacao, c->ingresso->LOTMAX);
}

void menu_Funcionario(){
        int in;
        char nome[20];
        int sala, hora, min;
    
        do{
            printf(" Cine SyStem - Funcionario\n");
            printf("___________________________\n");
            printf("1 - Adicionar Filme\n");
            printf("2 - Remover Filme\n");
            printf("3 - Listar Salas\n");
            printf("4 - Listar Filmes\n");
            printf("5 - Sair \n");  
            printf("___________________________\n");
            scanf("%d", &in);
            getchar();
            switch(in){
                case 1:                         
                        printf("Filme: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = 0;  
                        printf("Sala: ");
                        scanf("%d", &sala);
                        getchar();
                        printf("Hora:");
                        scanf("%d", &hora);
                        getchar();
                        printf("Minuto:");
                        scanf("%d", &min);
                        getchar();                        
                        adiciona_filme(&primeiro_no,nome,sala,hora,min);
                        printf("Ta certo isso?");
                        break;
                
                case 2: 
                        printf("Nome do filme: ");
                        fgets(nome, sizeof(nome), stdin);
                        getchar();
                        printf("Sala: ");
                        scanf("%d", &sala);
                        getchar();
                        remove_filme(&primeiro_no, nome, sala);
                        break;
               
                case 3: 
                        lista_salas(primeiro_no);
                        break;
                
                case 4: 
                        lista_filmes(primeiro_no);
                        break;
            }

        } while(in != 5);
        
        
}

void menu_Cliente(){
    int in, sala;
    char nome[20];
    char nome_cliente[20];

    USU *primeiro_cliente = (USU*) malloc(sizeof(USU));
        printf("Nome Cliente: ");
        fgets(nome_cliente, sizeof(nome_cliente), stdin);
        getchar();
        strcpy(primeiro_cliente->nome, nome_cliente);
    do{
        printf("Cine SyStem - Cliente\n");
        printf("----------------\n");
        printf("1 - Comprar Ingressos\n");
        printf("2 - Comprovante Ingresso\n");
        printf("3 - Listar Salas\n");
        printf("4 - Listar Filmes\n");
        printf("5 - Sair \n");
        scanf("%d", &in);
        getchar();
        switch(in){
            case 1:
                printf("  Cine SyStem - Cliente\n");
                printf("__________________________\n");

                
                        printf("Filme: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = 0;  
                        printf("Sala: ");
                        scanf("%d", &sala);
                        getchar();
                compra_ingresso(&primeiro_no, nome, sala);
                printf("Filme: %s Sala: %d Horario: %d:%d", primeiro_cliente->ingresso->Nome, primeiro_cliente->ingresso->sala, primeiro_cliente->ingresso->hora, primeiro_cliente->ingresso->min);
                printf("Compra sucedida! Volte sempre!");
                in = 5;
                break;
            case 2:
                printf("_____________________________\n");
                imprimir_ingresso(primeiro_cliente);
                printf(" %s", primeiro_cliente->nome);
                printf("_____________________________\n");
                break;
            case 3: 
                lista_salas(primeiro_no);
                break;
            case 4: 
                lista_filmes(primeiro_no);
                break;
        }

    } while(in != 5);
}

main(){
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
