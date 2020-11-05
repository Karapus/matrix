#include <cassert>
#include <initializer_list>
template <typename T, std::size_t n>
class Vector {
	T data_[n];
	public:
	Vector() = default;
	Vector(std::initializer_list<T> list) {
		auto dit = data_;
		for (auto i : list)
			*dit++ = i;
	}
	Vector(const Vector &rhs) = default;
	Vector &operator = (const Vector &rhs) = default;
	Vector(Vector &&rhs) = default;
	Vector &operator = (Vector &&rhs) = default;
	~Vector() = default;

	T &operator [] (std::size_t i) {
		assert(i < n);
		return data_[i];
	}
};

template <typename T, std::size_t n_col, std::size_t n_row = n_col>
class Matrix {
	T *data_;
	using Row = Vector<T, n_col>;
	Row **rows_;
	public:
	Matrix() :
		data_(new T[sizeof(Row) * n_row]),
		rows_(new Row *[n_row])
	{
		for (auto it = rows_; it < rows_ + n_row; ++it)
			*it = new(data_ + (it - rows_) * sizeof(Row)) Row{};
	}
	Matrix(std::initializer_list<std::initializer_list<T>> list) :
		data_(new T[sizeof(Row) * n_row]),
		rows_(new Row *[n_row])
	{
		auto row = rows_;
		for (auto i : list) {
			*row = new(data_ + (row - rows_) * sizeof(Row)) Row{i};
			row++;
		}
	}
	~Matrix() {
		for (auto it = rows_; it < rows_ + n_row; ++it)
			(*it)->~Row();
		delete[] data_;
		delete[] rows_;
	}
	Matrix(const Matrix &rhs) : Matrix() {
		*this = rhs;
	}
	Matrix &operator = (const Matrix &rhs) {
		for (std::size_t i = 0; i < n_row; ++i)
			(*this)[i] = rhs[i];
		return *this;
	}
	Matrix(Matrix &&rhs);
	Matrix &operator = (Matrix &&rhs);
	Row &operator [] (std::size_t i) {
		assert(i < n_row);
		return *rows_[i];
	}
	const Row &operator [] (std::size_t i) const {
		return (*const_cast<Matrix *>(this))[i];
	}
#if 0
	operator -
	operator +=
	operator -=
	int det()
	Matrix<T, n_row, n_col> transpose() const {
		return (res = this)->transpose();
	}
#endif
};

#if 0
operator *
*
*
operator +
operator -
#endif
