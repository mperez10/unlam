package grafos;

public class Arista implements Comparable<Arista> {
	
	private Nodo extremo1, extremo2;
	private int peso;
	
	public Arista(Nodo i, Nodo j, int p) {
		extremo1 = i;
		extremo2 = j;
		peso = p;
	}

	@Override
	public int compareTo(Arista otraArista) {
		return this.peso - otraArista.getPeso();
	}
	
	public Nodo getExtremo1() {
		return extremo1;
	}
	
	public Nodo getExtremo2() {
		return extremo2;
	}
	
	public int getPeso() {
		return peso;
	}
}
