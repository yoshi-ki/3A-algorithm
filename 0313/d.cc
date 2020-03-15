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
  int N,M,K;
  cin >> N >> M >> K;
  int friendnum [100010] = {};
  UnionFind friendtree(N);
  UnionFind blocktree(N);
  int ans[100010];
  for (int i = 0; i < M; i++){
    int a,b;
    cin >> a;
    cin >> b;
    friendtree.unite(a-1,b-1);
    friendnum[a-1] = friendnum[a-1] + 1;
    friendnum[b-1] = friendnum[b-1] + 1;
  }

  //ノード数の配列を作成
  int root_num[100010]={};
  for(int i=0;i<N;i++){
    root_num[friendtree.root(i)-1]++;
  }

  for(int i = 0; i < N; i++){
    int count = root_num[friendtree.root(i)-1];
    ans[i] = count - friendnum[i];
  }

  for (int i = 0; i < K; i++){
    int c,d;
    cin >> c;
    cin >> d;
    if(friendtree.same(c-1,d-1)){
      ans[c-1] = ans[c-1] - 1;
      ans[d-1] = ans[d-1] - 1;
    }
  }

  for(int i = 0; i < N; i++){
    cout << ans[i]-1 << " ";
  }





  return 0;
}
