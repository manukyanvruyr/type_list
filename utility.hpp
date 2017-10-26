#pragma once

namespace utility
{

template <typename H>
class print_helper
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H>
void print()
{
	print_helper<H>{}();
}

template <typename H>
struct length
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, unsigned int i>
struct type_at
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, typename T>
struct index_of
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, typename ... Tail>
struct append
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, typename T>
struct erase
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, typename T>
struct erase_all
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H>
struct remove_duplicates
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, typename T, typename U>
struct replace
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

template <typename H, typename T, typename U>
struct replace_all
{
	static_assert(sizeof(H) < 0, "there is no specialization for the given type");
};

} // namespace utility

#include "utility_impl.hpp"
