#include "polynomial.hpp"
#include <vector>
#include <cmath>

// Constructors
Polynomial::Polynomial()
    : coefficients_(std::vector<double>()) {}                           // Default constructor

Polynomial::Polynomial(std::vector<double> const& coefficients)
    : coefficients_(coefficients) {}                                    // Constructor taking values

Polynomial::Polynomial(Polynomial const& other)
    : coefficients_(other.coefficients_) {}                             // Copy constructor


std::vector<double> Polynomial::GetCoefficients() const noexcept {
    return std::vector<double>(coefficients_);  // return a copy
}
const std::vector<double>& Polynomial::GetCoefficientsRef() const noexcept {
    return coefficients_;  // return a reference
}

double Polynomial::compute(double x) const {
    double result = 0;
    for (int i = 0; i < coefficients_.size(); i++) {
        result += coefficients_[i] * std::pow(x, i);
    }
    return result;
}

int Polynomial::degree() const {
    if (coefficients_.size() == 0) return 0;
    return coefficients_.size() - 1;
}

// Operators
Polynomial Polynomial::operator+(Polynomial const& other) const {
    Polynomial poly;
    std::vector<double> coofs_other = other.GetCoefficients();
    std::vector<double> coofs_this = this->GetCoefficients();
    std::vector<double> result(std::max(coofs_other.size(), coofs_this.size()), 0.0);
    int last_added_index = 0;
    for (int i = 0; i < std::min(coofs_other.size(), coofs_this.size()); ++i) {
        result[i] = coofs_this[i] + coofs_other[i];
        last_added_index = i;
    }

    if (coofs_other.size() > coofs_this.size()) {
        for (int i = last_added_index + 1; i < coofs_other.size(); ++i) {
            result[i] = coofs_other[i];
        }
    } else if (coofs_this.size() > coofs_other.size()) {
        for (int i = last_added_index + 1; i < coofs_this.size(); ++i) {
            result[i] = coofs_this[i];
        }
    }
    return result;
}

Polynomial Polynomial::operator-(Polynomial const& other) const {
    return *this + (other * Polynomial(std::vector<double>({-1})));
}

Polynomial Polynomial::operator*(Polynomial const& other) const {
    std::vector<double> coofs_other = other.GetCoefficients();
    std::vector<double> coofs_this = this->GetCoefficients();
    std::vector<double> result(coofs_other.size() + coofs_this.size() - 1, 0.0);
    for (int i = 0; i < coofs_this.size(); ++i) {
        for (int j = 0; j < coofs_other.size(); ++j) {
            result[i + j] += coofs_this[i] * coofs_other[j];
        }
    }
    return result;
}

bool Polynomial::operator==(Polynomial const& other) const {
    return this->GetCoefficients() == other.GetCoefficients();
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    std::vector<double> coeffs = poly.GetCoefficients();
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        if (coeffs[i] == 0) continue;
        if (i > 0) {
            os << coeffs[i] << "x^" << i << " + ";
        } else {
            os << coeffs[i];
        }
    }
    return os;
}

