#pragma once

namespace utility
{

template <typename H>
class print_helper;

template <typename H>
void print()
{
	print_helper<H>{}();
}

template <typename H>
struct length;

template <typename H, unsigned int i>
struct type_at;

template <typename H, typename T>
struct index_of;

template <typename H, typename ... Tail>
struct append;

template <typename H, typename T>
struct erase;

template <typename H, typename T>
struct erase_all;

} // namespace utility

#include "utility_impl.hpp"
