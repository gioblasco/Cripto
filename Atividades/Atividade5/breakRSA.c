#include<stdio.h>

void eea(int r0, int r1, int *ri, int *inv);
void qem(int X, int k, int N, int *y);

int main(){
  int N, E, C, M, r, inv;

  scanf("%d %d %d", &N, &E, &C);

  eea(N, E, &r, &inv);

  printf("%d\n", r);

  eea(E, r, &r, &inv);

  qem(C, inv, N, &M);

  printf("%d\n", inv);

  printf("%d\n", M);

  return 0;
}

void eea(int r0, int r1, int *ri, int *inv){
  int auxr, tant, t, auxt, rant, r, q;

      tant = 0; t = 1;

      rant = r0; r = r1;
      if(r1 > r0){
        rant = r1; r = r0;
        r0 = rant; r1 = r;
      }

      while(r != 0){
          // if(t < 0)
          //     t = t + r0;
          q = rant/r;
          auxr = rant;
          rant = r;
          if((auxr % r) == 1)
            *ri = r;
          r = auxr % r;
          auxt = tant;
          tant = t;
          t = auxt - q*t;
      }

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
