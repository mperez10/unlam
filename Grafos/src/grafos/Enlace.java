package grafos;

public class Enlace implements Comparable<Enlace> {
	
	private Nodo extremo;
	private int peso;
	
	public Enlace(Nodo i, int p) {
		extremo = i;
		peso = p;
	}

	@Override
	public int compareTo(Enlace otraArista) {
		return this.peso - otraArista.getPeso();
	}
	
	public Nodo getExtremo() {
		return extremo;
	}
	
	public int getPeso() {
		return peso;
	}
}
