#ifndef edgeconnected
#define edgeconnected

//Мостом в графе нзывается ребро после удаления котрого связный граф распадается на два не связанных между собой подграфа. 
//Граф у которого нет мостов называется реберно-связным(edge-connected)
template <class Graph>
class EC : public SEARCH<Graph>
{
	int bcnt;
	vector<int> low;
	void searchC(Edge e)
	{
		int w = e.w;
		ord[w] = cnt++;
		low[w] = ord[w];
		typename Graph::adjIterator A(G, w);
		for (int t = A.beg(); !A.end(); t = A.nxt())
		{
			if (ord[t] == -1)
			{
				searchC(Edge(w, t));
				if (low[w] > low[t])
					low[w] = low[t];
				if (low[t] == ord[t]) //если минимальный прямой номер равен
					bcnt++;
			}
			else if (t != e.v) //если вершина помечена и ссылка в t не родительная
				if (low[w] > ord[t]) //если ссыла в t - обратная
					low[w] = ord[t];
		}

	}
public:
	EC(const Graph &G) : SEARCH<Graph>(G), bcnt(0), low(G.V(), -1)
	{
		search();
	}
	int count() const { return bcnt + 1; }
};


#endif // edgeconnected
