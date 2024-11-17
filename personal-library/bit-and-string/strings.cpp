
const string ALPHA_NUM_ALL = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string DIGITS_ALL    = "0123456789";
const string ALPHA_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHA_LOWER = "abcdefghijklmnopqrstuvwxyz";








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


vi to_digits(int number){
  vi sd;

  while (number > 0)
  {
      int digit = number%10;
      number /= 10;
      sd.push_back(digit);
  }
  return sd;
}
