package grafos;

import java.util.ArrayList;

public class Nodo implements Comparable<Nodo> {
//	private ArrayList<Enlace> vecinos;
	private ArrayList<Arista> aristasVecinos;
	private boolean visitado = false;
	private int nroNodo;
	private int grado = 0;
	private int color;
	
	public Nodo(int n) {
		nroNodo = n;
//		vecinos = new ArrayList<Enlace>();
		aristasVecinos = new ArrayList<Arista>();
		color = -1;
	}
	
	public void addVecino(Nodo vertice1, Nodo vertice2, int costo) {
		aristasVecinos.add(new Arista(vertice1, vertice2, costo));
		grado++;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + nroNodo;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Nodo other = (Nodo) obj;
		if (nroNodo != other.nroNodo)
			return false;
		return true;
	}

	public boolean esVecino(Nodo nodoVecino) {
		for (Arista aristaVecina : aristasVecinos)
			if(aristaVecina.otro(this).equals(nodoVecino))
				return true;
		return false;
	}
	
	public ArrayList<Arista> getAristasVecinos() {
		return aristasVecinos;
	}
	
//	public void addVecino(Nodo nodo, int costo) {
//		vecinos.add( new Enlace(nodo, costo));
//		grado++;
//	}
//	
//	public boolean esVecino(Nodo nodo) {
//		return vecinos.contains(nodo);
//	}
//	
//	public ArrayList<Enlace> getVecinos() {
//		return vecinos;
//	}
	
	public int getCosto(Nodo vecino) {
//		for (Enlace arista : vecinos) {
		for (Arista arista : aristasVecinos) {
//			if(arista.getExtremo() == vecino)
			if(arista.otro(this) == vecino)
				return arista.getPeso();
		}
		return Grafo.INFINITO;
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
