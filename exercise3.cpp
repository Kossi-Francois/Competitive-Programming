

#include <bits/stdc++.h>
using namespace std;

//int64_t
typedef long long ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pl> vpl;
typedef vector<string> vs;                 

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()


#define f first
#define s second

#define coutfix(n) std::setprecision(n) << std::fixed 







ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}



ll arrGCD(vl& A){

    ll ans = A[0];

    trav(elt, A){
        ans = gcd(ans, elt);
        if(ans == 1){
            break;
        }

    }

    return ans;
}





int main() {
	
	
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TT;
    cin >> TT;
    for (int tt = 1; tt <= TT; ++tt) {
        ll N; cin >> N;

        vl A(N);
        for(int j=0; j<N; j++){
            cin >> A[j];
        }

        ll arr_gcd =  arrGCD(A);

        trav(Ai, A){
            cout << Ai/arr_gcd << " ";
        }

        cout << endl;


    }
    
	
	return 0;
}




