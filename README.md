Huffman (Compactar e Descompactar)
===========================================

![License](https://img.shields.io/github/license/rafaelescaleira/huffman.svg)

Esse repositório possui funções implementadas em linguagem C.
Segue a lista das funções :

* Compressão;
* Descompressão;

Instruções para Compilação
--------------------------

Para compilar `` huffman.c `` utilizando `` main.c `` , ou seja, caso deseja compactar ou descompactar um arquivo :

* `` ~$ gcc huffman.c main.c -Wall -std=c99 -pedantic ``

Instruções para Execução
------------------------

Existe duas maneiras de executar o arquivo já compilado com `` main.c `` :

* Para compactar o arquivo :

	* `` ~$ ./a.out compactar (nome do arquivo a ser compactado) (nome do arquivo compactado) ``
	* Exemplo : `` ~$ ./a.out compactar frases.txt frases.zip ``

* Para descompactar o arquivo :

	* `` ~$ ./a.out descompactar (nome do arquivo a ser descompactado) (nome do arquivo descompactado) ``
	* Exemplo : `` ~$ ./a.out descompactar frases.zip frases.text ``
