import java.util.ArrayList;
import java.util.concurrent.Callable;

public class MySolver implements Callable<ArrayList<Node>>{
	Node board;
	String heuristic;
	MySolver(Node b, String h) {
		board = b;
		heuristic = h;
	}
	@Override
	public ArrayList<Node> call() throws Exception {
		DB_Solver2 solver = new DB_Solver2(board, heuristic);
		Node path = solver.findSolutionPath();
		return solver.getSolutionPath(path);
	}

}
