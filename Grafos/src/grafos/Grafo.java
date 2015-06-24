package grafos;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Grafo {
	
	public static final int INFINITO = Integer.MAX_VALUE;
	private ArrayList<Nodo> nodos;
	
	Grafo(int adyacencia[][]) {
		// Constructor en base a matriz de adyacencia.
		nodos = new ArrayList<Nodo>(adyacencia.length);
		// Se agregan los nodos
		for(int i = 0; i < adyacencia.length; i++)
			nodos.add(new Nodo());
		// Se vinculan los nodos
		for (int i = 0; i < adyacencia.length; i++)
			for (int j = 0; j < adyacencia.length; j++)
				if(i != j && adyacencia[i][j] != INFINITO)
					nodos.get(i).addVecino(nodos.get(j), adyacencia[i][j]);
	}
	
	public void DFS(Nodo inicio) {
		inicio.setVisitado(true);
		for (Nodo vecino : inicio.getVecinos().keySet())
			// Para cada nodo vecino que no fue anteriormente
			// visitado, se realiza DFS.
			if(!vecino.visitado())
				DFS(vecino);
	}
	
	public void BFS(Nodo inicio) {
		Queue<Nodo> cola = new LinkedList<Nodo>();
		Nodo actual;
		cola.offer(inicio);
		inicio.setVisitado(true);
		while(!cola.isEmpty()) {
			// Hasta que la cola esta vacia:
			actual = cola.poll();
			for (Nodo vecino : actual.getVecinos().keySet())
				// Se agregan a la cola todos los nodos vecinos
				// que no hayan sido visitados anteriormente.
				if(!vecino.visitado()) {
					cola.offer(vecino);
					vecino.setVisitado(true);
				}
		}
	}
	
	public Nodo getNodo(int posicion) {
		return nodos.get(posicion);
	}
	
	public void resetEstadoNodos() {
		for (Nodo nodo : nodos)
			nodo.setVisitado(false);
	}
}
