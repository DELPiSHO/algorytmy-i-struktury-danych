import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Set {
	private static Node findSet(Node x) {
		if(!x.isRoot())
			x.setP(findSet(x.getP()));
		return x.getP();	
	}
	
	private static void union(Node x, Node y) {
		if(x.getRank() > y.getRank())
			y.setP(x);
		else {
			x.setP(y);
			if(x.getRank()==y.getRank())
				y.setRank(y.getRank()+1);
		}
	}
	
	private static void kruskal(int ilW, int ilK, List<Edge> E) {
		int i;
		Node ru, rv;
		Node V[] = new Node[ilW];
		EdgeComparator edComp = new EdgeComparator();
		for(i=0; i<ilW-1; i++)
			V[i]=new Node(i);
		Collections.sort(E, edComp);
		for(i=0; i<ilK-1; i++) {
			ru=findSet(V[E.get(i).getU()]);
			rv=findSet(V[E.get(i).getV()]);
			if(!ru.equals(rv)) {
				System.out.println(E.get(i).getU()+" "+E.get(i).getV());
				union(ru,rv);
			}
		}
	}
	
	public static void main(String [ ] args){
		List<Edge> E = new ArrayList<>();
	
		E.add(new Edge(0, 1, 2));
		E.add(new Edge(0, 2, 1));
		E.add(new Edge(0, 3, 3));
		E.add(new Edge(1, 2, 1));
		E.add(new Edge(1, 3, 3));
		E.add(new Edge(2, 3, 1));
		E.add(new Edge(3, 4, 2));
		E.add(new Edge(1, 4, 5));
		
		kruskal(6, E.size(), E);
		
	}
}
