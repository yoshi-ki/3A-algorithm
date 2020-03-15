#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;



int main(){
  int N;
  int A[9];
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      cin >> A[i*3 + j];
    }
  }

  cin >> N;
  bool a[9];
  for (int i = 0; i < 9; i++){
    a[i] = false;
  }
  for (int i = 0; i < N; i++){
    int b;
    cin >> b;
    for (int j = 0; j < 9; j++){
      if(A[j] == b) a[j] = true;
    }
  }

  if(a[0]==true && a[3] == true && a[6] == true){cout << "Yes" << endl;return 0;}
  if(a[0]==true && a[1] == true && a[2] == true){cout << "Yes" << endl;return 0;}
  if(a[1]==true && a[4] == true && a[7] == true){cout << "Yes" << endl;return 0;}
  if(a[3]==true && a[4] == true && a[5] == true){cout << "Yes" << endl;return 0;}
  if(a[2]==true && a[5] == true && a[8] == true){cout << "Yes" << endl;return 0;}
  if(a[6]==true && a[7] == true && a[8] == true){cout << "Yes" << endl;return 0;}
  if(a[0]==true && a[4] == true && a[8] == true){cout << "Yes" << endl;return 0;}
  if(a[2]==true && a[4] == true && a[6] == true){cout << "Yes" << endl;return 0;}
  cout << "No" << endl;



  return 0;
}
