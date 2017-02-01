//>>>>>>>>>>>>>>>>>>GRUPO: PHELIPE, MAYKOM E RENATO<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct arvdir
{
    int tipo;
    struct arvdir *pai, *filho, *prox_irmao;
    void *info;
} TAD;

typedef struct diretorio
{
    char nome[31];
    char dataCriacao[31];
    char horaCriacao[31];
    int nArq;
    int nDir;
} TD;

typedef struct arquivo
{
    char nome[31];
    char tipo;
    char dataCriacao[31];
    char horaCriacao[31];
    int tam;
} TA;

TD *inicializa_dir()
{
    return NULL;
}

TD *insere_info_dir(TD *dir,char *nome,int nArq,int nDir)
{
    TD *novo=(TD*)malloc(sizeof(TD));
    strcpy(novo->dataCriacao,__DATE__);
    strcpy(novo->horaCriacao,__TIME__);
    novo->nArq=nArq;
    novo->nDir=nDir;
    strcpy(novo->nome,nome);
    return novo;
}

TAD *aloca_dir(TD *dir)
{
    TAD *novo=(TAD*)malloc(sizeof(TAD));
    novo->tipo=0;
    novo->filho=novo->prox_irmao=NULL;
    novo->info=dir;
    novo->pai=NULL;
    return novo;
}


TA *inicializa_arq()
{
    return NULL;
}

TA *insere_info_arq(TA *arq,char *nome,int tipo,int tam)
{
    TA *novo=(TA*)malloc(sizeof(TA));
    strcpy(novo->dataCriacao,__DATE__);
    strcpy(novo->horaCriacao,__TIME__);
    if(tipo==1) novo->tipo='B';
    else if(tipo==2) novo->tipo='T';
    novo->tam=tam;
    strcpy(novo->nome,nome);
    return novo;
}

TAD *aloca_arq(TA *arq)
{
    TAD *novo=(TAD*)malloc(sizeof(TAD));
    novo->tipo=1;
    novo->filho=novo->prox_irmao=NULL;
    novo->info=arq;
    novo->pai=NULL;
    return novo;
}

void insere(TAD *pai,TAD *filho)
{
    if(pai->tipo==1)
    {
        printf("\nNao e possivel inserir dentro de um arquivo. Selecione um diretorio.");
    }
    else
    {
        filho->prox_irmao=pai->filho;
        pai->filho=filho;
        filho->pai=pai;

    }
}


TAD *busca_dir(TAD *a,char *x)
{
    if(a->tipo==0){
        TD *dir=a->info;
        int num=strcmp(dir->nome,x);
        if(num==0) return a;

    }
    a=a->filho;
    while(a){
        if(a->tipo==0){
            TD *dir=a->info;
            int num=strcmp(dir->nome,x);
            if(num==0) return a;
        }
        a=a->prox_irmao;
    }
    return NULL;
}

TAD *busca_arq_bin(TAD *a,char *x)
{
    TAD *filho=a->filho;
    while(filho){
        if(filho->tipo==1){
            TA *arq=filho->info;
            if(arq->tipo=='B'){
                int num=strcmp(arq->nome,x);
                if(num==0) return filho;
            }
        }
        filho=filho->prox_irmao;
    }
    return NULL;
}

TAD *busca_arq_texto(TAD *a,char *x)
{
    TAD *filho=a->filho;
    while(filho){
        if(filho->tipo==1){
            TA *arq=filho->info;
            if(arq->tipo=='T'){
                int num=strcmp(arq->nome,x);
                if(num==0) return filho;
            }
        }
        filho=filho->prox_irmao;
    }
    return NULL;

}

void libera(TAD* a){
    if(a->filho){
        libera(a->filho);
    }
    if(a->prox_irmao){
        libera(a->prox_irmao);
    }
    free(a);
}

TAD *retira_diretorio(TAD *a,char *nome)
{
    TAD *b=a->filho;
    while(b){
        if(b->tipo==0){
            TD *dir=b->info;
            int num=strcmp(dir->nome,nome);
            if(num==0) break;
        }
        b=b->prox_irmao;
    }
    if(!b)
    {
        printf("O diretorio que voce deseja retirar nao existe.\n\n");
        return a;
    }
    TAD *pai=b->pai;
    if(pai->filho==b)
    {
        TAD *aux=b;
        b=b->prox_irmao;
        pai->filho=b;
        libera(aux);
    }
    else
    {
        TAD *filho=pai->filho;
        while(filho&&filho->prox_irmao!=b) filho=filho->prox_irmao;
        filho->prox_irmao=b->prox_irmao;
        libera(b);
    }
    TD *dir=pai->info;
    dir->nDir--;
    strcpy(dir->dataCriacao,__DATE__);
    strcpy(dir->horaCriacao,__TIME__);
    return a;
}

