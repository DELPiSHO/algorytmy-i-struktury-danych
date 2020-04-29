public class Main {
	Main(){}
	
	public static void main(String [ ] args){
		Huffman l = new Huffman();
		l.koduj(l.getLista().get(0), new StringBuffer());
		l.wypiszDrzewo(l.getLista().get(0));
	}
}
