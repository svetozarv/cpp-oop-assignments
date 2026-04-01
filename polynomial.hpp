#include <vector>
#include <iostream>

class Polynomial {
    std::vector<double> coefficients_;  // index odpowiada potędze

  public:
    Polynomial();
    Polynomial(const std::vector<double>& coefficients);

    // Rule of 5 (don't need to define, since we are using std::vector which manages its own resources well enough)
    // Default implementation of copy constructor is probably not needed too, but we can define it explicitly for clarity
    ~Polynomial() = default;                                        // 1. Destructor
    Polynomial(Polynomial const& other);                            // 2. Copy Constructor
    Polynomial& operator=(Polynomial const& other) = default;       // 3. Copy Assignment
    Polynomial(Polynomial&& other) noexcept = default;              // 4. Move Constructor
    Polynomial& operator=(Polynomial&& other) noexcept = default;   // 5. Move Assignment

    std::vector<double> GetCoefficients() const noexcept;
    const std::vector<double>& GetCoefficientsRef() const noexcept;

    double compute(double x) const;
    int degree() const;

    Polynomial operator+(Polynomial const& other) const;
    Polynomial operator-(Polynomial const& other) const;
    Polynomial operator*(Polynomial const& other) const;
    bool operator==(Polynomial const& other) const;

    friend std::ostream& operator<< (std::ostream &os, const Polynomial &p);
    // friend std::istream& operator>> (std::istream &is, Polynomial &p);
};