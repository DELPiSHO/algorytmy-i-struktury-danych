#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0
#define SZER_EKR 80
#define IL_POZ 8

typedef struct Tree{
	struct Tree *ojciec, *lewy, *prawy;
	int klucz, kolor;
} RBT;

void rotacjaLewa(RBT**, RBT*);
void rotacjaPrawa(RBT**, RBT*);
RBT *minWezel(RBT*);
RBT *nastepca(RBT*);
void usunRBT_fix(RBT*, RBT*);
RBT *usunRBT(RBT*, RBT*);
RBT *stworzWezel(int);
RBT *szukajWezla(RBT*, int);
void wstaw(RBT**, RBT*);
void wstawRBT(RBT**, int);
void drukujOst(RBT*, int, int, int);
void drukujWew(RBT*, int, int, int);
void drukuj(RBT*);
int maxWysokosc(RBT*);
int minWysokosc(RBT*);
int ileCzerwonych(RBT*);

RBT *tree = NULL;
char wydruk[IL_POZ+1][SZER_EKR];

int main(){
	wstawRBT(&tree, 38);
	wstawRBT(&tree, 31);
	wstawRBT(&tree, 22);
	drukuj(tree);
	szukajWezla(tree, 22);
	szukajWezla(tree, 8);
	wstawRBT(&tree, 8);
	wstawRBT(&tree, 20);
	wstawRBT(&tree, 5);
	wstawRBT(&tree, 10);
	drukuj(tree);
	szukajWezla(tree, 9);
	wstawRBT(&tree, 9);
	szukajWezla(tree, 9);
	wstawRBT(&tree, 21);
	drukuj(tree);
	usunRBT(tree, szukajWezla(tree, 8));
	drukuj(tree);
	wstawRBT(&tree, 27);
	wstawRBT(&tree, 29);
	wstawRBT(&tree, 25);
	drukuj(tree);
	usunRBT(tree, szukajWezla(tree, 29));
	usunRBT(tree, szukajWezla(tree, 40));
	wstawRBT(&tree, 28);
	drukuj(tree);
	printf("\nmax wys= %d", maxWysokosc(tree));
	printf("\nmin wys= %d", minWysokosc(tree));
	printf("\nilosc czerwonych= %d", ileCzerwonych(tree));
	
	return 0;
}

void rotacjaLewa(RBT **korzen, RBT *tmp)
{
	RBT *prawySyn = tmp->prawy;
	tmp->prawy = prawySyn->lewy;
	if (prawySyn->lewy != NULL){
		prawySyn->lewy->ojciec = tmp;
	}
	prawySyn->ojciec = tmp->ojciec;
	if (tmp->ojciec == NULL){
		*(korzen) = prawySyn;
	}else if (tmp == tmp->ojciec->lewy){
		tmp->ojciec->lewy = prawySyn;
	}else{
		tmp->ojciec->prawy = prawySyn;
	}
	prawySyn->lewy = tmp;
	tmp->ojciec = prawySyn;
}

void rotacjaPrawa(RBT **korzen, RBT *tmp)
{
	RBT *lewySyn = tmp->lewy;
	tmp->lewy = lewySyn->prawy;
	if (lewySyn->prawy != NULL){
		lewySyn->prawy->ojciec = tmp;
	}
	lewySyn->ojciec = tmp->ojciec;
	if (tmp->ojciec == NULL){
		*(korzen) = lewySyn;
	}else if (tmp == tmp->ojciec->lewy){
		tmp->ojciec->lewy = lewySyn;
	}else{
		tmp->ojciec->prawy = lewySyn;
	}
	lewySyn->prawy = tmp;
	tmp->ojciec = lewySyn;
}

RBT *minWezel(RBT *korzen)  //zwraca adres wezla o najmniejszej wartosci
{
	RBT *tmp = korzen;
	while (tmp->lewy != NULL){
		tmp = tmp->lewy;
	}
	return tmp;
}

RBT *nastepca(RBT *korzen)
{
	RBT *tmp = korzen;
	if (tmp->prawy != NULL){
		return minWezel(tmp->prawy);
	}
	RBT *rodzic = korzen->ojciec;
	while (rodzic != NULL && tmp == rodzic->prawy){
		tmp = rodzic;
		rodzic = rodzic->ojciec;
	}
	return rodzic;
}

