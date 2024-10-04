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
    if (sz <= 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz >= MAX_VECTOR_SIZE)
        throw out_of_range("Vector size is too large");
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
      this->sz = v.sz;
      pMem = new T[sz];

      for (int i = 0; i < sz; ++i)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this->sz = v.sz;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      delete[] pMem;
      pMem = new T[v.sz];
      this->sz = v.sz;
      
      for (int i = 0; i < sz; ++i) {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (*this == v) return *this;
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this->sz = v.sz;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }
  T* data() const noexcept { return pMem; }

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
      if ((ind > 0) && (ind < sz))
          return pMem[ind];
      else
          throw "Incorrect index!";
  }
  const T& at(size_t ind) const
  {
      if ((ind > 0) && (ind < sz))
          return pMem[ind];
      else
          throw "Incorrect index!";
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return 0;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i]) return 0;
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return 1;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i]) return 1;
      return 0;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> vRes(*this);
      for (int i = 0; i < sz; ++i) vRes.pMem[i] = pMem[i] + val;
      return vRes;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector<T> vRes(*this);
      for (int i = 0; i < sz; ++i) vRes.pMem[i] = pMem[i] - val;
      return vRes;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector<T> vRes(*this);
      for (int i = 0; i < sz; ++i) vRes.pMem[i] = val * pMem[i];
      return vRes;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->size() != v.size()) throw "Not equal sizes";
      TDynamicVector<T> vRes(*this);
      for (int i = 0; i < vRes.sz; ++i) vRes.pMem[i] = pMem[i] + v.pMem[i];
      return vRes;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->size() != v.size()) throw "Not equal sizes";
      TDynamicVector<T> vRes(*this);
      for (int i = 0; i < vRes.sz; ++i) vRes.pMem[i] = pMem[i] - v.pMem[i];
      return vRes;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (this->size() != v.size()) throw "Not equal sizes";
      T Res = 0;
      for (int i = 0; i < v.sz; ++i) Res += pMem[i] * v.pMem[i];
      return Res;
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
    if (sz <= 0)
        throw out_of_range("Vector size should be greater than zero");
    if (sz >= MAX_MATRIX_SIZE)
        throw out_of_range("Vector size is too large");

    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::operator=;
  using TDynamicVector<TDynamicVector<T>>::operator*;
  using TDynamicVector<TDynamicVector<T>>::data;
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 0;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != m.pMem[i]) return 0;
      return 1;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 1;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != m.pMem[i]) return 1;
      return 0;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicVector<T> vRes(*this);
      for (int i = 0; i < sz; ++i) vRes.pMem[i] = val * pMem[i];
      return vRes;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->size() != v.size()) throw "Not equal sizes";
      TDynamicVector<T> vRes(this->size());
      for (int i = 0; i < this->size(); ++i) 
          vRes[i] = pMem[i] * v;
      return vRes;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (this->size() != m.size()) throw "Not equal sizes";
      TDynamicMatrix<T> mRes(*this);
      for (int i = 0; i < mRes.size(); ++i) mRes.pMem[i] = pMem[i] + m.pMem[i];
      return mRes;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (this->size() != m.size()) throw "Not equal sizes";
      TDynamicMatrix<T> mRes(*this);
      for (int i = 0; i < mRes.size(); ++i) mRes.pMem[i] = pMem[i] - m.pMem[i];
      return mRes;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this->size() != m.size()) throw "Not equal sizes";
      TDynamicMatrix<T> mRes(this->size());
      T save = 0;
      for (int i=0;i<this->size(); i++)
          for (int j = 0; j < m[0].size(); j++) {
              for (int k = 0; k < this->size(); k++) {
                  save = (*this)[i][k]*m[k][j];
                  mRes[i][j] += save;
                  //std::cout << "\n " << save << std::endl;
              }
              save = 0;
              
          }
      return mRes;
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
          ostr << v.pMem[i] << '\n'; 
      return ostr;
  }
};

#endif
