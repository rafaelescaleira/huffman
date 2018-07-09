/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 * Nome : Rafael Escaleira Ferreira dos Santos.  *
 * Universidade Federal do Mato Grosso do Sul    *
 * Disciplina : Estrutura de Dados e Programação *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

tnode * constroi_arvore  () {

    tnode * parv = malloc (sizeof (tnode));

    parv -> zero = 1;
    parv -> raiz = 1;
    parv -> folha = 1;
    
    parv -> pai = NULL;
    parv -> esq_filho = NULL;
    parv -> dir_filho = NULL;
    
    parv -> letra = INVALIDO;
    parv -> chave = 0;
    parv -> ordem = QUANTIDADE_SIMBOLOS * 2;
    
    return parv;

}

tnode * obter_arvore_caracter (unsigned char letra, tarv * * pparv ) {

    tarv * caracter_arvore = pparv [(unsigned int) letra];

    if (!caracter_arvore) {

        return NULL;

    }
    
    return caracter_arvore -> parv;

}

void inverter_codigo (int * codigo, int tamanho_codigo) {

    int * inicio, * fim, temp;

    if (codigo == NULL) {

        return ;

    }

    inicio = codigo;
    fim = codigo + (tamanho_codigo - 1);
    
    while (inicio < fim) {

        temp = * inicio;
        * inicio = * fim;
        * fim = temp;
        inicio = inicio + 1;
        fim = fim - 1;;

    }

}

int * no_codigo (tnode * pnode, int * n) {

    tnode * no_atual, * pai;
    int * codigo, i;

    no_atual = pnode;
    codigo = malloc (QUANTIDADE_SIMBOLOS * 2 * sizeof (int));
    i = 0;

    while (!no_atual -> raiz) {

        pai = no_atual -> pai;
        codigo[i] = (pai -> esq_filho == no_atual) ? 0 : 1;
        no_atual = no_atual -> pai;
        i = i + 1;

    }

    inverter_codigo (codigo, i);
    
    * n = i;

    return codigo;

}

tnode * criar_filho (tnode * pai, int zero, int raiz, unsigned char caracter, int chave, int ordem) {

    tnode * pnode;

    pnode = (tnode *) malloc (sizeof (tnode));
    pnode -> zero = zero;
    pnode -> raiz = raiz;
    pnode -> folha = 1;
    pnode -> pai = pai;
    pnode -> esq_filho = NULL;
    pnode -> dir_filho = NULL;
    pnode -> letra = caracter;
    pnode -> chave = chave;
    pnode -> ordem = ordem;

    return pnode;

}

tnode * criar_caracter  (unsigned char caracter, tnode * * no_inicio, tarv * * pparv) {

    tnode * no_esq, * no_dir, * anterior_inicio;
    unsigned int indice_caracter;

    no_esq = criar_filho (* no_inicio, 1, 0, INVALIDO, 0, (* no_inicio) -> ordem - 2);
    no_dir = criar_filho (* no_inicio, 0, 0, caracter, 1, (* no_inicio) -> ordem - 1);

    anterior_inicio = * no_inicio;

    (* no_inicio) -> zero = 0;
    (* no_inicio) -> folha = 0;
    (* no_inicio) -> esq_filho = no_esq;
    (* no_inicio) -> dir_filho = no_dir;
    
    indice_caracter = (unsigned int) caracter;

    pparv [indice_caracter] = malloc (sizeof (tarv));
    pparv [indice_caracter] -> caracter = caracter;
    pparv [indice_caracter] -> parv = no_dir;
    
    * no_inicio = no_esq;
    
    return anterior_inicio;

}

tnode * busca_no (tnode * atual_maximo, tnode * raiz) {

    tnode * resultado, * maior_esq, * maior_dir;

    resultado = atual_maximo;
    
    if (raiz -> chave > resultado -> chave && !raiz -> folha) {

        maior_esq = busca_no (resultado, raiz -> esq_filho);

        if (maior_esq) {

            resultado = maior_esq;

        }
        
        maior_dir = busca_no (resultado, raiz -> dir_filho);

        if (maior_dir) {

            resultado = maior_dir;

        }

    } 

    else if (raiz -> chave == resultado -> chave && raiz -> ordem > resultado -> ordem) {

        resultado = raiz;

    }
    
    return (resultado != atual_maximo) ? resultado : NULL;

}

