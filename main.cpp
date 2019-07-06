#include<iostream>
using namespace std;

//#define CONSTRUCTORS_CHECK
//#define METHODS_CHECK
//#define OPERATORS_CHECK
#define COMPARISON_OPERATORS_CHECK

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);

class Fraction
{
	int integer; //целая часть
	int numenator; //числитель
	int denominator; //знаменатель
public:
	const int& get_integer() const
	{
		return integer;
	}
	int& get_integer()
	{
		return integer;
	}
	const int& get_numenator() const
	{
		return numenator;
	}
	int& get_numenator()
	{
		return numenator;
	}
	const int& get_denominator() const
	{
		return denominator;
	}
	int& get_denominator()
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numenator(int numenator)
	{
		this->numenator = numenator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//    Constructors
	Fraction()
	{
		this->integer = 0;
		this->numenator = 0;
		this->denominator = 1;
		cout << "DefConstructor:\t " << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numenator = 0;
		this->denominator = 1;
		cout << "SingleArgConstructor: " << this << endl;
	}
	Fraction(int numenator, int denominator)
	{
		this->integer = 0;
		this->numenator = numenator;
		this->set_denominator(denominator);
		cout << "Constructor:\t " << this << endl;
	}
	Fraction(int integer, int numenator, int denominator)
	{
		this->integer = integer;
		this->numenator = numenator;
		this->set_denominator(denominator);
		cout << "Constructor:\t " << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numenator = other.numenator;
		this->denominator = other.denominator;
		cout << "CopyConstructor: " << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t " << this << endl;
	}
	//   Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numenator = other.numenator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t " << this << endl;
		return *this;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this *other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//   Increment/Decrement
	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}
	Fraction& operator--()
	{
		this->integer--;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction temp = *this;// сохраняем значение, которое нужно вернуть
							//(текущее состояние обьекта)
		this->integer++;
		return temp;
	}
	Fraction operator--(int)
	{
		Fraction temp = *this;// сохраняем значение, которое нужно вернуть
							//(текущее состояние обьекта)
		this->integer--;
		return temp;
	}

	/*operator bool()
	{
		if (integer == 0 && numenator == 0) return false;
		return true;
	}*/

	//     Aritmetical operators
	/*Fraction operator*(const Fraction& other) const
	{
		Fraction left = *this;
		Fraction right = other;
		left.to_improper();
		right.to_improper();
		return Fraction(left.numenator*right.numenator, left.denominator*right.denominator).reduce().to_proper();
	}*/

	//Type cast  operators:
	/*operator int()
	{
		return integer;
	}*/

	//  Methods:
	Fraction& to_proper()
	{
		//переводит дробь в правильную (выделяет целую часть, если она есть);
		integer += numenator / denominator;
		numenator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//переводит дробь в неправильную (целую часть сливает с числителем);
		numenator += integer * denominator;
		integer -= integer;
		return *this;
	}
	Fraction& reduce()
	{
		//Сокращает дробь;
		int more;
		int less;
		int reminder = 0;
		if (numenator > denominator) more = numenator, less = denominator;
		else less = numenator, more = denominator;
		do
		{
			reminder = more % less;
			more = less;
			less = reminder;
		} while (reminder);
		int GCD = more;
		numenator /= GCD;
		denominator /= GCD;
		return *this;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction(left.get_numenator()*right.get_numenator(), left.get_denominator()*right.get_denominator()).reduce().to_proper();
}

Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction(left.get_numenator()*right.get_denominator(), left.get_denominator() * right.get_numenator()).reduce().to_proper();
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	return Fraction
	(left.get_integer() + right.get_integer(),
		left.get_numenator()*right.get_denominator() + right.get_numenator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()).to_proper().reduce();
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper().reduce();
	right.to_improper().reduce();
	return Fraction
	(left.get_numenator()*right.get_denominator() - right.get_numenator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()).to_proper().reduce();
}

bool operator==(Fraction left, Fraction right)
{
	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numenator() == right.get_numenator() && left.get_denominator() == right.get_denominator();
}

bool operator!=(Fraction left, Fraction right)
{
	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numenator() * right.get_denominator() != right.get_numenator() * left.get_denominator();
}

bool operator>(Fraction left, Fraction right)
{
	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numenator()*right.get_denominator() > right.get_numenator() * left.get_denominator();
}

