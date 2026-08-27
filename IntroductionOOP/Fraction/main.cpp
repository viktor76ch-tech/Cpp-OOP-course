//1. Для класса 'Fraction' перегрузить все арифметические операторы : / , +, -;
//2. Перегрузить составные присваивания : +=, -=, *=, /=;
//3. Перегрузить Incremento / Decremento(++ / --);
//4. Перегрузить операторы сравнения : == , != , >, <, >= , <= ;


#include<iostream>
using namespace std;

class Fraction
{
	int integer;       // Целая часть
	int numerator;     // Числитель
	int denominator;   //Знаминатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denomirator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	// Constructor
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Fraction(int integer)	//explicit - явный
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:" << this << endl;
	}
	//Fraction(double decimal)
	//{
	//	//decimal - десятичная дробь.
	//	decimal += 1e-10;
	//	integer = decimal;		//1) получаем целую часть дроби;
	//	decimal -= integer;		//2) убираем целую часть из десятичной дроби;
	//	denominator = 1e+9;		//3) получаем максимально возможный знаменатель 1000000000;
	//	numerator = decimal * denominator;//4) вытаскиваем дробную часть в числитель;
	//	reduce();
	//	cout << "SingleArgumentConstructor:" << this << endl;
	//}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}
	// Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//Methods:
	Fraction& to_improper()
	{
		//перевод в неправильную дробь:
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		//перевод в правильную дробь:
		integer += numerator / denominator;
		numerator < 0 ? numerator *= -1 : numerator;
		numerator %= denominator;
		return *this;
	}
	Fraction& turn_over()
	{
		//переворачиваем дробь:
		int temp;
		temp = numerator;
		numerator = denominator;
		denominator = temp;
		return *this;
	}
	void Print()const
	{
		if (integer) cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}

	//operators overloading
	Fraction operator+=(Fraction right)
	{
		this->to_improper();
		right.to_improper();
		return Fraction
		(
			(this->get_numerator() * right.get_denomirator() +
				right.get_numerator() * this->get_denomirator()),
			this->get_denomirator() * right.get_denomirator()
		).to_proper();
	}
	Fraction operator-=(Fraction right)
	{
		this->to_improper();
		right.to_improper();
		return Fraction
		(
			(this->get_numerator() * right.get_denomirator() -
				right.get_numerator() * this->get_denomirator()),
			this->get_denomirator() * right.get_denomirator()
		).to_proper();
	}
	Fraction operator*=(Fraction right)
	{
		this->to_improper();
		right.to_improper();
		return Fraction
		(
			this->get_numerator() * right.get_numerator(),
			this->get_denomirator() * right.get_denomirator()
		).to_proper();
	}
	Fraction operator/=(Fraction right)
	{
		this->to_improper();
		right.to_improper().turn_over();
		return Fraction
		(
			this->get_numerator() * right.get_numerator(),
			this->get_denomirator() * right.get_denomirator()
		).to_proper();
	}
	Fraction& operator++()
	{
		this->set_integer(this->get_integer() + 1);
		return *this;
	}
	Fraction& operator++(int)
	{
		this->set_integer(this->get_integer() + 1);
		return *this;
	}
	Fraction& operator--()
	{
		this->set_integer(this->get_integer() - 1);
		return *this;
	}
	Fraction& operator--(int)
	{
		this->set_integer(this->get_integer() - 1);
		return *this;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator()* right.get_numerator());
	result.set_denominator(left.get_denomirator()* right.get_denomirator());*/
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denomirator() * right.get_denomirator()
	).to_proper();
}

Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper().turn_over();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denomirator() * right.get_denomirator()
	).to_proper();
}

Fraction operator+(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();
	Fraction result;
	result.set_numerator(left.get_numerator() * right.get_denomirator() + right.get_numerator() * left.get_denomirator());
	result.set_denominator(left.get_denomirator() * right.get_denomirator());
	result.to_proper();
	return result;*/


	left.to_improper();
	right.to_improper();
	return Fraction
	(
		(left.get_numerator() * right.get_denomirator() +
			right.get_numerator() * left.get_denomirator()),
		left.get_denomirator() * right.get_denomirator()
	).to_proper();
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		(left.get_numerator() * right.get_denomirator() -
			right.get_numerator() * left.get_denomirator()),
		left.get_denomirator() * right.get_denomirator()
	).to_proper();
}

bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() / left.get_denomirator() ==
		right.get_numerator() / right.get_denomirator())
		return true;
	else
		return false;
}
bool operator!=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() / left.get_denomirator() !=
		right.get_numerator() / right.get_denomirator())
		return true;
	else
		return false;
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() / left.get_denomirator() >
		right.get_numerator() / right.get_denomirator())
		return true;
	else
		return false;
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() / left.get_denomirator() <
		right.get_numerator() / right.get_denomirator())
		return true;
	else
		return false;
}
bool operator<=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() / left.get_denomirator() <=
		right.get_numerator() / right.get_denomirator())
		return true;
	else
		return false;
}
bool operator>=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() / left.get_denomirator() >=
		right.get_numerator() / right.get_denomirator())
		return true;
	else
		return false;
}

//#define CONSTRUCTOR_CHECK
//#define TASK_1
//#define TASK_2
//#define TASK_3
#define TASK_4

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTOR_CHECK
	Fraction A;		//Default constructor
	A.Print();

	Fraction B = 5;//Single-Argument constructor
	B.Print();

	Fraction C(1, 2);
	C.Print();

	Fraction D(2, 3, 4);
	D.Print();

#endif // CONSTRUCTOR_CHECK

	Fraction A(1, 2, 3);
	A.Print();

	Fraction B(2, 3, 4);
	B.Print();

	Fraction N(1, 2, 3);
	N.Print();

#ifdef TASK_1
	Fraction C = A * B;
	C.Print();

	Fraction D = B / A;
	D.Print();

	Fraction E = A + B;
	E.Print();

	Fraction F = A - B;
	F.Print();

	Fraction G = B - A;
	G.Print();

#endif // TASK_1

#ifdef TASK_2

	Fraction H = A += B;
	H.Print();

	Fraction I = A -= B;
	I.Print();

	Fraction J = A *= B;
	J.Print();

	Fraction K = B /= A;
	K.Print();

#endif // TASK_2

#ifdef TASK_3

	++A;
	A.Print();

	A++;
	A.Print();

	--B;
	B.Print();

	B--;
	B.Print();

#endif // TASK_3

#ifdef TASK_4

	cout << "Дроби 'A' и 'N' " << (A == N ? "" : "не ") << "равны!" << endl;
	cout << "Дроби 'A' и 'B' " << (A != B ? "не " : "") << "равны!" << endl;
	cout << "Дробь 'A' " << (A > B ? "" : "не ") << "больше дроби 'B'" << endl;
	cout << "Дробь 'A' " << (A < B ? "" : "не ") << "меньше дроби 'B'" << endl;
	cout << "Дробь 'A' " << (A <= B ? "" : "не ") << "меньше или равна дроби 'B'" << endl;
	cout << "Дробь 'A' " << (A >= B ? "" : "не ") << "больше или равна дроби 'B'" << endl;
	


#endif // TASK_4
}