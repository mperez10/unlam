package grafos;

import java.util.ArrayList;

public class Test {
	
	public static void main(String[] args) {
		ArrayList<Arista> camino = null;
		int inf = Grafo.INFINITO;
<<<<<<< HEAD
		int matriz1[][] = {  {0, 2, 4},
							{2, 0, 5},
							{4, 5, 0}  };
		int matriz2[][] = {  {0, 5, 4, inf, inf, inf, inf, 9},
							{5, 0, 4, inf, 1, inf, 4, inf},
							{4, 4, 0, 3, inf, inf, inf, inf},
							{inf, inf, 3, 0, 2, inf, inf, inf},
							{inf, 1, inf, 2, 0, 10, inf, inf},
							{inf, inf, inf, inf, 10, 0, 2, 1},
							{inf, 4, inf, inf, inf, 2, 0, 3},
							{9, inf, inf, inf, inf, 1, 3, 0}  };
		Grafo g = new Grafo(matriz2);
=======
		int matriz[][] = {  {0, 2, 4},
				    {inf, 0, 5},
				    {inf, inf, 0}  };
		Grafo g = new Grafo(matriz);
>>>>>>> origin/master
//		g.DFS(g.getNodo(0));
//		g.BFS(g.getNodo(0));
//		g.resetEstadoNodos();
		camino = g.kruskal();
		System.out.println(Grafo.costoCamino(camino));
	}
}
