

#include <bits/stdc++.h>
using namespace std;

//int64_t // uint64_t
typedef long long ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pd;

typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<int> vi;
typedef vector<ld> vld;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
typedef vector<string> vs;


#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, N, a) for (int i = (N)-1; i >= (a); --i)
#define R0F(i, N) ROF(i, N, 0)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

#define all(v)  v.begin(), v.end()
#define rall(v) v.rbegin(),v.rend()
#define lwb(c, x)  distance((c).begin(), lower_bound(all(c), (x))) // first elt >= 
#define lbg(c, x)  distance((c).begin(), lower_bound(all(c), (x), greater{}))
#define upb(c, x)  distance((c).begin(), upper_bound(all(c), (x))) // fist elt >
#define ubg(c, x)  distance((c).begin(), upper_bound(all(c), (x), greater{}))

#define f first
#define s second

#define pq priority_queue

#define coutfix(n) std::setprecision(n) << std::fixed 
#define fast() ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL)
#define endl '\n'


template<class T> using minpq = pq<T, vector<T>, greater<T>>;
template<class T> using vset  = vector<set<T>>;
template<typename T> ostream& operator<<(ostream& out, vector<T> &a) {for (auto &x : a) out << x << ' '; return out;};
template<typename T> istream& operator>>(istream& cin, vector<T> &a) {for (auto &x : a) cin >> x;        return cin;};

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; } // set a = min(a,b)
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; } // set a = max(a,b)


void debug(){ /*break point*/  }





int resolve(){
    int E, W; cin >> E >> W;

    vvi ww(E, vi(W));
    FOR(i, 0, E){
        cin >> ww[i];
    }

    // vvi common(E, vi(E));
    // FOR(i, 0, E){
    //     vi minw(W, 1e5 + 10);
    //     FOR(j, i, E){
    //         FOR(k, 0, W){
    //             ckmin(minw[k], ww[j][k]);
    //             common[i][j] += minw[k];
    //         }
    //     }
    // }


    vvl shared_cnt(E, vl(E+1));
    for (int i = 0; i < E; i++) {
        for (int t = 0; t < W; t++) {
            int cnt = ww[i][t];
            for (int k = i; k < E; k++) {
                cnt = min(cnt, ww[k][t] );
                shared_cnt[i][k+1] += cnt;
            }
        }
    }

    debug();

    vvl dp(E, vl(E+1));
    FOR(i, 0, E){ dp[i][i+1] = shared_cnt[i][i+1]; }

    debug();

    FOR(l, 2, E+1) for(int i = 0, j = l; j <= E; i++, j++) {

        dp[i][j] = 1e9;

        debug();

        FOR(k, i+1, j){

            dp[i][j] = min(dp[i][j],  dp[i][k] + dp[k][j] - shared_cnt[i][j]) ;

            debug();
        }
    }

    

    

    // 1 1 1
// 0 2 1
// 0 0 1


    return 2 * dp[0][E];
}





int main() {
	
	
    fast();

    int TT = 1;   cin>>TT;
	for (int tt = 1; tt <= TT; tt++) 
	{

        //cout << "Case #" << tt << ": ";
        
        //resolve();
        cout << "Case #" << tt << ": " << resolve() << endl;
        //cout << (ans ? "YES" : "NO") << endl;
    

		
	}



   
    
	
	return 0;
}




