










template<class T, int R, int C> struct Matrix {

	VT<VT<T>>  d;
	Matrix(){
		d = VT<VT<T>>(R, VT<T>(C, 0ll));
	}

	Matrix(VT<VT<T>>& _mat ){
		assert(R == sz(_mat) && C == sz(_mat[0]) );
		d = _mat;
	}

	template<int R1, int C1>
	Matrix<T, R, C1> operator*(const Matrix<T, R1, C1>& m) const {
		return (*this).dot(m,  0ll );
	}

	vector<T> operator*(const vector<T>& vec) const {
		return (*this).dot(vec, 0ll );
	}

	Matrix operator*(const T x) const {
		Matrix<T, R, C> res;
		FOR(i, 0, R) FOR(j, 0, C) res.d[i][j] = d[i][j] * x;
		return res;
	}

	Matrix operator^(ll p) const {
		return (*this).exp(p, 0ll);
	}


	template<int R1, int C1>
	Matrix<T, R, C1> dot(const Matrix<T, R1, C1>& m, ll _mod = 0ll ) const {
		assert(C == R1 );
		Matrix<T, R, C1> res;
		FOR(i, 0, R) FOR(j, 0, C1)
			FOR(k, 0, C){ 
				if( _mod == 0ll){
					res.d[i][j] += d[i][k]* m.d[k][j];  
				}else{
					res.d[i][j] += (d[i][k]* m.d[k][j])%_mod  ; 
					res.d[i][j] %= _mod;
				}
			} 

		return res;
	}

	vector<T> dot(const vector<T>& vec, ll _mod=0ll) const {
		assert(sz(vec) == C);
		vector<T> ret(R);
		FOR(i, 0, R) FOR(j, 0, C){
			if(_mod == 0ll){
				ret[i] += d[i][j] * vec[j];
			}else{
				ret[i] += (d[i][j] * vec[j])%_mod ;
				ret[i] %= _mod;
			}
		} 
		return ret;
	}

	Matrix exp(ll p, ll _mod = 0ll) const {
		assert(R == C );//assert square matx
		assert(p >= 0);
		Matrix a, b(*this);
		FOR(i, 0, R) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a.dot(b, _mod) ;
			b = b.dot(b, _mod) ;
			p >>= 1;
		}
		return a;
	}
};


