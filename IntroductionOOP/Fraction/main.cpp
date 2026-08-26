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
		numerator %= denominator;
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

//#define CONSTRUCTOR_CHECK
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

	Fraction C = A * B;
	C.Print();
}