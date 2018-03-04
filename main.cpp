#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <fstream>
#include <ctime>
#include <string>
#include <queue>

#include "densegraph.h"
#include "articulationpoint.h"
#include "pathfind.h"
#include "bipartite.h"

using namespace std;



//
//template<class Graph>
//class IO
//{
//public:
//	static void show(const Graph &);
//	static void scanEZ(Graph &);
//	static void scan(Graph &);
//};


//template<class Graph>
//void IO<Graph>::show(const Graph &G)
//{
//	for (int s = 0; s < G.V(); s++)
//	{
//		cout.width(2); cout << s << ":";
//		typename Graph::adjIterator A(G, s);
//		for (int t = A.beg(); !A.end()!; t = A.nxt())
//		{
//			cout.width(2);
//			cout << t << " ";
//		}
//		cout << endl;
//	}
//}


template <class Graph>
class DEGREE
{
	const Graph &G;
	vector<int> degree;
public:
	DEGREE(const Graph &G) : G(G), degree(G.V(), 0)
	{
		for (int v = 0; v < G.V(); v++)
		{
			typename Graph::adjIterator A(G, v);
			for (int w = A.beg(); !A.end(); w = A.nxt())
			{
				degree[v]++;
			}
		}
	}
	int operator[](int v) const
	{
		return degree[v];
	}
};



template <class Graph>
class DFS : public SEARCH<Graph>
{
	vector<int> st;
	void searchC(Edge e)
	{
		int w = e.w;
		ord[w] = cnt++; //used
		st[e.w] = e.v; //where
		typename Graph::adjIterator A(G, w);
		for (int t = A.beg(); !A.end(); t = A.nxt())
		{
			if (ord[t] == -1)
			{
				searchC(Edge(w, t));
			}
		}
	}
public:
	DFS(const Graph &G) : SEARCH<Graph>(G), st(G.V(), -1)
	{
		search();
	}
	int ST(int v) const
	{
		return st[v];
	}
};

template <class Graph>
class DFS2
{
private:
	const Graph &G;
	vector <int> used;
	vector <int> where;
	int it = 0;
public:
	DFS2(const Graph &_G) :G(_G), used(G.V(), -1), where(G.V(), -1) {
		for (int i = 0; i < G.V(); i++)
		{
			if (used[i] == -1) dfs(i);
		}
	}
	void dfs(int start) {
		Graph::adjIterator A(G, start);
		used[start] = it; it++;
		
		for (int j = A.beg(); !A.end(); j = A.nxt())
		{
			if (used[j] == -1) {
				dfs(j);
				where[j] = start;

			}
			
		}

	}
};


template <class Graph>
class BFS : public SEARCH<Graph>
{
	vector<int> st;
	void searchC(Edge e)
	{
		queue<Edge> Q;
		Q.push(e);
		while (!Q.empty())
		{
			e = Q.front();
			Q.pop();
			if (ord[e.w] == -1)
			{
				int v = e.v;
				int w = e.w;
				ord[w] = cnt++;
				st[w] = v;
				typename Graph::adjIterator A(G, w);
				for (int t = A.beg(); !A.end(); t = A.nxt())
					if (ord[t] == -1)
						Q.push(Edge(w, t));
			}
		}
	}
public:
	BFS(Graph &G): SEARCH<Graph>(G), st(G.V(), -1)
	{
		search();
	}
	int ST(int v) const { return st[v]; }
};

template <class Graph>
class G2neato
{
private:
	const Graph &G;

public:
	G2neato(const Graph &_G) :G(_G)
	{
	}

	void graph(string path)
	{
		ofstream myfile;
		myfile.open("graph");
		myfile << "Graph G{\ngraph [overlap=scale sep=3.5];\nnode [shape=point];\n";
		for (int i = 0; i < G.V(); i++)
		{
			Graph::adjIterator A(G, i);
			for (int j = A.beg(); !A.end(); j = A.nxt())
			{
				if (i <= j)
				{
					myfile << '\t' << i << " -- " << j << ";" << endl;
				}
			}
		}
		myfile << "}";
		myfile.close();
		system("circo graph -Tpng -o grapg.png && start grapg.png");
	}
	void bipartite_graph(string path)
	{
		BI<Graph> b(G);
		if (!b.bipartite())
			return;
		ofstream myfile;
		myfile.open("graph");
		myfile << "Graph G{\ngraph [splines=true overlap=scale sep=3.5];\nnode [shape=circle style=filled];\n";
		for (int i = 0; i < G.V(); i++)
		{
			string color = b.color(i) ? "blue" : "white";
			myfile << i << "[fillcolor=" << color << "];" << endl;
		}
		for (int i = 0; i < G.V(); i++)
		{
			Graph::adjIterator A(G, i);
			for (int j = A.beg(); !A.end(); j = A.nxt())
			{
				if (i <= j)
				{
					myfile << '\t' << i << " -- " << j << ";" << endl;
				}
			}
		}
		myfile << "}";
		myfile.close();
		system("sfdp -x graph -Tpng -o grapg.png && start grapg.png");
	}
};

int main()
{
	auto pr_vec = [](vector<int> &v) -> void
	{
		for_each(v.begin(), v.end(), [](int x) {cout << x << " "; });
	};




	DenseGRAPH G(5, false);
	srand(time(NULL));
	G.insert(Edge(0, 1));
	G.insert(Edge(0, 2));
	G.insert(Edge(1, 2));
	G.insert(Edge(1, 3));
	G.insert(Edge(3, 4));


	AP<DenseGRAPH> findBridge(G);
	cout << findBridge.count();
	/*DFS2<DenseGRAPH> bfs(G);*/
	//for (int t = 6; t != 1; t = bfs.ST(t))
	//	cout << t << '-';
	//cout << 1 << endl;



	G2neato<DenseGRAPH> N(G);
	N.bipartite_graph("");



	sPATH<DenseGRAPH> path(G, 0, 3);
	ePATH<DenseGRAPH> pa(G, 0, 2);
	cout << path.exists() << pa.exists() << endl;
	pa.show();
	//cout << singleNumber(vector<int>{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 5, 3, 4});

}

template<class Graph>
int ePATH<Graph>::tour(int v)
{
	while (true)
	{
		typename Graph::adjIterator A(G, v);
		int w = A.beg();
		if (A.end())
			break;
		S.push(v);
		G.remove(Edge(v, w));
		v = w;
	}
	return v;
}

template <class Graph>
void ePATH<Graph>::show()
{
	if (!found)
		return;
	while (tour(v) == v && !S.empty())
	{
		v = S.top();
		S.pop();
		cout << "-" << v;
	}
	cout << endl;
}