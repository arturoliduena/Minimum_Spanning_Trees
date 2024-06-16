#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct edge
{
  int u, v;
  int cost;

  bool operator<(const edge &other) const
  {
    return (cost < other.cost);
  }
};

class UnionFind
{
protected:
  vector<int> P;
  int n_blocks;

public:
  // Default constructor
  UnionFind() : n_blocks(0) {}

  // Constructor with n elements - Creates the partition {{0}, {1}, ..., {n-1}}
  UnionFind(int n)
  {
    for (int i = 0; i < n; ++i)
    {
      P.push_back(i);
    };
    n_blocks = n;
  };

  bool merge(int i, int j)
  {
    int ri = find(i);
    int rj = find(j);
    if (ri != rj)
    {
      P[ri] = rj;
      --n_blocks;
      return true;
    }
    else
    {
      return false;
    }
  }

  // destructor
  ~UnionFind() {}

  // Returns the representative of the class to which i belongs
  int find(int i)
  {
    if (P[i] == i || P[i] < 0)
      return i;

    P[i] = find(P[i]);
    return P[i];
  }

  // Returns the number of blocks in the union-find set
  int nr_blocks() const
  {
    return n_blocks;
  };

  vector<int> Parents() const
  {
    return P;
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

    vector<edge> edges(m);
    // Read m triples x y c, indicating that the maintenance cost of the road between x and y is c
    for (int i = 0; i < m; i++)
    {
      cin >> edges[i].u;
      cin >> edges[i].v;
      cin >> edges[i].cost;
    }

    // sort edges by cost
    sort(edges.begin(), edges.end());

    UnionFind nodes(n);
    int savings = 0;
    for (int i = 0; i < m; i++)
    {
      const int u = edges[i].u, v = edges[i].v, cost = edges[i].cost;
      if (nodes.nr_blocks() == 1)
      {
        savings += cost;
        continue;
      }

      bool merged = nodes.merge(u, v);
      if (!merged)
      {
        savings += cost;
      }
    }

    cout << savings << endl;
  }
}