// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        if (this != &v) {
            if (sz != v.sz) {
                sz = v.sz;
                delite[] pMem;
                pMem = new T[sz];
            }
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
        return *this;
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        swap(*this, v);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if ((ind >= 0) && (ind < sz)) {
            return pMem[ind];
        }
    }
    const T& at(size_t ind) const
    {
        if ((ind >= 0) && (ind < sz)) {
            return pMem[ind];
        }
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        int k = 1;
            if (sz != v.sz)
                return false;
            for (int i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) {
                    k = 0;
                    break;
                }
            }
        if (k == 1)
            return true;
        else
            return false;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return true;
        int k = 1;
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                k = 0;
                break;
            }
        }
        if (k == 0)
            return true;
        else
            return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector vec(sz);
        for (int i = 0; i < sz; i++) {
            vec.pMem[i] = pMem[i] + val;
        }
        return vec;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector vec(sz);
        for (int i = 0; i < sz; i++) {
            vec.pMem[i] = pMem[i] - val;
        }
        return vec;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector vec(sz);
        for (int i = 0; i < sz; i++) {
            vec.pMem[i] = pMem[i] * val;
        }
        return vec;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz == v.sz) {
            TDynamicVector vec(sz);
            for (int i = 0; i < sz; i++) {
                vec.pMem[i] = pMem[i] + v.pMem[i];
            }
            return vec;
        }
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz == v.sz) {
            TDynamicVector vec(sz);
            for (int i = 0; i < sz; i++) {
                vec.pMem[i] = pMem[i] - v.pMem[i];
            }
            return vec;
        }
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz == v.sz) {
            T res = 0;
            for (int i = 0; i < sz; i++) {
                res = res + pMem[i] * v.pMem[i];
            }
            return res;
        }
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator ==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = (*this)[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz = v.sz) {
            TDynamicVector res(sz);
            for (int i = 0; i < sz; i++) {
                res[i] = (*this)[i] * v;
            }
            return res;
        }
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz = m.sz) {
            TDynamicMatrix res(sz);
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    res[i][j] = (*this)[i][j] + m[i][j];
                }
            }
            return res;
        }
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz = v.sz) {
            TDynamicMatrix res(sz);
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    res[i][j] = (*this)[i][j] + m[i][j];
                }
            }
            return res;
        }
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz = v.sz) {
            TDynamicMatrix res(sz);
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    for (int k = 0; k < sz; k++) {
                        res.pMem[i][j] = res.pMem[i][j] + pMem[i][k] * m.pMem[k][j]
                    }
                }
            }
            return res;
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; 
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << "\n";
        return ostr;
    } 
};

#endif
