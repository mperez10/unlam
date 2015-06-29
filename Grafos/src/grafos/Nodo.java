package grafos;

import java.util.ArrayList;

public class Nodo implements Comparable<Nodo> {
	private ArrayList<Enlace> vecinos;
	private boolean visitado = false;
	private int nroNodo;
	private int grado = 0;
	private int color;
	
	public Nodo(int n) {
		nroNodo = n;
		vecinos = new ArrayList<Enlace>();
		color = -1;
	}
	
	public void addVecino(Nodo nodo, int costo) {
		vecinos.add( new Enlace(nodo, costo));
		grado++;
	}
	
	public boolean esVecino(Nodo nodo) {
		return vecinos.contains(nodo);
	}
	
	public int getCosto(Nodo vecino) {
		for (Enlace arista : vecinos) {
			if(arista.getExtremo() == vecino)
				return arista.getPeso();
		}
		return Grafo.INFINITO;
	}
	
	public ArrayList<Enlace> getVecinos() {
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
	
	public int getGrado() {
		return grado;
	}

	@Override
	public int compareTo(Nodo o) {
		return this.getGrado() - o.getGrado();
	}
	
	public int getColor() {
		return color;
	}
	
	public void setColor(int c) {
		color = c;
	}
	
	public boolean estaPintado() {
		return color != -1;
	}
}
