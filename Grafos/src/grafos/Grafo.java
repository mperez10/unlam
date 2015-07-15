package grafos;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;

public class Grafo {
	
	public static final int INFINITO = Integer.MAX_VALUE;
	private ArrayList<Nodo> nodos;
	private ArrayList<Arista> aristas;
	
	public Grafo(int cantNodos) {
		nodos = new ArrayList<Nodo>();
		for (int i = 0; i < cantNodos; i++)
			nodos.add(new Nodo(i));
	} // Grafo vac�o
	
	public Grafo(int adyacencia[][]) {
		Set<Arista> aristasUnicas = new HashSet<Arista>();
		// Constructor en base a matriz de adyacencia.
		nodos = new ArrayList<Nodo>(adyacencia.length);
		// Se agregan los nodos
		for(int i = 0; i < adyacencia.length; i++)
			nodos.add(new Nodo(i));
		// Se vinculan los nodos y se crean las aristas correspondientes
		for (int i = 0; i < adyacencia.length; i++)
			for (int j = 0; j < adyacencia.length; j++)
				if(i != j && adyacencia[i][j] != INFINITO) {
					nodos.get(i).addVecino(nodos.get(i), nodos.get(j), adyacencia[i][j]);
					aristasUnicas.add(new Arista(nodos.get(i), nodos.get(j), adyacencia[i][j]));
				}
		aristas = new ArrayList<Arista>(aristasUnicas);
	}
	
	public void crearNodo(int n) {
		nodos.add(new Nodo(n));
	}
	
	public void unirVecino(int n, int v, int costo) {
		nodos.get(n).addVecino(nodos.get(n), nodos.get(v), costo);
	}
	
	public ArrayList<Arista> kruskal() {
		ArrayList<Arista> solucion = new ArrayList<Arista>();
		Arista actual;
		aristas.sort(null);
		for (int i = 0; i < aristas.size(); i++) {
			actual = aristas.get(i);
			if(actual.unVerticeNoVisitado()) {
				solucion.add(actual);
				actual.verticesVisitados();
			}
		}
		return solucion;
	}
	
	public int[] dijkstra(Nodo inicio) {
		Queue<Nodo> cola = new LinkedList<Nodo>();
		Nodo actual, nodoVecino;
		int nroNodoVecino;
		// distancia: vector con las distancias a cada nodo desde el nodo de inicio
		// padre: vector con los padres de cada nodo
		int distancia[] = new int[nodos.size()],
			padre[] = new int[nodos.size()];
		// Inicializa los vectores
		for (int i = 0; i < nodos.size(); i++) {
			distancia[i] = INFINITO;
			padre[i] = INFINITO;
		}
		// Dijkstra:
		distancia[inicio.getNroNodo()] = 0;
		padre[inicio.getNroNodo()] = 0;
		cola.offer(inicio);
		while(!cola.isEmpty()) {
			actual = cola.poll();
			for (Arista aristaVecino : actual.getAristasVecinos()) {
				nodoVecino = aristaVecino.otro(actual);
				// Agrega todos los vecinos a la cola
				cola.offer(nodoVecino);
				nroNodoVecino = nodoVecino.getNroNodo();
				// Si la distancia al nodo vecino m�s la distancia al nodo actual
				// desde el nodo inicial es menor que la distancia actual al nodo
				// vecino desde el nodo inicial, entonces se cambia por la menor
				// y tambi�n se cambia el padre del nodo vecino para que sea el nodo actual.
				if((aristaVecino.getPeso() + distancia[actual.getNroNodo()]) < distancia[nroNodoVecino]) {
					distancia[nroNodoVecino] = aristaVecino.getPeso() + distancia[actual.getNroNodo()];
					padre[nroNodoVecino] = actual.getNroNodo();
				}
			}
		}
		String distancias = "";
		for (int i = 0; i < distancia.length; i++) {
			distancias += distancia[i] + " ";
		}
		System.out.println("Nodo inicial: " + inicio.getNroNodo() + "\n" + distancias);
		return distancia;
	}
	
	public void floyd() { // Floyd trucho
		int[][] matrizDistancias = new int[nodos.size()][nodos.size()];
		for (int i = 0; i < nodos.size(); i++)
			matrizDistancias[i] = dijkstra(getNodo(i));
	}
	
	public int colorear() {
		int cantNodosColoreados = 0, colorActual = 0;
		boolean pintar;
		nodos.sort(null);
		while(cantNodosColoreados < nodos.size()) {
			colorActual++;
			pintar = true;
			for (Nodo actual : nodos) {
				if(!actual.estaPintado()) {
					for (Arista vecino : actual.getAristasVecinos())
						if (vecino.otro(actual).getColor() == colorActual)
							pintar = false;
					if (pintar) {
						actual.setColor(colorActual);
						cantNodosColoreados++;
					}
				}
			}
		}
		return colorActual;
	}
	
	public ArrayList<Arista> prim(Nodo inicio) {
		PriorityQueue<Arista> cola = new PriorityQueue<Arista>(inicio.getAristasVecinos());
		ArrayList<Arista> solucion = new ArrayList<Arista>();
		Arista aristaActualVecino;
		Nodo nodoActual = inicio;
		inicio.setVisitado(true);
		while(!cola.isEmpty()) {
			aristaActualVecino = cola.poll();
			if((nodoActual = aristaActualVecino.getVerticeNoVisitado()) != null) {
				solucion.add(aristaActualVecino);
				aristaActualVecino.verticesVisitados();
				for (Arista aristaDelVecino : nodoActual.getAristasVecinos())
					if(!solucion.contains(aristaDelVecino))
						cola.add(aristaDelVecino);
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
		for (Arista aristaVecino : inicio.getAristasVecinos()) {
			// Para cada nodo vecino que no fue anteriormente
			// visitado, se realiza DFS.
			vecino = aristaVecino.otro(inicio);
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
			for (Arista aristaVecino : actual.getAristasVecinos()) {
				vecino = aristaVecino.otro(actual);
				// Se agregan a la cola todos los nodos vecinos
				// que no hayan sido visitados anteriormente.
				if(!vecino.visitado()) {
					cola.offer(vecino);
					vecino.setVisitado(true);
				}
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
	
	public ArrayList<Nodo> getNodos() {
		return nodos;
	}
}
