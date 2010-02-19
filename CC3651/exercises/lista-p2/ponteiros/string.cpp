/**
 *  Author: wesley
 *  
 * 09 - Faça uma função que verifique se a expressão apontada por substr está
 * presente na cadeia apontada por str. A função possui o protótipo abaixo:
 *      int posicao(char *substr, char *str);
 * e retorna a posição em que a sub-cadeia aparece em cadeia.
 *  
 * Código devidamete chupinhado do exercício 9 (que coincidência!) da lista
 * para a P2 (denovo!) da matéria CC2621 do semestre passado, esboçando a
 * técnica de reaproveitamento de código.
 * 
 * http://github.com/blabos/CC3651/commit/5588edef480301c0a9caebfe9307aa62f36aa8c5
 */

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
