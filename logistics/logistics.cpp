#include "logistics.h"

using namespace std;

unordered_map<int, double> organizeLogistics(vector<pair<string,double>> start, vector <pair<string,double>> end);

int main() {
  vector<pair<string,double>> startLocs;
  vector<pair<string,double>> endLocs;
  unordered_map<int, double> ret;


  startLocs.push_back(pair<string,double> ("sanDiego", 0));
  endLocs.push_back(pair<string,double> ("reno", 0));

  ret = organizeLogistics(startLocs, endLocs);

  for (pair<int,double> p : ret) {
    cout << p.first << " " << p.second << endl;
  }
}
