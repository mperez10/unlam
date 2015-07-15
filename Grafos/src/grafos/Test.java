package grafos;

import java.util.ArrayList;

public class Test {
	
	public static void main(String[] args) {
		ArrayList<Arista> solucion = null;
		int X = Grafo.INFINITO;
		int matriz1[][] = {  {0, 2, 4},
							{2, 0, 5},
							{4, 5, 0}  };
		int matriz2[][] = {  {0, 5, 4, X, X, X, X, 9},
							 {5, 0, 4, X, 1, X, 4, X},
							 {4, 4, 0, 3, X, X, X, X},
							 {X, X, 3, 0, 2, X, X, X},
							 {X, 1, X, 2, 0, 10, X, X},
							 {X, X, X, X, 10, 0, 2, 1},
							 {X, 4, X, X, X, 2, 0, 3},
							 {9, X, X, X, X, 1, 3, 0}  };
		int ejColoreo[][] = {  {0, 1, X, X, 1, X, X, X},
		                       {1, 0, 1, X, 1, X, X, 1},
		                       {X, 1, 0, 1, X, X, X, X},
		                       {X, X, 1, 0, 1, 1, 1, X},
		                       {1, 1, X, 1, 0, X, X, X},
		                       {X, X, X, 1, X, 0, X, X},
		                       {X, X, X, 1, X, X, 0, 1},
		                       {X, 1, X, X, X, X, 1, 0}  };
		int ejDijkstra[][] = { {0, 2, 6, 7, X},
							   {X, 0, X, 3, 6},
							   {X, X, 0, X, 1},
							   {X, X, X, 0, 5},
							   {X, X, X, X, 0} };
		int ejPrim[][] = { {0, 2, 5, X, X},
						   {2, 0, X, 2, 4},
						   {5, X, 0, X, X},
						   {X, 2, X, 0, 3},
						   {X, 4, X, 3, 0} };
		Grafo g = new Grafo(ejPrim);
//		g.DFS(g.getNodo(0));
//		g.BFS(g.getNodo(0));
//		g.resetEstadoNodos();
//		solucion = g.kruskal();
//		System.out.println(Grafo.costoCamino(camino));
//		System.out.println(g.colorear());
//		g.dijkstra(g.getNodo(0));
//		g.floyd();
		solucion = g.prim(g.getNodo(0));
		for (Arista arista : solucion) {
			System.out.println(arista.toString());
		}
	}
}
