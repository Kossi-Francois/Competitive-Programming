

// STL C++
#include <bits/stdc++.h>
using namespace std;

// GNU C++
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

// #include <ext/rope> //header with rope
// using namespace __gnu_cxx; //namespace with rope and some additional stuff


//int64_t // uint64_t
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef pair<ll, int> pli;
typedef pair<ll, pii> plii;


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

#define tcT template<class T
#define tcTU tcT, class U
tcT > using VT = vector<T>;

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

#define argmax(c)  distance((c).begin(), max_element(all(c)) )
#define argmin(c)  distance((c).begin(), min_element(all(c)) )

#define not_in(c, x)  c.find(x) == c.end()
#define  is_in(c, x)  c.find(x) != c.end()

#define set_intersec(set1, set2, setres) set_intersection( all(set1), all(set2), std::inserter(setres, setres.begin()));



#define f first
#define s second

#define coutfix(n) std::setprecision(n) << std::fixed 
#define trailfill(n, c) std::left << std::setfill(c) << std::setw(n);
#define fast() ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL)
#define endl '\n'

#define pq priority_queue


template<class T> using ordered_set      = tree<T,  null_type, less<T>,        rb_tree_tag, tree_order_statistics_node_update> ;
template<class T> using ordered_multiset = tree<T,  null_type, less_equal<T>,  rb_tree_tag, tree_order_statistics_node_update> ; //erase with oset.erase(oset.upper_bound(value))

template<class T> using minpq = pq<T, vector<T>, greater<T>>;
// #define pqnode(comp) template<class T> pq<T, vector<T>, decltype( comp ) > pqvar( comp );

template<class T> using vset  = vector<set<T>>;


template<typename T> bool chkmax(T &m, const T q) { return m < q ? (m = q, true) : false; }
template<typename T> bool chkmin(T &m, const T q) { return m > q ? (m = q, true) : false; }

template<typename T> void unique( vector<T> &arr ) { sort(all(arr));  arr.erase( unique( all(arr) ), arr.end() );  }


template<typename T> ostream& operator<<(ostream& out, vector<T> &a) {for (auto &x : a) out << x << ' '; return out;};
template<typename T> istream& operator>>(istream& cin, vector<T> &a) {for (auto &x : a) cin >> x;        return cin;};
template<typename T1, typename T2> ostream& operator<<(ostream& out, vector<pair<T1, T2>> &a) {for (auto &x : a) out << x.f << ' ' << x.s << endl; return out;};
template<typename T1, typename T2> istream& operator>>(istream& cin, vector<pair<T1, T2>> &a) {for (auto &x : a) cin >> x.f >> x.s;  return cin;};

template<typename T> ostream& operator<<(ostream& out, set<T> &a) {for (auto &x : a) out << x << ' '; return out;};




ll const MOD = 1e9 + 7LL;
ll const modInv2 = 500000004LL;
ll const modInv4 = 250000002LL;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll maxintll = numeric_limits<ll>::max() - 100ll;
const ll minintll = numeric_limits<ll>::min() + 100ll;

const int maxint = numeric_limits<int>::max() - 100;
const int minint = numeric_limits<int>::min() + 100;



tcTU> T binMin_fIncrease(T lo, T hi, U f) {
	++hi; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		T mid = lo+(hi-lo)/2;
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}

tcTU> T binMax_fIncrease(T lo, T hi, U f) {
	T ans = minint;
	++hi; assert(lo <= hi); // assuming f is increasing
	while (lo <= hi) { // find last index such that f is true 
		T mid = lo+(hi-lo)/2;
		f(mid) ? ( lo = mid + 1, chkmax(ans, mid)  ): (hi = mid - 1) ; 
	} 
	return ans;
}




tcTU> T lstTrue(T lo, T hi, U f) {
	--lo; assert(lo <= hi); // assuming f is decreasing
	while (lo < hi) { // find first index such that f is true 
		T mid = lo+(hi-lo+1)/2;
		f(mid) ? lo = mid : hi = mid-1;
	} 
	return lo;
}




void debug(){ /*break point*/  }
void YES(){ cout << "Yes" << endl;  }
void NO() { cout << "No"  << endl;  }







ll resolve(){


    return 0;
}


void stressTestGen(){
	int t=100;
	pll n_range  = {1, 150};
	pll ai_range = {1, 1e9};

	if(t > 1){cout << t << endl;}

	FOR(i, 0, t){
		ll n = uid(n_range.f, n_range.s);
		ll b = uid(ai_range.f, ai_range.s);
		vl aa(n); trav(x, aa){x = uid(ai_range.f, ai_range.s);}
		vl bb(n); trav(x, bb){x = uid(ai_range.f, ai_range.s);}

		cout << n << " " << b << endl;
		cout << aa << endl;
		cout << bb << endl;
	}
}


int main() {
	
	std::clock_t prog_start_time = std::clock();
	
    fast();

    int TT = 1;   cin>>TT;
	for (int tt = 1; tt <= TT; tt++) 
	{

        //cout << "Case #" << tt << ": ";
        
        resolve();
        //cout << "Case #" << tt << ": " << resolve() << endl;
        //cout << (ans ? "YES" : "NO") << endl;
    
	}

	double prog_runtime = ( std::clock() - prog_start_time ) / (double) CLOCKS_PER_SEC;
	return 0;
}



// don't funcking get stuck
// think of something
// think of anything
// try new approach
// the solution is here 
// just think smart, think hard, think sm-hard

// ----- Do your best, and if that's not enough, do the best of someone better ----- //
// -- But remember, just because you don't give up, doesn't mean you will make it -- //