TAD *retira_arq_bin(TAD *a,char *nome)
{
    TAD *b=busca_arq_bin(a,nome);
    if(!b)
    {
        printf("O arquivo que voce deseja retirar nao existe.\n\n");
        return a;
    }
    TAD *pai=b->pai;
    if(pai->filho==b)
    {
        TAD *aux=b;
        b=b->prox_irmao;
        pai->filho=b;
        free(aux);
    }
    else
    {
        TAD *filho=pai->filho;
        while(filho->prox_irmao!=b) filho=filho->prox_irmao;
        filho->prox_irmao=b->prox_irmao;
        free(b);
    }
    TD *dir=pai->info;
    dir->nArq--;
      strcpy(dir->dataCriacao,__DATE__);
    strcpy(dir->horaCriacao,__TIME__);
    return a;
}

TAD *retira_arq_texto(TAD *a,char *nome)
{
    TAD *b=busca_arq_texto(a,nome);
    if(!b)
    {
        printf("O arquivo que voce deseja retirar nao existe.\n\n");
        return a;
    }
    TAD *pai=b->pai;
    if(pai->filho==b)
    {
        TAD *aux=b;
        b=b->prox_irmao;
        pai->filho=b;
        free(aux);
    }
    else
    {
        TAD *filho=pai->filho;
        while(filho->prox_irmao!=b) filho=filho->prox_irmao;
        filho->prox_irmao=b->prox_irmao;
        free(b);
    }
    TD *dir=pai->info;
    dir->nArq--;
     strcpy(dir->dataCriacao,__DATE__);
    strcpy(dir->horaCriacao,__TIME__);
    return a;
}


void imprime(TAD *a)
{
    if(a->tipo==0)
    {
        TD *dir=a->info;
        if(a->pai)
        {
            TD *dirPai=a->pai->info;
            printf("\nD/%s/%s/Pastas: %d/Arquivos: %d/%s/%s\n",dir->nome,dirPai->nome,dir->nDir,dir->nArq,dir->dataCriacao,dir->horaCriacao);
        }
        else
        {
            printf("\nD/%s/NULL/Pastas: %d/Arquivos: %d/%s/%s\n",dir->nome,dir->nDir,dir->nArq,dir->dataCriacao,dir->horaCriacao);
        }
    }
    else
    {
        TA *arq=a->info;
        TA *arqPai=a->pai->info;
        if(arq->tipo=='B')printf("\nB/%s/%s/%d/%s/%s\n",arq->nome,arqPai->nome,arq->tam,arq->dataCriacao,arq->horaCriacao);
        else if(arq->tipo=='T') printf("\nT/%s/%s/%d/%s/%s\n",arq->nome,arqPai->nome,arq->tam,arq->dataCriacao,arq->horaCriacao);
    }
    TAD *p=a->filho;
    for(; p; p=p->prox_irmao)
    {
        imprime(p);
    }
}

TAD *muda_nome_dir(TAD *b2,char *nome)
{
    char nome2[31];
    TAD *filho=b2->filho;
    while(filho)
    {
        if(filho->tipo==0)
        {
            TD *dir=filho->info;
            int num=strcmp(dir->nome,nome);

            if(num==0){
                break;
            }
        }
        filho=filho->prox_irmao;
    }
    if(filho)
    {
        printf("\n\nDigite o novo nome do diretorio: ");
        scanf(" %[^\n]",nome2);
        TAD *aux=busca_dir(b2,nome2);
        if(aux) printf("\n\nNome ja existente.");
        else
        {
            TD *dir=filho->info;
            strcpy(dir->nome,nome2);
            TD *dirB=filho->pai->info;
            strcpy(dir->dataCriacao,__DATE__);
            strcpy(dir->horaCriacao,__TIME__);
            strcpy(dirB->dataCriacao,__DATE__);
            strcpy(dirB->horaCriacao,__TIME__);
        }
    }
    else
    {
        printf("\n\nDiretorio nao existente.");
    }
    return b2;
}

