#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//tabela de Expansao
const unsigned char M[48] = {
            32, 1,  2,  3,  4,  5,
            4,  5,  6,  7,  8,  9,
            8,  9,  10, 11, 12, 13,
            12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21,
            20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29,
            28, 29, 30, 31, 32, 1
        };

// tabela PC1
const unsigned char PC_1[56] = {
                            57, 49, 41, 33, 25, 17, 9,
                            1, 58, 50, 42, 34, 26, 18,
                            10, 2, 59, 51, 43, 35, 27,
                            19, 11, 3, 60, 52, 44, 36,
                            63, 55, 47, 39, 31, 23, 15,
                            7, 62, 54, 46, 38, 30, 22,
                            14, 6, 61, 53, 45, 37, 29,
                            21, 13, 5, 28, 20, 12, 4
                        };

// tabela PC2
const unsigned char PC_2[48] = {
                            14, 17, 11, 24, 1, 5,
                            3, 28, 15, 6, 21, 10,
                            23, 19, 12, 4, 26, 8,
                            16, 7, 27, 20, 13, 2,
                            41, 52, 31, 37, 47, 55,
                            30, 40, 51, 45, 33, 48,
                            44, 49, 39, 56, 34, 53,
                            46, 42, 50, 36, 29, 32
                        };

const int tabela_shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// tabelas constantes Sbox
const unsigned char S1[64] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                               0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                               4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                               15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };

const unsigned char S2[64] = { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                               3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                               0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                               13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };

const unsigned char S3[64] = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                               13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                               13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                               1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };

const unsigned char S4[64] = { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                               13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                               10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                               3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };

const unsigned char S5[64] = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                               14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                               4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                               11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };

const unsigned char S6[64] = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                               10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                               9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                               4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };

const unsigned char S7[64] = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                               13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                               1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                               6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };

const unsigned char S8[64] = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                               1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                               7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                               2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

// tabela permutação dos rounds
unsigned char P[32] = { 16, 7, 20, 21, 29, 12, 28, 17,
                       1, 15, 23, 26, 5, 18, 31, 10,
                       2, 8, 24, 14, 32, 27, 3, 9,
                       19, 13, 30, 6, 22, 11, 4, 25};

// máscaras para a separação da chave em sub-chaves C e D
unsigned long long int mascara_D = 268435455;  //0000000000000000000000000000000000001111111111111111111111111111
unsigned long long int mascara_C = 72057593769492480; //0000000011111111111111111111111111110000000000000000000000000000

/* FUNÇÕES DE TABELA */
void permutacao_inicial(unsigned char *hexa);
void divide_bloco(unsigned char *hexa, unsigned char *G, unsigned char *D);
void expansao(unsigned char *D, unsigned char *E);
void permuted_choice_1(unsigned char *chave, unsigned char *pc_1);
void permuted_choice_2(unsigned char *chave, unsigned char *pc_2);
void xor_primeiro(unsigned char *chave, unsigned char *E, unsigned char *after_xor1);
void funcoes_selecao(unsigned char *chave, unsigned char *res);
void permuta_final(unsigned char *S, unsigned char *res_per);
void xor_ultimo(unsigned char *Linicial, unsigned char *P, unsigned char *after_xor2);
void swap(unsigned char *L, unsigned char *R, unsigned char *S);
void IP_inverso(unsigned char *G, unsigned char *D);

/* FUNÇÕES AUXILIARES */
void print_saida(unsigned char *vetor, short int tam);
void atribui(unsigned char *v1, unsigned char *v2, short int tam);
void desloca_chave(unsigned long long int *C, unsigned long long int *D, int round);
void divide_chave(unsigned char *chave, unsigned long long int *C, unsigned long long int *D);
void concatena_chave(unsigned char *chave, unsigned long long *C, unsigned long long *D);

