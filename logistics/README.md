## CPSC 2120 - Algorithm and Data Structures
### Logistics Final Project
### Arnav Guneta

### Algorithm
I used the Ford-Fulkerson algorithm. 
The Ford-Fulkerson algorithm is a greedy algorithm used to find the maximum throughput through a graph. 
Although I couldn’t implement backwards capability, this algorithm uses breadth first search to find an augmenting path (a path with available capacity) from the source to the sink. 
- If the sink is not visited, a path does not exist, and the algorithm ends. 
- However, if a path does exist, the algorithm finds the maximum flow through the path found. It continues to do so until no path exists to the end node. 
An augmenting path has two conditions: a forward non-full edge, and a backwards non-empty edge.

To implement this algorithm:
- I created a list of cities, interconnected with links. 
I didn’t implement any bonus cases, but (just like with the A* algorithm) I chose to be time efficient rather than storage efficient. 
Each city acted as a node in the flow graph, connected by links which stored the flow, capacity, and the other connected city. 

### Functions
`organizeLogistics(start, finish)` -- where s and t are vector<pair<string,double>>, and your output is an unordered_map<int, double>. 

The int is the ID value for the edge, and the double is how much flow is on that edge in your final solution.
