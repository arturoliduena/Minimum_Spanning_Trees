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
  string line;

  // Read input until EOF
  while (getline(cin, line))
  {
    istringstream iss(line);

    // Read the first two numbers in each line
    int n, m;
    iss >> n >> m;

    vector<Edge> G(m);
    int count = 0;

    // Read remaining triplets
    int x, y, c;
    while (count < m && (iss >> x >> y >> c))
    {
      G.push_back(Edge(x, y, c));
      count++;
    }

    while (count < m && getline(cin, line))
    {
      istringstream next_iss(line);
      while (count < m && (next_iss >> x >> y >> c))
      {
        G.push_back(Edge(x, y, c));
        count++;
      }
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