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

// functie ce va sorta siteurile gasite dupa numarul de accesari, in ordine descrescatoare
void sortare_acces(date *siteuri,int nr_nou)
{
    int i,j;
    char aux[200];
    int ajut;
    for(i=0;i<nr_nou;i++)
        for(j=i+1;j<nr_nou;j++)
        {
            if (siteuri[i].accesari < siteuri[j].accesari)
            {
                strcpy(aux, siteuri[i].url);
                strcpy(siteuri[i].url, siteuri[j].url);
                strcpy(siteuri[j].url, aux);

                strcpy(aux,siteuri[i].continut);
                strcpy(siteuri[i].continut,siteuri[j].continut);
                strcpy(siteuri[j].continut,aux);

                ajut=siteuri[i].accesari;
                siteuri[i].accesari=siteuri[j].accesari;
                siteuri[j].accesari=ajut;
            }
        }
}

int main(){
    int i,j;
    int nr_site=0;
    int noul_nr=0;
    char s[100];
    // variabila in care se vor afla url-urile siteurilor gasite, trecute o singura data
    char aux[200];
    aux[0]=' ';
    aux[1]='\0';
    char *cuv;
    char *continut;
    char *sep=" \n";
    // variabile cu care vom verifica ce se afla inainte si dupa tokenul "cuv"
    char *space;
    char *space2;
    number_site(&nr_site);
    //alocam dinamica structura "date"
    date *siteuri;
    siteuri = (date*)malloc(sizeof(date) * 3);
    if(nr_site>3)
    {
        siteuri=(date*)realloc(siteuri,sizeof(date)*nr_site);
    }
    // aceasta variabila va afisa valorile in ordinea potrivita(copie)
    date afisare[20];
    site_names(siteuri);
    scanf("%[^\n]s",s);
    // aceste variabile stocheaza elementele care se afla in interiorul ghilimelelor, respectiv ce se afla dupa "-"
    char *s_ghilimele=(char*)calloc(strlen(s)+1,sizeof(char));
    char *s_exclus=(char*)calloc(strlen(s)+1,sizeof(char));
    // atribuim variabilelor elementele lor, daca exista
    for(i=0;i<strlen(s);i++)
    {
        if(s[i]=='"')
        {
            i++;
            j=0;
            while(s[i]!='"')
            {
                s_ghilimele[j]=s[i];
                i++;
                j++;
            }
            s_ghilimele[j]='\0';
        }
        if(s[i]=='-')
        {
            i++;
            j=0;
            while(s[i]!='\0')
            {
                s_exclus[j]=s[i];
                i++;
                j++;
            }
            s_exclus[j]='\0';
        }
    }

    cuv=strtok(s,sep);
    // tokenul se va opri daca intalneste caracterele '"', respectiv '-'
    while((cuv != NULL) && (cuv[0] != '"') && (cuv[0] != '-'))
    {
        for(i=0;i<nr_site;i++)
        {
            continut=strstr(siteuri[i].continut,cuv);
            space=continut+strlen(cuv);
            space2=strstr(siteuri[i].continut,cuv)-1;
            // conditii pentru cuv sa fie un cuvant independent, nu inclus in alte cuvinte
            if((continut!=NULL) && (space[0]==' ' || space[0]=='\n') && (space2[0]==' ' || space2[0]=='\n'))
            {
                if(strlen(s_exclus) != 0)
                {
                    // verificam daca in continutul siteurilor exista cuvantul exclus
                    if ((strstr(aux,siteuri[i].url) == NULL) && (strstr(siteuri[i].continut,s_exclus) == NULL))
                    {
                        afisare[noul_nr++] = siteuri[i];
                        strcat(aux, siteuri[i].url);
                        strcat(aux, "\n");
                    }
                }
                else
                {
                    if (strstr(aux,siteuri[i].url) == NULL)
                    {
                        afisare[noul_nr++] = siteuri[i];
                        strcat(aux, siteuri[i].url);
                        strcat(aux, "\n");
                    }
                }
            }
        }
        cuv=strtok(NULL,sep);
    }

    if(strlen(s_ghilimele) != 0)
    {
        for(i=0;i<nr_site;i++)
        {
            continut=strstr(siteuri[i].continut,s_ghilimele);
            space=continut+strlen(s_ghilimele);
            space2=strstr(siteuri[i].continut,s_ghilimele)-1;
            // nu mai exista conditii deoarece cuvantul dintre ghilimele nu se poate afla in interiorul altor cuvinte
            if(continut!=NULL)
            {
                if(strlen(s_exclus) != 0)
                {
                    // verificam daca cuvantul exclus se afla in continutul siteului
                    if ((strstr(aux,siteuri[i].url) == NULL) && (strstr(siteuri[i].continut,s_exclus) == NULL))
                    {
                        afisare[noul_nr++] = siteuri[i];
                        strcat(aux, siteuri[i].url);
                        strcat(aux, "\n");
                    }
                }
                else
                {
                    if (strstr(aux,siteuri[i].url) == NULL)
                    {
                        afisare[noul_nr++] = siteuri[i];
                        strcat(aux, siteuri[i].url);
                        strcat(aux, "\n");
                    }
                }
            }
        }
    }
    // sortam structura cu elementele gasite
    sortare_acces(afisare,noul_nr);
    for(i=0;i<noul_nr;i++)
        printf("%s\n",afisare[i].url);
    free(siteuri);
    free(s_exclus);
    free(s_ghilimele);
    return 0;
}