/* compilar com -lgmp */

#include<stdio.h>
#include<gmp.h>

int main(){
  int base;
  mpz_t n, expo, claro, cifrado;

  scanf("%d", &base);
  mpz_inits(n, expo, claro, cifrado, NULL);
  if(base == 10){
    gmp_scanf("%Zd\n%Zd\n%Zd", &n, &expo, &claro);
  } else {
    gmp_scanf("%Zx\n%Zx\n%Zx", &n, &expo, &claro);
  }

  mpz_powm_sec(cifrado, claro, expo, n);

  gmp_printf("Texto cifrado ou decifrado decimal:\n%Zd\n\n", cifrado);
  gmp_printf("Texto cifrado ou decifrado hexa:\n%Zx\n\n", cifrado);

  return 0;
}
