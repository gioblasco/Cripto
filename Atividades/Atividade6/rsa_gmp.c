#include<stdio.h>
#include<gmp.h>

int main(){
  FILE *fp;
  int base;
  mpz_t n, e, claro, cifrado;

  fp = fopen("./testes/Teste1_512_cripto.txt", "r");
  if(fp == NULL){
    printf("Nao foi possivel abrir o arquivo de entrada\n");
    return 0;
  }

  mpz_init(n);
  mpz_init(e);
  mpz_init(claro);
  mpz_init(cifrado);
  gmp_fscanf(fp, "%d\n%Zd\n%Zd\n%Zd\n%Zd", &base, &n, &e, &claro, &cifrado);

  fclose(fp);

  fp = fopen("decripto.txt", "w+");
  if(fp == NULL){
    printf("Nao foi possivel abrir o arquivo de saida\n");
    return 0;
  }

  gmp_fprintf(fp, "%d\n%Zd\n%Zd\n%Zd\n%Zd\n", base, n, e, claro, cifrado);

  fclose(fp);
  return 0;
}
