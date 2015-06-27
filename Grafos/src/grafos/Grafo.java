package grafos;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Grafo {
	
	public static final int INFINITO = Integer.MAX_VALUE;
	private ArrayList<Nodo> nodos;
	
	public Grafo(int adyacencia[][]) {
		// Constructor en base a matriz de adyacencia.
		nodos = new ArrayList<Nodo>(adyacencia.length);
		// Se agregan los nodos
		for(int i = 0; i < adyacencia.length; i++)
			nodos.add(new Nodo(i));
		// Se vinculan los nodos y se crean las aristas correspondientes
		for (int i = 0; i < adyacencia.length; i++)
			for (int j = 0; j < adyacencia.length; j++)
				if(i != j && adyacencia[i][j] != INFINITO)
					nodos.get(i).addVecino(nodos.get(j), adyacencia[i][j]);
	}
	
	
	/* TODO ACTUALIZAR PARA LA NUEVA ESTRUCTURA
	public ArrayList<Arista> kruskal() {
		Hashtable<Nodo, Integer> caminoNodos = new Hashtable<Nodo, Integer>();
		ArrayList<Arista> caminoAristas = new ArrayList<Arista>();
		int menorNroCamino, mayorNroCamino, caminoAristaExtremo1, caminoAristaExtremo2;
		// Se agregan los nodos a tabla con su propio numero como numero de camino
		for (Nodo nodo : nodos)
			caminoNodos.put(nodo, nodo.getNodo());
		// Se ordenan y recorren las aristas de menor a mayor
		aristas.sort(null);
		for (Arista arista : aristas) {
			caminoAristaExtremo1 = caminoNodos.get(arista.getExtremo1());
			caminoAristaExtremo2 = caminoNodos.get(arista.getExtremo2());
			// Se diferencia el mayor numero de camino del menor
			menorNroCamino = Math.min(caminoAristaExtremo1, caminoAristaExtremo2);
			mayorNroCamino = Math.max(caminoAristaExtremo1, caminoAristaExtremo2);
			if ( caminoAristaExtremo1 != caminoAristaExtremo2) {
				for (Nodo nodo : caminoNodos.keySet())
					// Se reemplaza en los nodos que tienen el numero mayor
					// por el numero menor, para asi formar el nuevo camino
					if(caminoNodos.get(nodo) == mayorNroCamino)
						caminoNodos.replace(nodo, menorNroCamino);
				caminoAristas.add(arista);
			}
		}
		return caminoAristas;
	}
	*/
	
	public ArrayList<Arista> prim(Nodo inicio) { // TODO AGREGAR COMO OBTENER EL CAMINO
		PriorityQueue<Arista> cola = new PriorityQueue<Arista>();
		ArrayList<Arista> solucion = new ArrayList<Arista>();
		Arista vecino;
//		int padre[] = new int[nodos.size()];
//		padre[inicio.getNroNodo()] = inicio.getNroNodo();
		while(!cola.isEmpty()) {
			vecino = cola.poll();
			for (Arista arista : vecino.getExtremo().getVecinos()) {
				if(!solucion.contains(arista)) {
					solucion.add(arista);
					for (Arista aristaDelVecino : inicio.getVecinos())
						if(!solucion.contains(aristaDelVecino))
							cola.add(aristaDelVecino);
				}
			}
		}
		return solucion;
	}
	
	public static int costoCamino(ArrayList<Arista> camino) {
		int costoTotal = 0;
		for (Arista arista : camino)
			costoTotal += arista.getPeso();
		return costoTotal;
	}
	
	public void DFS(Nodo inicio) {
		Nodo vecino;
		inicio.setVisitado(true);
		for (Arista arista : inicio.getVecinos()) {
			// Para cada nodo vecino que no fue anteriormente
			// visitado, se realiza DFS.
			vecino = arista.getExtremo();
			if(!vecino.visitado())
				DFS(vecino);
		}
	}
	
	public void BFS(Nodo inicio) {
		Queue<Nodo> cola = new LinkedList<Nodo>();
		Nodo actual, vecino = null;
		cola.offer(inicio);
		inicio.setVisitado(true);
		while(!cola.isEmpty()) {
			// Hasta que la cola esta vacia:
			actual = cola.poll();
			for (Arista arista : actual.getVecinos())
				vecino = arista.getExtremo();
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
