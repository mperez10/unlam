package grafos;

import java.util.Hashtable;

public class Nodo {
	private Hashtable<Nodo, Integer> vecinos;
	private boolean visitado = false;
	
	public Nodo() {
		vecinos = new Hashtable<Nodo, Integer>();
	}
	
	public void addVecino(Nodo nodo, int costo) {
		vecinos.put(nodo, costo);
	}
	
	public void getCosto(Nodo nodo) {
		vecinos.get(nodo);
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
}
