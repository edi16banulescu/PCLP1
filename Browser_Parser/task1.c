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

int main(){
    int nr_site=0;
    int i;
    number_site(&nr_site);
    //alocam dinamic structura "date", initial cu 3, apoi daca numarul siteurilor este mai mare, o realocam
    date *siteuri;
    siteuri = (date*)malloc(sizeof(date) * 3);
    if(nr_site>3)
    {
        siteuri=(date*)realloc(siteuri,sizeof(date)*nr_site);
    }
    site_names(siteuri);
    for(i=0;i<nr_site;i++)
        printf("%s %d %s\n",siteuri[i].url,siteuri[i].accesari,siteuri[i].titlu);
    free(siteuri);
    return 0;
}