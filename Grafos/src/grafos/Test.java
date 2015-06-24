package grafos;

public class Test {
	
	public static void main(String[] args) {
		int inf = Grafo.INFINITO;
		int matriz[][] = {  {0, 2, 4},
							{inf, 0, 5},
							{inf, inf, 0}  };
		Grafo g = new Grafo(matriz);
//		g.DFS(g.getNodo(0));
		g.BFS(g.getNodo(0));
		g.resetEstadoNodos();
	}
}