int main(int argc, char **argv){
    unsigned char entrada[8], chave[8], L[4], Lfinal[4], R[4], E[6], pc_1[7], pc_2[6], res_xor1[6], res_sbox[4], res_permuta[4], res_xor2[4], texto[8], final[8];
    unsigned long long int C = 0, D = 0;
    FILE *entfile, *chavefile;

    if(argc != 3){
        printf("Chamada errada! Argumentos: ./des arquivo_texto arquivo_chave\n");
        return 0;
    }

    entfile = fopen(argv[1], "r");
    if(!entfile){
        printf("Erro ao abrir arquivo de entrada!");
    }
    for (int i = 0; i < 8; i++) {
        fscanf(entfile, "%2hhx", &entrada[i]);
    }
    fclose(entfile);

    chavefile = fopen(argv[2], "r");
    if(!chavefile){
        printf("Erro ao abrir arquivo da chave!");
    }
    for (int i = 0; i < 8; i++) {
        fscanf(chavefile, "%2hhx", &chave[i]);
    }
    fclose(chavefile);


    printf("PLAIN TEXT\n");
    print_saida(entrada, 8);

    permutacao_inicial(entrada);
    printf("\nIP\n");
    print_saida(entrada, 8);
    atribui(texto, entrada, 8);

    printf("\nCHAVE\n");
    print_saida(chave, 8);

    permuted_choice_1(chave, pc_1);

    printf("\nPC1 - SELECIONA CHAVE\n");
    print_saida(pc_1, 7);
    divide_chave(pc_1, &C, &D);

    atribui(texto, entrada, 8);

    // round de 16 passos
    for(int i = 0; i < 16; i++){
        divide_bloco(texto, L, R);
        atribui(Lfinal, R, 4);

        printf("\nCHAVE DE ROUND %d\n", i+1);
        printf("Deslocamento: ");
        desloca_chave(&C, &D, i);
        concatena_chave(pc_1, &C, &D);
        print_saida(pc_1, 7);

        permuted_choice_2(pc_1, pc_2);
        printf("PC2: ");
        print_saida(pc_2, 6);
        print_saida(pc_2, 6);

        printf("\nROUND %d\n", i+1);

        print_saida(texto, 8);
        expansao(R, E);
        printf("Expansao: ");
        print_saida(E, 6);
        xor_primeiro(pc_2, E, res_xor1);
        printf("Add Key: ");
        print_saida(res_xor1, 6);
        funcoes_selecao(res_xor1, res_sbox);
        printf("S-Box: ");
        print_saida(res_sbox, 4);
        permuta_final(res_sbox, res_permuta);
        printf("Permuta: ");
        print_saida(res_permuta, 4);
        xor_ultimo(L, res_permuta, res_xor2);
        printf("Add Left: ");
        print_saida(res_xor2, 4);

        atribui(R, res_xor2, 4);
        atribui(L, Lfinal, 4);

        swap(R, L, texto);
        print_saida(texto, 8);
    }

    swap(L, R, texto);
    printf("\nSwap: ");
    print_saida(texto, 8);

    IP_inverso(texto, final);
    printf("\nIP Inverso: ");
    print_saida(final, 8);

    return 0;
}

