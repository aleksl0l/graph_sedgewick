#ifndef gengraph
#define gengraph


//случайный граф
template<class Graph>
void randE(Graph &G, int E)
{
	for (int i = 0; i < E; i++)
	{
		int v = int(G.V()* rand() / (1.0 + RAND_MAX));
		int w = int(G.V()* rand() / (1.0 + RAND_MAX));
		G.insert(Edge(v, w));
	}
}

//случайный граф улучшенный
template<class Graph>
void randG(Graph &G, int E)
{
	double p = 2.0*E / G.V() / (G.V() - 1);
	for (int i = 0; i < G.V(); i++)
		for (int j = 0; j < i; j++)
		{
			if (rand() < p*RAND_MAX)
			{
				G.insert(Edge(i, j));
			}
		}
}
//написать k-граф


#endif // !gengraph
