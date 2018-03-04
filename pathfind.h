#ifndef pathfind
#define pathfind


template<class Graph>
class ePATH {
	Graph G;
	int v, w;
	bool found;
	std::stack<int> S;

	int tour(int v);
public:
	ePATH(const Graph &G, int v, int w) :
		G(G), v(v), w(w)
	{
		DEGREE<Graph> deg(G);
		int t = deg[v] + deg[w];
		if ((t % 2) != 0)
		{
			found = false;
			return;
		}
		for (t = 0; t < G.V(); t++)
		{
			if ((t != v) && t != w)
			{
				if (deg[t] % 2 != 0)
				{
					found = false;
					return;
				}
			}
		}
		found = true;
	}
	bool exists() const
	{
		return found;
	}
	void show();
};

template <class Graph>
class sPATH
{
	const Graph &G;
	vector<bool> visited;
	bool found;
	//поиск в глубину
	bool searchR(int v, int w)
	{
		if (v == w) return true;
		visited[v] = true;
		typename Graph::adjIterator A(G, v);
		for (int t = A.beg(); !A.end(); t = A.nxt())
		{
			if (!visited[t])
			{
				if (searchR(t, w))
					return true;
			}
		}
		return false;
	}
public:
	sPATH(const Graph &G, int v, int w) :G(G), visited(G.V(), false)
	{
		found = searchR(v, w);
	}
	bool exists() const
	{
		return found;
	}
};

#endif // !pathfind