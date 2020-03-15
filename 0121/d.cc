#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;


int main(){
  int N;
  cin >> N;
  int C [9][9];
  for (int i = 1; i < 10; i++){
    for (int j = 1; j < 10; j++){
      int count = 0;
      for (int n = 1; n <= N; n++){
        int j2 = n % 10;
        int tempn = n;
        while(!(tempn < 10)){
          tempn = tempn/10;
        }
        int i2 = tempn;
        if (i2 == i && j2 == j ) count++;
      }
      C[i-1][j-1] = count;
    }
  }

  int ans = 0;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      ans = ans + C[i][j] * C[j][i];
    }
  }
  cout << ans << endl;

  return 0;
}
