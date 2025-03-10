#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NormRANu (2.3283063671E-10F)
#define Frec_Max 100
unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran,ig1,ig2,ig3;
int frec[Frec_Max];

float Random(){

    float r;
    ig1=ind_ran-24;
    ig2=ind_ran-55;
    ig3=ind_ran-61;
    irr[ind_ran]=irr[ig1]+irr[ig2];
    ir1=(irr[ind_ran]^irr[ig3]);
    ind_ran++;
    r=ir1*NormRANu;
    //printf("r=%f\n",r);
    return r;

}

void ini_ran(int SEMILLA)
{
    int INI,FACTOR,SUM,i;
    srand(SEMILLA);
    INI=SEMILLA;
    FACTOR=67397;
    SUM=7364893;
    for(i=0;i<256;i++)
    {
    INI=(INI*FACTOR+SUM);
    irr[i]=INI;
    }
    ind_ran=ig1=ig2=ig3=0;
}

int main ()
{
    ini_ran(36);
    int N=100000,i,max=10,min=-10;
    double data[Frec_Max],epsilon=0.1,cambio,cociente,x,xnew;
    x=-9.8;
    double delta=(max-min)/100.;

    ini_ran(123); //Porque???

    for (i=0;i<Frec_Max;i++){
        data[i]=0;
    }

    for(i=1;i<N;i++){
        cambio=epsilon*2*(Random()-0.5);
        xnew=x+cambio;
        if(xnew>max)xnew=xnew-(max-min);
        if(xnew<min)xnew=xnew+(max-min);

        cociente=exp(-20*(xnew*xnew-x*x));

        if(Random()<cociente)x=xnew;

        data[(int)((x-min)/delta)]++;
        }
     FILE *f=fopen("hist.txt","w");
     for (i=0;i<Frec_Max;i++){
        fprintf(f,"%lf\n",data[i]);
    }
    fclose(f);
    //GNUPLOT:    plot “hist.txt” w boxes

return 0;
}
