#include "test.hpp"
#include "type_list.hpp"
#include "utility.hpp"

namespace
{

using T1 = TL::type_list<int, TL::nulltype>;
using T2 = TL::type_list<int>;
using T3 = TL::type_list<int, double>;
using T4 = TL::type_list<int, unsigned int, long int>;
using T5 = TL::type_list<int, TL::type_list<double, TL::type_list<char>>>;
using T6 = TL::type_list<int, abstract>;

void type_checker()
{
	static_assert(!std::is_same<T1, T2>::value, "type_list<int, TL::nulltype> != type_list<int>");
	static_assert(std::is_same<T1::head, int>::value, "T1 head");
	static_assert(std::is_same<T1::tail, TL::nulltype>::value, "T1 tail");

	static_assert(std::is_same<T2::head, int>::value, "T2 head");
	static_assert(std::is_same<T2::tail, TL::nulltype>::value, "T2 tail");

	static_assert(std::is_same<T3::head, int>::value, "T3 head");
	static_assert(std::is_same<T3::tail, TL::type_list<double>>::value, "T3 tail");

	static_assert(std::is_same<T4::head, int>::value, "T4 head");
	static_assert(std::is_same<T4::tail, TL::type_list<unsigned int, long int>>::value, "T4 tail");

	static_assert(std::is_same<T5::head, int>::value, "T5 head");
	static_assert(std::is_same<T5::tail, TL::type_list<double, TL::type_list<char>>>::value, "T5 tail");
	static_assert(std::is_same<T5::tail::head, double>::value, "T5 tail::head");
	static_assert(std::is_same<T5::tail::tail, TL::type_list<char>>::value, "T5 tail::tail");

	static_assert(std::is_same<T6::tail, TL::type_list<abstract>>::value, "T6 tail");

	using T = TL::type_list<int, double, char>;
	static_assert(!std::is_same<T, T5>::value, "type_list<int, double, char> != type_list<int, TL::type_list<double, TL::type_list<char>>>");
}

void length_checker()
{
	static_assert(utility::length<T1>::value == 1, "T1 length");
	static_assert(utility::length<T2>::value == 1, "T2 length");
	static_assert(utility::length<T3>::value == 2, "T3 length");
	static_assert(utility::length<T4>::value == 3, "T4 length");
	static_assert(utility::length<T5>::value == 3, "T5 length");
	static_assert(utility::length<T6>::value == 2, "T6 length");
}

void type_index_checker()
{
	static_assert(std::is_same<typename utility::type_at<T1, 0>::value, int>::value, "type_at<T1, 0> test");
	static_assert(std::is_same<typename utility::type_at<T2, 0>::value, int>::value, "type_at<T2, 0> test");
	static_assert(std::is_same<typename utility::type_at<T3, 0>::value, int>::value, "type_at<T3, 0> test");
	static_assert(std::is_same<typename utility::type_at<T3, 1>::value, double>::value, "type_at<T3, 1> test");
	static_assert(std::is_same<typename utility::type_at<T4, 0>::value, int>::value, "type_at<T4, 0> test");
	static_assert(std::is_same<typename utility::type_at<T4, 1>::value, unsigned int>::value, "type_at<T4, 1> test");
	static_assert(std::is_same<typename utility::type_at<T4, 2>::value, long int>::value, "type_at<T4, 2> test");
	static_assert(std::is_same<typename utility::type_at<T5, 0>::value, int>::value, "type_at<T5, 0> test");
	static_assert(std::is_same<typename utility::type_at<T5, 1>::value, double>::value, "type_at<T5, 1> test");
	static_assert(std::is_same<typename utility::type_at<T5, 2>::value, char>::value, "type_at<T5, 2> test");
	static_assert(std::is_same<typename utility::type_at<T6, 0>::value, int>::value, "type_at<T6, 0> test");
	static_assert(std::is_same<typename utility::type_at<T6, 1>::value, abstract>::value, "type_at<T6, 1> test");
}

void search_type_checker()
{
	static_assert(utility::index_of<T1, int>::value == 0, "index_of<T1, int>");
	static_assert(utility::index_of<T1, double>::value == -1, "index_of<T1, double>");

	static_assert(utility::index_of<T2, int>::value == 0, "index_of<T2, int>");

	static_assert(utility::index_of<T3, double>::value == 1, "index_of<T3, double>");
	static_assert(utility::index_of<T3, char>::value == -1, "index_of<T3, char>");

	static_assert(utility::index_of<T4, long int>::value == 2, "index_of<T4, long int>");

	static_assert(utility::index_of<T5, double>::value == 1, "index_of<T5, double>");
	static_assert(utility::index_of<T5, char>::value == 2, "index_of<T5, char>");
	static_assert(utility::index_of<T5, int*>::value == -1, "index_of<T5, int*>");

	static_assert(utility::index_of<T6, abstract>::value == 1, "index_of<T6, abstract>");
}

} // namespace unnamed

namespace test
{

void print()
{
	utility::print<T1>();
	utility::print<T2>();
	utility::print<T3>();
	utility::print<T4>();
	utility::print<T5>();
	utility::print<T6>();
}

}
