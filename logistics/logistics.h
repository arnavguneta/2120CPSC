#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <climits>
using namespace std;

struct city;

struct link {
  int ID;
  string end;
  double flow;
  double capacity;
  double cost;
  link(int ID, double capacity, double cost): ID(ID), capacity(capacity), cost(cost) {}
  link(int ID, string end, double capacity, double cost): ID(ID), end(end), capacity(capacity), cost(cost) {}
};

struct city {
  string name;
  // links exiting this city
  vector<link> neighbors;
  city(string name): name(name) {}
  city(): name("") {}
  // operator== overloading for find() function
  bool operator==(const city& a) {
    return (name == a.name);
  }
  city& operator=(const city& a) {
    name = a.name;
    neighbors = a.neighbors;
    return *this;
  }
};

bool bfs(vector<city> &cities, vector<pair<city*,city*>> &parents, city *start, city *end) {
  // the number of vertices (cities) in our given graph
  int vertices = cities.size();
  // set all as unvisited
  vector<pair<city*,bool>> visited;
  bool bfs = false;
  double flowOverCap;

  for (int i = 0; i < vertices; i++) {
    visited.push_back(pair<city*,bool>(&cities[i],false));
  }

  // mark start as visited
  for (pair<city*,bool> p : visited) {
    if (p.first == start)
      p.second = true;
  }

  // start doesnt have a parent
  city c;
  parents.push_back(pair<city*,city*>(start,&c));

  queue<city*> q;
  q.push(start);
  // bfs to find path
  while (!q.empty()) {
    city *current = q.front();
    q.pop();
    // find match between city i and city current
    // current -> visited[i].first
    for (int i = 0; i < vertices; i++) {
      bool linkExists = false;
      // check to see if a link exists for between the current city and the one at index i
      for (link l : current->neighbors) {
        if (l.end == visited[i].first->name) {
          linkExists = true;
          flowOverCap = l.capacity - l.flow;
        }
      }
      if (visited[i].second == false && linkExists && flowOverCap > 0) {
        // adds the next city to the queue and marks it as visited
        q.push(visited[i].first);
        visited[i].second = true;
        // sets the next city's parent as current
        parents.push_back(pair<city*,city*>(visited[i].first,current));
      }
    }
  }
  // if end has been visited, bfs is complete
  for (pair<city*,bool> p : visited) {
    if (p.first == end) {
      bfs = p.second;
    }
  }
  return bfs;
}

// returns max flow
void fordFulkerson(vector<city> &cities, city *start, city *end) {
  city *current, *parent;
  // a vector to keep track of parents. <city, its parent>. updated in bfs function.
  vector<pair<city*,city*>> parents;
  while (bfs(cities, parents, start, end)) {
    int flow = INT_MAX, temp = -1;
    // finds max flow through the path
    for (current = end; current != start; current = parent) {
      // finds parent
      for (pair<city*,city*> p : parents) {
        if (p.first == current) {
          parent = p.second;
        }
      }
      // get the capacity of the link that connects parent -> current
      for (city c : cities) {
        if (c.name == parent->name) {
          for (link l : c.neighbors) {
            if (l.end == current->name) {
              temp = l.capacity - l.flow;
            }
          }
        }
      }
      // get the max throughput
      flow = min(flow, temp);
      // update parent in a way that replaces current
      for (pair<city*,city*> p : parents) {
        if (p.first == parent) {
          parent = p.first;
        }
      }
    }

    // update the cities flow
    for (current = end; current != start; current = parent) {
      // finds parent
      for (pair<city*,city*> p : parents) {
        if (p.first == current) {
          parent = p.second;
        }
      }
      // update flow for link connecting parent->current
      for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == parent->name) {
          for (int j = 0; j < cities[i].neighbors.size(); j++) {
            if (cities[i].neighbors[j].end == current->name) {
              cities[i].neighbors[j].flow += flow;
            }
          }
        }
      }
      // update parent in a way that replaces current
      for (pair<city*,city*> p : parents) {
        if (p.first == parent) {
          parent = p.first;
        }
      }
    }
  }
}

// accepts a start location - string is the name of the city, double is the starting weight (bonus)
// accepts an end location - string is the name of the city, double is the desired weight (bonus)
unordered_map<int, double> organizeLogistics(vector<pair<string,double>> startLocs, vector <pair<string,double>> endLocs) {
  // int is the id number for the link, double is the amount of cargo being passed through that link
  unordered_map<int, double> ret;
  vector<city> cities;
  city *start, *end;

  // reads the file and initializes cities and links
  ifstream file("worldmap.txt");
  int ID;
  string startName, endName;
  double capacity, cost;
  city startLink;
  while (file >> ID) {
    bool startFound = false, endFound = false;

    file >> startName >> endName >> capacity >> cost;
    // searches to see if the city exists
    for (int i = 0; i < cities.size(); i++) {
      if (cities[i].name == startName) {
        startLink = cities[i];
        startFound = true;
      } else if (cities[i].name == endName) {
        endFound = true;
      }
    }

    // if end is not found, create the city
    if (!endFound) {
      city c(endName);
      cities.push_back(c);
    }

    // if start is not found, create city
    if (!startFound) {
      city c(startName);
      startLink = c;
    }

    // create the link object with startLink and endName
    link link(ID, endName, capacity, cost);

    // if city was not stored, store it. else, find in vector and store it.
    if (!startFound) {
      startLink.neighbors.push_back(link);
      cities.push_back(startLink);
    } else {
      for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == startName) {
          cities[i].neighbors.push_back(link);
        }
      }
    }
  }

  // finds the start and end cities
  for (int i = 0; i < cities.size(); i++) {
    if (cities[i].name == startLocs[0].first) {
      start = &cities[i];
    } else if (cities[i].name == endLocs[0].first) {
      end = &cities[i];
    }
  }
  // performs the algorithm, updates max flow for each path
  fordFulkerson(cities, start, end);

  for (city c : cities) {
    for (struct link l : c.neighbors) {
      ret.insert(pair<int,double>(l.ID,l.flow));
    }
  }
  return ret;
}
