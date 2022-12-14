

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




vl factorial;
void generateFactorial(ll N){
    // Base case
    factorial[0] = 1;
 
    // Calculate value
    // factorials up to n
    for(int i = 1; i <= N; i++)
    factorial[i] = i * factorial[i - 1];
}


ll permutationCoeff(ll n, ll k){
    // P(n,k) = n! / (n - k)!

    // Base Cases
    if (k > n){ return 0;  }
    if (k == 0 ){ return 1;  }
    
    return factorial[n] / factorial[n - k]; 

    
}



int binomialCoeff(ll n, ll k){

    //the number of ways, disregarding order, that k objects can be chosen 
    //from among n objects more formally, 
    //the number of k-element subsets (or k-combinations) of a n-element set.
    //c(n,k) = n!/(k! * (n-k)!)

    // Base Cases
    if (k > n){ return 0;  }
    if (k == 0 || k == n){ return 1;  }

    return factorial[n] / (factorial[k] * factorial[n - k]);
        
}





vector<bool> isPrime;
void SieveOfEratosthenes(int n)
{
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }

}






int solution(int N, vi& A){




    return 0;
}





int main() {
	
	
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    ll NN = 1e5+10;
    isPrime.assign(NN + 1, true);


    int TT;
    cin >> TT;
    for (int tt = 1; tt <= TT; ++tt) {
        int N;
        cin >> N;
        
        vi A(N);
        for(int j=0; j<N; j++){
            int temp;
            cin >> temp;
            
            A[j] = temp;
        }
        

        
        cout << "Case #" << tt << ": " << solution( N, A) << endl;
    }
    
	
	return 0;
}