void cria_dir(TAD *arvore,char *nome,char *nome2)
{
    printf("\n\nDigite o nome do novo diretorio: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho aonde deseja inseri-lo: ");
    scanf(" %[^\n]",nome2);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }


    if(b2)
    {

        TAD *filho=b2->filho;
        int compara=-2;
        while(filho)
        {
            compara=strcmp(filho->info,nome3);
            if(compara==0&&filho->tipo==0) break;
            filho=filho->prox_irmao;
        }
        if(!filho)
        {
            TD *novoDir=inicializa_dir();
            novoDir=insere_info_dir(novoDir,nome3,0,0);
            TAD *novo=aloca_dir(novoDir);
            insere(b2,novo);
            TD *dirB=b2->info;
            dirB->nDir++;
            strcpy(dirB->dataCriacao,__DATE__);
            strcpy(dirB->horaCriacao,__TIME__);
        }
        else
        {
            printf("\n\nO diretorio que voce esta querendo inserir nesse diretorio ja existe.\n\n");
        }
    }
    else
    {
        printf("\n\nO diretorio aonde voce esta querendo inserir nao existe.\n\n");
    }
}

void renomear_dir(TAD *arvore,char *nome,char *nome2)
{
    char nome3[31];
    int opcao;
    printf("\n\nDigite a opcao de diretorio que deseja renomear:\n\n1 - Raiz\n2 - Outro\n\n");
    scanf(" %d",&opcao);
    if(opcao==2){
        printf("\n\nDigite o nome do diretorio que deseja renomear: ");
        scanf(" %[^\n]",nome);
        strcpy(nome3,nome);
        printf("\n\nDigite o caminho do diretorio que deseja renomear: ");
        scanf(" %[^\n]",nome2);
        char *token=strtok(nome2,"/");
        TAD *b2=arvore;
        while (token != NULL)
        {
            b2=busca_dir(b2,token);
            if(!b2)break;
            token = strtok(NULL, "/");
        }
        if(b2)
        {
            b2=muda_nome_dir(b2,nome3);

        }
        else
        {
            printf("\n\nCaminho nao existente.\n\n");
        }
    }else if(opcao==1){
        TD *raiz=arvore->info;
        printf("\n\nDigite o novo nome do diretorio: ");
        scanf(" %[^\n]",nome);
        strcpy(nome3,nome);
        strcpy(raiz->nome,nome3);
    }
}

void destruir_dir(TAD *arvore,char *nome,char *nome2)
{
    int opcao;
    printf("\n\nDigite a opcao de diretorio que deseja destruir:\n\n1 - Raiz\n2 - Outro\n\n");
    scanf(" %d",&opcao);

    if(opcao==2){
        printf("\n\nDigite o nome do diretorio que deseja destruir: ");
        scanf(" %[^\n]",nome);
        char nome3[31];
        strcpy(nome3,nome);
        printf("\n\nDigite o caminho aonde o diretorio que deseja remover se encontra: ");
        scanf(" %[^\n]",nome2);
        char *token=strtok(nome2,"/");
        TAD *b2=arvore;
        while (token != NULL)
        {
            b2=busca_dir(b2,token);
            if(!b2)break;
            token = strtok(NULL, "/");
        }
        if(b2)
        {
            b2=retira_diretorio(b2,nome3);
        }
        else printf("Diretorio nao existente.");
    }else if(opcao==1){

        TAD *b= arvore->filho;
        TAD *pai=b->pai;
        while(b){
            TAD *aux=b;
            b=b->prox_irmao;
            pai->filho=b;
            libera(aux);
        }
        TD *dir=arvore->info;
        dir->nArq=0;
        dir->nDir=0;
        strcpy(dir->dataCriacao,__DATE__);
        strcpy(dir->horaCriacao,__TIME__);
    }
}

TAD *retira_diretorio_sem_liberar(TAD *a,char *nome)
{
    TAD *b=busca_dir(a,nome);
    if(!b)
    {
        printf("O diretorio que voce deseja retirar nao existe.\n\n");
        return a;
    }
    TAD *pai=b->pai;
    if(pai->filho==b)
    {
        b=b->prox_irmao;
        pai->filho=b;
    }
    else
    {
        TAD *filho=pai->filho;
        while(filho->prox_irmao!=b) filho=filho->prox_irmao;
        filho->prox_irmao=b->prox_irmao;

    }
    TD *dir=pai->info;
    dir->nDir--;
    strcpy(dir->dataCriacao,__DATE__);
    strcpy(dir->horaCriacao,__TIME__);
    return a;
}



