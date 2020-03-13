#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include "math.h"
using namespace std;

struct UnionFind {
    // union tree
    // used for tracking a set of elements partitioned into a number of disjoint subsets
    // rankなしでの実装
  
    vector<int> par; 
    // par[i] means i's parent
    // (ex) par[3] = 2 means 2 is a parent of 3

    UnionFind(int N) : par(N) {
      //used for initialization
      for(int i = 0; i < N; i++) par[i] = i;
    }

    int root(int x) { 
      // データxが属する木の根を再帰で得る
      // root(x) = {xの木の根}
      if (par[x] == x) return x;
      return par[x] = root(par[x]);
    }

    void unite(int x, int y) { 
      // xとyのtreeのmerge
      int rx = root(x); //xの根をrx
      int ry = root(y); //yの根をry
      if (rx == ry) return; //同じ時はそのままに
      par[rx] = ry; //xの根rxをyの根ryにつける
    }

    bool same(int x, int y) { 
      // 2つのデータx, yが属する木が同じならtrueを返す
      int rx = root(x);
      int ry = root(y);
      return rx == ry;
    }
};


int main(){
  int N, M;
  cin >> N >> M;

  UnionFind tree(N);

  for(int i = 0; i < M; i++){
    int a,b;
    cin >> a >> b;    
    tree.unite(a-1,b-1);
  }

  int ans = 0;
  for(int i = 0; i < N; i++){
    if(!tree.same(0,i)){
      ans++;
      tree.unite(0,i);
    }
  }
  cout << ans << endl;
  return 0;
}


