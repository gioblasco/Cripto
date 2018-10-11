#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


// funções de tabela
void permutacao_inicial(unsigned char *hexa);
void divide_bloco(unsigned char *hexa, unsigned char *G, unsigned char *D);
unsigned char * expansao(unsigned char *D);

// funções auxiliares
unsigned char reverseBits(unsigned char num);
void print_bin(unsigned char num);
void atribui(unsigned char *v1, unsigned char *v2);

void main(){
    unsigned char entrada[8], chave[8], L[4], Lfinal[4], R[4], *E;

    // primeiro setando direto pra ver se os valores batem
    entrada[0] = 0x67;
    entrada[1] = 0x5A;
    entrada[2] = 0x69;
    entrada[3] = 0x67;
    entrada[4] = 0x5E;
    entrada[5] = 0x5A;
    entrada[6] = 0x6B;
    entrada[7] = 0x5A;

    /*
    for (int i = 0; i < 8; i++) {
        scanf("%2x", &entrada[i]);
    }
    */

    permutacao_inicial(entrada);
    divide_bloco(entrada, L, R);
    // round de 16 passos
    for(int i = 0; i < 16; i++){
      atribui(Lfinal, R);

      E = expansao(R);

      atribui(L, Lfinal);
    }
}

void permutacao_inicial(unsigned char *hexa){
/*
 *  PASSOS:
 *  1. aplicar a máscara em cada posição do vetor na ordem correta
 *  2. concatena o resultado de todas as posições com as máscaras
 *  no vetor resultante
 *      obs: para 'concatenar' os números, devemos fazer um | entre
 *      o número atual e o novo número (resultado da aplicação da
 *      máscara)
 */
    /*
        unsigned int mascara_1 = 128;
        unsigned int mascara_2 = 64;
        unsigned int mascara_3 = 32;
        unsigned int mascara_4 = 16;
        unsigned int mascara_5 = 8;
        unsigned int mascara_6 = 4;
        unsigned int mascara_7 = 2;
        unsigned int mascara_8 = 1;
    */

    unsigned char mascaras[8];   // mascaras de bit
    unsigned char permutado[8];  // vetor final
    int shift_counter[8];       // vetor de valores usados nos shifts.

    // ordem das linhas da tabela inicial para a tabela final.
    // 2,4,6,8,1,3,5,7
    static int ordem_permutacao[8] = {1,3,5,7,0,2,4,6};


    // mascaras inicializadas com potências de 2
    int j = 0;
    for (int i = 7; i >= 0; i--) {
        mascaras[j] = ceil(pow(2, i));
        j++;
    }

    j = 0;
    for (int i = 0; i > -8; i--) {
        shift_counter[j] = i;
        j++;
    }

    // vetor final inicializado com zeros
    for (int i = 0; i < 8; i++)
        permutado[i] = 0;

    printf("\nApos permutacao inicial:\n");
    for(int j = 0; j < 8; j++) {
        for(int i = 0; i < 8; i++) {
            if (shift_counter[ordem_permutacao[j]] < 0)
                permutado[j] |= ((hexa[i]&mascaras[ordem_permutacao[j]]) << abs(shift_counter[ordem_permutacao[j]]));
            else
                permutado[j] |= ((hexa[i]&mascaras[ordem_permutacao[j]]) >> shift_counter[ordem_permutacao[j]]);
            shift_counter[ordem_permutacao[j]]++;
        }
        permutado[j] = reverseBits(permutado[j]);
        printf("%2X ", permutado[j]);
    }
    // atribui valores a variavel de entrada
    atribui(hexa, permutado);

    printf("\n");
}

/* passos de cada round: https://br.ccm.net/contents/132-introducao-a-codificacao-des
https://www.nku.edu/~christensen/DESschneier.pdf

1. dividir o bloco de 64-bits (8 caracteres) iniciais em 2 blocos (de 32 bits) */
void divide_bloco(unsigned char *hexa, unsigned char *G, unsigned char *D){
  for(int i = 0; i < 4; i++){
    G[i] = 0;
    G[i] = hexa[i];
  }
  for(int j = 4; j < 8; j++){
    D[j] = 0;
    D[j] = hexa[j];
  }
}

/* 2. função de expansão: transforma 32 bits provenientes do vetor D e transforma em 48 bits */
unsigned char * expansao(unsigned char *D){
  for(int i = 0; i < 8; i++){

  }
}

