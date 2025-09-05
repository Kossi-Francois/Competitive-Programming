








ll power( ll b, ll e)
{
    if(e==0) return 1;
    if(e&1) return b*power(b*b,e/2);
    return power(b*b,e/2);
}


ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}


ll lcm(ll a, ll b) {
	return (a / gcd(a, b)) * b;
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





/////////////////////---------  Combinatory -------------////////////////////////


vl factorial;
void generateFactorial(ll N){

    factorial.resize(N+1);

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



ll binomialCoeff(ll n, ll k){

    //the number of ways, disregarding order, that k objects can be chosen 
    //from among n objects more formally, 
    //the number of k-element subsets (or k-combinations) of a n-element set.
    //c(n,k) = n!/(k! * (n-k)!)

    // Base Cases
    if (k > n){ return 0;  }
    if (k == 0 || k == n){ return 1;  }

    return factorial[n] / (factorial[k] * factorial[n - k]);
        
}






/////////////////////// ------ MODULUS -----------/////////////////


// ll power(ll b,ll e,ll m)
// {
//     if(e==0) return 1;
//     if(e&1) return b*power(b*b%m,e/2,m)%m;
//     return power(b*b%m,e/2,m);
// }


ll power(ll b, ll e, ll p)
{
    ll res = 1LL;    // Initialize result
    b = b % p;  
 
    while (e > 0)
    {
        // If n is odd, multiply 'b' with result
        if (e & 1)  res = (res*b) % p;
 
        // e must be even now
        e = e>>1; // e = e/2
        b = (b*b) % p;
    }
    return res;
}


vl modInverse;
void arrModInverse(ll n, ll m)
{
    modInverse.resize(n+1);
    modInverse[0] = 1;
    modInverse[1] = 1;
    for (long long i = 2; i <= n; i++)
        modInverse[i] = (m - ((m / i) * modInverse[m % i]) % m) % m;
}



/**
 * @brief compute factorial and inverse factorial, integer inverse modulo p
 * @param N ubpper bound range of factorial
 * @param p modulo
 */
vl factorial, invFactorial, modInverse;
void fact_modulo(ll N, ll p)
{

    N++;
    factorial    = vl(N);
    invFactorial = vl(N);
    modInverse   = vl(N);

    ll i;
    factorial[0]=1;
    for (i=1; i<N; i++) factorial[i]=(ll)factorial[i-1]*i%p;

    invFactorial[N-1]=power(factorial[N-1], p-2, p);
    for (i=N-1; i; i--) invFactorial[i-1]=(ll)invFactorial[i]*i%p;

    ll x; modInverse[1]=1;
    for (i=2; i<N; i++)
    {
        x=p/i;
        modInverse[i]=(ll)x*(p-modInverse[p-x*i])%p;
    }
}




ll binomialCoeff(ll n, ll k, ll mod){
    // Base Cases
    if (k > n){ return 0;  }
    if (k == 0 || k == n){ return 1;  }

    return ((factorial[n]%mod * invFactorial[k]%mod)%mod * invFactorial[n - k]%mod)%mod;
}


ll invMod(ll a, ll mod){ return power(a, mod-2, mod); }





template<typename T>
class Stirling2 {
	/** *
	 * Stirling numbers of the second kind, which count the number of ways to partition a set of n elements into k nonempty subsets 
	 * 	// https://rosettacode.org/wiki/Stirling_numbers_of_the_second_kind#C++
	 *	// https://en.wikipedia.org/wiki/Stirling_number
	 *	// https://codeforces.com/blog/entry/117906
	*/
	private:  std::map<std::pair<int, int>, T> cache_;
	public: T get(int n, int k) {
		if (k == n){ return 1;  }
		if (k == 0 || k > n){ return 0;  }
			
		pii p = std::make_pair(n, k);
		if ( is_in(cache_, p)){  return cache_[p]; }
			
		return cache_[p] = ((k * get(n - 1, k)) + get(n - 1, k - 1));
	}
};



////////////////////////////////  primes number //////////////////////////

vector<bool> isPrime; // init to true
void SieveOfEratosthenes(int n)
{
    n = max(n, 2); isPrime = vb(n+1, true); isPrime[0] = isPrime[1] =  false; 
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }

}




//Fermat's Little Theorem for Primality Test
bool isPrime(ll n, int k)
{
   // Corner cases
   if (n <= 1 || n == 4)  return false;
   if (n <= 3) return true;
   if (n >= 3 && n%2==0) return false;
 
   // Try k times
   while (k>0)
   {
       // Pick a random number in [2..n-2]       
       // Above corner cases make sure that n > 4
       ll a = 2 + rand()%(n-4); 
 
       // Checking if a and n are co-prime
       if (gcd(n, a) != 1)
          return false;
  
       // Fermat's little theorem
       if (power(a, n-1, n) != 1)
          return false;
 
       k--;
    }
 
    return true;
}



//primes factor decomposition
map<ll, ll> primeFactors(ll n)  
{  
    map<ll, ll> ans;
    // Print the number of 2s that divide n  
    while (n%2 == 0)  
    {  
        ans[2]++;  
        n = n/2;  
    }  
     
    // n must be odd at this point.  So we can skip   
    // one element (Note i = i +2)  ie 3 5 7....
    for (int i = 3; i <= sqrt(n); i = i+2)  
    {  
        // While i divides n, print i and divide n  
        while (n%i == 0)  
        {  
            ans[i]++;  
            n = n/i;  
        }  
    }  
     
    // This condition is to handle the case when n   
    // is a prime number greater than 2  
    if (n > 2)  
        ans[n]++;;  

    return ans;
}  


vl getDivisors(ll X){
  vector<ll> divisor;

  // Store all the divisors of X
    for (int i = 1; i * i <= X; i++) {
        if (X % i == 0) {
            divisor.push_back(i);
            if (X / i != i)
                divisor.push_back(X / i);
        }
    }

  return divisor;
}


////////////////////========================== PolyHash ==========================/////////////////////////

class PolyHash {
	// https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
	// https://codeforces.com/contest/1907/submission/235881833

	private:
		int length;
		static const  ll mod1 = 1e9 + 7, mod2 = 1e9 + 9; 	// prime mod of polynomial hashing
		inline static ll p1, p2;							// base (point of hashing)
		inline static vl inv_pow1, inv_pow2;
		inline static vl pow1, pow2; 						// pow[i] contains P^i % M
 
	public:
		inline static int inv_size = 1;

		vl  hash1, hash2;
		pll hash_pair;

		
		PolyHash() {}
	
		PolyHash(const vl& arr) {
			length = sz(arr);
			hash1.resize(length);
			hash2.resize(length);

			updatePow(length);
	
			ll h1 = 0, h2 = 0;
			for(int i = 0; i < length; i++) {
				h1 = (h1 + (arr[i] + 1) * pow1[i]) % mod1;
				h2 = (h2 + (arr[i] + 1) * pow2[i]) % mod2;
				hash1[i] = h1;
				hash2[i] = h2;
			}
			hash_pair = make_pair(h1, h2);
	
			updateInvPow( length);
		}

		static void updateInvPow(int length){
			if(inv_size < length) {
				for(; inv_size < length; inv_size <<= 1);
				
				inv_pow1.resize(inv_size, -1);
				inv_pow2.resize(inv_size, -1);
	
				inv_pow1[inv_size - 1] = invMod(power(p1, inv_size - 1, mod1), mod1);
				inv_pow2[inv_size - 1] = invMod(power(p2, inv_size - 1, mod2), mod2);
				
				for(int i = inv_size - 2; i >= 0 && inv_pow1[i] == -1; i--) {
					inv_pow1[i] = (1LL * inv_pow1[i + 1] * p1) % mod1;
					inv_pow2[i] = (1LL * inv_pow2[i + 1] * p2) % mod2;
				}
			}
		}

		static void updatePow(int length){

			if(pow1.empty()){
				pow1.push_back(1LL);
				pow2.push_back(1LL);
			}

			while ( sz(pow1) <= length + 1) {
				pow1.push_back(( pow1.back() * p1) % mod1);
				pow2.push_back(( pow2.back() * p2) % mod2);
			}
		}

		static void genBase(){
			auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    		std::mt19937 mt_rand(seed);
    		p1 = std::uniform_int_distribution<ll>(mod1/5, mod1/2)(mt_rand);
    		p2 = std::uniform_int_distribution<ll>(mod2/5, mod2/2)(mt_rand);

			if( p1&1 == 0){p1--;}
			if( p2&1 == 0){p2--;}
		}

	
		pll subarr(const int l, const int r) {
			if(l == 0) {
				return {hash1[r], hash2[r]};
			}
			ll temp1 = hash1[r] - hash1[l - 1];
			ll temp2 = hash2[r] - hash2[l - 1];
			temp1 += (temp1 < 0 ? mod1 : 0);
			temp2 += (temp2 < 0 ? mod2 : 0);
			temp1 = (temp1 * 1LL * inv_pow1[l]) % mod1;
			temp2 = (temp2 * 1LL * inv_pow2[l]) % mod2;
			return {temp1, temp2};
		}

		ll get(const int r){
			pll hsh12 = subarr(0, r);
			return hsh12.f * p2 + hsh12.s;
		}
	
		bool operator==(const PolyHash& other) {
			return (hash_pair == other.hash_pair);
		}
		
};


/////////////////////----------------------------------------------------------/////////////////////





///////////////////========================== Miscellaneous ==========================/////////////////


ll getLastDigit( ll b, ll e, ll nDigits){ // last n digits of b power e
  return power(b, e, pow(10, nDigits) );
}


vl int_to_digit(ll n){
  vl ans;
  ll base = 10ll;
  if(n==0){ans.push_back(0ll);}
  while(n > 0){
    ans.push_back( n%base );
    n /= base;
  }

  reverse(all(ans));
  return ans;
}


vvi genIntegerPartiton(int n, bool isSorted = true) 
{   
    vvi all_partitions;

    vi partitions(n); 
    int k = 0; // Index of last element in a partition 
    partitions[k] = n; // Initialize first partition as number itself 



    auto addPartition = [&](int idx) -> void{
        vi temp ( partitions.begin() ,  partitions.begin() + idx + 1 );
        if(isSorted){ sort(all(temp));  }  
        all_partitions.push_back(temp);
    };

    while (true) 
    { 
        addPartition(k);

        int rem_val = 0; 
        while (k >= 0 && partitions[k] == 1) 
        { 
            rem_val += partitions[k]; 
            k--; 
        } 
 
        // if k < 0, all the values are 1 so there are no more partitions 
        if (k < 0) {break;}; 
 
        // Decrease the p[k] found above and adjust the rem_val 
        partitions[k]--; 
        rem_val++; 
 

        while (rem_val > partitions[k]) 
        { 
            partitions[k+1] = partitions[k]; 
            rem_val = rem_val - partitions[k]; 
            k++; 
        } 
 
        // Copy rem_val to next position and increment position 
        partitions[k+1] = rem_val; 
        k++; 

    } 


    if(isSorted){ sort(all(all_partitions), [&](const vi a, const vi b){   return sz(a) < sz(b);}); }

    return all_partitions;
} 


template<typename T> 
void gen_comb(int N, int K, T fun)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
 
    // print integers and permute bitmask
    do {

		vi idx;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) idx.push_back(i);
        }

		fun(idx);
        
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}


template<typename T> 
void gen_permu(int n, T fun){

	vi idx(n, 0); iota(all(idx), 0);
	do {
		fun(idx);
	} while (next_permutation(all(idx)));
}


/**
 * @brief  Inclusion-Exclusion principle(aka formule du crible)
 * @param  k : number of sets
 * @param  fun : function which computes the cardinality of the intersection
 * @return cnt : the result of the inclusion-exclusion principle
**/
template<class U>
ll incl_excl_principle(int k, U fun){
	ll cnt = 0ll;
	FOR(mask, 1, 1 << k){
		vi idx;
		FOR(i, 0, k) if(mask & (1 << i)) { idx.push_back(i);}
		ll sign = __builtin_popcount(mask) % 2 == 0 ? -1ll : 1ll;
		cnt += sign * fun(idx);
	}
	return cnt;
}


///////////////////-------------------------------------------------------------/////////////////


