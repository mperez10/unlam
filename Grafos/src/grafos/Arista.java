package grafos;

public class Arista implements Comparable<Arista> {
	private Nodo vertice1, vertice2;
	private int peso;
	
	public Arista(Nodo a, Nodo b, int p) {
		vertice1 = a;
		vertice2 = b;
		peso = p;
	}
	
	public Nodo otro(Nodo a){
		if(vertice1.getNroNodo() == a.getNroNodo())
			return vertice2;
		else
			return vertice1;
	}

	public int getPeso() {
		return peso;
	}

	public boolean unVerticeNoVisitado() {
		if (!vertice1.visitado() || !vertice2.visitado())
			return true;
		else
			return false;
	}
	
	public void verticesVisitados() {
		vertice1.setVisitado(true);
		vertice2.setVisitado(true);
	}
	
	@Override
	public String toString() {
		if(vertice1.getAristasVecinos().contains(this)) {
			if(!vertice2.getAristasVecinos().contains(this))
				return vertice1.getNroNodo() + " --> " + vertice2.getNroNodo();
			else
				return vertice1.getNroNodo() + " <-> " + vertice2.getNroNodo();
		}
		else
			return vertice2.getNroNodo() + " --> " + vertice1.getNroNodo();
	}

	@Override
	public int compareTo(Arista o) {
		return this.peso - o.peso;
	}

	@Override
	public boolean equals(Object obj) {
		Arista otro = (Arista) obj;
		int nroVertice1 = this.vertice1.getNroNodo(),
			nroVertice2 = this.vertice2.getNroNodo(),
			nroVerticeOtro1 = otro.vertice1.getNroNodo(),
			nroVerticeOtro2 = otro.vertice2.getNroNodo();
		if (nroVertice1 == nroVerticeOtro1 && nroVertice2 == nroVerticeOtro2 ||
			nroVertice1 == nroVerticeOtro2 && nroVertice2 == nroVerticeOtro1)
			return true;
		else
			return false;
	}

	@Override
	public int hashCode() {
		return (vertice1.getNroNodo() + vertice2.getNroNodo()) * peso;
	}

	public Nodo getVerticeNoVisitado() {
		if(!vertice1.visitado())
			return vertice1;
		else if(!vertice2.visitado())
			return vertice2;
		else
			return null;
	}
	
	
	
}
