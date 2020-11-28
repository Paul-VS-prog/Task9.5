#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;
double * gauss(double **a, double *y, int n) {
  double *x, max;
  int k, ind;
  const double eps = 0.00001;
  x = new double[n];
  k = 0;
  while (k < n) {
    max = abs(a[k][k]);
    ind = k;
    for (int i = k + 1; i < n; i++) {
      if (abs(a[i][k]) > max) {
        max = abs(a[i][k]);
        ind = i;
      }
    }
    for (int j = 0; j < n; j++)  {
      double t = a[k][j];
      a[k][j] = a[ind][j];
      a[ind][j] = t;
    }
    double t = y[k];
    y[k] = y[ind];
    y[ind] = t;
    for (int i = k; i < n; i++) {
      double t = a[i][k];
      if (abs(t) < eps) continue;
      for (int j = 0; j < n; j++) {
        a[i][j] = a[i][j] / t;
      }
      y[i] = y[i] / t;
      if (i == k)  continue;
      for (int j = 0; j < n; j++) {
        a[i][j] = a[i][j] - a[k][j];
      }
      y[i] = y[i] - y[k];
    }
    k++;
  }
  for (k = n - 1; k >= 0; k--) {
    x[k] = y[k];
    for (int i = 0; i < k; i++) {
      y[i] = y[i] - a[i][k] * x[k];
    }
  }
  return x;
}
int main() {
  setlocale(LC_ALL, "Russian");
  double **a, *y, *x;
  int n;
  cout << "Введите количество уравнений: ";
  cin >> n;
  a = new double*[n];
  y = new double[n];
  cout << "Введите коэф. при X, начиная с Х1, и чему равны уравнения: ";
  for (int i = 0; i < n; i++)
  {
    a[i] = new double[n];
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
    cin >> y[i];
  }
  x = gauss(a, y, n);
  for (int i = 0; i < n; i++)
    cout << "X" << i << " = " << x[i] << endl;
  return 0;
}
