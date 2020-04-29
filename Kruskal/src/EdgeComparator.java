import java.util.Comparator;

public class EdgeComparator implements Comparator<Edge>
{

	@Override
	public int compare(Edge e1, Edge e2) {
		if(e1.getWaga() > e2.getWaga()) return 1;
		else if(e1.getWaga() < e2.getWaga()) return -1;
		else return 0;
	}
}