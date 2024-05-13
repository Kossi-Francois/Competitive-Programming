

// STL C++
#include <bits/stdc++.h>
using namespace std;

// GNU C++
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;


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

#define tcT template<class T
#define tcTU tcT, class U

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


#define f first
#define s second

#define coutfix(n) std::setprecision(n) << std::fixed 
#define trailfill(n, c) std::left << std::setfill(c) << std::setw(n);
#define fast() ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL)
#define endl '\n'

#define pq priority_queue


template<class T> using ordered_set      = tree<T,  null_type, less<T>,        rb_tree_tag, tree_order_statistics_node_update> ;
template<class T> using ordered_multiset = tree<T,  null_type, less_equal<T>,  rb_tree_tag, tree_order_statistics_node_update> ;

template<class T> using minpq = pq<T, vector<T>, greater<T>>;
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

const ll maxint = numeric_limits<ll>::max() - 100ll;
const ll minint = numeric_limits<ll>::min() + 100ll;




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





int numberOfStableArrays(int zero, int one, int limit) {

	unordered_map<string, ll> memo;

	auto keys = [](int a, int b, int c, int d){
		return to_string(a)+ "--->" + to_string(b)+ "+++>" + to_string(c)+ "***>"  +to_string(d);
	};
	

	function<ll(int, int, int, int)> dp = [&] (int prev, int cnt, int zz, int oo) -> ll{
		
		if( zz == 0 && oo == 0 && cnt <= limit ){return 1ll;}

		if(  (cnt > limit) || (zz < 0) || (oo < 0 )  ){
			return 0;
		}

		string key = keys(prev, cnt, zz, oo  );
		if(memo.find(key) !=memo.end()){
			return memo[key];
		}


		ll ans = 0;
		FOR(i, 1, limit+1){

			ans += (dp( 0, (prev == 0? cnt + i : 1  ), zz-i, oo   ) )%MOD ; 
			ans %= MOD; 
			ans += dp( 1, (prev == 1? cnt + i : 1  ), zz, oo-i   ) %MOD ;  
			ans %= MOD; 

			debug();
		}

		return memo[key] =  ans%MOD;

	};



	return dp(-1, 0, zero, one  );

}



int smallestDistancePair(vector<int>& nums, int k) {
	sort(all(nums));
	int n = sz(nums);

	minpq<pair<ll, pii>> pqu;
	FOR(i, 1, n){
		pqu.push({ abs(nums[i] - nums[0]),  {i, 0}});
	}

	int res;
	while (--k>=0)
	{
		pair<ll, pii> top = pqu.top(); pqu.pop();

		res = top.first;

		int next = top.s.s + 1;

		if(next <= top.s.f  - 1){
			pqu.push({ abs(nums[top.s.f] - nums[next])   ,  {top.s.f,  next } });
			debug();
		}

	}

	return res;

}



int resolve(){
	// vvi inp = {{1}, {1}};
	// int zero = 3, one = 3, limit = 2;
	// numberOfStableArrays( zero,  one,  limit);
	vi arr = {1,6,1}; int k = 3;
	int ans = smallestDistancePair(arr, k);
	cout << ans << endl;

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

