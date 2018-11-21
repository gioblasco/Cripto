#include<stdio.h>
#include <stdlib.h>

typedef struct {
  long long int x;
  long long int y;
} Ponto;

void addmultiply();
Ponto add(Ponto A, Ponto B);
char equals(Ponto A, Ponto B);
long long int inverse(long long int r0, long long int r1);

long long int n, a, p;
Ponto G;

int main (){
  scanf("%llu", &n);
  while(n != 0){
    scanf("%llu %llu %llu %llu", &a, &p, &G.x, &G.y);

    addmultiply();

    scanf("%llu", &n);
  }

  return 0;
}


void addmultiply(){
  unsigned long long int masc = 1;
  long long int i, t;
  Ponto T, auxT;
  char num = 0;
  masc <<= 63;

  t = n;
  T.x = G.x;
  T.y = G.y;

  for(i = (sizeof(long long int)*8)-1; i >= 0; i--){
    if(num == 0){
      if((t & masc) > 0){
        num = 1;
      }
    } else {
      auxT = add(T, T);
      T.x = auxT.x % p;
      T.y = auxT.y % p;

      if((t & masc) > 0){
        auxT = add(T, G);
        T.x = auxT.x % p;
        T.y = auxT.y % p;
      }
    }
    masc >>= 1;
  }

  printf("%lld %lld\n", T.x, T.y);
}

Ponto add(Ponto A, Ponto B){
  long long int r, aux;
  Ponto Q;
  if(equals(A, B)){
    r = ((3*(A.x*A.x) + a) % p) * (inverse(p, 2*A.y) % p);
  } else {
    aux = (B.x - A.x);
    if(aux < 0){
      aux += p;
    }
    r = ((B.y - A.y) % p) * (inverse(p, aux) % p);
  }

  Q.x = ((r*r) - A.x - B.x) % p;
  if(Q.x < 0){
    Q.x += p;
  }
  Q.y = (r*(A.x - Q.x) - A.y) % p;
  if(Q.y < 0){
    Q.y += p;
  }

  return Q;
}

char equals(Ponto A, Ponto B){
  if(A.x == B.x && A.y == B.y)
    return 1;
  return 0;
}

long long int inverse(long long int r0, long long int r1){
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

      return tant;
}
