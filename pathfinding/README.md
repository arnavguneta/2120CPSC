## CPSC 2120 - Algorithm and Data Structures
### Pathfinding Final Project
### Arnav Guneta

### Algorithm
I used the A* algorithm. The A* algorithm is popularly used to traverse through graphs and to path-find. 
The algorithm is essentially an extension of Dijkstra’s algorithm. It works by using the same concept as Dijkstra’s algorithm: 
- It computes the distance from the start to the next node and decides if it’s beneficial to head in that direction. 
Except, A* adds a heuristic function which also computes the distance from the next node to the goal node and adds it to the value calculated in Dijkstra’s algorithm. 

Together, the algorithm is fast and accurate and uses heuristics to find a path to the goal node. 
I used the equation: 

`f(n) = g(n) + h(n)` 

where g(n) is the value calculated by Dijkstra’s algorithm and h(n) is the heuristic function that calculates the Euclidian distance from the next node to the goal node. 
I created an object called cell for each node in the array. I connected the cells by have an array of its neighbors and traversing from one cell to the next. 
- I picked the neighbor with the lowest f(n) value as long as it was not a wall. 
- To avoid bombs, the g(n) for that particular cell would be its value plus 20. This would discourage the algorithm from picking this cell as its f(n) would most likely be higher than its neighbor. 
- Same concept for obtaining the most gold, instead of adding 20 to its g(n), I subtracted 4. This would encourage the algorithm to pick the cell with gold instead of its neighbor. 

My implementation of A* sacrifices memory in order to be fast. 

### Functions
`pathfinder(arr)` -- where arr is a previously-defined array, return value must be a vector<char>
