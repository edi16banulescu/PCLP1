#include <stdio.h>
#include <stdlib.h>

int reciproc(int a[][100],int M) // functie pentru aflarea numarului de perechi de nebuni care se ataca
{
    int nr=0; // numarul de perechi de nebuni ce se ataca
    int cpa[100][100]; // copie a matricei
    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
        cpa[i][j]=a[i][j]; // lucrez pe copie a matricii
    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
        {
            if(cpa[i][j]==1) // daca gasim un nebun, il parcurgem pe diagonala in dreapta jos, dreapta sus, stanga sus si stanga jos
            {
                int l,c; // indicele liniilor si al coloanelor pe care le vom parcurge
                l=i+1;
                c=j+1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(cpa[i][j]==cpa[l][c])
                        nr++;
                    l++;
                    c++;
                }
                l=i-1;
                c=j+1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(cpa[i][j]==cpa[l][c])
                        nr++;
                    l--;
                    c++;
                }
                l=i-1;
                c=j-1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(cpa[i][j]==cpa[l][c])
                        nr++;
                    l--;
                    c--;
                }
                l=i+1;
                c=j-1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(cpa[i][j]==cpa[l][c])
                        nr++;
                    l++;
                    c--;
                }
                cpa[i][j]=0;
            }
        }
    return nr;
}

// functie auxiliara pentru functia urmatoare 
int anulareNebun(int a[][100],int M) // aceasta functie va elimina primul nebun, pe care il gaseste, dintr-o pereche de nebuni
{
    int nr=0; // contor pentru cand o sa gasim primul nebun care se ataca
    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
        {
            if(a[i][j]==1)
            {
                int l,c; // indici ai liniilor si coloanelor cu care o sa lucram
                l=i+1;
                c=j+1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(a[i][j]==a[l][c])
                        nr++;
                    l++;
                    c++;
                }
                l=i-1;
                c=j+1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(a[i][j]==a[l][c])
                        nr++;
                    l--;
                    c++;
                }
                l=i-1;
                c=j-1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(a[i][j]==a[l][c])
                        nr++;
                    l--;
                    c--;
                }
                l=i+1;
                c=j-1;
                while((l>=0 && l<M) && (c>=0 && c<M))
                {
                    if(a[i][j]==a[l][c])
                        nr++;
                    l++;
                    c--;
                }
                if(nr!=0)
                {
                    a[i][j]=0;
                    return 1; // am eliminat nebunul
                }
            }
        }
    return 0;
}

int mutare(int a[][100],int M)
{
    if(reciproc(a,M)==1) // daca avem doar o pereche de nebuni
    {
        if(anulareNebun(a,M)==1) // eliminam nebunul pe care presupunem ca o sa il mutam
        {
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<M;j++)
            {
                if(a[i][j]==0) // luam fiecare pozitie libera in parte si o parcurgem in toate directiile pe diagonala
                {
                    int ok=0; // contor
                    int l,c;
                    l=i+1;
                    c=j+1;
                    while((l>=0 && l<M) && (c>=0 && c<M))
                    {
                        if(a[l][c]==1)
                            ok++;
                        l++;
                        c++;
                    }
                    l=i-1;
                    c=j+1;
                    while((l>=0 && l<M) && (c>=0 && c<M))
                    {
                        if(a[l][c]==1)
                            ok++;
                        l--;
                        c++;
                    }
                    l=i-1;
                    c=j-1;
                    while((l>=0 && l<M) && (c>=0 && c<M))
                    {
                        if(a[l][c]==1)
                            ok++;
                        l--;
                        c--;
                    }
                    l=i+1;
                    c=j-1;
                    while((l>=0 && l<M) && (c>=0 && c<M))
                    {
                        if(a[l][c]==1)
                            ok++;
                        l++;
                        c--;
                    }
                    if(ok==0)
                        return 1; // pozitia este libera
                }
            }
        }
        return 0; // nu exista nicio pozitie disponibila
        }
    }
    else
        return 0; // mai mult de o pereche
    return 0;
}

int main()
{
    int M;
    int N;
    int x,y; // pozitiile nebunilor
    int a[100][100];
    scanf("%d",&M);

    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
        a[i][j]=0; // presupunem ca nu avem niciun nebun
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        scanf("%d %d",&x,&y); // introducem nebunii
        a[x][y]=1;
    }
    printf("%d\n",reciproc(a,M)); // numarul de perechi de nebuni
    if(mutare(a,M)==1)
        printf("DA\n");
    else
        printf("NU\n");
    return 0;
}