void permutacao_inicial(unsigned char *hexa){
    unsigned char permutado[8];  // vetor final
    int k, l;

    // vetor final inicializado com zeros
    for (int i = 0; i < 8; i++)
        permutado[i] = 0;

    for (int j = 0; j < 4; j++){
      k = j*2;
      l = 0;
      for(int i = 7; i >= 0; i--){
        permutado[j+4] |= ((hexa[i]&(128>>k)) << k) >> l;
        permutado[j] |= ((hexa[i]&(128>>(k+1))) << (k+1)) >> l;
        l++;
      }
    }

    // atribui valores a variavel de entrada
    atribui(hexa, permutado, 8);
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

/* 2. função de expansão: transforma 32 bits provenientes do vetor D em 48 bits */
void expansao(unsigned char *D, unsigned char *E){
    unsigned char expandido[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int mascara[8] = {1, 128, 64, 32, 16, 8, 4, 2};
    unsigned char temp_bit;
    int shift_counter, j = 0;

    for (int i = 0; i < 6; i++) {
        for (shift_counter = 7; shift_counter >= 0; shift_counter--) {
            // D[M([j]-1)/8] faz a conversão da tabela fixa de bits M para a 
            // posição do vetor D. 
            // por exemplo, se M[j] = 32, o bit deve ser da posição D[3], que
            // contém os últimos 8 bits.
            temp_bit = (D[(M[j]-1)/8] & mascara[M[j]%8]);
            if (temp_bit > 0)
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
    unsigned char temp_bit = 0;
    unsigned char permutado[7] = {0, 0, 0, 0, 0, 0, 0};
    int shift_counter, j = 0;

    for (int i = 0; i < 7; i++) {
        for (shift_counter = 7; shift_counter >= 0; shift_counter--) {
            temp_bit = chave[(PC_1[j]-1)/8] & 128 >> ((PC_1[j]-1)%8);
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
    int shift = tabela_shift[round];
    unsigned long long temp_C, temp_D;
    unsigned long long int novo_bit_C = 0;
    unsigned long long int novo_bit_D = 0;
    // separa o bit mais significativo de cada meia-chave
    unsigned long long int msb_D = 134217728;
    unsigned long long int msb_C = 36028797018963968;

    for (int i = 0; i < tabela_shift[round]; i++){
        // aplicar a máscara pra pegar o bit mais significativo
        novo_bit_C = *C & msb_C;
        novo_bit_D = *D & msb_D;

        temp_C = (*C << 1) & mascara_C;
        temp_D = (*D << 1) & mascara_D;

        // inserir o bit no final para que o shift seja circular
        if (novo_bit_C > 0)
            novo_bit_C = 1 << 28;

        if(novo_bit_D > 0)
            novo_bit_D  = 1;

        *C = temp_C | novo_bit_C;
        *D = temp_D | novo_bit_D;
    }
}

/* 4. permutação PC-2 -> transforma 56 bits em 48 bits */
void permuted_choice_2(unsigned char *chave, unsigned char *pc_2){
    unsigned char temp_bit = 0;
    unsigned char permutado[6] = {0, 0, 0, 0, 0, 0};
    int shift_counter, j = 0;

    for (int i = 0; i < 6; i++) {
        for (shift_counter = 7; shift_counter >= 0; shift_counter--) {
            temp_bit = chave[(PC_2[j]-1)/8] & 128 >> ((PC_2[j]-1)%8);
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
void xor_primeiro(unsigned char *chave, unsigned char *E, unsigned char *after_xor1){
  for(int i = 0; i < 6; i++){
    after_xor1[i] = chave[i] ^ E[i];
  }
}

/* 6. passa a resultado proveniente do XOR pelas S-box */
void funcoes_selecao(unsigned char *xor, unsigned char *res_sbox){
  unsigned char posicao = 0, aux = 0;
  for(short int i=0; i < 4; i++){
    res_sbox[i] = 0;
  }

  // final | inicial + meio
  posicao = (((xor[0] & 4) >> 2) | ((xor[0] & 128) >> 6)) * 16 + ((xor[0] & 120) >> 3);
  res_sbox[0] |= S1[posicao] << 4;

  posicao = (((xor[1] & 16) >> 4) | (xor[0] & 2)) * 16 + (((xor[1] & 224) >> 5) | ((xor[0] & 1) << 3));
  res_sbox[0] |= S2[posicao];

  posicao = (((xor[2] & 64) >> 6) | ((xor[1] & 8) >> 2)) * 16 + (((xor[2] & 128) >> 7) | ((xor[1] & 7) << 1));
  res_sbox[1] |= S3[posicao] << 4;

  posicao = ((xor[2] & 1) | ((xor[2] & 32) >> 4)) * 16 + ((xor[2] & 30) >> 1);
  res_sbox[1] |= S4[posicao];

  posicao = (((xor[3] & 4) >> 2) | ((xor[3] & 128) >> 6)) * 16 + ((xor[3] & 120) >> 3);
  res_sbox[2] |= S5[posicao] << 4;

  posicao = (((xor[4] & 16) >> 4) | (xor[3] & 2)) * 16 + (((xor[4] & 224) >> 5) | ((xor[3] & 1) << 3));
  res_sbox[2] |= S6[posicao];

  posicao = (((xor[5] & 64) >> 6) | ((xor[4] & 8) >> 2)) * 16 + (((xor[5] & 128) >> 7) | ((xor[4] & 7) << 1));
  res_sbox[3] |= S7[posicao] << 4;

  posicao = ((xor[5] & 1) | ((xor[5] & 32) >> 4)) * 16 + ((xor[5] & 30) >> 1);
  res_sbox[3] |= S8[posicao];
}

// Permuta
void permuta_final(unsigned char *S, unsigned char *res_per){
  unsigned char aux = 0;
  for(int i = 0; i < 4; i++){
    res_per[i] = 0;
  }
  for(int i = 0; i < 32; i++){
    //128 = 10000000b
    aux = S[(P[i]-1)/8] & (128 >> ((P[i]-1)%8));
    aux <<= ((P[i]-1)%8);

    res_per[i/8] |= (aux >> i%8);
  }
}

/* 7. XOR entre L e resultado proveniente da permuta final */ // Add Left
void xor_ultimo(unsigned char *Linicial, unsigned char *P, unsigned char *after_xor2){
  for(int i = 0; i < 4; i++){
    after_xor2[i] = Linicial[i] ^ P[i];
  }
}

//L vai para o lugar do R e R vai para o lugar do L -> funciona tanto como swap, como para transformar os dois vetores em 1
void swap(unsigned char *L, unsigned char *R, unsigned char *S){
  for(int i = 0; i<4; i++){
    S[i] = R[i];
    S[i+4] = L[i];
  }
}

/* apos todas as iteracoes, é feita uma ultima permuta com os vetores G e D resultantes */
void IP_inverso(unsigned char *C, unsigned char *F){
  int k = 7, l;

  for (int i = 0; i < 8; i++)
      F[i] = 0;

  for(int j = 0; j < 8; j++){
    l = 0;
    for(int i = 0; i < 4; i++){
      F[k] |= ((C[i+4]&(128>>j)) << j) >> l;
      l++;
      F[k] |= ((C[i]&(128>>j)) << j) >> l;
      l++;
    }
    k--;
  }

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
  printf("\n");
}


/* divide chave para o PC2 */
void divide_chave (unsigned char *chave, unsigned long long int *C, unsigned long long *D){
    unsigned long long chave_int = 0;

    chave_int = (unsigned long long) chave[0] << 48 |
                (unsigned long long) chave[1] << 40 |
                (unsigned long long) chave[2] << 32 |
                (unsigned long long) chave[3] << 24 |
                (unsigned long long) chave[4] << 16 |
                (unsigned long long) chave[5] << 8  |
                (unsigned long long) chave[6];


    *C = chave_int & mascara_C;
    *D = chave_int & mascara_D;
}

/* concatena as chaves separadas e faz o cast para o PC2 */
void concatena_chave (unsigned char *chave, unsigned long long *C, unsigned long long *D){
    unsigned long long chave_concatenada = 0;
    unsigned char chave_temp[8];

    chave_concatenada = *C | *D;

    int j = 0;
    for (int i = 6; i >= 0; i--) {
        chave[j] = (chave_concatenada >> 8*i) & 0xFF;
        j++;

    }
}
