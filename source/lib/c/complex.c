#include "complex.h"

complex_t c_mul(complex_t a, complex_t b)
{
  return (complex_t) {
    (a.real * b.real - a.imag * b.imag),
    (a.real * b.imag + a.imag * b.real)
  };
}

complex_t c_div(complex_t a, complex_t b)
{
  double div = (b.real * b.real + b.imag * b.imag);
  return (complex_t) {
      (a.real * b.real + a.imag * b.imag) / div,
      (a.imag * b.real - a.real * b.imag) / div
  };
}

complex_t c_sub(complex_t a, complex_t b)
{
  return (complex_t) {a.real - b.real, a.imag - b.imag};
}

complex_t c_add(complex_t a, complex_t b)
{
  return (complex_t) {(a.real + b.real), (a.imag + b.imag)};
}
