

#include <bits/stdc++.h>
using namespace std;

//int64_t // uint64_t
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;

typedef vector<int> vi;
typedef vector<ld> vld;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vb> vvb;
typedef vector<vc> vvc;
typedef vector<vs> vvs;


#define FORK(i, a, b, k) for (int i=a; i<(b); i+=k)
#define FOR(i, a, b) FORK(i, a, b, 1)
#define F0R(i, a) FOR(i, 0, a)
#define ROFK(i, N, a, k) for (int i = (N)-1; i >= (a); i-=k)
#define ROF(i, N, a) ROFK(i, N, a, 1)
#define R0F(i, N) ROF(i, N, 0)
#define trav(x, arr) for (auto& x : arr)
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

#define sz(x) (int)(x).size()
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
#define trailfill(n, c) std::left << std::setfill(c) << std::setw(n);
#define fast() ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL)
#define endl '\n'


template<class T> using minpq = pq<T, vector<T>, greater<T>>;
template<class T> using vset  = vector<set<T>>;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
template<typename T> ostream& operator<<(ostream& out, vector<T> &a) {for (auto &x : a) out << x << ' '; return out;};
template<typename T> istream& operator>>(istream& cin, vector<T> &a) {for (auto &x : a) cin >> x;        return cin;};


void debug(){ /*break point*/  }
void YES(){ cout << "Yes" << endl;  }
void NO() { cout << "No"  << endl;  }

ll const MOD = 1e9 + 7LL;
ll  modInv2 = 500000004LL;
ll  modInv4 = 250000002LL;

int maxint = numeric_limits<int>::max();



int totalStrength(vector<int>& strength) {

    int n = sz(strength);

    vi left(n, -1), right(n, n);    //  S[l[i]] <  S[i]  >= S[r[i]]
    stack<int> staq;

    FOR(i, 0, n){
        while (!staq.empty()  && strength[staq.top()] >= strength[i])
        {
            staq.pop();
        }
        if(!staq.empty()){ left[i] = staq.top();  }
        staq.push(i);
    }

    staq = stack<int>();
    FOR(i, 0, n){
        while (!staq.empty()  && strength[staq.top()] <= strength[i])
        {
            
            right[ staq.top()  ] = i; staq.top();
        }
        staq.push(i);
    }


    vl pref(n+1, 0ll), pref2(n+1, 0ll);
    partial_sum(all(strength), pref.begin()+1, [&](int a, int b){return (a+b)%MOD;});
    partial_sum(all(pref),    pref2.begin()+1, [&](int a, int b){return (a+b)%MOD;});

    ll ans = 0ll;
    FOR(i, 0, n){
        ans += ((strength[i]%MOD) * (  ( i - left[i]  )%MOD * (  pref2[ right[i] + 1]  - pref2[i+1] )%MOD     -    ( right[i] - i )%MOD * ( pref2[i+1] - pref2[left[i] + 1]   )%MOD  + 2 * MOD  )%MOD  )%MOD;
    }

    return ans;
    
}






vector<int> secondGreaterElement(vector<int>& nums) {
    int n = sz(nums);
    vi vans(n, -1);
    stack<int > staq2, staq1;
    deque<int> dqu2;

    FOR(i, 0, n){

        while (!staq2.empty()   &&  nums[staq2.top()] < nums[i] )
        {
            vans[staq2.top()] = nums[i]; staq2.pop();
        }
        while ( !staq1.empty() &&  nums[staq1.top()]  < nums[i] )
        {
            dqu2.push_back( staq1.top() ); staq1.pop();
        }

        while ( !dqu2.empty() )
        {
            staq2.push( dqu2.back()   );  dqu2.pop_back();
        }
        
        dqu2.push_back(i);
    }
    
    return vans;
}






int resolve(){
  int a, b; cin >> a >> b;
  //vi chargeTimes = {3,6,1,3,4},  runningCosts = {2,1,3,4,5}; ll budget = 25;
  vi chargeTimes = {11,12,19},  runningCosts = {10,8,7}; ll budget = 19;

  //cout << distributeCandies(  a, b  ) << endl;
  //cout <<  secondGreaterElement(nums) << endl;
  
  cout << maximumRobots( chargeTimes,  runningCosts,  budget) << endl;;
 


    return 0;
}





int main() {
	
	
    fast();

    int TT = 1;   //cin>>TT;
	for (int tt = 1; tt <= TT; tt++) 
	{

        //cout << "Case #" << tt << ": ";
        
        resolve();
        //cout << "Case #" << tt << ": " << resolve() << endl;
        //cout << (ans ? "YES" : "NO") << endl;
    

		
	}



   
    
	
	return 0;
}




