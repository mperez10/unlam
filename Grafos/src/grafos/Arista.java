package grafos;

public class Arista implements Comparable<Arista> {
	
	private Nodo extremo;
	private int peso;
	
	public Arista(Nodo i, int p) {
		extremo = i;
		peso = p;
	}

	@Override
	public int compareTo(Arista otraArista) {
		return this.peso - otraArista.getPeso();
	}
	
	public Nodo getExtremo() {
		return extremo;
	}
	
	public int getPeso() {
		return peso;
	}
}