/* 3. faz o deslocamento de chave (rotação)
de tal maneira que os bits em segunda posição tomam a primeira posição,
os em terceira posição a segunda, etc e os bits em primeira posição passam para a última posição.  */
void desloca_chave(unsigned char *chave){

}

/* 4. permutação CP-2 -> transforma 56 bits em 48 bits */
void *cp2(unsigned char *chave){

}

/* 5. XOR entre texto expandido e chave (ambos 48 bits) */
unsigned char * xor_primeiro(unsigned char *chave, unsigned char *E){

}

/* 6. passa a resultado proveniente do XOR pelas S-box */
unsigned int funcoes_selecao(unsigned char *chave){

  unsigned char mascarafim = 1, mascarainicio = 32, mascarameio = 30, posicao = 0;
  int res_sbox = 0, aux = 0;

  // tabelas constantes Sbox -> colocar lá no cabeçalho
  unsigned char S1[64] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                           0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                           4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                           15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };

  unsigned char S2[64] = { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                           3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                           0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                           13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };

  unsigned char S3[64] = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                           13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                           13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                           1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };

  unsigned char S4[64] = { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                           13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                           10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                           3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };

  unsigned char S5[64] = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                           14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                           4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                           11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };

  unsigned char S6[64] = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                           10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                           9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                           4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };

  unsigned char S7[64] = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                           13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                           1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                           6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };

  unsigned char S8[64] = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                           1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                           7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                           2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

  for(short int i = 1; i <= 8; i++){
    // posicao absoluta na lista da sbox com indice de linha e coluna calculado
    posicao = ((chave[i] & mascarafim) | ((chave[i] & mascarainicio) >> 4)) * 16 + ((chave[i] & mascarameio) >> 1) + 1;
    // cada bloco de 6 bits é substituído em um bloco de 4 bits
    switch(i){
      case 1:
        chave[i] = S1[posicao];
        aux = chave[i];
        aux <<= 28;
        res_sbox |= aux;
      break;
      case 2:
        chave[i] = S2[posicao];
        aux = chave[i];
        aux <<= 24;
        res_sbox |= aux;
      break;
      case 3:
        chave[i] = S3[posicao];
        aux = chave[i];
        aux <<= 20;
        res_sbox |= aux;
      break;
      case 4:
        chave[i] = S4[posicao];
        aux = chave[i];
        aux <<= 16;
        res_sbox |= aux;
      break;
      case 5:
        chave[i] = S5[posicao];
        aux = chave[i];
        aux <<= 12;
        res_sbox |= aux;
      break;
      case 6:
        chave[i] = S6[posicao];
        aux = chave[i];
        aux <<= 8;
        res_sbox |= aux;
      break;
      case 7:
        chave[i] = S7[posicao];
        aux = chave[i];
        aux <<= 4;
        res_sbox |= aux;
      break;
      case 8:
        chave[i] = S8[posicao];
        aux = chave[i];
        res_sbox |= aux;
      break;
    }
    posicao = 0;
  }

  return res_sbox;
}

/* 7. XOR entre L e resultado proveniente das S-box */
unsigned char * xor_ultimo(unsigned char *Linicial, unsigned char *S){

}

/* apos todas as iteracoes, é feita uma ultima permuta com os vetores G e D resultantes */
unsigned char * permutacao_reversa(unsigned char *G, unsigned char *D){

}



/*
 * função retirada de https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/
 */
unsigned char reverseBits(unsigned char num) {
    // sizeof é o tamanho em BYTESSSS
    unsigned char count = sizeof(num) * 8 - 1;
    unsigned char reverse_num = num;

    num >>= 1;
    while(num) {
        reverse_num <<= 1;
        reverse_num |= num & 1;     // 1 é o bit menos significativo
        num >>= 1;
        count--;
    }
    reverse_num <<= count;

    return reverse_num;
}

void print_bin(unsigned char num){
    int k;

    for(int c = 31; c > 0; c--) {
        k = num >> c;

        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

/* atribui o valor do vetor v2 para o vetor v1 */
void atribui(unsigned char *v1, unsigned char *v2){
  for(int i = 0; i < strlen(v1); i++){
    v1[i] = v2[i];
  }
}
