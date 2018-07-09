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

int main (int argc, char * argv[]) {

    FILE * arquivo_entrada;
    FILE * arquivo_saida;
    int opcao;

    opcao = 0;
    
    /* Arquivo de Entrada */

    arquivo_entrada = fopen (argv [2], "r");

    /* Opção: Codificar ou Decodificar */

    if (strcmp (argv[1], "compactar") == 0) {

        opcao = COMPACTAR;

    } 

    else if (strcmp (argv[1], "descompactar") == 0) {

        opcao = DESCOMPACTAR;

    }
    
    if (opcao == COMPACTAR) {

        /* Arquivo de Saída */

        arquivo_saida = fopen (argv [3], "w");

        compactar (arquivo_entrada, arquivo_saida);

        cor_texto (magenta);
        printf("\n\t* * * * * * * * * * * * * *\n\t*");
        estilo_texto (resetar_estilo);

        printf("    Arquivo Compactado   ");

        cor_texto (magenta);
        printf("*\n\t* * * * * * * * * * * * * *\n\n");
        estilo_texto (resetar_estilo);

    }

    else {

        arquivo_saida = fopen (argv [3], "w");

        descompactar (arquivo_entrada, arquivo_saida);

        cor_texto (magenta);
        printf("\n\t* * * * * * * * * * * * * * * *\n\t*");
        estilo_texto (resetar_estilo);

        printf("    Arquivo Descompactado    ");

        cor_texto (magenta);
        printf("*\n\t* * * * * * * * * * * * * * * *\n\n");
        estilo_texto (resetar_estilo);


    }
    
    fclose (arquivo_entrada);
    fclose (arquivo_saida);
    
    return 0;

}
