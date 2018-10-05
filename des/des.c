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
unsigned int * xor_primeiro(unsigned char *chave, unsigned char *E){

}

/* 6. passa a chave proveniente do XOR pelas S-box */
unsigned char * funcoes_selecao(unsigned char *chave){

}

/* 7. XOR entre L e chave proveniente das S-box (ambos 48 bits) */
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
