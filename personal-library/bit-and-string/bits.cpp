


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
     * @return binary array in big-endian format (MSB comes first(0)), eg 3 --> 0 0 1 1
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

bool isPowerOfTwo(ll n){  return (n > 0) && ((n & (n - 1)) == 0);}

ll lsBit(ll n){return (n & -n); } // Least SB

ll msBit(unsigned long long N) { // Most SB
  if( N == 0){return 0;} return 1ll << (64 - __builtin_clzll(N) - 1);
}

unsigned int flipAllExceptK(unsigned int n, unsigned int k)
{
  /*1) Toggle k-th bit by doing n ^ (1 << k)
    2) Toggle all bits of the modified number */
  return ~(n ^ (1 << k));
}




