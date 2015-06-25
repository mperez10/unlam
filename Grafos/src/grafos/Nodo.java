package grafos;

import java.util.Hashtable;

public class Nodo {
	private Hashtable<Nodo, Integer> vecinos;
	private boolean visitado = false;
	private int nroNodo;
	
	public Nodo(int n) {
		nroNodo = n;
		vecinos = new Hashtable<Nodo, Integer>();
	}
	
	public void addVecino(Nodo nodo, int costo) {
		vecinos.put(nodo, costo);
	}
	
	public boolean esVecino(Nodo nodo) {
		return vecinos.containsKey(nodo);
	}
	
	public int getCosto(Nodo vecino) {
		return vecinos.get(vecino);
	}
	
	public Hashtable<Nodo, Integer> getVecinos() {
		return vecinos;
	}
	
	public void setVisitado(boolean v) {
		visitado = v;
	}
	
	public boolean visitado() {
		return visitado;
	}
	
	public int getNodo() {
		return nroNodo;
	}
}
