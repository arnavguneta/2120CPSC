#include <string>
#include <deque>
#include <vector>
#include <cmath>

using namespace std;

struct Cell {
  char data;
  // "coordinates" in the grid
  int i, j;
  // f(n) = g(n) + h(n), [WIKIPEDIA]
  // where n is the next node on the path,
  // g(n) is the cost of the path from the start node to n,
  // and h(n) is a heuristic function that estimates the cost of the cheapest path from n to the goal.
  double f, g, h;
  struct Neighbor {
    Cell *cell;
    char relativePos;
  };
  // a collection of neighboring cells, walls not included
  vector<Neighbor> neighbors;
  // the previous cell, used to determine final path
  Cell *cameFrom;

  // operator== overloading for find function
  bool operator==(const Cell& a) {
    return (i == a.i && j == a.j && data == a.data);
  }

  Cell& operator=(const Cell& a) {
    i = a.i;
    j = a.j;
    data = a.data;
    return *this;
  }
  Cell (): i(0), j(0) {}
  Cell (int i, int j): i(i), j(j) {}
};

// evaluates neighbors for all cells
template <std::size_t rows, std::size_t cols>
void evaluateNeighbors(Cell (&map)[rows][cols]) {
  typename Cell::Neighbor neighbor;
  Cell *cell;
  // adds each cells neighbors while checking boundaries and wall status
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cell = &map[i][j];
      // bottom boundary check
      if (i < rows - 1) {
        neighbor.cell = &map[i + 1][j];
        neighbor.relativePos = 'U';
        if (neighbor.cell->data != 'w')
          cell->neighbors.push_back(neighbor);
      }
      // top boundary check
      if (i > 0) {
        neighbor.cell = &map[i - 1][j];
        neighbor.relativePos = 'D';
        if (neighbor.cell->data != 'w')
          cell->neighbors.push_back(neighbor);
      }
      // right boundary check
      if (j < cols - 1) {
        neighbor.cell = &map[i][j + 1];
        neighbor.relativePos = 'L';
        if (neighbor.cell->data != 'w')
          cell->neighbors.push_back(neighbor);
      }
      // left boundary check
      if (j > 0) {
        neighbor.cell = &map[i][j - 1];
        neighbor.relativePos = 'R';
        if (neighbor.cell->data != 'w')
          cell->neighbors.push_back(neighbor);
      }
    }
  }
}

// helper function that helps calculate euclidian distance between cell1 and cell2
double calculateHeuristic(Cell *cell1, Cell *cell2) {
  // euclidian distance formula
  return sqrt( pow((cell2->i - cell1->i), 2) + pow((cell2->j - cell1->j), 2) );
}

// returns the shortest path (vector of chars) from start to finish
template <std::size_t rows, std::size_t cols>
vector<char> pathfinder(char (&maze) [rows][cols]) {
  Cell map[rows][cols];
  Cell *start, *end, *current;
  deque<Cell*> openSet;
  deque<Cell*> closedSet;
  vector<char> moves;

  // convers char arr to a cell arr
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Cell cell(i, j);
      cell.data = maze[i][j];
      map[i][j] = cell;

      // initializes start and end
      if (map[i][j].data == 's') {
        start = &map[i][j];
        Cell dummy(-1000, -1000);
        start->cameFrom = &dummy;
      } else if (map[i][j].data == 'f') {
        end = &map[i][j];
      }
    }
  }

  openSet.push_back(start);
  // initializes neighbors for all cells
  evaluateNeighbors(map);

  while (!openSet.empty()) {
    // find the index of the cell with lowest f value
    int currentIndex = 0;
    for (int i = 0; i < openSet.size(); i++) {
      if (openSet[i]->f < openSet[currentIndex]->f) {
        currentIndex = i;
      } else if (openSet[i]->f == openSet[currentIndex]->f) {
        // if a tie occurs, we want to pick the path thats closer to goal (lower h(n) = higher g(n))
        if (openSet[i]->g > openSet[currentIndex]->g)
          currentIndex = i;
      }
    }

    current = openSet[currentIndex];

    // if end is visisted, end the program
    if (current == end) {
      Cell *temp = current;
      while (temp->cameFrom->i >= 0) {
        for (typename Cell::Neighbor n : temp->neighbors) {
          // debug this if statement
          if (n.cell->i == temp->cameFrom->i && n.cell->j == temp->cameFrom->j) {
            moves.insert(moves.begin() + 0, n.relativePos);
          }
        }
        temp = temp->cameFrom;
      }
      return moves;
    }

    // marks current as "visited" and removes it from openSet
    closedSet.push_back(current);
    openSet.erase(openSet.begin() + currentIndex);

    for (int i = 0; i < current->neighbors.size(); i++) {
      Cell *neighbor = current->neighbors[i].cell;
      bool updatePath = false;

      // if closedSet does not contain the neighbor
      if (find(closedSet.begin(), closedSet.end(), neighbor) == closedSet.end()) {
        int g;
        if (neighbor->data == 'b')
          g = current->g + 20;
        else if (neighbor->data == 'g')
          g = current->g - 4;
        else
          g = current->g + 1;

        // if openSet contains neighbor (evaluated already)
        if (find(openSet.begin(), openSet.end(), neighbor) != openSet.end()) {
          if (g < neighbor->g)
            updatePath = true;
        } else {
          // if it hasn't been evaluated already
          updatePath = true;
          openSet.push_back(neighbor);

        }

        if (updatePath) {
          // calculates g(n), h(n) and updates f(n)
          neighbor->g = g;
          neighbor->h = calculateHeuristic(neighbor, end);
          neighbor->f = neighbor->g + neighbor->h;
          neighbor->cameFrom = current;
        }
      }
    }
  };
  // no sol
  return moves;
}
