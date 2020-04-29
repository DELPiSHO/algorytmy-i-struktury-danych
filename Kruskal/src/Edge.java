public class Edge {
	private int u, v, waga;
	
	Edge(int u, int v, int waga){
		this.u=u;
		this.v=v;
		this.waga=waga;
	}
	
	public int getU() {
		return u;
	}

	public void setU(int u) {
		this.u = u;
	}

	public int getV() {
		return v;
	}

	public void setV(int v) {
		this.v = v;
	}

	public int getWaga() {
		return waga;
	}

	public void setWaga(int waga) {
		this.waga = waga;
	}
}
