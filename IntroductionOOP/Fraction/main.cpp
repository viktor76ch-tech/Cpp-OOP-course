#include<iostream>
using namespace std;

class Fraction;        //Объявление класса
Fraction operator*(Fraction left, Fraction right);//объявление функции
Fraction operator/(const Fraction& left, const Fraction& right);
class Fraction         //Реализация класса
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
	int get_denominator()const
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

	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}

	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//				Incremento/Decremento:
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	const Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()
	{
		integer--;
		return *this;
	}
	const Fraction operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
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
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);	//Функция swap() меняет местами 2 переменные
		return inverted;
	}
	Fraction& reduce()
	{
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		int more, less, rest;
		//more - больше
		//less - меньше
		//rest - остаток
		if (numerator > denominator)more = numerator, less = denominator;
		else	less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;	//GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
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

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator()* right.get_numerator());
	result.set_denominator(left.get_denominator()* right.get_denominator());*/
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}
//#define CONSTRUCTOR_CHECK
#define ARITHMETICAL_OPERATORS_CHECK
//#define INCREMENTO_DECREMENTO_CHECK
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

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.Print();

	Fraction B(3, 4, 5);
	B.Print();

	Fraction C = A * B;
	C.Print();

	C = A / B;
	C.Print();

	A *= B;
	A.Print();

	A /= B;
	A.Print();

	C = A + B;
	C.Print();

#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef INCREMENTO_DECREMENTO_CHECK
	Fraction A(2, 3, 4);
	Fraction B(2, 3, 4);
	B *= A++;
	A.Print();
	B.Print();
#endif // INCREMENTO_DECREMENTO_CHECK


}