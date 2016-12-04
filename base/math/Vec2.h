#pragma once
#ifndef SLOTH_MATH_VEC2_H_
#define SLOTH_MATH_VEC2_H_

namespace sloth {

	template <typename T>
	class Vec2 {
	public:
		union
		{
			class { T x, y; };
			class { T r, g; };
			class { T s, t; };
		};

		// -- Component accesses --
		typedef int length_type;
		constexpr length_type length() const;
		T& operator[](length_type i);
		const T & operator[](length_type i) const;

		// -- Implicit basic constructors --
		constexpr Vec2() = default;
		constexpr Vec2(const Vec2<T>& v) = default;

		// -- Explicit basic constructors --
		constexpr explicit Vec2(T scalar);
		constexpr Vec2(T s1, T s2);

		// -- Unary arithmetic operators --
		Vec2<T>& operator=(const Vec2<T> &v) = default;

		template <typename U>
		Vec2<T>& operator=(const Vec2<U> &v);
		template <typename U>
		Vec2<T>& operator+=(U scalar);
		template <typename U>
		Vec2<T>& operator+=(const Vec2<U> &v);
		template <typename U>
		Vec2<T>& operator-=(U scalar);
		template <typename U>
		Vec2<T>& operator-=(const Vec2<U> &v);
		template <typename U>
		Vec2<T>& operator*=(U scalar);
		template <typename U>
		Vec2<T>& operator*=(const Vec2<U> &v);
		template <typename U>
		Vec2<T>& operator/=(U scalar);
		template <typename U>
		Vec2<T>& operator/=(const Vec2<U> &v);

	};

	// -- Unary arithmetic operators --
	template <typename T>
	Vec2<T> operator+(const Vec2<T> &v);
	template <typename T>
	Vec2<T> operator-(const Vec2<T> &v);

	// -- Boolean operators --
	template <typename T>
	bool operator==(const Vec2<T> & v1, const Vec2<T> & v2);
	template <typename T>
	bool operator!=(const Vec2<T> & v1, const Vec2<T> & v2);
}


#endif // !SLOTH_MATH_VEC2_H_