void *mover_dir(TAD *arvore,char *nome,char *nome2)
{
    printf("\n\nDigite o diretorio que deseja mover: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho para o diretorio que deseja mover: ");
    scanf(" %[^\n]",nome2);
    char nome2Aux[strlen(nome2)];
    strcpy(nome2Aux,nome2);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        printf("\n\nDigite o caminho para onde o diretorio deve ser movido: ");
        scanf(" %[^\n]",nome2);
        char nome3Aux[strlen(nome2)];
        strcpy(nome3Aux,nome2);
        int pode=0;
        if(strlen(nome2Aux)>strlen(nome3Aux)){
            pode=1;
        }else{
            int i;
            for(i=0;i<strlen(nome2Aux);i++){
                if(nome2Aux[i]!=nome3Aux[i]){
                    pode=1;
                    break;
                }
            }
        }
        if(pode==1){
        token=strtok(nome2,"/");
        TAD *b=arvore;
        while (token != NULL)
        {
            b=busca_dir(b,token);
            if(!b)break;
            token = strtok(NULL, "/");
        }
        if(b)
        {
            TAD *filho=b2->filho;
            while(filho)
            {
                if(filho->tipo==0)
                {
                    TD *dir=filho->info;
                    int num=strcmp(dir->nome,nome3);
                    if(num==0)
                    {
                        TAD *aux=busca_dir(b,nome3);
                        if(aux)
                        {
                            printf("\n\nJa existe um diretorio com o mesmo nome.");
                            break;
                        }
                        else
                        {
                            TAD *novo=filho;
                            b2=retira_diretorio_sem_liberar(b2,nome3);
                            insere(b,novo);
                            TD *pai=b->info;
                            strcpy(pai->dataCriacao,__DATE__);
                            strcpy(pai->horaCriacao,__TIME__);
                            pai->nDir++;
                            break;
                        }
                    }

                }
                filho=filho->prox_irmao;
            }
            if(!filho) printf("O diretorio que deseja mover nao existe.");

        }
    }else printf("Nao e possivel inserir neste diretorio.");

    }
    else
    {
        printf("\n\nDiretorio nao existente.");
    }

}

void transforma_dir_em_arq(TAD *arvore,char *nome,char *nome2)
{
    int tipo;
    int tam;
    printf("\n\nDigite o diretorio que deseja transformar em arquivo: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho do diretorio que deseja transformar em arquivo: ");
    scanf(" %[^\n]",nome2);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
        scanf("%d",&tipo);
        TAD *busca;
        if(tipo==1)
        {
            busca=busca_arq_bin(arvore,nome3);

        }
        else if(tipo==2)
        {
            busca=busca_arq_texto(arvore,nome3);

        }
        if(!busca)
        {
            TAD *filho=b2->filho;
            while(filho)
            {
                if(filho->tipo==0)
                {
                    TD *dir=filho->info;
                    int num=strcmp(dir->nome,nome3);
                    if(num==0)
                    {
                        TAD *aux;
                        if(tipo==1) aux=busca_arq_bin(b2,nome3);
                        else if(tipo==2) aux=busca_arq_texto(b2,nome3);
                        int tipo2;
                        if(aux)
                        {
                            TA *aux2=aux->info;
                            if(aux2->tipo=='B') tipo2=1;
                            else if(aux2->tipo=='T') tipo2=2;
                        }
                        if(aux&&tipo==tipo2) printf("\n\nJa possui arquivo com esse nome.");
                        else
                        {
                            printf("\n\nDigite o tamanho do arquivo: ");
                            scanf("%d",&tam);
                            TA *novoArq=inicializa_arq();
                            novoArq=insere_info_arq(novoArq,dir->nome,tipo,tam);
                            TAD *alocaArq=aloca_arq(novoArq);
                            TD *pai=filho->pai->info;
                            pai->nArq++;
                            b2=retira_diretorio(b2,nome3);
                            insere(b2,alocaArq);
                            break;
                        }
                    }

                }
                filho=filho->prox_irmao;
            }
            if(!filho) printf("O diretorio que deseja transformar em arquivo nao existe.");
        }
    }
}

