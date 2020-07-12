#include <chrono>
#include <iostream>
#include "pathfinder.h"

using namespace std;

template <std::size_t rows, std::size_t cols>
vector<char> pathfinder(char (&maze) [rows][cols]);

int main() {
    char arr[15][20] = {
        {'s','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
        {'e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
        {'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','w','w'},
        {'e','w','e','w','b','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},
        {'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','g','g'},
        {'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},
        {'e','w','e','w','e','w','w','w','w','w','w','w','e','e','e','e','e','w','g','g'},
        {'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','w','w','e'},
        {'e','w','e','w','e','e','b','e','e','e','w','w','e','w','e','e','e','e','w','e'},
        {'e','w','e','w','e','g','b','f','e','e','w','e','e','w','e','w','w','e','w','e'},
        {'e','w','e','w','e','e','b','e','g','g','w','e','e','w','e','e','w','e','w','e'},
        {'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','w','e','e','e'},
        {'e','w','e','w','e','e','e','e','e','e','e','w','e','w','e','e','w','e','e','e'},
        {'e','e','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','e','e','e'},
        {'e','w','e','w','e','e','e','e','e','e','w','e','e','e','e','e','e','e','e','e'},
    };

    auto start = chrono::high_resolution_clock::now();
    vector<char> path = pathfinder(arr);
    auto finish = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";

    for (char c : path) {
      cout << c << " ";
    }
    cout << endl;
}
