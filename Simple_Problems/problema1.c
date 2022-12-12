#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int is_anagram(char *s1,char *s2)
{
    int i,j;
    char aux; 
    char cps1[50]; // efectuam copii pentru sirurile noastre si lucram pe ele
    char cps2[50];
    strcpy(cps1,s1);
    strcpy(cps2,s2);
    if(strlen(cps1)==strlen(cps2)) // daca cele doua siruri au aceeasi lungime exista posibilitatea de anagrame
    {   // ordonez sirurile in ordine crescatoare pentru a le putea compara cu strcmp
        for(i=0;i<strlen(cps1);i++)
            for(j=i+1;j<strlen(cps1);j++)
            if(cps1[i]>cps1[j])
        {
            aux=cps1[i];
            cps1[i]=cps1[j];
            cps1[j]=aux;
        }
        for(i=0;i<strlen(cps2);i++)
            for(j=i+1;j<strlen(cps2);j++)
            if(cps2[i]>cps2[j])
        {
            aux=cps2[i];
            cps2[i]=cps2[j];
            cps2[j]=aux;
        }
        if(strcmp(cps1,cps2)==0)
            return 1; // anagrame
        else
            return -1; // nu sunt anagrame

    }
    else
        return -1; // nu sunt anagrame
}

double compute_grade(char *s1, char *s2)
{
    double d=0;
    if(is_anagram(s1,s2)==1)
    {
        for(int i=0;i<strlen(s1);i++)
        {
                if(s1[i]!=s2[i]) 
                    d++; // calculez cate litere sunt diferite
        }
        return d/(double)strlen(s1); // impart literele diferite la numarul de litere pentru a putea calcula gradul
    }
    else
        return -1;
}

void sortare(char s1[1000][1000],char s2[1000][1000],double grad[1000],int N)
{
    double aux;
    char schimbare[100];
    for(int i=0;i<N-1;i++)
        for(int j=i+1;j<N;j++)
        {
            if(grad[i]<grad[j]) // salvez toate gradele intr-un vector pentru a-l putea ordona
            {
                aux=grad[i];
                grad[i]=grad[j];
                grad[j]=aux;

                strcpy(schimbare,s1[i]);
                strcpy(s1[i],s1[j]);
                strcpy(s1[j],schimbare);

                strcpy(schimbare,s2[i]);
                strcpy(s2[i],s2[j]);
                strcpy(s2[j],schimbare);
            }
            if(grad[i]==grad[j]) // daca sunt egale gradele, le iau in ordine descrescatoare lexicografica
            {
                if(strcmp(s1[i],s1[j])<0)
                {
                    aux=grad[i];
                    grad[i]=grad[j];
                    grad[j]=aux;

                    strcpy(schimbare,s1[i]);
                    strcpy(s1[i],s1[j]);
                    strcpy(s1[j],schimbare);

                    strcpy(schimbare,s2[i]);
                    strcpy(s2[i],s2[j]);
                    strcpy(s2[j],schimbare);
                }
            }
        }
}

int main()
{
    int N;
    char s1[1000][1000]; // primul cuvant din pereche
    char s2[1000][1000]; // al doilea cuvant din pereche
    double grad[1000];
    scanf("%d\n",&N);
    for(int i=0;i<N;i++)
        scanf("%s %s",s1[i],s2[i]);
    for(int i=0;i<N;i++)
        grad[i]=compute_grade(s1[i],s2[i]); // vectorul cu gradele perechilor
    sortare(s1,s2,grad,N); // le sortez
    for(int i=0;i<N;i++)
        printf("%s %s\n",s1[i],s2[i]);
    return 0;
}
