// struktura wezla B-drzewa i przyklad zapisu i odczytu na plik
// budowanie B-drzewa o zadanej wysokosci i drukowanie


#include <stdio.h>
#define T 3 // stopien B-drzewa

typedef struct {
	short wPliku;
	short wWezle;
} Pozycja;

typedef struct{
	short n;//ilosc kluczy (-1 oznacza wezel usuniety)
	short leaf; // czy lisc
	int k[2*T-1]; // klucze
	int c[2*T]; // wskazniki do synow (pozycje w pliku: 0,1,2 ...)
	int info[2*T-1];// wskazniki do informacji skojarzonej z kluczem
	// (pozycje w innym pliku); tutaj nie beda uzyte
} Wezel;

void rozbij(int wezel, int rodzic, int wstawiana);
Pozycja szukaj(int r, int szukana);
void wstaw(int r, int wstawiana);

int rozmiarw = sizeof(Wezel); // rozmiar wezla w bajtach
FILE *drzewo;// plik drzewa (zawierajacy wezly)

static int klucz=0; // kolejny klucz
static int pozycja=0; // wolna pozycja w pliku
int czyRozbijane = 0;

void zapisz(int i,Wezel *w){
	// zapisuje *w jako i-ty zapis w pliku drzewa
	fseek(drzewo,(long)i*rozmiarw,SEEK_SET);
	fwrite(w,rozmiarw,1,drzewo);
	//printf("z%d ",i);
}

void odczytaj(int i,Wezel *w){
	// odczytuje i-ty zapis w pliku drzewa i wpisuje do *w
	fseek(drzewo,(long)i*rozmiarw,SEEK_SET);
	fread(w,rozmiarw,1,drzewo);
	//printf("o%d ",i);
}

void usun(int i){
	// usuwa i-ty zapis w pliku drzewa
	// w tej wersji nie wykorzystujemy usunietych pozycji,
	// tylko zaznaczamy jako usuniete
	Wezel w;
	odczytaj(i,&w);
	w.n=-1;
	zapisz(i,&w);
}

int budujB(int g, int n){
	// buduje B-drzewo o wysokosci g, w kazdym wezle jest n kluczy
	// wynikiem jest pozycja korzenia w pliku - jest to ostatni 
	// zapis w pliku, co jest wazne dla dalszych zapisow do pliku
	// ktore trzeba robic zaczynajac od kolejnej pozycji
	Wezel w;
	w.n=n;
	int i;
	if (g==0){	// lisc
		for (i=0;i<n;i++){
			w.c[i]= -1; // w lisc
			w.k[i]= klucz;
			klucz += 3;
		}
		w.c[n]= -1;
		w.leaf=1;
	} else {	// wezel wewnetrzny
		for (i=0;i<n;i++){
			w.c[i]= budujB(g-1,n);
			w.k[i]= klucz;
			klucz += 2;
		}
		w.c[n]= budujB(g-1,n);;
		w.leaf=0;
	}
	zapisz(pozycja++,&w);
	return pozycja-1;
}

void drukujB(int r, int p){
	// drukuje B-drzewo o korzeniu r (pozycja w pliku)
	// wydruk przesuniety o p w prawo
	Wezel w;
	int i,j;
	odczytaj(r,&w);
	if (w.leaf){
		for (i=0;i<p;i++) printf(" ");
		for (i=0;i<w.n;i++) printf("%d ",w.k[i]);
		printf("\n");
	} else {
		drukujB(w.c[w.n],p+4);
		for (i=w.n-1;i>=0;i--){
			for (j=0;j<p;j++) printf(" ");
			printf("%d\n",w.k[i]);
			drukujB(w.c[i],p+4);
		}
	}
}


void sortuj(int tab[], int n) {
	int c, d, pom;

	for (c = 0 ; c < ( n - 1 ); c++) {
		for (d = 0 ; d < n - c - 1; d++) {
			if (tab[d] > tab[d+1]) {
				pom = tab[d];
        			tab[d] = tab[d+1];
        			tab[d+1] = pom;
			}
		}
	}
}

