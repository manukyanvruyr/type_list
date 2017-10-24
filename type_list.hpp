#pragma once

namespace TL
{

struct nulltype {};

template <typename H, typename ... Args>
struct type_list
{
    using head = H;
    using tail = type_list<Args...>;
};

template <typename H, typename ... Args>
struct type_list<H, type_list<Args...>>
{
	using head = H;
	using tail = type_list<Args...>;
};

template <typename H>
struct type_list<H>
{
    using head = H;
    using tail = nulltype;
};

/// to provia backward compatibality
template <typename H>
struct type_list<H, nulltype>
{
    using head = H;
    using tail = nulltype;
};

}
