#include<stdio.h>

int main(){
    unsigned long long int X, y, k, N, masc = 2147483648, aux;
    int i, num = 0;

    scanf("%lld %lld %lld", &X, &k, &N);

    y = X;

    for(i = sizeof(int)*8-1; i >= 0; i--){
      if(num == 0){
        aux = k & masc;
        if((aux) > 0){
          num = 1;
        }
      } else {
        y = (y*y) % N;
        aux = k & masc;
        if((aux) > 0){
          y = (y*X) % N;
        }
      }
      masc >>= 1;
    }

    printf("%lld\n", y);

return 0;
}