void cria_arq(TAD *arvore,char *nome,char *nome2)
{
    int tam;
    int tipo;
    printf("\n\nDigite o nome do novo arquivo:");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho aonde deseja inseri-lo: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nDigite o tamanho do arquivo: ");
    scanf("%d",&tam);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
        scanf("%d",&tipo);
        TA *novoArq=inicializa_arq();
        TAD *busca;
        if(tipo==1)
        {
            busca=busca_arq_bin(b2,nome3);

        }
        else if(tipo==2)
        {
            busca=busca_arq_texto(b2,nome3);
        }
        if(!busca)
        {

            novoArq=insere_info_arq(novoArq,nome3,tipo,tam);
            TAD *novo=aloca_arq(novoArq);
            insere(b2,novo);
            TD *dirB=b2->info;
            dirB->nArq++;
            strcpy(dirB->dataCriacao,__DATE__);
            strcpy(dirB->horaCriacao,__TIME__);
        }
        else
        {
            printf("O arquivo que voce deseja inserir ja existe.");
        }
    }
    else
    {
        printf("\n\nO diretorio aonde voce esta querendo inserir nao existe.");
    }
}

void renomear_arq(TAD *arvore,char *nome,char *nome2)
{
    int tipo;
    printf("\n\nDigite o nome do arquivo que deseja renomear: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho do arquivo que deseja renomear: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
    scanf("%d",&tipo);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *b;
        if(tipo==1)
        {
            b=busca_arq_bin(b2,nome3);
        }
        else if(tipo==2)
        {
            b=busca_arq_texto(b2,nome3);
        }
        if(b)
        {
            printf("\n\nDigite o novo nome do arquivo: ");
            scanf(" %[^\n]",nome3);
            TAD *aux;
            if(tipo==1) aux=busca_arq_bin(b2,nome3);
            else if(tipo==2) aux=busca_arq_texto(b2,nome3);
            int tipo2;
            TA *aux2;
            if(aux)
            {
                aux2=aux->info;
                if(aux2->tipo=='B')tipo2=1;
                else if(aux2->tipo=='T') tipo2=2;
            }
            if(aux&&tipo==tipo2) printf("Nome ja existente.");
            else
            {
                TA *arq=b->info;
                strcpy(arq->nome,nome3);
                TD *dirB=b->pai->info;
                strcpy(dirB->dataCriacao,__DATE__);
                strcpy(dirB->horaCriacao,__TIME__);
                strcpy(arq->dataCriacao,__DATE__);
                strcpy(arq->horaCriacao,__TIME__);
            }
        }
        else
        {
            printf("\n\nArquivo nao existente");
        }
    }
    else
    {
        printf("\n\nDiretorio nao existente.");
    }
}

void mudar_tam(TAD *arvore,char *nome,char *nome2)
{
    int tipo;
    int tam;
    printf("\n\nDigite o nome do arquivo que deseja renomear: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho do arquivo que deseja renomear: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
    scanf("%d",&tipo);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *b;
        if(tipo==1)
        {
            b=busca_arq_bin(b2,nome3);
        }
        else if(tipo==2)
        {
            b=busca_arq_texto(b2,nome3);
        }
        if(b)
        {
            printf("\n\nDigite o novo tamanho do arquivo: ");
            scanf("%d",&tam);
            TA *arq=b->info;
            arq->tam=tam;
            TD *dirB=b->pai->info;
            strcpy(dirB->dataCriacao,__DATE__);
            strcpy(dirB->horaCriacao,__TIME__);
            strcpy(arq->dataCriacao,__DATE__);
            strcpy(arq->horaCriacao,__TIME__);
        }
        else
        {
            printf("\n\nArquivo nao existente");
        }
    }
    else
    {
        printf("\n\nDiretorio nao existente.");
    }
}


TAD *retira_arq_bin_sem_liberar(TAD *a,char *nome)
{
    TAD *b=busca_arq_bin(a,nome);
    if(!b)
    {
        printf("O arquivo que voce deseja retirar nao existe.\n\n");
        return a;
    }
    TAD *pai=b->pai;
    if(pai->filho==b)
    {
        b=b->prox_irmao;
        pai->filho=b;
    }
    else
    {
        TAD *filho=pai->filho;
        while(filho->prox_irmao!=b) filho=filho->prox_irmao;
        filho->prox_irmao=b->prox_irmao;
    }
    TD *dir=pai->info;
    dir->nArq--;
    strcpy(dir->dataCriacao,__DATE__);
    strcpy(dir->horaCriacao,__TIME__);
    return a;
}

