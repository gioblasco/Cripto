#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
 unsigned char E[48] = {
                    0x20, 0x01, 0x02, 0x03, 0x04, 0x05,
                    0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
                    0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                    0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
                    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
                    0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x01
                };
*/

// funções de tabela
void permutacao_inicial(unsigned char *hexa);
void divide_bloco(unsigned char *hexa, unsigned char *G, unsigned char *D);
void expansao(unsigned char *D, unsigned char *E);
void permuted_choice_1(unsigned char *chave, unsigned char *pc_1);
void permuted_choice_2(unsigned char *chave, unsigned char *pc_2);
//void permuted_choice_2(unsigned char *chave);

// funções auxiliares
void print_bin(unsigned char num);
void print_saida(unsigned char *vetor, short int tam);
void atribui(unsigned char *v1, unsigned char *v2, short int tam);
void desloca_chave(unsigned long long int *C, unsigned long long int *D, int round);
void divide_chave (unsigned char *chave, unsigned long long int *C, unsigned long long int *D);
void concatena_chave (unsigned char *chave, unsigned long long *C, unsigned long long *D);
unsigned char reverseBits(unsigned char num);

void main(){
    unsigned char entrada[8], chave[8], L[4], Lfinal[4], R[4], E[6], pc_1[7], pc_2[6];
    unsigned long long int C, D;

    // primeiro setando direto pra ver se os valores batem
    entrada[0] = 0x69;
    entrada[1] = 0x6E;
    entrada[2] = 0x74;
    entrada[3] = 0x72;
    entrada[4] = 0x6F;
    entrada[5] = 0x64;
    entrada[6] = 0x75;
    entrada[7] = 0x63;

    /*
    for (int i = 0; i < 8; i++) {
        scanf("%2hhx", &entrada[i]);
    }
    */

    printf("PLAIN TEXT\n");
    print_saida(entrada, 8);

    permutacao_inicial(entrada);

    chave[0] = 0x31;
    chave[1] = 0x32;
    chave[2] = 0x33;
    chave[3] = 0x34;
    chave[4] = 0x35;
    chave[5] = 0x36;
    chave[6] = 0x37;
    chave[7] = 0x38;

    /*
    for (int i = 0; i < 8; i++) {
        scanf("%2hhx", &chave[i]);
    }
    */

    xor_primeiro(entrada, chave, Lfinal);

    printf("CHAVE\n");
    print_saida(chave, 8);

    divide_bloco(entrada, L, R);
    permuted_choice_1(chave, pc_1);

    printf("PC-1 - SELECIONA CHAVE\n");
    print_saida(pc_1, 7);
    divide_chave(pc_1, &C, &D);

    // round de 16 passos
    for(int i = 0; i < 1; i++){
        printf("CHAVE DE ROUND %d\n", i+1);
        printf("Deslocamento: ");
        desloca_chave(&C, &D, i);
        concatena_chave(pc_1, &C, &D);
        print_saida(pc_1, 7);

        permuted_choice_2(pc_1, pc_2);
        printf("PC2: ");
        print_saida(pc_2, 6);
        atribui(Lfinal, R, 4);

        printf("ROUND %d\n", i+1);

        expansao(R, E);
        printf("Expansao: ");
        print_saida(E, 6);    
        atribui(L, Lfinal, 4);
        // printf("Add Key: ");
        // printf("S-Bbox: ");
        // printf("Permuta: ");
        // printf("Add Left ");
    }
}

void permutacao_inicial(unsigned char *hexa){
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

    for(int j = 0; j < 8; j++) {
        for(int i = 0; i < 8; i++) {
            if (shift_counter[ordem_permutacao[j]] < 0)
                permutado[j] |= ((hexa[i]&mascaras[ordem_permutacao[j]]) << abs(shift_counter[ordem_permutacao[j]]));
            else
                permutado[j] |= ((hexa[i]&mascaras[ordem_permutacao[j]]) >> shift_counter[ordem_permutacao[j]]);
            shift_counter[ordem_permutacao[j]]++;
        }
        permutado[j] = reverseBits(permutado[j]);
    }
    // atribui valores a variavel de entrada
    atribui(hexa, permutado, 8);

    printf("IP\n");
    print_saida(hexa, 8);
}

/* passos de cada round: https://br.ccm.net/contents/132-introducao-a-codificacao-des
https://www.nku.edu/~christensen/DESschneier.pdf

1. dividir o bloco de 64-bits (8 caracteres) iniciais em 2 blocos (de 32 bits) */
void divide_bloco(unsigned char *hexa, unsigned char *G, unsigned char *D){
  for(int i = 0; i < 4; i++){
    G[i] = 0;
    G[i] = hexa[i];
    D[i] = 0;
    D[i] = hexa[i+4];
  }
}

