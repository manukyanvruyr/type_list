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
	static_assert(std::is_same<typename utility::type_at<T1, 0>::type, int>::value, "type_at<T1, 0> test");
	static_assert(std::is_same<typename utility::type_at<T2, 0>::type, int>::value, "type_at<T2, 0> test");
	static_assert(std::is_same<typename utility::type_at<T3, 0>::type, int>::value, "type_at<T3, 0> test");
	static_assert(std::is_same<typename utility::type_at<T3, 1>::type, double>::value, "type_at<T3, 1> test");
	static_assert(std::is_same<typename utility::type_at<T4, 0>::type, int>::value, "type_at<T4, 0> test");
	static_assert(std::is_same<typename utility::type_at<T4, 1>::type, unsigned int>::value, "type_at<T4, 1> test");
	static_assert(std::is_same<typename utility::type_at<T4, 2>::type, long int>::value, "type_at<T4, 2> test");
	static_assert(std::is_same<typename utility::type_at<T5, 0>::type, int>::value, "type_at<T5, 0> test");
	static_assert(std::is_same<typename utility::type_at<T5, 1>::type, double>::value, "type_at<T5, 1> test");
	static_assert(std::is_same<typename utility::type_at<T5, 2>::type, char>::value, "type_at<T5, 2> test");
	static_assert(std::is_same<typename utility::type_at<T6, 0>::type, int>::value, "type_at<T6, 0> test");
	static_assert(std::is_same<typename utility::type_at<T6, 1>::type, abstract>::value, "type_at<T6, 1> test");
}

}

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
