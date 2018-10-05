#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* TODO:
 *
 *  1. Fazer a permutação inicial
 *      bits pares para a metade esquerda
 *      bits ímpares para a metade direita
 *
 */

// funções de tabela
void permutacao_inicial(unsigned int *hexa);
void divide_bloco(unsigned int *hexa, unsigned int *G, unsigned int *D);
unsigned int * expansao(unsigned int *D);

// funções auxiliares
void printa_vetor(char *nome, void *vetor, int flag_unsigned);
unsigned int reverseBits(unsigned int num);

void main(){
    unsigned int entrada[8], chave[8], L[4], Lfinal[4], R[4], *E;

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
      Lfinal = R;
      E = expansao(R);




      L = Lfinal;
    }
}

/*
 *  montar um vetor de unsigned int onde cada posição representa
 *  um número em hexa
 *
 *  1. aplicar a máscara em cada posição do vetor na ordem correta
 *      (2, 4, 6, 8, 1, 3, 5  7)
 *
 *  2. concatena o resultado de todas as posições com as máscaras
 *  no vetor resultante
 *
 *  para 'concatenar' os números, devemos fazer um | entre
 *  o número atual e o novo número (resultado da aplicação da
 *  máscara)
 */
void permutacao_inicial(unsigned int *hexa){
    /*
        // máscaras
        unsigned int mascara_1 = 128;
        unsigned int mascara_2 = 64;
        unsigned int mascara_3 = 32;
        unsigned int mascara_4 = 16;
        unsigned int mascara_5 = 8;
        unsigned int mascara_6 = 4;
        unsigned int mascara_7 = 2;
        unsigned int mascara_8 = 1;
    */

    unsigned int mascaras[8];   // mascaras de bit
    unsigned int permutado[8];  // vetor final
    int shift_counter[8];       // vetor de valores usados nos shifts.

    // ordem das linhas da tabela inicial para a tabela final. o certo seria 2,4,6,8,1,3,5,7,
    // mas como o índice começa em 0, eu tirei 1 de cada posição
    static int ordem_permutacao[8] = {1,3,5,7,0,2,4,6};


    // inicialização dos vetores
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

    printf("\n\nApos permutacao inicial:\n");
    for(int j = 0; j < 8; j++) {
        for(int i = 0; i < 8; i++) {
            if (shift_counter[ordem_permutacao[j]] < 0)
                permutado[j] |= ((hexa[i]&mascaras[ordem_permutacao[j]]) << abs(shift_counter[ordem_permutacao[j]]));
            else
                permutado[j] |= ((hexa[i]&mascaras[ordem_permutacao[j]]) >> shift_counter[ordem_permutacao[j]]);
            shift_counter[ordem_permutacao[j]]++;
        }
        permutado[j] = reverseBits(permutado[j]);
        printf("%4X ", permutado[j]);
        /* se fizer:
        hexa[j] = reverseBits(permutado[j]);
        printf("%4X ", hexa[j]);

        hexa ta ficando com valores finais errados, diferentes do permutado.
        n entendi nada
        */
    }
    printf("\n");
}

/* passos de cada round: https://br.ccm.net/contents/132-introducao-a-codificacao-des
https://www.nku.edu/~christensen/DESschneier.pdf

1. dividir o bloco de 64-bits (8 caracteres) iniciais em 2 blocos (de 32 bits) */
void divide_bloco(unsigned int *hexa, unsigned int *G, unsigned int *D){
  for(int i = 0; i < 4; i++)
    G[i] = hexa[i];
  for(int i = 4; i < 8; i++)
    D[i] = hexa[i];
}

/* 2. função de expansão: transforma 32 bits provenientes do vetor D e transforma em 48 bits */
unsigned int * expansao(unsigned int *D){
  for(int i = 0; i < 8; i++){

  }
}

/* 3. faz o deslocamento de chave (rotação)
de tal maneira que os bits em segunda posição tomam a primeira posição,
os em terceira posição a segunda, etc e os bits em primeira posição passam para a última posição.  */
void desloca_chave(unsigned int *chave){

}

/* 4. permutação CP-2 -> transforma 56 bits em 48 bits */
void *cp2(unsigned int *chave){

}

/* 5. XOR entre texto expandido e chave (ambos 48 bits) */
unsigned int * xor_primeiro(unsigned int *chave, unsigned int *E){

}

/* 6. passa a chave proveniente do XOR pelas S-box */
unsigned int * funcoes_selecao(unsigned int *){

}

/* 7. XOR entre L e chave proveniente das S-box (ambos 48 bits) */
unsigned int * xor_ultimo(unsigned int *Linicial, unsigned int *S){

}

/* apos todas as iteracoes, é feita uma ultima permuta com os vetores G e D resultantes */
unsigned int * permutacao_reversa(unsigned int *G, unsigned int *D){

}



/*
 * função retirada de https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/
 */
unsigned int reverseBits(unsigned int num) {
    // sizeof é o tamanho em BYTESSSS
    unsigned int count = sizeof(num) * 8 - 1;
    unsigned int reverse_num = num;

    num >>= 1;
    while(num)
    {
        reverse_num <<= 1;
        reverse_num |= num & 1;     // 1 é o bit menos significativo
        num >>= 1;
        count--;
    }
    reverse_num <<= count;
    return reverse_num;
}