void usunRBT_fix(RBT *korzen, RBT *tmp)
{
	while (tmp != korzen && tmp->kolor == BLACK){

		if (tmp == tmp->ojciec->lewy){
			RBT *brat = tmp->ojciec->prawy;

			if (brat->kolor == RED){    //przypadek 1 - brat x czerwony
				brat->kolor = BLACK;
				tmp->ojciec->kolor = RED;
				rotacjaLewa(&korzen, tmp->ojciec);
				brat = tmp->ojciec->prawy;
			}

			if (brat->lewy->kolor == BLACK && brat->prawy->kolor == BLACK){ //przypadek 2 - brat i jego synowie czarni
				brat->kolor = RED;
				tmp = tmp->ojciec;
			}else if (brat->prawy->kolor == BLACK){ //przypadek 3 - brat czarny, syn lewy czerwony, prawy czarny
				brat->lewy->kolor = BLACK;
				brat->kolor = RED;
				rotacjaPrawa(&korzen, brat);
				brat = tmp->ojciec->prawy;
			}                                   //przypadek 4 - brat czarny, syn lewy czarny, prawy czerwony
			brat->kolor = brat->ojciec->kolor;
			tmp->ojciec->kolor = BLACK;
			brat->prawy->kolor = BLACK;
			rotacjaLewa(&korzen, tmp->ojciec);
			tmp = korzen;
		}else{  //odbicie lustrzane
			RBT *brat = tmp->ojciec->lewy;

			if (brat->kolor == RED){
				brat->kolor = BLACK;
				tmp->ojciec->kolor = RED;
				rotacjaPrawa(&korzen, tmp->ojciec);
				brat = tmp->ojciec->lewy;
			}

			if (brat->prawy->kolor == BLACK && brat->lewy->kolor == BLACK){
				brat->kolor = RED;
				tmp = tmp->ojciec;
			}else if (brat->lewy->kolor == BLACK){
				brat->prawy->kolor = BLACK;
				brat->kolor = RED;
				rotacjaLewa(&korzen, brat);
				brat = tmp->ojciec->lewy;
			}
			brat->kolor = brat->ojciec->kolor;
			tmp->ojciec->kolor = BLACK;
			brat->lewy->kolor = BLACK;
			rotacjaPrawa(&korzen, tmp->ojciec);
			tmp = korzen;
		}
	}
	tmp->kolor = BLACK;
}

RBT *usunRBT(RBT *korzen, RBT *tmp)
{
	int kluczUsuniety = tmp->klucz;
	RBT *x, *y;
	if (tmp->ojciec == NULL){
		printf("Nie mozna usunac %d\n", kluczUsuniety);
		return tmp;
	}

	if (tmp->lewy == NULL && tmp->prawy == NULL){ //nie ma synow
		x = tmp;
	} else {
		x = nastepca(tmp);
	}
	if (x->lewy != NULL){   //ma lewego syna
		y = x->lewy;
	}else{                  //ma prawego syna
		y = x->prawy;
	}

	if (y != NULL){
		y->ojciec = x->ojciec;
	}

	if (x->ojciec == NULL){    //x jest korzeniem
		korzen = y;
	}else if (x == x->ojciec->lewy){
		x->ojciec->lewy = y;
	}else{
		x->ojciec->prawy = y;
	}

	if (x != tmp){
		tmp->klucz = x->klucz;
	}

	if (x->kolor == BLACK){
		usunRBT_fix(korzen, y);
	}

	printf("Usunieto %d\n", kluczUsuniety);
	return x;
}

RBT *stworzWezel(int klucz)
{    //tworzy nowy wezel
	RBT *tmp = (RBT*) malloc(sizeof(RBT));
	tmp->ojciec = NULL;
	tmp->lewy = NULL;
	tmp->prawy = NULL;
	tmp->klucz = klucz;
	tmp->kolor = RED;
	return tmp;
}

RBT *szukajWezla(RBT *korzen, int x)    //zwraca adres wezla o wartosci x
{
	if (korzen){
		if (korzen->klucz == x){
			printf("Znaleziono %d\n", x);
			return korzen;
		}else{
			if (x < korzen->klucz){
				return szukajWezla(korzen->lewy, x);
			} else{
				return szukajWezla(korzen->prawy, x);
			}
		}
	}else{
		printf("W drzewie nie ma %d\n", x);
		RBT *tmp = stworzWezel(x);
		return tmp;
	}
}

void wstaw(RBT **korzen, RBT *tmp)  //wstawia nowy wezel do drzewa
{
	if ((*korzen) == NULL){
		*korzen = tmp;
		printf("Wstawiono %d\n", tmp->klucz);
		return;
	}else{
		if (tmp->klucz < (*korzen)->klucz){
			wstaw(&(*korzen)->lewy, tmp);
			(*korzen)->lewy->ojciec = *korzen;
		}else if (tmp->klucz >= (*korzen)->klucz){
			wstaw(&(*korzen)->prawy, tmp);
			(*korzen)->prawy->ojciec = *korzen;
		}
	}
}