void troca_no (tnode * a, tnode * b) {
    
    tnode * pnode_aux;
    int aux;

    aux = a -> ordem;
    a -> ordem = b -> ordem;
    b -> ordem = aux;
    
    if (a -> pai -> esq_filho == a) {

        a -> pai -> esq_filho = b;

    } 

    else {

        a -> pai -> dir_filho = b;

    }
    
    if (b -> pai -> esq_filho == b) {

        b -> pai -> esq_filho = a;

    } 

    else {

        b -> pai -> dir_filho = a;

    }
    
    pnode_aux = a -> pai;
    a -> pai = b -> pai;
    b -> pai = pnode_aux;

}

void verifica_arvore  (tnode * no_atual, tnode * raiz) {

    tnode * pnode_aux;

    while (!no_atual -> raiz) {

        pnode_aux = busca_no (no_atual, raiz);
        
        if (pnode_aux && no_atual -> pai != pnode_aux) {

            troca_no (no_atual, pnode_aux);

        }
        
        (no_atual -> chave) = (no_atual -> chave) + 1;
        no_atual = no_atual -> pai;

    }
    
    (no_atual -> chave) = (no_atual -> chave) + 1;

}

unsigned char armazena_codigo (int * codigo, int tamanho_codigo, FILE * arquivo, unsigned char local_armazena, int * tamanho) {

    unsigned char armazena_atual, bit;
    int i;

    armazena_atual = local_armazena;

    for (i = 0; i < tamanho_codigo; i ++) {

        bit = ((unsigned char) codigo[i]) << (* tamanho - 1);
        armazena_atual = armazena_atual | bit;
        (* tamanho) = (* tamanho) - 1;
        
        if (* tamanho == 0) {

            fwrite (&armazena_atual, sizeof (unsigned char), 1, arquivo);
            armazena_atual = 0;
            * tamanho = 8;

        }

    }
    
    return armazena_atual;

}

unsigned char armazena_byte (char byte, FILE * arquivo, unsigned char local_armazena, int * tamanho) {

    unsigned char armazena_atual, aux;
    int quantidade_bits_escritos, tamanho_shit;

    armazena_atual = local_armazena;
    quantidade_bits_escritos = * tamanho;
    tamanho_shit = 8 - quantidade_bits_escritos;
    aux = ((unsigned char) byte) >> tamanho_shit;
    armazena_atual = armazena_atual | aux;
    
    fwrite (&armazena_atual, sizeof (unsigned char), 1, arquivo);
    
    armazena_atual = byte << quantidade_bits_escritos;
    
    return (* tamanho == 8) ? 0 : armazena_atual;

}

void escreve_bits_restantes (FILE * arquivo, unsigned char local_armazena, int tamanho) {

    if (tamanho < 8) {

        fwrite (&local_armazena, sizeof (unsigned char), 1, arquivo);

    }
    
    local_armazena = (tamanho == 8) ? 8 : 8 - tamanho;
    fwrite (&local_armazena, sizeof (unsigned char), 1, arquivo);

}

