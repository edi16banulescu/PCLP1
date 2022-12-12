#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura in care vom stoca toate datele
typedef struct
{
    char url[50];
    int accesari;
    int checksum;
    int octeti;
    char titlu[50];
    char continut[1000];
}date;

// functia care atribuie elementelor structurii "date" exact ce trebuie
void parsare(char *siteuri,date *html)
{
    FILE *site = fopen(siteuri,"r");
    char c;
    int j=0;
    while((c=fgetc(site))!=' ')
    {
        html->url[j]=c;
        j++;
    }
    html->url[j] = '\0';
        
    html->octeti=0;
    while((c=fgetc(site)) != ' ')
    {
        html->octeti=html->octeti*10+(c-'0');
    }

    html->accesari=0;
    while((c=fgetc(site))!=' ')
    {
        html->accesari=html->accesari*10+(c-'0');
    }

    html->checksum=0;
    while((c=fgetc(site))!='\n')
    {
        html->checksum=html->checksum*10+(c-'0');
    }
    while((c=fgetc(site))!='>')
    {
        
    }
    while((c=fgetc(site))!='>')
    {

    }
    j=0;
    while((c=fgetc(site))!='<')
    {
        html->titlu[j]=c;
        j++;
    }
    html->titlu[j]='\0';
    while((c=fgetc(site))!='>')
    {
        
    }
    while((c=fgetc(site))!='>')
    {

    }
    j=0;
    while((c=fgetc(site))!='<')
    {
        html->continut[j]=c;
        j++;
    }
    html->continut[j]='\0';
    fclose(site);
}

// functie care extrage numele siteurilor din fisierul "master.txt"
void site_names(date *siteuri)
{
    FILE *master = fopen("master.txt","r");
    char c;
    char nume[50];
    int j=0;
    int i=0;
    date continut_site;
    while(1)
    {
        c=fgetc(master);
        if(c==EOF)
            break;
        if(c != '\n')
        {
            nume[j]=c;
            j++;
        }
        else
        {
            nume[j]='\0';
            parsare(nume,&continut_site);
            siteuri[i++]=continut_site;
            j=0;
        }
    }
    fclose(master);
}