void wstawRBT(RBT **korzen, int klucz)  //wstawienie i naprawa kolorow
{
	RBT *tmp = stworzWezel(klucz);
	wstaw(&(*korzen), tmp);
	RBT *rodzic = NULL;
	RBT *dziadek = NULL;
	while ((tmp != *(korzen)) && (tmp->ojciec->kolor == RED)){
		rodzic = tmp->ojciec;
		dziadek = tmp->ojciec->ojciec;
		if (rodzic == dziadek->lewy){
			RBT *stryj = dziadek->prawy;
			if (stryj != NULL && stryj->kolor == RED){ //przypadek 1 - brat ojca czerwony
				stryj->kolor = BLACK;
				dziadek->kolor = RED;
				rodzic->kolor = BLACK;
				tmp = dziadek;
			}else{
				if (tmp == rodzic->prawy){  //przypadek 2 - ojciec i wezel tworza zakret
					rotacjaLewa(korzen, rodzic);
					tmp = rodzic;
					rodzic = tmp->ojciec;
				}                           //przypadek 3 - ojciec i wezel leza w jednej linii
				rodzic->kolor = BLACK;
				dziadek->kolor = RED;
				rotacjaPrawa(korzen, dziadek);
			}
		}else{  //lustrzane odbicie sytuacji powyzej
			RBT *stryj = dziadek->lewy;
			if (stryj != NULL && stryj->kolor == RED){
				dziadek->kolor = RED;
				rodzic->kolor = BLACK;
				tmp = dziadek;
			}else{
				if (tmp == rodzic->lewy){
					rotacjaPrawa(korzen, rodzic);
					tmp = rodzic;
					rodzic = tmp->ojciec;
				}
				rodzic->kolor = BLACK;
				dziadek->kolor = RED;
				rotacjaLewa(korzen, dziadek);
			}
		}
	}
	(*korzen)->kolor = BLACK;
}

void drukujOst(RBT *w, int l, int p,int poziom)
{
    int srodek = (l+p)/2;
    if (w==NULL) return;
    wydruk[poziom][srodek]='*';
}

void drukujWew(RBT *w, int l, int p,int poziom)
{
    int srodek = (l+p)/2;
    int ilosc = (l+p)/4;
    int i,dl;
    char s[19];
    if (w==NULL) return;
    if (w->kolor==BLACK)
        dl=sprintf(s,"(%d)",w->klucz);
    else
        dl=sprintf(s,"[%d]",w->klucz);
    for (i=0;i<dl;i++)
        wydruk[poziom][srodek-dl/2+i]=s[i];
    if (++poziom<IL_POZ){
        drukujWew(w->lewy,l,srodek,poziom) ;
        drukujWew(w->prawy,srodek+1,p,poziom) ;
    }else{
        drukujOst(w->lewy,l,srodek,poziom) ;
        drukujOst(w->prawy,srodek+1,p,poziom) ;
    }
}

void drukuj(RBT *w)
{
    int j,i;
    for (i=0;i<=IL_POZ;i++)
        for (j=0;j<SZER_EKR;j++)
            wydruk[i][j] = ' ';
    drukujWew(w,0,SZER_EKR,0);
    for (i=0;i<=IL_POZ;i++){
        for (j=0;j<SZER_EKR;j++)
            putchar(wydruk[i][j]);
        printf("\n");
    }
}

int maxWysokosc(RBT *root) 
{
   	if (root==NULL) 
   	    return 0;
  	else{
       /* compute the depth of each subtree */
      	int wysL = maxWysokosc(root->lewy);
     	int wysP = maxWysokosc(root->prawy);
 
       	/* use the larger one */
       	if (wysL > wysP) 
           	return(wysL+1);
       	else return(wysP+1);
	}
} 

int minWysokosc(RBT *root) 
{
   	if (root==NULL) 
   	    return 0;
  	else{
       /* compute the depth of each subtree */
      	int wysL = minWysokosc(root->lewy);
     	int wysP = minWysokosc(root->prawy);
 
       	/* use the larger one */
       	if (wysL < wysP) 
           	return(wysL+1);
       	else return(wysP+1);
   	}
}

int ileCzerwonych(RBT *root) {
    int ile = 0;
    if (root == NULL) {
        return 0;
    }
    ile += ileCzerwonych(root->lewy);
    ile += ileCzerwonych(root->prawy);

    if(root->kolor == RED){
        ile++;
    }
    return ile;
} 
