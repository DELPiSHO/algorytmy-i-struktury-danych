public class Wezel {
	private int n;
	private boolean leaf;
	private Wezel[] syn;
	private int[] key;
	
	Wezel(){
		setSyn(new Wezel[n+2]);
		setKey(new int[n]);
	}

	public boolean isLeaf() {
		return leaf;
	}

	public void setLeaf(boolean leaf) {
		this.leaf = leaf;
	}

	public Wezel[] getSyn() {
		return syn;
	}

	public void setSyn(Wezel[] syn) {
		this.syn = syn;
	}

	public int[] getKey() {
		return key;
	}

	public void setKey(int[] key) {
		this.key = key;
	}

	public int getN() {
		return n;
	}

	public void setN(int n) {
		this.n = n;
	}
	
	void rozbij(){
		Wezel z = new Wezel(this.n);
		z.leaf = 
	}
}
