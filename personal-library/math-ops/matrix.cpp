








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


//////////////////// --v2 ---------------------/// 

template<class T> struct Matrix {
	VT<VT<T>> data;
	int R, C;

	Matrix(int _R, int _C) : R(_R), C(_C) {
		data = VT<VT<T>>(R, VT<T>(C, 0ll));
	}

	Matrix(const VT<VT<T>>& _mat) {
		R = sz(_mat); C = sz(_mat[0]);
		data = _mat;
	}

	Matrix<T> operator*(const Matrix<T>& m) const {
		return this->dot(m, 0ll);
	}

	vector<T> operator*(const vector<T>& vec) const {
		return this->dot(vec, 0ll);
	}

	Matrix operator*(const T x) const {
		Matrix<T> res(R, C);
		FOR(i, 0, R) FOR(j, 0, C) res.data[i][j] = data[i][j] * x;
		return res;
	}

	Matrix operator^(ll p) const {
		return this->exp(p, 0ll);
	}

	Matrix<T> dot(const Matrix<T>& m, ll _mod = 0ll) const {
		assert(C == m.R);
		Matrix<T> res(R, m.C);
		FOR(i, 0, R) FOR(j, 0, m.C)
			FOR(k, 0, C) {
				if (_mod == 0ll) {
					res.data[i][j] += data[i][k] * m.data[k][j];
				} else {
					res.data[i][j] += (data[i][k] * m.data[k][j]) % _mod;
					res.data[i][j] %= _mod;
				}
			}
		return res;
	}

	vector<T> dot(const vector<T>& vec, ll _mod = 0ll) const {
		assert(sz(vec) == C);
		vector<T> ret(R);
		FOR(i, 0, R) FOR(j, 0, C) {
			if (_mod == 0ll) {
				ret[i] += data[i][j] * vec[j];
			} else {
				ret[i] += (data[i][j] * vec[j]) % _mod;
				ret[i] %= _mod;
			}
		}
		return ret;
	}

	Matrix exp(ll p, ll _mod = 0ll) const {
		assert(R == C);
		assert(p >= 0);
		Matrix a(R, C), b(*this);
		FOR(i, 0, R) a.data[i][i] = 1;
		while (p) {
			if (p & 1) a = a.dot(b, _mod);
			b = b.dot(b, _mod);
			p >>= 1;
		}
		return a;
	}
};






//////////////// v3 ---/////////


// Forward declaration of Matrix template
template<class T, typename Ops> struct Matrix;

template<class T> struct MatrixOps{
	
	static T coeff_ops(const VT<T> &vec1, const VT<T> &vec2, ll _mod = 0ll) ;

	static Matrix<T, MatrixOps<T>> power_zero(int R, int C, T default_val = 0ll) ;
};

template<class T> struct MatrixOps_Multiply: public MatrixOps<T> {

	static T coeff_ops(const VT<T> &vec1, const VT<T> &vec2, ll _mod = 0ll)  {
		assert(sz(vec1) == sz(vec2));
		T res = 0;

		FOR(i, 0, sz(vec1)) {
			if (_mod == 0ll) {
				res += vec1[i] * vec2[i];
			} else {
				res += (vec1[i]% _mod * vec2[i]% _mod) % _mod;
				res %= _mod;
			}
		}
		return res;
	}

	static Matrix<T, MatrixOps<T>> power_zero(int R, int C, T default_val = 0ll) {
		Matrix<T, MatrixOps<T>> res(R, C, default_val);
		FOR(i, 0, R) res.data[i][i] = 1; // identity matrix
		return res;
	}

};

template<class T> struct MatrixOps_MinOfSum : public MatrixOps<T> {
	static T coeff_ops(const VT<T> &vec1, const VT<T> &vec2, ll _mod = 0ll)  {
		assert(sz(vec1) == sz(vec2));
		T res = maxintll;

		FOR(i, 0, sz(vec1)) {
			if(vec1[i] == maxintll or vec2[i] == maxintll) continue; // skip if any of the coeff is inf

			chkmin(res, vec1[i] + vec2[i]);
		}
		return res;
	}

	static Matrix<T, MatrixOps_MinOfSum<T>> power_zero(int R, int C, T default_val = maxintll) {
		Matrix<T, MatrixOps_MinOfSum<T>> res(R, C, maxintll);
		FOR(i, 0, R) res.data[i][i] = 0;
		return res;
	}
};



template<class T, typename Ops> struct Matrix {
	VT<VT<T>> data;
	int R, C;

	Matrix(int _R, int _C, T default_val = 0ll) : R(_R), C(_C) {
		data = VT<VT<T>>(R, VT<T>(C, default_val));
	}

	Matrix(const VT<VT<T>>& _mat) {
		R = sz(_mat); C = sz(_mat[0]);
		data = _mat;
	}

	Matrix operator*(const Matrix& m) const {
		return this->dot(m, 0ll);
	}

	vector<T> operator*(const vector<T>& vec) const {
		return this->dot(vec, 0ll);
	}

	Matrix operator*(const T x) const {
		Matrix res(R, C);
		FOR(i, 0, R) FOR(j, 0, C) res.data[i][j] = data[i][j] * x;
		return res;
	}

	Matrix operator^(ll p) const {
		return this->exp(p, 0ll);
	}

	Matrix dot(const Matrix& m, ll _mod = 0ll) const {
		assert(C == m.R);
		Matrix res(R, m.C);
		VT<T> vec2(C); //todo replace with transposed copy of m

		FOR(i, 0, R) FOR(j, 0, m.C){
			FOR(k, 0, C){vec2[k] = m.data[k][j];}
			res.data[i][j] = Ops::coeff_ops(data[i], vec2, _mod);
		}

		return res;
	}

	vector<T> dot(const vector<T>& vec, ll _mod = 0ll) const {
		assert(sz(vec) == C);
		vector<T> ret(R);
		FOR(i, 0, R){
			ret[i] = Ops::coeff_ops(data[i], vec, _mod);
		}
		return ret;
	}

	Matrix exp(ll p, ll _mod = 0ll) const {
		// make sure coeff_ops is associative
		assert(R == C);
		assert(p >= 0);
		Matrix a = Ops::power_zero(R, C, maxintll), b(*this);
		FOR(i, 0, R) a.data[i][i] = 0;
		while (p) {
			if (p & 1) a = a.dot(b, _mod);
			b = b.dot(b, _mod);
			p >>= 1;
		}
		return a;
	}
};