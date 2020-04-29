#include <stdio.h>
#include <string.h>

void nwp(char*, char*, int, int);

int main()
{
    char buf[50];

    printf("Pierwszy ciag: ");
    scanf("%s", buf);
    char x[strlen(buf)];
    sprintf(x, "%s", buf);

    printf("Drugi ciag: ");
    scanf("%s", buf);
    char y[strlen(buf)];
    sprintf(y, "%s", buf);

    int m = strlen(x);
    int n = strlen(y);

    nwp(x, y, m, n);
    return 0;
}

void nwp( char *X, char *Y, int m, int n )
{
    int i, j;
    int tabWart[m+1][n+1];

    for (i=0; i<=m; i++){
        for (j=0; j<=n; j++){
            if (i==0 || j==0)
                tabWart[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                tabWart[i][j] = tabWart[i-1][j-1] + 1;
            else
                tabWart[i][j] = tabWart[i-1][j] > tabWart[i][j-1] ? tabWart[i-1][j] : tabWart[i][j-1];
        }
    }

    //Wypisywanie podciagu
    int ind = tabWart[m][n];
    char ciag[ind+1];
    ciag[ind] = '\0';
    //Startujemy z prawego dolnego rogu
    i = m; j = n;
    while (i>0 && j>0){
        if (X[i-1]==Y[j-1]){ //jesli znaki sa takie same, jest to czesc podciagu
            ciag[ind-1]=X[i-1];
            i--; j--; ind--;
        }
        else if (tabWart[i-1][j]>tabWart[i][j-1])  //jesli nie takie same to idziemy w strone wiekszej wartosci
            i--;
        else
            j--;
    }
    printf("Najdluzszy wspolny podciag to: %s\n", ciag);
}
