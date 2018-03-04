#ifndef artpoint 
#define artpoint

#include "search.h"

//класс для поиска точек сочленения
template <class Graph>
class AP : public SEARCH<Graph>
{
	int pcnt;
	vector<int> low;
	void searchC(Edge e)
	{
		int w = e.w;
		low[w] = ord[w] = cnt++;
		typename Graph::adjIterator A(G, w);
		for (int t = A.beg(); !A.end(); t = A.nxt())
		{
			if (t == e.v)
				continue;
			if (ord[t] == -1)
			{
				searchC(Edge(w, t));
				if (low[w] > low[t])
					low[w] = low[t];
				if (low[t] >= ord[w] && ord[w] != e.v) //если минимальный прямой номер равен
					pcnt++;
			}
			else //if (t != e.v) //если вершина помечена и ссылка в t не родительная
			{
				if (low[w] > low[t])
					low[w] = low[t];
			}
		}

	}
public:
	AP(const Graph &G) : SEARCH<Graph>(G), pcnt(0), low(G.V(), -1)
	{
		search();
	}
	int count() const { return pcnt; }
};


#endif