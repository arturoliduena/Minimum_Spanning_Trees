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

int representantive(int x, vector<int> &parent)
{
  if (parent[x] == -1)
    return x;
  int repre = representantive(parent[x], parent);
  parent[x] = repre;
  return repre;
}

int spanning_tree(int n, const vector<Edge> &G)
{
  int savings = 0;
  vector<int> parent(n, -1);
  for (int i = 0; n > 1 and i < G.size(); ++i)
  {
    int rx = representantive(G[i].x, parent);
    int ry = representantive(G[i].y, parent);
    if (rx != ry)
    {
      parent[ry] = rx;
      // --n;
    }
    else
    {
      savings += G[i].c;
    }
  }
  return savings;
}

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

    int savings = spanning_tree(n, G);
    cout << savings << endl;
  }
}