#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Edge
{
  int x, y, c;
  // Default constructor
  Edge() : x(0), y(0), c(0) {}

  // Constructor
  Edge(int x, int y, int c) : x(x), y(y), c(c) {}
};

class SpanningTree
{
public:
  int n;
  vector<Edge> G;
  vector<int> parent;
  // Constructor to initialize the graph and parent vector
  SpanningTree(int n, vector<Edge> G) : n(n), G(G), parent(n, -1) {}

  // Method to find the representative of a set
  int findRepresentative(int x)
  {
    if (parent[x] == -1)
    {
      return x;
    }
    // parent[x] = findRepresentative(parent[x]); // Path compression
    // return parent[x];
    return findRepresentative(parent[x]);
  }

  // Method to compute the savings in the spanning tree
  int computeSavings()
  {
    int savings = 0;
    int i = 0;
    int added = 0;
    while (added < n - 1 and i < G.size())
    {
      int rx = findRepresentative(G[i].x);
      int ry = findRepresentative(G[i].y);
      if (rx != ry)
      {
        parent[ry] = rx; // Union
        ++added;
      }
      else
      {
        savings += G[i].c;
      }
      ++i;
    }
    while (i < G.size())
    {
      savings += G[i].c;
      ++i;
    }
    return savings;
  }
};

int main()
{
  while (true)
  {
    // Read the number of towns (vertices) n and the number of roads (edges) m
    int n, m;
    cin >> n >> m;

    if (cin.peek() == EOF)
      break; // after some cin to skip trailing whitespace

    vector<Edge> G(m);

    // Read m triples x y c, indicating that the maintenance cost of the road between x and y is c
    for (int i = 0; i < m; i++)
    {
      int x, y, c;
      cin >> x >> y >> c;
      G.push_back(Edge(x, y, c));
    }

    // Sorting the G by cost
    sort(G.begin(), G.end(), [](const Edge &a, const Edge &b)
         { return a.c < b.c; });

    SpanningTree *spanning_tree = new SpanningTree(n, G);
    int savings = spanning_tree->computeSavings();
    cout << savings << endl;
    delete spanning_tree;
  }
}