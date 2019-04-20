#include <stdio.h>
#include <stdlib.h>
#define MAX 20

void yer_degistir(int *sayi1,int *sayi2)
{
    int gecici_sayi;
    gecici_sayi=*sayi1;
    *sayi1=*sayi2;
    *sayi2=gecici_sayi;
    return;
}

void kucukten_buyuge_sirala(int v[],int eleman_say)
{
    int i, gecis_say=0, yer_degisti;
    do{
        gecis_say++;
        yer_degisti=0;
        for(i=0;i<eleman_say-gecis_say+1;i++){
            if(v[i]>v[i+1]) {
                yer_degistir(&v[i],&v[i+1]);
                yer_degisti=1;
            }
        }
    } while(yer_degisti==1);
    return;
}

void push(int *yigin1,int *yigin2,int *tepe,int yeni)
{
    if (*tepe>MAX-1)
        printf("Yigin dolu!");
    else
    {
        *tepe=*tepe+1;
        yigin1[*tepe]=yeni;
        yigin2[*tepe]=yeni;
        kucukten_buyuge_sirala(yigin2,*tepe);
    }
    return;
}

int pop(int *yigin,int *tepe)
{
    int gecici;

    gecici=yigin[*tepe];
    *tepe=*tepe-1;

    return gecici;
}

int main()
{
    int i,sayi;
    int yigin1[MAX],yigin2[MAX];
    int tepe=-1;
    for (i=0;i<MAX;i++)
    {
        printf("%d. tam sayiyi giriniz: ",i+1);
        scanf("%d",&sayi);
        push(yigin1,yigin2,&tepe,sayi);
    }
    for (i=0;i<MAX;i++)
    {
        sayi=pop(yigin2,&tepe);
        printf("\n%d",sayi);
    }
    return 0;
}
