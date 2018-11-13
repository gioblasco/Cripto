#include<stdio.h>

void eea(long long int r0, long long int r1, long long int *ri, long long int *inv);
void qem(long long int X, long long int k, long long int N, long long int *y);
void primo(long long int N, long long int *P);

int main(){
  long long int N, E, C, M, P, Q, r, inv;

  scanf("%lld %lld %lld", &N, &E, &C);

  primo(N, &P);

  Q = N/P;

  eea((P-1)*(Q-1), E, &r, &inv);

  qem(C, inv, N, &M);

  printf("%lld\n", M);

  return 0;
}

void eea(long long int r0, long long int r1, long long int *ri, long long int *inv){
      long long int auxr, tant, t, auxt, rant, r, q;

      tant = 0; t = 1;

      rant = r0; r = r1;

      while(r != 0){
          q = rant/r;
          auxr = rant;
          rant = r;
          r = auxr % r;
          auxt = tant;
          tant = t;
          t = auxt - q*t;
      }

      if(tant < 0)
         tant += r0;
      *ri = rant;
      *inv = tant;
}

void qem(long long int X, long long int k, long long int N, long long int *y){
  unsigned long long int masc = 1;
  int i, num = 0;
  masc <<= 63;

  *y = X;

  for(i = (sizeof(long long int)*8)-1; i >= 0; i--){
    if(num == 0){
      if((k & masc) > 0){
        num = 1;
      }
    } else {
      (*y) = ((*y)*(*y)) % N;
      if((k & masc) > 0){
        (*y) = ((*y)*X) % N;
      }
    }
    masc >>= 1;
  }
}

void primo(long long int N, long long int *P){
  long long int max, prime = 2;

  while(N!=0){
    if((N % prime) != 0)
      prime++;
    else {
      max = N;
      N /= prime;

      if(N == 1){
        *P = max;
        break;
      }
    }
  }
}
