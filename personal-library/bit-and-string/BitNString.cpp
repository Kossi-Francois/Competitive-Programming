


const string ALPHA_NUM_ALL = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string DIGITS_ALL    = "0123456789";
const string ALPHA_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHA_LOWER = "abcdefghijklmnopqrstuvwxyz";






class BitsSet {
	public :
		int bitsize;
		vi bitset;

		ll currentVal;

		BitsSet(int bitsize){
			__init__(bitsize);
		}

		BitsSet(){
			bitsize = 32;
			__init__(bitsize);
		}

		void __init__(int bitsz){
			bitsize = bitsz;
			bitset = vi(bitsize, 0);
		}



		void  updateAND(ll val, bool addOrRemove){

			vi bitsx = decimalToBinary(val, bitsize);
			FOR(i, 0, bitsize)  {
				bitset[i] += (bitsx[i] == 0 ? 1 : 0) * (addOrRemove ? +1 : -1); // count for bit which is not set (0)
			}
			currentVal = binaryToDecimal(bitset, 0 );// for biwise &, take 0 as the bit wich is set
		};


		void  updateOR(ll val, bool addOrRemove){

			vi bitsx = decimalToBinary(val, bitsize);
			vi _bitset(bitsize);
			FOR(i, 0, bitsize)  {
				bitset[i] += (bitsx[i] == 1 ? 1 : 0) * (addOrRemove ? +1 : -1); // count for bit set (1)
				_bitset[i] = bitset[i] > 0 ;
			}
			currentVal = binaryToDecimal(_bitset, 1 );// for biwise &, take 1 as the bit wich is set
		};


    /**
     * @brief  Convert an int into a padded binary array
     * @param  x:  integer to convert
     * @param  n:  length of pdded array, if n < minimum needed size to represent x in bin array, no padding is applied
     * @param  padding:  value of padding
     * @return binary array in big-endian format (MSB comes first(0)), eg 7 --> 0 1 1 1
    */
		static vi decimalToBinary(ll x, int n, bool padding = 0) {
			vi ret;
			while(x) {
				ret.push_back(  (x&1) ?  1 : 0);
				x>>=1;  
			}

			if(sz(ret) < n){ // zeros padding
				ret.resize(n, padding);
			}

			reverse(ret.begin(),ret.end());
			return ret;
		}


    /**
     * @brief  Convert binary array into a integer
     * @param  bitSet:  binary array in big-endian format (MSB comes first(0)), eg 3 --> 0 0 1 1
     * @param  checkedBit:  value of set bit
     * @return intger
    */
		static ll binaryToDecimal(vi bitSet, bool checkedBit = true ){
			ll dec_num = 0;
			int power  = 0;
			int n = sz(bitSet);
			
			ROF(i, n, 0){
				if(bitSet[i] == checkedBit ){
					dec_num += (1<<power) ;
				}
				power++ ;
			}
			
			return dec_num;
		}

};







bool isKthBitSetL(ll n, int k)
{
  return (n & (1 << k ));
}

bool isKthBitSetR(ll n, int k)
{
  return ((n >> k ) & 1);
}



// function to toggle bits in the given range
ll setAllBitgivenRange(ll n, int l, int r)
{
    // calculating a number 'range' having set
    // bits in the range from l to r and all other
    // bits as 0 (or unset).
    ll range = (((1LL << (l - 1)) - 1) ^   
                ((1LL << (r)) - 1));
 
    return (n | range);
}


int xorFirstN(int n){

  // If n is a multiple of 4 
  if (n % 4 == 0) 
    return n; 
  
  // If n%4 gives remainder 1 
  if (n % 4 == 1) 
    return 1; 
  
  // If n%4 gives remainder 2 
  if (n % 4 == 2) 
    return n + 1; 
  
  // If n%4 gives remainder 3 
  return 0; 
}


int xorRange(int l, int r){
  return xorFirstN(l - 1) ^ xorFirstN(r);
}



//////////////////////////// --- string ---- /////////////////

bool isPalindrome(string& palinS, int i, int j){
  while (i <= j) {
    if (palinS[i] != palinS[j]) {
      return false;
    }
    i++;
    j--;
  }
  return true;
}




/* Overloading * operator for string */
string operator * (string a, unsigned int b) {
    string output = "";
    while (b--) {
        output += a;
    }
    return output;
}



ll hamming_distance(string x, string y, ll N)
{
    ll dist = 0;

    for(ll i = 0; i<N; i++){
        if(x[i] != y[i]) dist++;
    }
    return dist;
}


int costAlphaCycle(char a, char b){
	int aa = a - 'a';
	int bb = b - 'a';

	if(bb < aa){swap(aa, bb);}
	
	return min( bb - aa,   26 - bb + aa   );
}



bool issubstring(string str2, string rep1)
{
  int M = str2.length();
  int N = rep1.length();
 
  // Check for substring from starting
  // from i'th index of main string
  for (int i = 0; i <= N - M; i++) {
      int j;

      // For current index i,
      // check for pattern match
      for (j = 0; j < M; j++)
          if (rep1[i + j] != str2[j])
              break;

      if (j == M) // pattern matched
          return true;
  }

  return false; // not a substring
}





std::string trim(const std::string & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}




ll stringToInt(string& num) {
    ll ans = 0ll;
    trav(digit, num) {
        ans = ans * 10 + (digit-'0');
    }
    return ans;
}



template<typename T>
string join( T& inp, string sep = "" ){

  std::stringstream ss;
  int i = 0;
  trav(item, inp)
  {
    if(i++ != 0){ ss << sep;   }
    ss << item;
  }
  std::string res = ss.str();
  return res;
}


vs split( string inputString, char delimiter = ','  ){
  stringstream ss(inputString); 

  // Tokenize the input string by comma delimiter 
  string token; 
  vector<string> tokens; 

  while (getline(ss, token, delimiter)) { 
    tokens.push_back(token); 
  } 

  return tokens;
}


