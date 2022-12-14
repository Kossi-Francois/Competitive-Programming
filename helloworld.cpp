

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












bool solution0(vi& arr, int N, int sum){

    vector<vector<bool>> dp(N+1, vector<bool>(sum+1, false) );
    dp[0][0] = true;

    for(int i = 1; i<=N;  i++){
        dp[i][0] = true;
    }
    for(int j = 1; j<=sum; j++){
        dp[0][j] = false;
    }

    for(int i = 1; i<=N; i++){

        for(int j = 1; j<=sum; j++){

            dp[i][j] = (dp[i-1][j]  )  ||  (  (j-arr[i-1] >= 0 )? dp[i-1][j-arr[i-1]]  : false );
        }

    }

    return dp[N][sum];
  
}









vector<vector<int>> dp;
vector<int> arr;
int M;
int N;

bool solution(int idx, int target){


    if(idx > N || target < M ){
        return false;
    }

    if(dp[idx][target] != -1 ){
        return dp[idx][target];
    }

    if(target == 0 || target%M == 0){
        return true;
    }



    int ans =  solution(idx+1,  target- arr[idx]) || solution(idx+1,  target);

    dp[idx][target] = ans;

    return ans;


}




 




int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);



  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {

    cin >> N >> M;

    arr.reserve(N);

    int temp;
    int target = 0;
    for(int j = 0; j<N; j++){
        cin >> temp;
        arr[j] = temp;

        target+= temp;
    }

    dp.assign(N+1, vector<int>(target+1, -1));
    

    
    //productPrimeFactors(B, A);
    cout << solution(0, target ) << endl;

    
  }
  return 0;
}


    











