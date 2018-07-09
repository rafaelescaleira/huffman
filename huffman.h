/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 * Nome : Rafael Escaleira Ferreira dos Santos.  *
 * Universidade Federal do Mato Grosso do Sul    *
 * Disciplina : Estrutura de Dados e Programação *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#define INVALIDO - 1
#define QUANTIDADE_SIMBOLOS 256

/* * * * * * * * * * * * * * * Cores * * * * * * * * * * * * * * * */

#define cor_texto(cor) cor
#define estilo_texto(estilo) estilo
 
#define magenta printf("\033[35m")
#define resetar_estilo printf("\033[0m")

/* * * * * * * * * * * * * * Registros * * * * * * * * * * * * * * */

enum { 

    COMPACTAR,
    DESCOMPACTAR

};

typedef struct _node {

    int zero;
    int raiz;
    int folha;
    
    struct _node * pai;
    struct _node * esq_filho;
    struct _node * dir_filho;
    
    unsigned char letra;
    int chave;
    int ordem;

} tnode;

typedef struct _arv {

    char caracter;
    tnode * parv;

} tarv;

/* * * * * * * * * * * * Cabeçalho das Funções * * * * * * * * * * */

void compactar (FILE * arquivo_entrada, FILE * arquivo_saida);

void descompactar (FILE * arquivo_entrada, FILE * arquivo_saida);

/* * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif
