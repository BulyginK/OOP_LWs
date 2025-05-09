// blog.skillfactory.ru/kompleksnye-chisla-chto-eto-takoe-i-zachem-nuzhny/
// ru.wikipedia.org/wiki/Комплексное_число
#include "Complex.h"
#include <stdexcept>

CComplex::CComplex(double real, double image)
	: m_real (real)
	, m_image (image)
{
	if (std::isnan(real) || std::isnan(image)) {
		throw std::invalid_argument("Complex number parts cannot be NaN");
	}
};

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return std::hypot(m_real, m_image);
}

double CComplex::GetArgument() const {
	if (m_real == 0.0 && m_image == 0.0) {
		throw std::invalid_argument("Argument of zero complex number is undefined");
	}
	return std::atan2(m_image, m_real);
}

// Бинарыне +, -, *, /
CComplex operator+(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.m_real + rhs.m_real, lhs.m_image + rhs.m_image);
}
CComplex operator-(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.m_real - rhs.m_real, lhs.m_image - rhs.m_image);
}
CComplex operator*(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(
		lhs.m_real * rhs.m_real - lhs.m_image * rhs.m_image,
		lhs.m_real * rhs.m_image + lhs.m_image * rhs.m_real
	);
}
CComplex operator/(const CComplex& lhs, const CComplex& rhs)
{
	const double denominator = rhs.m_real * rhs.m_real + rhs.m_image * rhs.m_image;
	if (denominator == 0.0)
		throw std::invalid_argument("Division by zero");

	return CComplex(
		(lhs.m_real * rhs.m_real + lhs.m_image * rhs.m_image) / denominator,
		(lhs.m_image * rhs.m_real - lhs.m_real * rhs.m_image) / denominator
	);
}

// Унарные + и -
CComplex CComplex::operator+() const 
{ 
	return *this;
}
CComplex CComplex::operator-() const
{ 
	return CComplex(-m_real, -m_image);
}

// Составные операторы присваивания
CComplex& CComplex::operator+=(const CComplex& other)
{
	m_real += other.m_real;
	m_image += other.m_image;
	return *this;
}
CComplex& CComplex::operator-=(const CComplex& other)
{
	m_real -= other.m_real;
	m_image -= other.m_image;
	return *this;
}
CComplex& CComplex::operator*=(const CComplex& other)
{
	*this = *this * other;
	return *this;
}
CComplex& CComplex::operator/=(const CComplex& other)
{
	*this = *this / other;
	return *this;
}

// Операторы сранения
bool operator==(const CComplex& lhs, const CComplex& rhs)
{
	return fabs(lhs.m_real - rhs.m_real) < DBL_EPSILON &&
		fabs(lhs.m_image - rhs.m_image) < DBL_EPSILON;
}

bool operator==(double lhs, const CComplex& rhs)
{
	return CComplex(lhs) == rhs;
}

bool operator!=(const CComplex& lhs, const CComplex& rhs)
{
	return !(lhs == rhs);
}

bool operator!=(double lhs, const CComplex& rhs)
{
	return !(lhs == rhs);
}

// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& os, const CComplex& num)
{
	os << num.m_real;
	os << (num.m_image >= 0 ? "+" : "") << num.m_image << "i";
	return os;
}

std::istream& operator>>(std::istream& is, CComplex& num)
{
	double real = 0, imag = 0;
	char sign = '+', i = '\0';

	is >> real >> sign;
	if (sign != '+' && sign != '-') {
		is.setstate(std::ios::failbit);
		return is;
	}

	is >> imag >> i;
	if (i != 'i') {
		is.setstate(std::ios::failbit);
		return is;
	}

	if (sign == '-') imag = -imag;
	num = CComplex(real, imag);
	return is;
}

//std::ostream& operator<<(std::ostream& stream, CComplex const& complex)
//{
//	std::string sign;
//	sign = complex.Im() >= 0 ? '+' : '-';
//	stream << complex.Re() << sign << fabs(complex.Im()) << 'i';
//	return stream;
//}
//
//std::istream& operator>>(std::istream& stream, CComplex& complex)
//{
//	double re;
//	double im;
//	if ((stream >> re) && (stream >> im) && (stream.get() == 'i'))
//	{
//		CComplex newComplex(re, im);
//		complex = newComplex;
//	}
//	else
//	{
//		stream.setstate(std::ios_base::failbit | stream.rdstate());
//	}
//	return stream;
//}