void rozbij(int rodzic, int syn, int wstawiana) {
	Wezel wSyn, wRodzic, wNowy;
	int srodWar, i;
	int wstawInd;
	czyRozbijane = 1;
	
	odczytaj(syn,&wSyn);
	odczytaj(syn,&wNowy);
	odczytaj(rodzic,&wRodzic);
	
	srodWar = wSyn.k[T-1];
	
	if(wSyn.leaf) {
		wSyn.k[wSyn.n] = wstawiana;
		wSyn.n++;
		sortuj(wSyn.k, wSyn.n);
	}
	wRodzic.k[wRodzic.n] = srodWar;
	(wRodzic.n)++;
	sortuj(wRodzic.k, wRodzic.n);
	for(i = 0; i < wRodzic.n; i++) {
		if(wRodzic.k[i] == srodWar) {
			wstawInd = i;
		}
	}
	int n = 0;
	for(i = 0; i < wSyn.n; i++) {
		wNowy.k[i] = wSyn.k[wSyn.n-1-i];
		if(wNowy.k[i] > srodWar) {
			n++;
		}
	}
	wNowy.n = n;
	wSyn.n = wSyn.n-n-1;
	
	sortuj(wNowy.k, wNowy.n);
	
	usun(syn);
	zapisz(syn, &wSyn);
	usun(rodzic);
	
	zapisz(pozycja, &wNowy);
	
	for(i = wRodzic.n+1; i > wstawInd+1; i--) {
		wRodzic.c[i] = wRodzic.c[i-1];
	}
	wRodzic.c[wstawInd+1] = pozycja;
	pozycja++;
	
	zapisz(rodzic, &wRodzic);
}

Pozycja szukaj(int r, int szukana) {
	Wezel w, wPom;
	Pozycja poz;
	poz.wPliku = -1;
	poz.wWezle = -1;
	int i;
	odczytaj(r,&w);
	
	for(i = 0; i < w.n; i++) {
		if(szukana == w.k[i]) {
			poz.wPliku = r;
			poz.wWezle = i;
			return poz;
		}
		else if(szukana < w.k[i] && !(w.leaf)) {
			odczytaj(w.c[i], &wPom);
			if(wPom.n == 2*T-1) {
				rozbij(r, w.c[i], szukana);
			}
			return szukaj(w.c[i], szukana);
		}
		else if(szukana > w.k[i] && i == ((w.n)-1) && !(w.leaf)) {
			odczytaj(w.c[w.n], &wPom);
			if(wPom.n == 2*T-1) {
				rozbij(r, w.c[w.n], szukana);
			}
			return szukaj(w.c[w.n], szukana);
		}
		else if(szukana != w.k[i] && i == ((w.n)-1) && w.leaf) {
			poz.wPliku = r;
			poz.wWezle = -1;
			return poz;
		}
	}
}

void wstaw(int r, int wstawiana) {
	Pozycja pozycja;
	Wezel wezel;
	int i, poz;
	
	pozycja = szukaj(r, wstawiana);
	odczytaj(pozycja.wPliku, &wezel);
	
	if(wezel.n < 2*T-1 && pozycja.wWezle == -1) {
		wezel.k[wezel.n] = wstawiana;
		(wezel.n)++;
		sortuj(wezel.k, wezel.n);
	}
	else {
		poz = pozycja.wWezle;
		pozycja = szukaj(wezel.c[poz], wstawiana);
		wstaw(pozycja.wPliku, wstawiana);
		return;
	}
	
	if(czyRozbijane == 0) {
		usun(pozycja.wPliku);
		zapisz(pozycja.wPliku, &wezel);
	}
	czyRozbijane = 0;
}

int main(){
	drzewo = fopen("bdrzewo","w+");
	int root;
	Pozycja poz;
	int szukana, wstawiana;
	int wybor = -1;

	root=budujB(2,3);
	drukujB(root,0);
	
	while(wybor != 0) {
		printf("1- szukaj, 2- wstaw, 3- drukuj, 0- wyjdz\n");
		scanf("%i", &wybor);

		switch(wybor) {
			case 1:
				printf("znajdz wartosc (-1 konczy)\n");
				scanf("%i", &szukana);
				while(szukana != -1) {
					poz = szukaj(root, szukana);
					printf("%i %i\n", poz.wPliku, poz.wWezle);
					scanf("%i", &szukana);
				}

			break;
			case 2:
				printf("wstaw wartosc (-1 konczy)\n");
				scanf("%i", &wstawiana);
				while(wstawiana != -1) {
					wstaw(root, wstawiana);
					scanf("%i", &wstawiana);
				}

			break;
			case 3:
				drukujB(root,0);
			break;
		}
	}

	fclose(drzewo);
	return 0;
}
