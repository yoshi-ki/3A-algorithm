#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <functional>
#include <cmath>
#include <cstring>
#include <numeric>
#include <random>
#include <map>
#include <unordered_map>
#include <queue>
#include <regex>
#include <complex>
#include <list>
#include <cassert>
#include <deque>

#define addf(T) [](T a, T b){return (a + b);}
#define minf(T) [](T a, T b){return min(a, b);}
#define maxf(T) [](T a, T b){return max(a, b);}
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()

using namespace std;
using ll = long long;

/*
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

template<typename T>
struct SegTree {
  //segment tree

  //木は配列で表現
  vector<T> seg;
  //木の1/2の大きさ
  int size;
  //単位元
  const T unit;
  //比較関数の型
  using F = function<T(T,T)>;
  //mergeする関数
  const F f;

  //単位元がaで大きさnのsegtreeの初期化を行う
  //大きさnとはすなわち葉の数がnであることをいう
  SegTree(int n, const T a, const F f) : unit(a), f(f) {
    size = 1;
    while(size < n) size <<= 1;
    seg.assign(2*size, unit);
    size--;
  }

  //k番目にtを代入する
  void set(int k, const T& t) {
    seg[k + size] = t;
  }

  //関数fによって木を構築する
  void build(){
    for (int i = size - 1; i >=0; i--){
      seg[i] = f(seg[i*2+1],seg[i*2+2]);
    }
  }

  //i番目の要素を返す
  T operator[](const int i){
    return seg[i + size];
  }

  //k番目の値をaに更新する
  void update(int k, T a){
    k = k + size;
    //必要ならばここを変えても良い
    seg[k] = a;
    //自分の親の情報を再帰的に更新していく
    while(k>0){
      k = ((k-1) >> 1);
      seg[k] = f(seg[k*2+1],seg[k*2+2]);
    }
  }

  //[a,b)についてfをした結果を返す
  //例えば、fがminだったらどうなるかを考えるとわかりやすい
  //unitについては足し算なら0,掛け算なら1,minならinf,どんな値が来てもその値を返すもの
  T query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
      return unit;
    } else if (a <= l && r <= b) {
      return seg[k];
    } else {
      T lch = query(a, b, k * 2 + 1, l, (l + r) / 2);
      T rch = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return f(lch, rch);
    }
  }
  T query(int a, int b) { return query(a, b, 0, 0, size+1); }
};
*/

/* --- ここからコード --- */
const int MX = 2005;
bool d[3][3][MX];

int main(){
  int ans  = MX * 3;
  vector<string> s(3);
  rep(i,3) cin >> s[i];
  sort(all(s));
  do{
    rep(i,3)rep(j,3)rep(k,s[i].size()) {
      bool ok = true;
      if(i >= j) continue;
      for(int ni = k; ni < s[i].size();ni++){
        int nj = ni-k;
        if(nj >= s[j].size()) break;
        if(s[i][ni] == '?' || s[j][nj] == '?') continue;
        if(s[i][ni] != s[j][nj]) ok = false;
      }
      d[i][j][k] = ok;
    }

    auto f = [&](int i,int j, int k){
      if(k>=s[i].size()) return true;
      return d[i][j][k];
    };
    rep(x,MX)rep(y,MX) {
      if(!f(0,1,x)) continue;
      if(!f(1,2,y)) continue;
      if(!f(0,2,x+y)) continue;
      int now = 0;
      now = max<int>(now,s[0].size());
      now = max<int>(now,x+s[1].size());
      now = max<int>(now,x+y+s[2].size());
      ans = min(ans,now);
    }
  }while(next_permutation(all(s)));
  cout << ans << endl;
  return 0;
}
