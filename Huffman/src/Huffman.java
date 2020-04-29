import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class Huffman {
	private List<Wezel> lista = new ArrayList<Wezel>();
	
	Huffman(){
		stworzListe();
		zbudujDrzewo();
	}
	
	void dodajWezel(String c) {
		int ind=znajdzIndZnaku(c);
		if(ind==-1) {
			Wezel w = new Wezel(null, null, 1, c);
			lista.add(w);
		}
		else {
			lista.get(ind).setWartosc(lista.get(ind).getWartosc()+1);
		}
	}
	
	int znajdzIndZnaku(String c) {
		for(Wezel w : lista) {
			if(w.getZnak().equals(c))
				return lista.indexOf(w);
		} return -1;
	}
	
	Wezel znajdzMin() {
		int indexMin=0;
		for(Wezel w : lista)
			if(w.getWartosc()<lista.get(indexMin).getWartosc())
				indexMin=lista.indexOf(w);
		return lista.get(indexMin);
	}
	
	public List<Wezel> getLista(){
		return lista;
	}
	
	void stworzListe() {
		File file = new File("src/test.txt");
		try {
			FileInputStream fis = new FileInputStream(file);
			char current;
			while (fis.available() > 0) {
				current = (char) fis.read();
				dodajWezel(Character.toString(current));
			}
			fis.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	void zbudujDrzewo() {
		Wezel z;
		int i=1;
		while(lista.size()>1) {
			Wezel w1 = znajdzMin();
			lista.remove(w1);
			Wezel w2 = znajdzMin();
			lista.remove(znajdzMin());
			
			z = new Wezel(w1, w2, w1.getWartosc()+w2.getWartosc(), "z"+i++);
			lista.add(z);
		}
	}
	
	void wypiszListe() {
		for(Wezel w : lista) {
			System.out.println(w.getZnak()+" : "+w.getWartosc());
		}
	}
	
	void koduj(Wezel w, StringBuffer pre) {
		if(w.jestLisciem()) {
			w.setKod(pre.toString());
		}
		else {
			pre.append('0');
			koduj(w.getlSyn(), pre);
			pre.deleteCharAt(pre.length()-1);
			
			pre.append('1');
            koduj(w.getpSyn(), pre);
            pre.deleteCharAt(pre.length()-1);
		}	
	}
	
	void wypiszDrzewo(Wezel w) {
		if(w.jestLisciem()) {
			System.out.println(w.getZnak()+" : "+w.getWartosc()+" : "+w.getKod());
		}else {
			wypiszDrzewo(w.getlSyn());
			wypiszDrzewo(w.getpSyn());
		}
	}
}
