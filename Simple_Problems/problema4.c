#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int xbol(int a,int b) // functie pentru produsul boolean
{
    if(a==0 && b==0)
        return 0;
    if(a==0 && b==1)
        return 0;
    if(a==1 && b==1)
        return 1;
    if(a==1 && b==0)
        return 0;
    return -1;
}

int sumbol(int a,int b) // functie pentru suma booleana
{
    if(a==1 && b==0)
        return 1;
    if(a==1 && b==1)
        return 1;
    if(a==0 && b==0)
        return 0;
    if(a==0 && b==1)
        return 1;
    return -1;
}


void dec_to_bin(int n,char *s) // aplic metoda impartirii si a restului
{
    s[8]='\0';
    if(n>=0 && n<=65535)
    {
        for(int i=0;i<8;i++)
        {
            if(n%2==0)
                s[8-1-i]='0';
            else
                s[8-1-i]='1';
            n=n/2;
        }
    }
}

int bin_to_dec(char *s) // transform in baza 10 si aplic " -'0' " pentru a transforma in intreg
{
    int baza=1;
    int numar=0;
    for(int i=strlen(s)-1;i>=0;i--)
    {
        int caracter=s[i]-'0';
        numar=numar+caracter*baza;
        baza=baza*2;
    }
    return numar;
}

void produs(int a[][8], int b[][8], int prod[][8]) // inmultesc matricile folosind regulile boolene
{
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            prod[i][j] = 0;
            for(int x=0;x<8;x++) {
                prod[i][j]=sumbol(prod[i][j],xbol(a[i][x],b[x][j]));
            }
        }
    }

}

void transpusa(int a[][8],int tr[][8]) // transpusa unei matrici
{
    for(int i=0;i<8;i++)
   {
      for (int j=0;j<8;j++)
      {
            tr[i][j]=a[j][i];
      }
   }
}

int sum_X_0(int m[][8])
{
    int p=0; // nr de puncte
    int pp1=0,sec1=0; // initializari pentru numarul de '1'de pe diagonala principala si secundara din sfertul rosu
    for(int i=0;i<4;i++){ //sfertul rosu
        int linie=0,col=0; // initializari pentru numarul de '1'de pe linie si coloana din sfertul rosu
        for(int j=0;j<4;j++)
        {
            if(m[i][j]==1)
                linie++;
            if(m[j][i]==1)
                col++;
        }
        if(m[i][i]==1)
            pp1++;
        if(m[i][4-1-i]==1)
            sec1++;
        if(linie==4) // daca sunt 4 de '1' pe linie sau pe coloana sau pe diagonala adunam un punct
            p++;
        if(col==4)
            p++;
    }
    if(pp1==4)
        p++;
    if(sec1==4)
        p++;

    int pp2=0,sec2=0; // aplicam aceeasi logica pentru fiecare sfert
    for(int i=0;i<4;i++){ // sfertul albastru
        int linie=0,col=0; 
        for(int j=4;j<8;j++)
        {
            if(m[i][j]==1)
                linie++;
            if(m[8-1-j][8-1-i]==1)
                col++;
        }
        if(m[4+i][4+i]==1)
            pp2++;
        if(m[i][8-1-i]==1)
            sec2++;
        if(linie==4)
            p++;
        if(col==4)
            p++;
    }
    if(pp2==4)
        p++;
    if(sec2==4)
        p++;

    int pp3=0,sec3=0;
    for(int i=4;i<8;i++){ // sfertul galben
        int linie=0,col=0;
        for(int j=0;j<4;j++)
        {
            if(m[i][j]==1)
                linie++;
            if(m[8-1-j][8-1-i]==1)
                col++;
        }
        if(m[i][i-4]==1)
            pp3++;
        if(m[i][8-1-i]==1)
            sec3++;
        if(linie==4)
            p++;
        if(col==4)
            p++;
    }
    if(pp3==4)
        p++;
    if(sec3==4)
        p++;

    int pp4=0,sec4=0;
    for(int i=4;i<8;i++){ // sfertul verde
        int linie=0,col=0;
        for(int j=4;j<8;j++)
        {
            if(m[i][j]==1)
                linie++;
            if(m[j][i]==1)
                col++;
        }
        if(m[i][i]==1)
            pp4++;
        if(m[i][11-i]==1)
            sec4++;
        if(linie==4)
            p++;
        if(col==4)
            p++;
    }
    if(pp4==4)
        p++;
    if(sec4==4)
        p++;

    return p;
}

int main()
{
    int n;
    int pa=0; // nr de puncte al matricei A
    int pprod=0; //nr de puncte al matricei A*A(transpus)
    int pa2=0; // nr de puncte al matricei A la patrat
    int a[8][8],transp[8][8],prod[8][8],a2[8][8];
    char s[100];
    for(int i=0;i<8;i++){
        scanf("%d",&n);
        dec_to_bin(n,s);
        for(int j=0;j<8;j++)
        a[i][j]=s[j]-'0'; // transform elementele matricei in tip intreg.
    }
    // construim cele 3 matrici
    transpusa(a,transp);
    produs(a,transp,prod);
    produs(a,a,a2);
    // aflam numarul de puncte
    pa=sum_X_0(a);
    pprod=sum_X_0(prod);
    pa2=sum_X_0(a2);
    // efectuam comparatii intre numarul de puncte al fiecarei matricii si al ordinii mentionate in enunt
    if(pa>=pprod && pa>=pa2)
    {
        for(int i=0;i<8;i++)
        {
            s[8]='\0';
            for(int j=0;j<8;j++)
            s[j]=a[i][j]+'0';
            printf("%d\n",bin_to_dec(s));
        }
    }
    else if(pprod>pa && pprod>=pa2)
        {
            for(int i=0;i<8;i++)
            {
                s[8]='\0';
                for(int j=0;j<8;j++)
                s[j]=prod[i][j]+'0';
                printf("%d\n",bin_to_dec(s));
            }
        }
        else if(pa2>pa && pa2>pprod)
            {
                for(int i=0;i<8;i++)
                {
                    s[8]='\0';
                    for(int j=0;j<8;j++)
                    s[j]=a2[i][j]+'0';
                    printf("%d\n",bin_to_dec(s));
                }
            }
    return 0;
}
