public class Wezel {
	private Wezel lSyn;
	private Wezel pSyn;
	private int wartosc;
	private String znak;
	private String kod;
	
	Wezel(String znak){
		this.znak=znak;
		this.lSyn=null;
		this.pSyn=null;
	}
	Wezel(Wezel lSyn, Wezel pSyn, int wartosc, String znak){
		this.lSyn=lSyn;
		this.pSyn=pSyn;
		this.wartosc=wartosc;
		this.znak=znak;
	}
	
	public Wezel getpSyn() {
		return pSyn;
	}
	public void setpSyn(Wezel pSyn) {
		this.pSyn = pSyn;
	}
	public Wezel getlSyn() {
		return lSyn;
	}
	public void setlSyn(Wezel lSyn) {
		this.lSyn = lSyn;
	}
	public int getWartosc() {
		return wartosc;
	}
	public void setWartosc(int wartosc) {
		this.wartosc = wartosc;
	}
	public String getZnak() {
		return znak;
	}
	public void setZnak(String znak) {
		this.znak = znak;
	}
	public String getKod() {
		return kod;
	}
	public void setKod(String kod) {
		this.kod = kod;
	}
	
	boolean jestLisciem() {
		if(lSyn == null && pSyn == null)
			return true;
		else return false;
	}
}
