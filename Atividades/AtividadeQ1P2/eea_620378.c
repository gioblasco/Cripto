#include<stdio.h>

int main(){
    int r0, r1, auxr, tant, t, auxt, rant, r, q;

    scanf("%d %d", &r1, &r0);

    tant = 0; t = 1;
    rant = r0; r = r1;

    while(r != 0){
        if(t < 0)
            t = t + r0;
        q = rant/r;
        auxr = rant;
        rant = r;
        r = auxr % r;
        auxt = tant;
        tant = t;
        t = auxt - q*t;
    }

    if(rant == 1)
        printf("%d %d\n", rant, tant);
    else
        printf("%d N\n", rant);

return 0;
}
