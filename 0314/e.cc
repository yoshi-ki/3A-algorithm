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

int main(){

  int N, P;
  cin >> N >> P;
  string S;
  cin >> S;

  ll ans = 0;

  if(P==2){
    for (int i = 0; i < S.size(); i++) {
      int d = (int)(S[i] - '0');
      if (d % 2 == 0) ans += i + 1;
    }
    cout << ans << endl;
    return 0;
  }
  else if(P==5){
    for (int i = 0; i < S.size(); i++) {
      int d = (int)(S[i] - '0');
      if (d == 0 || d == 5) ans += i + 1;
    }
    cout << ans << endl;
    return 0;
  }

  //10の倍数は先に計算しておく
  vector<int> ten(N);
  vector<ll> dp(P,0);
  ten[0] = 1;
  dp[0] = 1;
  for (int i = 1; i < N; i++) ten[i] = (ten[i - 1] * 10) % P;
  int a = 0;
  reverse(all(S));
  for (int i = 0; i < S.size(); i++) {
    //桁を取り出す
    int digit = (int)(S[i] - '0');
    //次にその桁の部分を数字に変換
    int d = (digit * ten[i]) % P;
    //aは今までの蓄積
    
    ans+=dp[(a+d)%P];
    dp[(a+d)%P]++;
    a = (a + d)%P;
    /*
    a = ((a - d) % P + P) % P;
    dp[(a + d) % P]++;
    ans += dp[a];
    */
  }
  
  
  cout << ans << endl;

















  return 0;
}
