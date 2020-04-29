public class Node {
	
	Node(int key){
		this.key=key;
		this.rank=0;
		this.p=this;
	}
	
	private int key;
	private Node p;
	private int rank;

	public int getKey() {
		return key;
	}
	public void setKey(int key) {
		this.key = key;
	}
	public Node getP() {
		return p;
	}
	public void setP(Node p) {
		this.p = p;
	}
	public int getRank() {
		return rank;
	}
	public void setRank(int rank) {
		this.rank = rank;
	}
	
	public boolean isRoot() {
		if(this.p.equals(this))
			return true;
		else return false;
	}
}
