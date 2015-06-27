package grafos;

import java.util.ArrayList;

public class Nodo {
	private ArrayList<Arista> vecinos;
	private boolean visitado = false;
	private int nroNodo;
	
	public Nodo(int n) {
		nroNodo = n;
		vecinos = new ArrayList<Arista>();
	}
	
	public void addVecino(Nodo nodo, int costo) {
		vecinos.add( new Arista(nodo, costo));
	}
	
	public boolean esVecino(Nodo nodo) {
		return vecinos.contains(nodo);
	}
	
	public int getCosto(Nodo vecino) {
		for (Arista arista : vecinos) {
			if(arista.getExtremo() == vecino)
				return arista.getPeso();
		}
		return Grafo.INFINITO;
	}
	
	public ArrayList<Arista> getVecinos() {
		return vecinos;
	}
	
	public void setVisitado(boolean v) {
		visitado = v;
	}
	
	public boolean visitado() {
		return visitado;
	}
	
	public int getNroNodo() {
		return nroNodo;
	}
}
