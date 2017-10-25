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

/////////////// print ///////////////
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

/////////////// length ///////////////
template <typename H, typename ... Args>
struct length<TL::type_list<H, Args...>>
{
	static constexpr int value = 1 + length<typename TL::type_list<H, Args...>::tail>::value;
};

template <typename H>
struct length<TL::type_list<H>>
{
	static constexpr int value = 1;
};

template <>
struct length<TL::nulltype>
{
	static constexpr int value = 0;
};

/////////////// type_at ///////////////
template <typename H, typename ... Args>
struct type_at<TL::type_list<H, Args...>, 0>
{
	using value = H;
};

template <unsigned int i>
struct type_at<TL::nulltype, i>
{
	static_assert(sizeof(i) < 0, "out of range");
	using value = TL::nulltype;
};

template <typename H, typename ... Args, unsigned int i>
struct type_at<TL::type_list<H, Args...>, i>
{
	using value = typename type_at<typename TL::type_list<H, Args...>::tail, i - 1>::value;
};

/////////////// index_of ///////////////
template <typename H, typename ... Args>
struct index_of<TL::type_list<H, Args...>, H>
{
	static constexpr int value = 0;
};

template <typename H>
struct index_of<TL::nulltype, H>
{
	static constexpr int value = -1;
};

template <typename H, typename ... Args, typename T>
struct index_of<TL::type_list<H, Args...>, T>
{
private:
	static constexpr int tmp_value = index_of<typename TL::type_list<H, Args...>::tail, T>::value;

public:
	static constexpr int value = (tmp_value == -1) ? -1 : 1 + tmp_value;
};

/////////////// append ///////////////
// e.g., append<type_list1, type_list2>
template <typename H, typename ... Tail>
struct append<TL::type_list<H, TL::nulltype>, TL::type_list<Tail...>>
{
	using value = TL::type_list<H, TL::type_list<Tail...>>;
};

template <typename H, typename ... Tail>
struct append<TL::type_list<H>, TL::type_list<Tail...>>
{
	using value = TL::type_list<H, TL::type_list<Tail...>>;
};

template <typename H, typename ... Args, typename ... Tail>
struct append<TL::type_list<H, Args...>, TL::type_list<Tail...>>
{
	using value = TL::type_list<H, typename append<typename TL::type_list<H, Args...>::tail, TL::type_list<Tail...>>::value>;
};

// e.g., append<type_list, int, double, ... >
template <typename H, typename ... Tail>
struct append<TL::type_list<H, TL::nulltype>, Tail...>
{
	using value = TL::type_list<H, TL::type_list<Tail...>>;
};

template <typename H, typename ... Tail>
struct append<TL::type_list<H>, Tail...>
{
	using value = TL::type_list<H, TL::type_list<Tail...>>;
};

template <typename H, typename ... Args>
struct append<TL::type_list<H, Args...>, TL::nulltype>
{
	using value = TL::type_list<H, Args...>;
};

template <typename H, typename ... Args, typename ... Tail>
struct append<TL::type_list<H, Args...>, Tail...>
{
	using value = TL::type_list<H, typename append<typename TL::type_list<H, Args...>::tail, Tail...>::value>;
};

/////////////// erase ///////////////
template <typename T>
struct erase<TL::nulltype, T>
{
	using value = TL::nulltype;
};

template <typename H, typename ... Args>
struct erase<TL::type_list<H, Args...>, H>
{
	using value = typename TL::type_list<H, Args...>::tail;
};

template <typename H, typename ... Args, typename T>
struct erase<TL::type_list<H, Args...>, T>
{
	using value = TL::type_list<H, typename erase<typename TL::type_list<H, Args...>::tail, T>::value>;
};

} // namespace utility