bool operator<(Fraction left, Fraction right)
{
	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numenator()*right.get_denominator() < right.get_numenator() * left.get_denominator();
}

bool operator>=(Fraction left, Fraction right)
{
	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numenator()*right.get_denominator() >= right.get_numenator() * left.get_denominator();
}

bool operator<=(Fraction left, Fraction right)
{
	left.reduce().to_improper();
	right.reduce().to_improper();
	return left.get_numenator()*right.get_denominator() <= right.get_numenator() * left.get_denominator();
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer() != 0) os << obj.get_integer();
	if (obj.get_numenator() != 0)
	{
		if (obj.get_integer() != 0) os << "(" << obj.get_numenator() << "/" << obj.get_denominator() << ")";
		else  os << obj.get_numenator() << "/" << obj.get_denominator();
	}
	if (obj.get_integer() == 0 && obj.get_numenator() == 0) os << 0;
	return os;
}

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef CONSTRUCTORS_CHECK
	Fraction A(2, 3, 4);
	cout << A << endl;
	Fraction B = A; //Copy constructor
	cout << B << endl;
	Fraction C;     //Default constructor
	C = B;          //Copy assignment
	Fraction D = C++;
	cout << D << "\t" << C << endl;
	cout << C++ << endl;
	cout << C << endl;
#endif CONSTRUCTORS_CHECK
#ifdef METHODS_CHECK
	Fraction A(3600, 840);
	cout << A.to_proper() << endl;
	cout << A.to_improper() << endl;
	cout << A.reduce() << endl;
#endif METHODS_CHECK
#ifdef OPERATORS_CHECK
	Fraction A(1, 3, 3);
	Fraction B(1, 2, 3);
	cout << "\n---------------------------------" << endl;
	cout << "A * B = " << A * B << endl;
	cout << "\n---------------------------------" << endl;
	cout << "A / B = " << (A / B) << endl;
	cout << "\n---------------------------------" << endl;
	cout << "A + B = " << A + B << endl;
	cout << "\n---------------------------------" << endl;
	cout << "A - B = " << (A - B) << endl;
	cout << "\n---------------------------------" << endl;
	/*cout << "A += B = " << (A += B) << endl;*/
	/*A += B;
	cout << A << endl;*/
	/*cout << "\n---------------------------------" << endl;
	cout << "A -= B = " << (A -= B) << endl;
	*/
	/*cout << "\n---------------------------------" << endl;
	cout << "A *= B = " << (A *= B) << endl;*/
	/*A *= B;
	cout << A << endl;*/
	cout << "\n---------------------------------" << endl;
	cout << "A /= B = " << (A /= B) << endl;
#endif OPERATORS_CHECK

#ifdef COMPARISON_OPERATORS_CHECK
	Fraction A(1, 2, 3);
	Fraction B(5, 2, 3);
	cout << "\n---------------------------------" << endl;
	cout << (A == B) << endl;
	if (A == B)
	{
		cout << "Числа равны " << endl;
	}
	else cout << "Числа не равны " << endl;
	cout << "\n---------------------------------" << endl;
	cout << (A != B) << endl;
	if (A != B)
	{
		cout << "Числа не равны " << endl;
	}
	else cout << "Числа равны " << endl;
	cout << "\n---------------------------------" << endl;
	cout << (A > B) << endl;
	if (A != B && A > B)
	{
		cout << "A > B" << endl;
	}
	else if (A == B)
	{
		cout << "Числа равны " << endl;
	}
	else cout << "A < B" << endl;
	cout << "\n---------------------------------" << endl;
	cout << (A < B) << endl;
	if (A != B && A < B)
	{
		cout << "A < B" << endl;
	}
	else if (A == B)
	{
		cout << "Числа равны " << endl;
	}
	else cout << "A > B" << endl;
	cout << "\n---------------------------------" << endl;
	cout << (A >= B) << endl;
	if (A == B || A > B)
	{
		cout << "A >= B" << endl;
	}
	else cout << "A < B" << endl;
	cout << "\n---------------------------------" << endl;
	cout << (A <= B) << endl;
	if (A == B || A < B)
	{
		cout << "A <= B" << endl;
	}
	else cout << "A > B" << endl;
#endif COMPARISON_OPERATORS_CHECK
}