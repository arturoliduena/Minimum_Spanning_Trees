## Cuts
### Statement   

The government of a distant country is cutting as much as possible. Now they have noticed that, often, there is more than one path that goes from one town to another town (either a direct road, or a sequence of roads passing through other intermediate towns). Since every road has some maintenance cost, the government has decided to eliminate several roads to save as much as possible, but keeping the road system connected. Can you calculate the maximum savings?

### Input

Input consists of several cases. Every case begins with the number of towns (vertices) n and the number of roads (edges) m. Follow m triples x y c, indicating that the maintenance cost of the road between x and y is c. Towns are numbered from 0 to n − 1. Assume 1 ≤ n ≤ 104, n − 1 ≤ m ≤ 10 n, and 1 ≤ c ≤ 104. There may be more than one road between two towns, and even roads with x = y. Every given graph is connected.

### Output

For every case, print the maximum savings achiving that there is exactly one path between every pair of towns.