/* 2. função de expansão: transforma 32 bits provenientes do vetor D e transforma em 48 bits */
void expansao(unsigned char *D, unsigned char *E){
    unsigned char M[48] = {
                32, 1,  2,  3,  4,  5,
                4,  5,  6,  7,  8,  9,
                8,  9,  10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32, 1
            };
    unsigned char expandido[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int mascara[8] = {1, 128, 64, 32, 16, 8, 4, 2};
    unsigned char temp_bit;
    int shift_counter, j = 0;

    // printf("Entrada para expansão:\n");
    // print_saida(D, 4);

    for (int i = 0; i < 6; i++) {
        for (shift_counter = 7; shift_counter >= 0; shift_counter--) {
            temp_bit = (D[(M[j]-1)/8] & mascara[M[j]%8]);
            if (temp_bit != 0)
                temp_bit = 1 << shift_counter;
            else
                temp_bit = 0 << shift_counter;
            expandido[i] |= temp_bit;
            j++;
        }
        E[i] = expandido[i];
    }
}

/* 3. permutação inicial de chave (PC-1) 
 *  seleciona 56 bits da chave de 64 e divide em 2 blocos
 *  de 28 bits.
 */
void permuted_choice_1(unsigned char *chave, unsigned char *pc_1){
    unsigned char PC_1[56] = {
                                57, 49, 41, 33, 25, 17, 9, 
                                1, 58, 50, 42, 34, 26, 18, 
                                10, 2, 59, 51, 43, 35, 27, 
                                19, 11, 3, 60, 52, 44, 36,
                                63, 55, 47, 39, 31, 23, 15, 
                                7, 62, 54, 46, 38, 30, 22,
                                14, 6, 61, 53, 45, 37, 29, 
                                21, 13, 5, 28, 20, 12, 4 
                            };

    
    unsigned char temp_bit = 0;
    unsigned char permutado[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int mascara[8] = {256, 128, 64, 32, 16, 8, 4, 2};
    int shift_counter, j = 0;

    for (int i = 0; i < 7; i++) {
        for (shift_counter = 7; shift_counter >= 0; shift_counter--) {
            temp_bit = (chave[(PC_1[j]-1)/8] & mascara[PC_1[j]%8]);
            if (temp_bit != 0)
                temp_bit = 1 << shift_counter;
            else
                temp_bit = 0 << shift_counter;
            permutado[i] |= temp_bit;
            j++;
        }
        pc_1[i] = permutado[i];
    }
}

/* 3.1 deslocamento de chave -> desloca a chave de acordo com a tabela */
void desloca_chave(unsigned long long int *C, unsigned long long int *D, int round){
    int tabela_shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    int shift = tabela_shift[round];
    unsigned long long int novo_bit_C;
    unsigned long long int novo_bit_D;
    // separa o bit mais significativo de cada meia-chave
    unsigned long long int msb_C = 134217728;
    unsigned long long int msb_D = 9007199254740992;
    // máscaras para a separação da chave
    unsigned long long mascara_D = 268435455; 
    unsigned long long mascara_C = 72057593769492480;

    for (int i = 0; i < tabela_shift[round]; i++){
        // aplicar a máscara pra pegar o bit mais significativo
        novo_bit_C = *C & msb_C;
        novo_bit_C = *D & msb_D;

        printf("\n");
        printf("novo_bit_C: %llx\nnovo_bit_D: %llx\n", novo_bit_C, novo_bit_D); 
        
        printf("C: %llx\n", *C); 
        printf("D: %llx\n", *D); 
        *C = (*C << 1) & mascara_C;
        *D = (*D << 1) & mascara_D;
        printf("C: %llx\n", *C); 
        printf("D: %llx\n", *D); 
        
        // inserir o bit no final para que o shift seja circular
        if (novo_bit_C > 0)
            novo_bit_C = 1;
         
        if(novo_bit_D > 0) 
            novo_bit_D  = 1;
        
        *C |= novo_bit_C;
        *D |= novo_bit_D;
        printf("C: %llx\n", *C); 
        printf("D: %llx\n", *D); 
    }
}

/* 4. permutação PC-2 -> transforma 56 bits em 48 bits */
void permuted_choice_2(unsigned char *chave, unsigned char *pc_2){
    unsigned char PC_2[48] = {
                                14, 17, 11, 24, 1, 5, 
                                3, 28, 15, 6, 21, 10, 
                                23, 19, 12, 4, 26, 8, 
                                16, 7, 27, 20, 13, 2, 
                                41, 52, 31, 37, 47, 55, 
                                30, 40, 51, 45, 33, 48, 
                                44, 49, 39, 56, 34, 53, 
                                46, 42, 50, 36, 29, 32
                            };
    unsigned char temp_bit = 0;
    unsigned char permutado[6] = {0, 0, 0, 0, 0, 0};
    unsigned int mascara[8] = {256, 128, 64, 32, 16, 8, 4, 2};
    int shift_counter, j = 0;

    for (int i = 0; i < 6; i++) {
        for (shift_counter = 7; shift_counter >= 0; shift_counter--) {
            temp_bit = (chave[(PC_2[j]-1)/8] & mascara[PC_2[j]%8]);
            if (temp_bit != 0)
                temp_bit = 1 << shift_counter;
            else
                temp_bit = 0 << shift_counter;
            permutado[i] |= temp_bit;
            j++;
        }
        pc_2[i] = permutado[i];
    }
}

/* 5. XOR entre texto expandido e chave (ambos 48 bits) */
void * xor_primeiro(unsigned char *chave, unsigned char *E, unsigned char *after_xor1){
  unsigned char c[8] = { 0x50, 0x2C, 0xAC, 0x57, 0x2A, 0xC2 };
  unsigned char ex[8] = { 0x00, 0x17, 0xFE, 0x8A, 0x7C, 0xF4 };
  for(int i = 0; i < 6; i++){
    after_xor1[i] = c[i] ^ ex[i];
  }
}

/* 6. passa a resultado proveniente do XOR pelas S-box */
unsigned char * funcoes_selecao(unsigned char *chave){

  unsigned char mascarafim = 1, mascarainicio = 32, mascarameio = 30, posicao = 0, aux = 0, res_sbox[4];

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

  for(short int i=0; i < 4; i++){
    res_sbox[i] = 0;
  }

  for(short int i = 0; i < 8; i++){
    // posicao absoluta na lista da sbox com indice de linha e coluna calculado
    posicao = ((chave[i] & mascarafim) | ((chave[i] & mascarainicio) >> 4)) * 16 + ((chave[i] & mascarameio) >> 1) + 1;
    // cada bloco de 6 bits é substituído em um bloco de 4 bits
    switch(i){
      case 0:
        chave[i] = S1[posicao];
      break;
      case 1:
        chave[i] = S2[posicao];
      break;
      case 2:
        chave[i] = S3[posicao];
      break;
      case 3:
        chave[i] = S4[posicao];
      break;
      case 4:
        chave[i] = S5[posicao];
      break;
      case 5:
        chave[i] = S6[posicao];
      break;
      case 6:
        chave[i] = S7[posicao];
      break;
      case 7:
        chave[i] = S8[posicao];
      break;
    }
    aux = chave[i];
    if(i%2 == 0){
      aux <<= 4;
    }
    res_sbox[i/2] |= aux;
    posicao = 0;
  }

 // return res_sbox;
}

/* 7. XOR entre L e resultado proveniente das S-box */
unsigned char * xor_ultimo(unsigned char *Linicial, unsigned char *S){
  unsigned char res_xor[4];

  for(int i = 0; i < 4; i++){
    res_xor[i] = Linicial[i] ^ S[i];
  }

//  return res_xor;
}

/* apos todas as iteracoes, é feita uma ultima permuta com os vetores G e D resultantes */
unsigned char * permutacao_reversa(unsigned char *G, unsigned char *D){
  unsigned char P[32] = { 16, 7, 20, 21, 29, 12, 28, 17,
                          1, 15, 23, 26, 5, 18, 31, 10,
                          2, 8, 24, 14, 32, 27, 3, 9,
                          19, 13, 30, 6, 22, 11, 4, 25};
}



/* função retirada de https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/ */
unsigned char reverseBits(unsigned char num) {
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
void atribui(unsigned char *v1, unsigned char *v2, short int tam){
  for(short int i = 0; i < tam; i++){
    v1[i] = v2[i];
  }
}

/* printa as posições do vetor em hexa */
void print_saida(unsigned char *vetor, short int tam){
  for(short int i = 0; i < tam; i++)
    printf("%02X ", vetor[i]);
  printf("\n\n");
}


/* divide chave para o PC2 */
void divide_chave (unsigned char *chave, unsigned long long int *C, unsigned long long *D){
    unsigned long long chave_int = 0;
    unsigned long long mascara_D, mascara_C;

    chave_int = (unsigned long long) chave[0] << 48 | 
                (unsigned long long) chave[1] << 40 | 
                (unsigned long long) chave[2] << 32 |
                (unsigned long long) chave[3] << 24 |
                (unsigned long long) chave[4] << 16 |
                (unsigned long long) chave[5] << 8  |
                (unsigned long long) chave[6];

    // printf("chave unsigned int: ");
    // printf("%02llX\n", chave_int);

    // máscaras para a separação da chave
    mascara_D = 268435455; 
    mascara_C = 72057593769492480;

    *C = chave_int & mascara_C;
    *D = chave_int & mascara_D;
}

/* concatena as chaves separadas e faz o cast para o PC2 */
void concatena_chave (unsigned char *chave, unsigned long long *C, unsigned long long *D){
    unsigned long long chave_concatenada = 0;

    chave_concatenada = *C | *D;
    
    chave = (unsigned char *)&chave[7];
}
