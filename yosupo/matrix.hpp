#pragma once

namespace yosupo {

template <class T> struct Matrix {
    int h, w;
    std::vector<T> d;

    Matrix() : h(0), w(0), d() {}
    Matrix(int _h, int _w) : h(_h), w(_w), d(h * w) {}

    T& operator[](std::pair<int, int> idx) {
        return d[idx.first * w + idx.second];
    }
    const T& operator[](std::pair<int, int> idx) const {
        return d[idx.first * w + idx.second];
    }

    static Matrix e(int n) {
        Matrix mat(n, n);
        for (int i = 0; i < n; i++) {
            mat[{i, i}] = T(1);
        }
        return mat;
    }

    Matrix& operator+=(const Matrix& rhs) {
        assert(h == rhs.h);
        assert(w == rhs.w);
        for (int i = 0; i < h * w; i++) {
            d[i] += rhs.d[i];
        }
        return *this;
    }
    Matrix& operator-=(const Matrix& rhs) {
        assert(h == rhs.h);
        assert(w == rhs.w);
        for (int i = 0; i < h * w; i++) {
            d[i] -= rhs.d[i];
        }
        return *this;
    }
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
        return Matrix(lhs) += rhs;
    }
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
        return Matrix(lhs) -= rhs;
    }

    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        assert(lhs.w == rhs.h);
        Matrix res(lhs.h, rhs.w);
        for (int i = 0; i < lhs.h; i++) {
            for (int j = 0; j < rhs.w; j++) {
                for (int k = 0; k < lhs.w; k++) {
                    res[{i, j}] += lhs[{i, k}] * rhs[{k, j}];
                }
            }
        }
        return res;
    }
    Matrix& operator*=(const Matrix& r) { return *this = *this * r; }

    Matrix pow(long long n) const {
        assert(h == w);
        Matrix x = *this, r = e(h);
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};

}  // namespace yosupo
