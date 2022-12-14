

#include <bits/stdc++.h>
using namespace std;

//int64_t
typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;



#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()


#define f first
#define s second

#define coutfix(n) std::setprecision(n) << std::fixed 

const ll mod = 998244353;




int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    string SS;
    cin >> SS;

    ll N = SS.size();

    vector<char> S(N+1);
    ll idx = N;
    trav(cc, SS){
      S[idx] = cc;
      idx--;
    }


    
    ll odd  = 0;
    ll even = 0;

    for(int j =1; j<=N; j++){
      if(j%2==0 && S[j] == '1'){
        even++;
      }

      if(j%2==1 && S[j] == '1'){
        odd++;
      }
    }


    ll swapEven2Odd = 0;
    ll swapOdd2Even = 0;
    for(int j = 1; j<N; j++){
      
      if(S[j] == '0' && S[j+1] == '1' ){
        if( j%2 == 0){
          swapOdd2Even ++ ;
        }else{
          swapEven2Odd ++;
        }
      }

      if(S[j] == '1' && S[j+1] == '0' ){

        if( j%2 == 0 ){
          swapEven2Odd ++;
        }else{
          swapOdd2Even ++ ;
        }

      }



    }
    



    ll ans = -1;

    if( abs(odd - even)%3 == 0 ){
      ans = 0;
      
    }else{

      ll tempOdd;
      ll tempEven;
      ll ans0 = LONG_LONG_MAX;
      ll ans1 = LONG_LONG_MAX;
      bool flag = false;

      
      tempOdd = odd;
      tempEven = even;
      
      for(ll k=1;  k<=swapEven2Odd; k++){
        tempOdd++; tempEven--;
        if( tempOdd>N || tempEven<0 ){break;}
        if( abs(tempOdd - tempEven)%3 == 0 ){
          ans0 = k;
          flag = true;
          break;
        }
      }


      tempOdd = odd;
      tempEven = even;
      
      for(ll k=1;  k<=swapOdd2Even; k++){
        tempOdd--; tempEven++;
        if( tempOdd<0 || tempEven>N ){break;}
        if( abs(tempOdd - tempEven)%3 == 0 ){
          flag = true;
          ans1 = k;
          break;
        }

      }

      
      if(flag){  ans =  min(ans0, ans1); }
    }


    
    cout << ans << endl;

  }
  return 0;
}


