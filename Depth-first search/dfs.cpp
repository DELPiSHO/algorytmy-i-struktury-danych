#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>


#define Max_Nodes 20
using namespace std;

int Macierz[Max_Nodes][Max_Nodes];
int Odwiedzony[Max_Nodes];
int LiczbaWierzcholkow;

stack<int,vector<int> > stos;

//zwraca ostatni nieodwiedzony nastepnik
int nastepnik_dfs(int v){
    int i;

    for (i=LiczbaWierzcholkow-1;i>=0;i--)
        if ((Macierz[i][v]==1)&&(Odwiedzony[i]==0)){
            Odwiedzony[i]=1;
            return(i);
        }
//wirzcholek nie ma nastepnikow
    return(-1);
}

void dfs(int v) {
    int u;
    int nastepny;
    printf("%d ",v+1);
    Odwiedzony[v]=1;
    nastepny=nastepnik_dfs(v);
    while (nastepny!=-1){
        stos.push(nastepny);
        nastepny=nastepnik_dfs(v);
    }
    if (!stos.empty()){
        u=stos.top();
        stos.pop();
        dfs(u);
    }
}

int main(void){
    FILE *Plik_We;
    int i,j;

    for (i=0;i<Max_Nodes;i++)
        Odwiedzony[i]=0;

    Plik_We=fopen("graf.txt","rt");
    fscanf(Plik_We,"%d",&LiczbaWierzcholkow);

    for (j=0;j<LiczbaWierzcholkow;j++)
        for (i=0;i<LiczbaWierzcholkow;i++)
            fscanf(Plik_We,"%d",&Macierz[i][j]);

    printf("Przeszukiwanie DFS: ");
    dfs(0);

    for (i=0;i<Max_Nodes;i++)
        Odwiedzony[i]=0;

    printf("\n\nDowolny klawisz...");
    getch();
    fclose(Plik_We);
    return 0;
}
