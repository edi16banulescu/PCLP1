#include "task0.h"

//functie care numara cate siteuri avem in fisierul "master.txt"
void number_site(int *nr_site)
{
    FILE *master = fopen("master.txt","r");
    int nr=0;
    char c;
    while(1)
    {
        c=fgetc(master);
        if(c==EOF)
            break;
        if(c == '\n')
            nr++;
    }
    *nr_site=nr;
    fclose(master);
}

// functie ce ne va sorta elementele structurii in ordine alfabetica dupa "continut"
void sortare_alf(date *siteuri,int nr_nou)
{
    int i,j;
    char aux[100];
    int ajut;
    for(i=0;i<nr_nou;i++)
        for(j=i+1;j<nr_nou;j++)
        {
            if(strcmp(siteuri[i].continut,siteuri[j].continut)>0)
            {
                strcpy(aux,siteuri[i].url);
                strcpy(siteuri[i].url,siteuri[j].url);
                strcpy(siteuri[j].url,aux);

                strcpy(aux,siteuri[i].continut);
                strcpy(siteuri[i].continut,siteuri[j].continut);
                strcpy(siteuri[j].continut,aux);

                ajut=siteuri[i].accesari;
                siteuri[i].accesari=siteuri[j].accesari;
                siteuri[j].accesari=ajut;
            }
        }
}

//functie ce ne va sorta site-urile care au continutul identic, dupa numarul de accesari
void sortare_acces(date *siteuri,int nr_nou)
{
    int i,j;
    char aux[100];
    for(i=0;i<nr_nou;i++)
        for(j=i+1;j<nr_nou;j++)
        {
            if(strcmp(siteuri[i].continut,siteuri[j].continut)==0)
            {
                if(siteuri[i].accesari<siteuri[j].accesari)
                {
                    strcpy(aux,siteuri[i].url);
                    strcpy(siteuri[i].url,siteuri[j].url);
                    strcpy(siteuri[j].url,aux);
                }
            }
        }
}

int main(){
    int i;
    int nr_site=0;
    int noul_nr=0;
    char s[100];
    // variabila in care vom stoca numele siteurilor gasite
    char aux[100];
    char *cuv;
    char *continut;
    char *sep=" \n";
    // variabile cu care vom verifica ce se afla inainte si dupa tokenul "cuv"
    char *space;
    char *space2;
    number_site(&nr_site);
    // alocam dinamic structura "date"
    date *siteuri;
    siteuri = (date*)malloc(sizeof(date) * 3);
    if(nr_site>3)
    {
        siteuri=(date*)realloc(siteuri,sizeof(date)*nr_site);
    }
    // aceasta variabila va afisa in ordinea ceruta elementele gasite
    date afisare[20];
    site_names(siteuri);
    scanf("%[^\n]s",s);
    // separam in tokeni si cautam pe rand in fiecare site
    cuv=strtok(s,sep);
    while(cuv != NULL)
    {
        for(i=0;i<nr_site;i++)
        {
            continut=strstr(siteuri[i].continut,cuv);
            space=continut+strlen(cuv);
            space2=strstr(siteuri[i].continut,cuv)-1;
            // conditii pentru cuv sa fie un cuvant independent, nu inclus in alte cuvinte
            if((continut!=NULL) && (space[0]==' ' || space[0]=='\n') && (space2[0]==' ' || space2[0]=='\n'))
            {
                // verificam daca url-ul siteului se afla in lista "aux" cu toate url-urile gasite
                if (strstr(aux, siteuri[i].url) == NULL)
                {
                    afisare[noul_nr++] = siteuri[i];
                    strcat(aux, siteuri[i].url);
                    strcat(aux, "\n");
                }
            }
        }
        cuv=strtok(NULL,sep);
    }
    //sortam elementele din "afisare"
    sortare_alf(afisare,noul_nr);
    sortare_acces(afisare,noul_nr);
    for(i=0;i<noul_nr;i++)
        printf("%s\n",afisare[i].url);
    free(siteuri);
    return 0;
}