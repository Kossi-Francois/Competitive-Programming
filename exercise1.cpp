

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


const int mod = 1e9 +7;



class Graph{

    int V;
    vvi adj;

    public: vector<bool> visited;
    public: vi cnt;
    public: ll sum;


    public: Graph(int V){
        this->V = V;
        adj.assign(V, vector<int>(0));
        cnt.resize(V);
        sum = 0; 
        
    }

    public: void addEdge(int v, int w){
        adj[v].push_back(w);
        adj[w].push_back(v);
    }



    void DFSUtil(int v)
    {
        visited[v] = true;
        int k = 1;
        trav(i, adj[v])
            if (!visited[i]){
                DFSUtil(i);
                k += cnt[i];
            }
        cnt[v] = k;
    }


    void sumDfs(int v){
        visited[v] = true;

        ll tt =  1ll * (cnt[v] * (cnt[v] - 1) + 1) % mod;
        trav(i, adj[v])
            if (!visited[i]){
                sumDfs(i);
                tt = (tt - (cnt[i] * (cnt[i] - 1))) % mod ;
            }

       sum = (sum % mod + tt * (v+1) % mod) % mod;
        
    }



};




int main() {
	
	
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TT;
    cin >> TT;
    for (int tt = 1; tt <= TT; ++tt) {
        int N;
        cin >> N;

        Graph gg = Graph(N);
        
        int A, B;
        for(int j=0; j<N-1; j++){
            cin >> A >> B;
            A--; B--;
            gg.addEdge(A, B);
        }

        gg.visited.assign(N, false);
        gg.DFSUtil(0);

        fill( all(gg.visited), false);
        gg.sumDfs(0);


        cout <<  gg.sum << endl;
            
        
        
    }
    
	
	return 0;
}




