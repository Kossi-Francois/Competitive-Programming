






// --------- unredductible fraction class ---------

template<typename T>
class Rational{
	public:
	mutable T num, den;
	Rational(T n, T d) : num(n), den(d) {
		if(den == 0){ throw invalid_argument("Denominator cannot be zero"); }
		reduce();
	}
	Rational(T n) : num(n), den(1) { reduce(); } // constructor for integer
	Rational() : num(0), den(1) {} // default constructor for zero fraction
	Rational(const Rational &other) : num(other.num), den(other.den) { reduce();  } // copy constructor
	Rational& operator=(const Rational &other) {
		if(this != &other){
			num = other.num;
			den = other.den;
		}
		reduce();
		return *this;
	}

	void reduce() const {
		if(den < 0){ num = -num; den = -den; } // make denominator positive
		if(num == 0){ den = 1; return; } // zero fraction
		T g = __gcd(abs(num), abs(den));
		num /= g; den /= g;
	}

	ld eval() const {
		return static_cast<ld>(num) / den;
	}

	// Arithmetic operations
	Rational operator+( const Rational &other) const {
		if(den == 0 || other.den == 0){ throw invalid_argument("Cannot add with zero denominator"); }
		(*this).reduce();
		other.reduce();
		
		T new_num = num * other.den + other.num * den;
		T new_den = den * other.den;
		return Rational(new_num, new_den);
	}
	Rational operator-() const {
		reduce();
		return Rational(-num, den);
	}
	Rational operator-(const Rational &other) const {
		reduce();
		other.reduce();
		return (*this) + (-other);
	}
	Rational operator*(const Rational &other) const {
		if(den == 0 || other.den == 0){ throw invalid_argument("Cannot multiply with zero denominator"); }
		(*this).reduce();
		other.reduce();
		T new_num = num * other.num;
		T new_den = den * other.den;
		return Rational(new_num, new_den);
	}
	Rational operator/(const Rational &other) const {
		if(other.num == 0){ throw invalid_argument("Cannot divide by zero"); }
		reduce();
		other.reduce();
		return (*this) * Rational(other.den, other.num);
	}

	Rational operator+=(const Rational &other) {
		reduce();
		other.reduce();
		*this = *this + other;
		return *this;
	}
	Rational operator-=(const Rational &other) {
		(*this).reduce();
		other.reduce();
		*this = *this - other;
		return *this;
	}
	Rational operator*=(const Rational &other) {
		reduce();
		other.reduce();
		*this = (*this) * other;
		return *this;
	}
	Rational operator/=(const Rational &other) {
		if(other.num == 0){ throw invalid_argument("Cannot divide by zero"); }
		reduce();
		other.reduce();
		*this = *this / other;
		(*this).reduce();
		return *this;
	}

	Rational operator+(T scalar) const {
		return (*this) + Rational(scalar, 1);
	}
	Rational operator-(T scalar) const {
		return (*this) - Rational(scalar, 1);
	}
	Rational operator*(T scalar) const {
		return (*this) * Rational(scalar, 1);
	}
	Rational operator/(T scalar) const {
		if(scalar == 0){ throw invalid_argument("Cannot divide by zero"); }
		return (*this) / Rational(scalar, 1);
	}

	Rational operator++() {
		*this = (*this) + Rational(1, 1);
		return *this;
	}
	Rational operator--() {
		*this = (*this) - Rational(1, 1);
		return *this;
	}


	// Comparison operators
	bool operator==(const Rational &other) const {
		reduce();
		other.reduce();
		return num == other.num && den == other.den;
	}
	bool operator!=(const Rational &other) const {
		return !(*this == other);
	}
	bool operator<(const Rational &other) const {
		reduce();
		other.reduce();
		return num * other.den < other.num * den;
	}
	bool operator<=(const Rational &other) const {
		return (*this < other) || (*this == other);
	}
	bool operator>(const Rational &other) const {
		return !(*this <= other);
	}
	bool operator>=(const Rational &other) const {
		return !(*this < other);
	}
};

namespace std {
    template<typename T> class numeric_limits<Rational<T>> {
    public:
       static Rational<T> lowest() {return numeric_limits<T>::lowest() ;};
       static Rational<T> min() {return numeric_limits<T>::min() ;};
       static Rational<T> max() {return numeric_limits<T>::max() ;};
       // One can implement other methods if needed
    };
}





