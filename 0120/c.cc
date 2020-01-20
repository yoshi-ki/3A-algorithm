#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;



int main(){
  int N;
  cin >> N;
  int tempmin;
  cin >> tempmin;
  int ans = 1;
  for (int i = 0; i<N-1; i++){
    int t;
    cin >> t ;
    if (tempmin >= t){tempmin = t; ans++;}
  }
  cout << ans << endl;


  return 0;
}