TAD *retira_arq_texto_sem_liberar(TAD *a,char *nome)
{
    TAD *b=busca_arq_texto(a,nome);
    if(!b)
    {
        printf("O arquivo que voce deseja retirar nao existe.\n\n");
        return a;
    }
    TAD *pai=b->pai;
    if(pai->filho==b)
    {
        b=b->prox_irmao;
        pai->filho=b;
    }
    else
    {
        TAD *filho=pai->filho;
        while(filho->prox_irmao!=b) filho=filho->prox_irmao;
        filho->prox_irmao=b->prox_irmao;
    }
    TD *dir=pai->info;
    dir->nArq--;
    strcpy(dir->dataCriacao,__DATE__);
    strcpy(dir->horaCriacao,__TIME__);
    return a;
}

void mover_arq(TAD *arvore,char *nome,char *nome2)
{
    int tipo;
    printf("\n\nDigite o nome do arquivo que deseja mover: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho do arquivo que deseja mover: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
    scanf("%d",&tipo);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *b;
        if(tipo==1)
        {
            b=busca_arq_bin(b2,nome3);
        }
        else if(tipo==2)
        {
            b=busca_arq_texto(b2,nome3);
        }
        if(b)
        {
            printf("\n\nDigite o caminho para onde o arquivo deve ser movido: ");
            scanf(" %[^\n]",nome2);
            token=strtok(nome2,"/");
            TAD *b3=arvore;
            while (token != NULL)
            {
                b3=busca_dir(b3,token);
                if(!b)break;
                token = strtok(NULL, "/");
            }
            if(b3)
            {
                TAD *aux;
                if(tipo==1) aux=busca_arq_bin(b3,nome3);
                else if(tipo==2) aux=busca_arq_texto(b3,nome3);
                if(aux)
                {
                    printf("\n\nJa existe um arquivo com esse nome.");
                }
                else
                {
                    TAD *novo=b;
                    if(tipo==1) b2=retira_arq_bin_sem_liberar(b2,nome3);
                    else if(tipo==2) b2=retira_arq_texto_sem_liberar(b2,nome3);
                    insere(b3,novo);
                    TD *pai=b3->info;
                    strcpy(pai->dataCriacao,__DATE__);
                    strcpy(pai->horaCriacao,__TIME__);
                    pai->nArq++;

                }
            }
            else
            {
                printf("O caminho aonde deseja que o arquivo seja movido nao existe.");

            }

        }
        else printf("Arquivo nao existente.");
    }
    else
    {
        printf("\n\nDiretorio nao existente.");
    }
}

void destruir_arq(TAD *arvore,char *nome,char *nome2)
{
    int tipo;
    printf("\n\nDigite o nome do arquivo que deseja destruir: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o nome do diretorio aonde o arquivo se encontra: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
    scanf("%d",&tipo);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *b;
        if(tipo==1)
        {
            b=retira_arq_bin(b2,nome3);
        }
        else if(tipo==2)
        {
            b=retira_arq_texto(b2,nome3);
        }

    }
    else
    {
        printf("\n\nDiretorio nao existente.");
    }
}

void transforma_arq_em_dir(TAD *arvore,char *nome,char *nome2)
{
    int tipo;
    printf("\n\nDigite o nome do arquivo que deseja transformar em diretorio: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o nome do diretorio aonde o arquivo se encontra: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
    scanf("%d",&tipo);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *b;
        if(tipo==1)
        {
            b=busca_arq_bin(b2,nome3);
        }
        else if(tipo==2)
        {
            b=busca_arq_texto(b2,nome3);
        }
        if(b)
        {
            TAD *aux=busca_dir(b2,nome3);
            if(aux) printf("\n\nJa possui um diretorio com esse nome.");
            else
            {
                TD *dir=inicializa_dir();
                TA *arq=b->info;
                dir=insere_info_dir(dir,arq->nome,0,0);
                if(tipo==1) b2=retira_arq_bin(b2,nome3);
                else if(tipo==2) b2=retira_arq_texto(b2,nome3);
                TAD *novo=aloca_dir(dir);
                insere(b2,novo);
                dir=novo->pai->info;
                dir->nDir++;
            }
        }
        else printf("Arquivo nao existente.");
    }
    else
    {
        printf("\n\nCaminho nao existente.");
    }
}

