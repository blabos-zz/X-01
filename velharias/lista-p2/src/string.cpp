/*
 * string.cpp
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */
#include "../include/string.h"

/**
 * Calcula o comprimento de uma string.
 * 
 * @param const char* String.
 * 
 * @return int Comprimento da string.
 */
int strlen(const char* str) {
	int length = 0;
	while (str[length] != '\0') length++;
	
	return length;
}

/**
 * Copia uma string src para uma outra string dest.
 * 
 * @param char* String destino.
 * @param const char* String origem.
 */
void strcpy(char* dest, const char* src) {
	substr(dest, src, 0, strlen(src));
}

/**
 * Concatena uma string src no final de uma string dest, checando os
 * limites máximos.
 * 
 * @param char* String destino.
 * @param const char* String origem.
 */
void strcat(char* dest, const char* src) {
	int dlen = strlen(dest);
	int slen = strlen(src);
	
	int i = dlen;
	int j = 0;
	
	while ((i < (STR_MAX_LEN - 1)) && (j < slen)) {
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
}

/**
 * Copia count caracteres partir da posição from da string orig para a string
 * sub. Checa os limites máximos.
 * 
 * @param char* Sub-string destino.
 * @param const char* String original.
 * @param int Posição a partir da qual começa a copiar.
 * @prama int Quantidade de caracteres a ser copiada.
 */
void substr(char* sub, const char* orig, int from, int count){
	int i = 0;
	int j = from;
	int olen = strlen(orig);
	
	int max = STR_MAX_LEN - from;
	max = count > max ? max : count;
	
	while ((i < (STR_MAX_LEN - 1)) && (j < olen) && (i < max)) {
		sub[i++] = orig[j++];
	}
	sub[i] = '\0';
}

/**
 * Remove os count caracteres da string str, a partir da posição pos.
 * 
 * @param char* A string original.
 * @param int A posição a partir da qual começa a remover.
 * @param int A quantidade de caracteres a ser removida.
 */
void erase(char* str, int pos, int count) {
	int len = strlen(str);
	int i = pos;
	int j = pos + count;
	while ((str[j] != '\0') && (j < len)) {
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

/**
 * Procura em str pela primeira ocorrência do caracter ch.
 * 
 * @param const char* String onde procurar.
 * @param char Caracter a ser encontrado.
 * 
 * @return int A posição do caracter encontrado ou -1 se não encontrar.
 */
int find(const char* str, char ch) {
	int i = 0;
	while ((i < (STR_MAX_LEN - 1)) && (str[i] != ch)) i++;
	
	return i < (STR_MAX_LEN - 1) ? i : -1;
}

/**
 * Procura em str pela última ocorrência do caracter ch.
 * 
 * @param const char* String onde procurar.
 * @param char Caracter a ser encontrado.
 * 
 * @return int A posição do caracter encontrado ou -1 se não encontrar.
 */
int rfind(const char* str, char ch) {
	int i = strlen(str) - 1;
	
	while ((i >= 0) && (str[i] != ch)) i--;
	
	return i;
}

/**
 * Procura a primeira ocorrência de word dentro de phrase.
 * 
 * @param const char* A frase onde procurar.
 * @param const char* O texto a procurar.
 * 
 * @return a posição do primeiro caracter do texto encontrado ou -1 se não
 * encontrar.
 */
int findstr(const char* phrase, const char* word) {
	int phlen = strlen(phrase);
	int wrlen = strlen(word);
	int i = -1;
	
	while (i < (phlen - wrlen)) {
		i++;
		int j = 0;
		while ((phrase[i] == word[j]) && (j < wrlen)) {
			i++;
			j++;
		}
		if (j == wrlen) return i - j;
	}
	
	return -1;
}

/**
 * Preenche a string str com até count caracteres ch. Adiciona um caracter
 * nulo na última posição possível da string. checa os limites máximos.
 * 
 * @param char* String a ser preenchida.
 * @param char Caracter utilizado para preenchimento. Opcional. Default espaço.
 * @param char Quandidade de caracteres. Opcional. Default STR_MAX_LEN.
 */
void strpad(char* str, char ch, int count) {
	int i = 0;
	while ((i < (STR_MAX_LEN - 1)) && (i < count)) {
		str[i++] = ch;
	}
	
	str[i] = '\0';
}
