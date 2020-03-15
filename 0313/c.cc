#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include "math.h"
using namespace std;



int main(){
  int N;
  int M;
  cin >> N;
  cin >> M;
  int s[5];
  int c[5];
  for (int i = 0; i < M; i++){
    cin >> s[i] >> c[i] ;
  }
  int ans = -1;
  for(int n = 0; n < pow(10,N); n++){
    bool flag = true;;
    for (int j = 0; j < M; j++){
      //s[j]桁めを取り出す
      string temp = to_string(n);
      
      if ((int)(temp[s[j]-1])-48 != c[j]){ flag = false;}

    }
    if (flag) {
      if ((to_string(n)).length() == N)
      {ans = n;break;}
    }

  }
  cout << ans << endl;

  return 0;
}
