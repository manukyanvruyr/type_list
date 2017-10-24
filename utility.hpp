#pragma once

#include <iostream>
#include "type_list.hpp"

/// for testing
class abstract
{
public:
	virtual void f() = 0;
	abstract() = delete;
};

namespace utility
{

/// this implementation of print_base class will work with c++17
/*
template <typename T>
class print_base
{
protected:
	static void print_type()
	{
		if constexpr (std::is_same<T, int>::value) {
			std::cout << "int ";
		} else if constexpr (std::is_same<T, unsigned int>::value) {
			std::cout << "unsigned int ";
		} else if constexpr (std::is_same<T, long int>::value) {
			std::cout << "long int ";
		} else if constexpr (std::is_same<T, double>::value) {
			std::cout << "double ";
		} else if constexpr (std::is_same<T, long double>::value) {
			std::cout << "long double ";
		} else if constexpr (std::is_same<T, char>::value) {
			std::cout << "char ";
		} else if constexpr (std::is_same<T, char*>::value) {
			std::cout << "char* ";
		} else if constexpr (std::is_same<T, int*>::value) {
			std::cout << "int* ";
		} else if constexpr (std::is_same<T, double*>::value) {
			std::cout << "double* ";
		} else {
			static_assert(false, "there is no specialization for the given type");
		}
	}
};
*/

/////////////// Length ///////////////
class print_base
{
protected:
	template <typename T>
	static inline void print_type()
	{
		static_assert(sizeof(T) < 0, "there is no specialization for the given type");
	}
};

template <>
inline void print_base::print_type<int>()
{
	std::cout << "int ";
}

template <>
inline void print_base::print_type<unsigned int>()
{
	std::cout << "unsigned int ";
}

template <>
inline void print_base::print_type<long int>()
{
	std::cout << "long int ";
}

template <>
inline void print_base::print_type<double>()
{
	std::cout << "double ";
}

template <>
inline void print_base::print_type<long double>()
{
	std::cout << "long double ";
}

template <>
inline void print_base::print_type<char>()
{
	std::cout << "char ";
}

template <>
inline void print_base::print_type<char*>()
{
	std::cout << "char* ";
}

template <>
inline void print_base::print_type<int*>()
{
	std::cout << "int* ";
}

template <>
inline void print_base::print_type<double*>()
{
	std::cout << "double* ";
}

template <>
inline void print_base::print_type<abstract>()
{
	std::cout << "abstract ";
}

template <typename H>
class print_helper;

template <typename H>
class print_helper<TL::type_list<H>> : public print_base
{
public:
    void operator()()
    {
		print_type<H>();
		std::cout << std::endl;
    }
};

template <typename H>
class print_helper<TL::type_list<H, TL::nulltype>> : public print_base
{
public:
    void operator()()
    {
		print_type<H>();
		std::cout << std::endl;
    }
};

template <typename H, typename ... Args>
class print_helper<TL::type_list<H, Args...>> : public print_base
{
public:
    void operator()()
    {
		print_type<H>();
		print_helper<typename TL::type_list<H, Args...>::tail>{}();
    }
};

template <typename T>
void print()
{
	print_helper<T>{}();
}

/////////////// length ///////////////
template <typename T>
struct length;

template <typename H, typename ... Args>
struct length<TL::type_list<H, Args...>>
{
	enum { value = 1 + length<typename TL::type_list<H, Args...>::tail>::value };
};

template <typename H>
struct length<TL::type_list<H>>
{
	enum { value = 1 };
};

template <>
struct length<TL::nulltype>
{
	enum { value = 0 };
};

/////////////// type_at ///////////////
template <typename T, unsigned int i>
struct type_at;

template <typename H, typename ... Args>
struct type_at<TL::type_list<H, Args...>, 0>
{
	using type = H;
};

template <unsigned int i>
struct type_at<TL::nulltype, i>
{
	static_assert(sizeof(i) < 0, "out of range");
	using type = TL::nulltype;
};

template <typename H, typename ... Args, unsigned int i>
struct type_at<TL::type_list<H, Args...>, i>
{
	using type = typename type_at<typename TL::type_list<H, Args...>::tail, i - 1>::type;
};

} // namespace utility
