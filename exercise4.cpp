

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
typedef vector<pl> vpl;


#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()


#define f first
#define s second

#define coutfix(n) std::setprecision(n) << std::fixed 







vvl mmm ;
vector<pair<ll, pl>> A;
ll N, E;
vl visited;
ll totalans = 0;

void solution(ll idx, bool dir, ll ans){




    totalans = max(ans, totalans);

    FOR(i, 1, N+1){

        if( !visited[i]  && A[i].s.s <=  A[idx].s.s   ){
            
           visited[i] = true;

            ll costDir = 0;
            bool tempDir = dir;

        
            if( (A[i].s.f > A[idx].s.f  && !dir) ||  (A[i].s.f < A[idx].s.f  && dir)   ){
                costDir = -E;
                tempDir = !tempDir; 
            }

            
            solution( i, tempDir, ans + A[i].f + costDir) ;
            
            
            visited[i] = false;
            
        }

    }

    


    return;
}





int main() {
	
	
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TT;
    cin >> TT;
    for (int tt = 1; tt <= TT; ++tt) {
    
        cin >> N >> E;
        
        //A.assign(N+1, {0 , {0, 0}});
        A.reserve(N+1);
        A[0] = {0 , {0, 1e18+1}};

        visited.assign(N+1, false);
        visited[0] = true;

        totalans = 0;
        mmm.assign(N+1, vl(2, -1));

        ll xi, yi, ci;
        for(int j=1; j<N+1; j++){            
            cin >> xi >> yi >> ci;
            A[j] = {ci , {xi, yi}};
        }
        
        
            solution(  0, true, 0);
        
        
        
        cout << "Case #" << tt << ": " << totalans  << endl;
    }
    
	
	return 0;
}