void compactar (FILE * arquivo_entrada, FILE * arquivo_saida) {

    tnode * raiz, * no_inicio, * caracter_arvore, * novo_no;
    unsigned char local_armazena, byte_atual;
    int tamanho, tamanho_codigo, * codigo_inicio, * caracter_codigo;
    tarv * * pparv;

    raiz = constroi_arvore ();
    no_inicio = raiz;
    local_armazena = 0;
    tamanho = 8;
    pparv = calloc (QUANTIDADE_SIMBOLOS, sizeof (tarv *));

    while (fread (&byte_atual, sizeof (unsigned char), 1, arquivo_entrada) > 0) {

        caracter_arvore = obter_arvore_caracter (byte_atual, pparv);
        
        if (caracter_arvore) {

            caracter_codigo = no_codigo (caracter_arvore, &tamanho_codigo);
            local_armazena = armazena_codigo (caracter_codigo, tamanho_codigo, arquivo_saida, local_armazena, &tamanho);
            
            verifica_arvore (caracter_arvore, raiz);
            free (caracter_codigo);

        } 

        else {
            
            codigo_inicio = no_codigo (no_inicio, &tamanho_codigo);
            local_armazena = armazena_codigo (codigo_inicio, tamanho_codigo, arquivo_saida, local_armazena, &tamanho);
            local_armazena = armazena_byte (byte_atual, arquivo_saida, local_armazena, &tamanho);
            
            novo_no = criar_caracter (byte_atual, &no_inicio, pparv);
            verifica_arvore (novo_no, raiz);
            free (codigo_inicio);

        }

    }
    
    escreve_bits_restantes (arquivo_saida, local_armazena, tamanho);

}

int leitura_bit (FILE * arquivo, unsigned char * local_armazena, int * tamanho, long int tamanho_arquivo, int quantidade_bits_fim) {

    if (* tamanho == 0) {

        * tamanho = 8;
        fread (local_armazena, sizeof (unsigned char), 1, arquivo);

    }
    
    if (quantidade_bits_fim != 8) {

        if (ftell (arquivo) == tamanho_arquivo && quantidade_bits_fim <= (8 - *tamanho)) {

            return - 1;

        }

    }
    
    if (ftell (arquivo) > tamanho_arquivo || feof (arquivo)) {

        return - 1;

    }
    
    (* tamanho) = (* tamanho) - 1;
    
    return (* local_armazena >> * tamanho) & 1;

}

char leitura_byte (FILE * arquivo, unsigned char * local_armazena, int * tamanho, long int tamanho_arquivo, int quantidade_bits_fim) {

    char resultado;
    int i, bit;

    resultado = 0;

    for (i = 0; i < 8; i ++) {

        bit = leitura_bit (arquivo, local_armazena, tamanho, tamanho_arquivo, quantidade_bits_fim);
        bit = bit << (7 - i);
        resultado |= bit;

    }
    
    return resultado;

}

void descompactar (FILE * arquivo_entrada, FILE * arquivo_saida) {

    tnode * raiz, * no_inicio, * no_atual;
    unsigned char local_armazena, quantidade_bits_fim, aux;
    int tamanho, final_arquivo, bit;
    tarv * * pparv;
    long int tamanho_arquivo;

    raiz = constroi_arvore ();
    no_inicio = raiz;
    local_armazena = 0;
    tamanho = 0;
    pparv = calloc (QUANTIDADE_SIMBOLOS, sizeof (tarv *));
    
    fseek (arquivo_entrada, -1, SEEK_END);
    tamanho_arquivo = ftell (arquivo_entrada);
    
    fread (&quantidade_bits_fim, sizeof (unsigned char), 1, arquivo_entrada);
    rewind (arquivo_entrada);
    
    while (!feof (arquivo_entrada)) {

        no_atual = raiz;
        final_arquivo = 0;

        while (!no_atual -> folha && !final_arquivo) {

            bit = leitura_bit (arquivo_entrada, &local_armazena, &tamanho, tamanho_arquivo, quantidade_bits_fim);

            if (bit == 0) {

                no_atual = no_atual -> esq_filho;

            } 

            else if (bit == 1) {

                no_atual = no_atual -> dir_filho;

            } 

            else {

                final_arquivo = 1;

            }

        }
        
        if (final_arquivo) {

            break;

        }
        
        if (no_atual -> zero) {

            aux = leitura_byte (arquivo_entrada, &local_armazena, &tamanho, tamanho_arquivo, quantidade_bits_fim);
            no_atual = criar_caracter (aux, &no_inicio, pparv);

        } 

        else {

            aux = no_atual -> letra;

        }
        
        fwrite (&aux, sizeof (unsigned char), 1, arquivo_saida);
        verifica_arvore (no_atual, raiz);

    }

}
