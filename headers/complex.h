#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct complex_t {
  double real;
  double imag;
} complex_t;

complex_t c_mul(complex_t a, complex_t b);
complex_t c_div(complex_t a, complex_t b);
complex_t c_add(complex_t a, complex_t b);
complex_t c_sub(complex_t a, complex_t b);

#endif /* end of include guard: COMPLEX_H */