void realiza_busca_arq(TAD *arvore,char *nome,char *nome2){
    int tipo;
    printf("\n\nDigite o nome do arquivo que deseja buscar: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho aonde o arquivo se encontra: ");
    scanf(" %[^\n]",nome2);
    printf("\n\nTipo do arquivo:\n1 - Binario\n2 - Texto\n\n");
    scanf("%d",&tipo);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *b;
        if(tipo==1)
        {
            b=busca_arq_bin(b2,nome3);
        }
        else if(tipo==2)
        {
            b=busca_arq_texto(b2,nome3);
        }
        if(b)
        {
            imprime(b);
        }else{
            printf("\n\nArquivo inexistente.");
        }
    }else printf("\n\nCaminho inexistente.");
}

void realiza_busca_dir(TAD *arvore,char *nome,char *nome2){
printf("\n\nDigite o nome do diretorio que deseja buscar: ");
    scanf(" %[^\n]",nome);
    char nome3[31];
    strcpy(nome3,nome);
    printf("\n\nDigite o caminho aonde o diretorio se encontra: ");
    scanf(" %[^\n]",nome2);
    char *token=strtok(nome2,"/");
    TAD *b2=arvore;
    while (token != NULL)
    {
        b2=busca_dir(b2,token);
        if(!b2)break;
        token = strtok(NULL, "/");
    }
    if(b2)
    {
        TAD *aux=b2->filho;
        while(aux){
            if(aux->tipo==0){
                TD *dir=aux->info;
                int num=strcmp(dir->nome,nome3);
                if(num==0) break;
            }
            aux=aux->prox_irmao;
        }
        if(aux) imprime(aux);
        else printf("\n\nDiretorio nao existente.");
    }else{
        printf("\n\nCaminho inexistente.");
    }
}

TAD *busca_carrega_arq(TAD *a,char *x){
    if(a->tipo==0){
        TD *dir=a->info;
        int num=strcmp(dir->nome,x);
        if(num==0) return a;
    }
    TAD *p;
    for(p=a->filho;p;p=p->prox_irmao){
        TAD *resp=busca_carrega_arq(p,x);
        if(resp) return resp;
    }
    return NULL;
}


TAD *carrega_arq(TAD *arvore){

    char url[]="arvore.txt",
    ch1[500];
    int num=1;
    char nome[31];
    char pai[31];
    char dataCriacao[31];
    char horaCriacao[31];
    char tam[31];
    char tipo[2];
	FILE *arq;

	arq = fopen(url, "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fgets(ch1, sizeof(ch1), arq))!=NULL ){
            char *token=strtok(ch1,"/");
            while (token != NULL)
            {

                if(num==1){
                  strcpy(tipo,token);

                }
                else if(num==2) strcpy(nome,token);
                else if(num==3) strcpy(pai,token);
                else if(num==4){
                    int numD=strcmp(tipo,"D");
                    if(numD==0) strcpy(dataCriacao,token);
                    else strcpy(tam,token);
                }
                else if(num==5){
                    int numD=strcmp(tipo,"D");
                    if(numD==0) strcpy(horaCriacao,token);
                    else strcpy(dataCriacao,token);
                }
                else if(num==6){
                    int numD=strcmp(tipo,"D");
                    if(numD!=0) strcpy(horaCriacao,token);
                }
                num++;
                token = strtok(NULL, "/");
            }
            int numD=strcmp(tipo,"D");
            if(numD==0){
                TD *novoDir=inicializa_dir();
                novoDir=(TD*)malloc(sizeof(TD));
                strcpy(novoDir->dataCriacao,dataCriacao);
                strcpy(novoDir->horaCriacao,horaCriacao);
                novoDir->nArq=0;
                novoDir->nDir=0;
                strcpy(novoDir->nome,nome);
                int compara=strcmp(pai,"NULL");
                if(compara==0) {
                    arvore=aloca_dir(novoDir);
                }else{
                    TAD *novo=aloca_dir(novoDir);
                    TAD *b2=busca_carrega_arq(arvore,pai);
                    if(b2){
                        insere(b2,novo);
                        TD *dirB=b2->info;
                        dirB->nDir++;

                }

                }

            }else{
                int numB=strcmp(tipo,"B");
                int numT=strcmp(tipo,"T");
                TA *novo=inicializa_arq();
                novo=(TA*)malloc(sizeof(TA));
                strcpy(novo->dataCriacao,dataCriacao);
                strcpy(novo->horaCriacao,horaCriacao);
                if(numB==0) novo->tipo='B';
                else if(numT==0)novo->tipo='T';
                int tamInt= atoi(tam);
                novo->tam=tamInt;
                strcpy(novo->nome,nome);
                TAD *novo2=aloca_arq(novo);

                TAD *b2=busca_carrega_arq(arvore,pai);
                if(b2){
                    insere(b2,novo2);
                    TD *dirB=b2->info;
                    dirB->nArq++;
                }

            }
            num=1;

		}

	fclose(arq);
	return arvore;

}

