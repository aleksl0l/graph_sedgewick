#ifndef edgestruct
#define edgestruct

struct Edge
{
	int v, w;
	Edge(int v = -1, int w = -1) :v(v), w(w) {}
};

#endif // !edge