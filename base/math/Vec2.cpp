#include "Vec2.h"

#include <cassert>
namespace sloth{

	template<typename T>
	inline constexpr Vec2<T>::length_type Vec2<T>::length() const
	{
		return 2;
	}

	template<typename T>
	T & Vec2<T>::operator[](length_type i)
	{
		assert(i >= 0 && i < this->length());
		return (&x)[i];
	}

	template<typename T>
	const T & Vec2<T>::operator[](length_type i) const
	{
		assert(i >= 0 && i < this->length());
		return (&x)[i];
	}
	template<typename T>
	constexpr explicit Vec2<T>::Vec2(T scalar) :x(scalar), y(scalar) {}
	template<typename T>
	constexpr Vec2<T>::Vec2(T s1, T s2) : x(s1), y(s2) {}

	template <typename T>
	template <typename U>
	Vec2<T>& Vec2<T>::operator=(const Vec2<U>& v) {
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec2<T>& sloth::Vec2<T>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec2<T>& Vec2<T>::operator+=(const Vec2<U>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec2<T>& sloth::Vec2<T>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec2<T>& Vec2<T>::operator-=(const Vec2<U>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		return *this;
	}
	template<typename T>
	template<typename U>
	Vec2<T>& sloth::Vec2<T>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec2<T>& Vec2<T>::operator*=(const Vec2<U>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		return *this;
	}
	template<typename T>
	template<typename U>
	Vec2<T>& sloth::Vec2<T>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec2<T>& Vec2<T>::operator/=(const Vec2<U>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	Vec2<T> operator+(const Vec2<T>& v)
	{
		return v;
	}
	template<typename T>
	Vec2<T> operator-(const Vec2<T>& v)
	{
		return Vec2<T>(
			-v.x,
			-v.y
			);
	}
	template<typename T>
	bool operator==(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y);
	}
	template<typename T>
	bool operator!=(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y);
	}
}