int main()
{
    char nome[31];
    char nome2[31];
    int tam;
    int tipo;
    int opcao1,opcao2;
    TAD *arvore=carrega_arq(arvore);
    printf("\n\nMenu - Escolha a opcao com a qual deseja trabalhar:\n1 - Diretorio\n2 - Arquivo\n3 - Imprimir\n4 - Sair\n\n");
    scanf("%d",&opcao1);
    while(opcao1!=4)
    {
        if(opcao1==1)
        {
            printf("\n\n1 - Criar diretorio\n2 - Mover diretorio\n3 - Renomear diretorio\n4 - Destruir diretorio\n5 - Transformar em arquivo\n6 - Imprimir\n7 - Buscar Diretorio\n8 - Voltar para o Menu Principal\n\n");
            scanf("%d",&opcao2);
            while(opcao2!=8)
            {
                if(opcao2==1)
                {
                    cria_dir(arvore,nome,nome2);
                }
                else if(opcao2==4)
                {
                    destruir_dir(arvore,nome,nome2);
                }
                else if(opcao2==6)
                {
                    imprime(arvore);
                }
                else if(opcao2==3)
                {
                    renomear_dir(arvore,nome,nome2);
                }
                else if(opcao2==2)
                {
                    mover_dir(arvore,nome,nome2);
                }
                else if(opcao2==5)
                {
                    transforma_dir_em_arq(arvore,nome,nome2);
                }else if(opcao2==7){
                    realiza_busca_dir(arvore,nome,nome2);
                }
                printf("\n\n1 - Criar diretorio\n2 - Mover diretorio\n3 - Renomear diretorio\n4 - Destruir diretorio\n5 - Transformar em arquivo\n6 - Imprimir\n7 - Buscar diretorio\n8 - Voltar para o Menu Principal\n\n");
                scanf("%d",&opcao2);

            }

        }
        else if(opcao1==2)
        {
            printf("\n\n1 - Criar arquivo\n2 - Mover arquivo\n3 - Renomear arquivo\n4 - Destruir arquivo\n5 - Transformar em diretorio\n6 - Imprimir\n7 - Modificar tamanho\n8 - Buscar arquivo\n9 - Voltar para o Menu Principal\n\n");
            scanf("%d",&opcao2);
            while(opcao2!=9)
            {
                if(opcao2==1)
                {
                    cria_arq(arvore,nome,nome2);
                }
                else if(opcao2==6)
                {
                    imprime(arvore);
                }
                else if(opcao2==3)
                {
                    renomear_arq(arvore,nome,nome2);
                }
                else if(opcao2==7)
                {
                    mudar_tam(arvore,nome,nome2);
                }
                else if(opcao2==2)
                {
                    mover_arq(arvore,nome,nome2);
                }
                else if(opcao2==4)
                {
                    destruir_arq(arvore,nome,nome2);
                }
                else if(opcao2==5)
                {
                    transforma_arq_em_dir(arvore,nome,nome2);
                }else if(opcao2==8){
                    realiza_busca_arq(arvore,nome,nome2);
                }
                printf("\n\n1 - Criar arquivo\n2 - Mover arquivo\n3 - Renomear arquivo\n4 - Destruir arquivo\n5 - Transformar em diretorio\n6 - Imprimir\n7 - Modificar tamanho\n8 - Buscar arquivo\n9 - Voltar para o Menu Principal\n\n");
                scanf("%d",&opcao2);
            }
        }
        else if(opcao1==3)
        {
            imprime(arvore);

        }else if(opcao1==4){
            carrega_arq(arvore);
        }
        printf("\n\nMenu - Escolha a opcao com a qual deseja trabalhar:\n1 - Diretorio\n2 - Arquivo\n3 - Imprimir\n4 - Sair\n\n");
        scanf("%d",&opcao1);
    }
    libera(arvore);
    return 0;
}
