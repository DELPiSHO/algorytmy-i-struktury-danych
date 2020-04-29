package wyszukiwanieWzorca;

import java.io.*;

public class Main {
	private final static int d=256;
	private final static int q=27077;
	
	private static String odczytPliku(String file) throws IOException {
	    BufferedReader reader = new BufferedReader(new FileReader (file));
	    String line = null;
	    StringBuilder stringBuilder = new StringBuilder();

	    try {
	        while((line = reader.readLine()) != null) {
	            stringBuilder.append(line);
	        }

	        return stringBuilder.toString();
	    } finally {
	        reader.close();
	    }
	}
	
	public static void naiwny(String P, String T) {
		int i, j;
        int m = P.length();
        int n = T.length();

        //przechodzimy P[] znak po znaku
        for (i = 0; i <= n - m; i++) {
        	//dla obecnego i sprawdzamy zgodnosc z wzorcem
            for (j = 0; j < m; j++)
                if (T.charAt(i + j) != P.charAt(j))
                    break;
 
            if (j == m) //jesli P[0...m-1] = T[i, i+1, ... , i+m-1]
                System.out.println("Wzorzec znaleziony na indeksie: " + i);
        }
    }
	
	static void RabinKarp(String P, String T) {
        int m = P.length();
        int n = T.length();
        int i, j;
        int p = 0;
        int t = 0;
        int h = 1;
     
        for (i = 0; i < m-1; i++)
            h = (h*d)%q;
     
        //liczy hash wzorca i tekstu
        for (i = 0; i < m; i++){
            p = (d*p + P.charAt(i))%q;
            t = (d*t + T.charAt(i))%q;
        }
     
        for (i = 0; i <= n - m; i++){
        	//sprawdza wartosci hasha dla tekstu i wzorca, jesli sie zgadzaja sprawdza znak po znaku
            if ( p == t ){
                /* sprawdza znak po znaku */
                for (j = 0; j < m; j++){
                    if (T.charAt(i+j) != P.charAt(j))
                        break;
                }
                // jesli p == t i P[0...m-1] = T[i, i+1, ...i+m-1]
                if (j == m)
                    System.out.println("Wzorzec znaleziony na indeksie: " + i);
            }
            if ( i < n-m ){
                t = (d*(t - T.charAt(i)*h) + T.charAt(i+m))%q;
     
                //zamiana na dodatnia w razie ujemnej wartosci
                if (t < 0)
                t = (t + q);
            }
        }
    }
		
	 private static void KMP(String P, String T) {
	        int m = P.length();
	        int n = T.length();
	 
	        int pi[] = new int[m];
	        int j = 0;  // indeks dla P[]
	 
	        prefixFunction(P, pi);  //liczymy tablice pi
	 
	        int i = 0;  // indeks dla T[]
	        while (i < n){
	            if (P.charAt(j) == T.charAt(i)){
	                j++;
	                i++;
	            }
	            if (j == m){
	                System.out.println("Wzorzec znaleziony na indeksie: " + (i-j));
	                j = pi[j-1];
	            }
	 
	            // niedopasowanie po j pasujacym
	            else if (i < n && P.charAt(j) != T.charAt(i)){
	                if (j != 0)
	                    j = pi[j-1];
	                else
	                    i = i+1;
	            }
	        }
	    }
	 
	    private static void prefixFunction(String P, int pi[]) {
	        int len = 0;
	        int m = P.length();
	        int i = 1;
	        pi[0] = 0;
	 
	        // petla liczy pi[i] od i=1 do m-1
	        while (i < m){
	            if (P.charAt(i) == P.charAt(len)){
	                len++;
	                pi[i] = len;
	                i++;
	            }
	            else {  // (P[i] != P[len]
	                if (len != 0)
	                    len = pi[len-1];
	                else {  // if (len == 0)
	                    pi[i] = len;
	                    i++;
	                }
	            }
	        }
	    }
	
	public static void main(String [ ] args) throws IOException{
		String P, T;
		long czasRozpN, czasZakN, czasTrwN;
		long czasRozpRK, czasZakRK, czasTrwRK;
		long czasRozpKMP, czasZakKMP, czasTrwKMP;
		
		P = odczytPliku("src/wzorzec.txt");
		T = odczytPliku("src/tekst.txt");
		
		System.out.println("Naiwny: ");
		czasRozpN = System.nanoTime();
		naiwny(P, T);
		czasZakN = System.nanoTime();
		czasTrwN = czasZakN - czasRozpN;
		System.out.println("Czas trwania: " + czasTrwN + " ns");
		
		System.out.println("\nRabin-Karp: ");
		czasRozpRK = System.nanoTime();
		RabinKarp(P, T);
		czasZakRK = System.nanoTime();
		czasTrwRK = czasZakRK - czasRozpRK;
		System.out.println("Czas trwania: " + czasTrwRK + " ns");
		
		System.out.println("\nKnuth-Morris-Pratt: ");
		czasRozpKMP = System.nanoTime();
		KMP(P, T);
		czasZakKMP = System.nanoTime();
		czasTrwKMP = czasZakKMP - czasRozpKMP;
		System.out.println("Czas trwania: " + czasTrwKMP + " ns");
	}	
}
