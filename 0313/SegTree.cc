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

#define addf(T) [](T a, T b){return (a + b);}
#define minf(T) [](T a, T b){return min(a, b);}
#define maxf(T) [](T a, T b){return max(a, b);}

using namespace std;
using ll = long long;
template<typename T>

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
*/
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
    seg.assign(2*size-1, unit);
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
  T query(int a, int b){
    T l = unit;
    T r = unit;
    for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
      if (!(a & 1))l = f(l, seg[a++]);
      if (!(b & 1))r = f(seg[b--], r);
    }
    return f(l, r);
  }

  //[start, end) について、[l, r) を調べながら k 番目が check を満たすか二分探索 
  //最後が true なら left, false なら right fの逆演算
  template<typename C>
  int find(const int start, const int end, int l, int r, int k, const C check, T& checknum, const bool b, const function<T(T, T)> revf) {
    //cerr << checknum << '\n';
    //範囲外またはそこがすでに満たさないとき
    //cerr << k << ',' << checknum << '\n';
    if (start <= l && r <= end && !check(seg[k], checknum)) {
      checknum = revf(checknum, seg[k]);
      return -1;
    }
    if ((r <= start || l >= end)) {
      return -1;
    }
    //既に葉
    if (k >= size) {
      return k - size;
    }
    int res;
    if (b) {
      //左側を調べる
      res = find< C >(start, end, l, ((l + r) >> 1), (k << 1) + 1, check, checknum, b, revf);
      //左側が適してたらそれが答え
      if (res != -1)return (res);
      return find< C >(start, end, ((l + r) >> 1), r, (k << 1) + 2, check, checknum, b, revf);
    }
    else {
      //右側を調べる
      res = find< C >(start, end, ((l + r) >> 1), r, (k << 1) + 2, check, checknum, b, revf);
      //右側が適してたらそれが答え
      if (res != -1)return (res);
      return find< C >(start, end, l, ((l + r) >> 1), (k << 1) + 1, check, checknum, b, revf);
    }
  }

  template<typename C>
  int find_left(int start, int end, const C check, T& checknum, function<T(T, T)> revf) {
    return find< C >(start, end, 0, size + 1, 0, check, checknum, true, revf);
  }

  template<typename C>
  int find_right(int start, int end, const C check, T& checknum, function<T(T, T)> revf) {
    return find< C >(start, end, 0, size + 1, 0, check, checknum, false, revf);
  }



};

int main(){


  int q;
  scanf("%d", &q);
  int t, x;
  SegTree<int> tree(200001, 0, addf(int));
  for(int i = 0; i < q; i++) {
    scanf("%d%d", &t, &x);
    if (t == 1) {//add
      tree.update(x, tree[x] + 1);
    }
    else {//erase
      int p = tree.find_left<function<bool(int, int)>>(0, 200010, [](int a, int b) {return a >= b; }, x, [](int a, int b) {return a - b; });
      cout << p << endl;
      tree.update(p, tree[p] - 1);
    }
  }

  return 0;
}

