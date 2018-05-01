#ifndef _POLYNOMIAL_REGRESSION_H
#define _POLYNOMIAL_REGRESSION_H

/**
* Copied from: https://gist.github.com/chrisengelsma/108f7ab0a746323beaaf7d6634cf4add
* Modified by Stefan Grimm, all credits to the originator!
*
* PURPOSE:
*  Polynomial Regression aims to fit a non-linear relationship to a set of
*  points. It approximates this by solving a series of linear equations using
*  a least-squares approach.
*
*  We can model the expected value y as an nth degree polynomial, yielding
*  the general polynomial regression model:
*
*  y = a0 + a1 * x + a2 * x^2 + ... + an * x^n
* @author Chris Engelsma
*/

class PolynomialRegression {
  public:
  template <typename TMATH>
  static void fitIt(int numSamples, const TMATH x[], const TMATH y[], const int order, TMATH coeffs[]) {
    
    int N = numSamples;
    int n = order;
    int np1 = n + 1;
    int np2 = n + 2;
    int tnp1 = 2 * n + 1;
    TMATH tmp;
    
    // X = vector that stores values of sigma(xi^2n)
    TMATH* X = new TMATH[tnp1] ();
    for (int i = 0; i < tnp1; ++i) {
      X[i] = 0;
      for (int j = 0; j < N; ++j) {
        X[i] += (TMATH)pow(x[j], i);
      }
    }

    // a = vector to store final coefficients.
    TMATH* a = new TMATH[np1] ();
    
    // B = normal augmented matrix that stores the equations.
    // std::vector<std::vector<TYPE> > B(np1, std::vector<TYPE> (np2, 0));
    TMATH** B = new TMATH*[np1] ();
    for(int i = 0; i < np1; ++i) { B[i] = new TMATH[np2] (); }

    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        B[i][j] = X[i + j];
      }
    }
    
    // Y = vector to store values of sigma(xi^n * yi)
    TMATH* Y = new TMATH[np1] ();
    for (int i = 0; i < np1; ++i) {
      Y[i] = (TMATH)0;
      for (int j = 0; j < N; ++j) {
        Y[i] += (TMATH)pow(x[j], i)*y[j];
      }
    }

    // Load values of Y as last column of B
    for (int i = 0; i <= n; ++i) {
      B[i][np1] = Y[i];
    }

    n += 1;
    int nm1 = n-1;

    // Pivotisation of the B matrix.
    for (int i = 0; i < n; ++i) {
      for (int k = i+1; k < n; ++k) {
        if (B[i][i] < B[k][i]) {
          for (int j = 0; j <= n; ++j) {
            tmp = B[i][j];
            B[i][j] = B[k][j];
            B[k][j] = tmp;
          }
        }
      }
    }

    // Performs the Gaussian elimination.
    // (1) Make all elements below the pivot equals to zero
    //     or eliminate the variable.
    for (int i=0; i<nm1; ++i) {
      for (int k =i+1; k<n; ++k) {
        TMATH t = B[k][i] / B[i][i];
        for (int j=0; j<=n; ++j) {
          B[k][j] -= t*B[i][j];         // (1)
        }
      }
    }

    // Back substitution.
    // (1) Set the variable as the rhs of last equation
    // (2) Subtract all lhs values except the target coefficient.
    // (3) Divide rhs by coefficient of variable being calculated.
    for (int i=nm1; i >= 0; --i) {
      a[i] = B[i][n];                   // (1)
      for (int j = 0; j<n; ++j) {
        if (j != i) {
          a[i] -= B[i][j] * a[j];       // (2)
        }
      }
      a[i] /= B[i][i];                  // (3)
    }

    for (int i = 0; i < np1; ++i) {
      coeffs[i] = a[i];
    }


    delete[] X;
    delete[] a;
    delete[] Y;
    for(int i = 0; i < np1; ++i) {
      delete[] (B[i]);
    }
    delete[] B;
  }
};

#endif
