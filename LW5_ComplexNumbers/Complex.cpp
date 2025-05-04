// blog.skillfactory.ru/kompleksnye-chisla-chto-eto-takoe-i-zachem-nuzhny/
// ru.wikipedia.org/wiki/Комплексное_число
#include "Complex.h"
#include <cmath>
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

