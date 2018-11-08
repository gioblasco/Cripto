#include<stdio.h>

void eea(int r0, int r1, int *ri, int *inv);
void qem(int X, int k, int N, int *y);
void primo(int N, int *P);

int main(){
  int N, E, C, M, P, Q, r, inv;

  scanf("%d %d %d", &N, &E, &C);

  primo(N, &P);

  Q = N/P;

  eea((P-1)*(Q-1), E, &r, &inv);

  qem(C, inv, N, &M);

  printf("%d\n", M);

  return 0;
}

void eea(int r0, int r1, int *ri, int *inv){
  int auxr, tant, t, auxt, rant, r, q;

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

      if(t < 0)
        t = t + r0;
      *ri = rant;
      *inv = tant;
}

void qem(int X, int k, int N, int *y){
  unsigned int masc = 2147483648;
  int i, num = 0;

  *y = X;

  for(i = sizeof(int)*8-1; i >= 0; i--){
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

void primo(int N, int *P){
  int max, prime = 2;

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
