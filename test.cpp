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

void append_checker()
{
	static_assert(std::is_same<T1, typename utility::append<T1, TL::nulltype>::value>::value, "T1 == append<T1, nulltype>");
	static_assert(std::is_same<T2, typename utility::append<T2, TL::nulltype>::value>::value, "T2 == append<T2, nulltype>");
	static_assert(std::is_same<T3, typename utility::append<T3, TL::nulltype>::value>::value, "T3 == append<T3, nulltype>");
	static_assert(std::is_same<T4, typename utility::append<T4, TL::nulltype>::value>::value, "T4 == append<T4, nulltype>");
	static_assert(std::is_same<T5, typename utility::append<T5, TL::nulltype>::value>::value, "T5 == append<T5, nulltype>");
	static_assert(std::is_same<T6, typename utility::append<T6, TL::nulltype>::value>::value, "T6 == append<T6, nulltype>");

	static_assert(std::is_same<TL::type_list<int, TL::type_list<int>>, typename utility::append<T1, int>::value>::value, "type_list<int, type_list<int>> == append<T1, int>");

	using t1 = typename utility::append<T3, double, int*, abstract>::value;
	static_assert(utility::length<t1>::value == 5, "length<t1>");
	static_assert(std::is_same<t1::tail::tail::tail::head, int*>::value, "t1::tail::tail::tail::head");
	static_assert(std::is_same<typename utility::type_at<t1, 4>::value, abstract>::value, "type_at<t1, 4>");
	static_assert(utility::index_of<t1, int*>::value == 3, "index_of<t1, int*>");

	using t2 = typename utility::append<T3, T4>::value;
	static_assert(utility::length<t2>::value == 5, "length<t2>");
	static_assert(std::is_same<t2::tail::tail::tail::head, unsigned int>::value, "t2::tail::tail::tail::head");
	static_assert(std::is_same<typename utility::type_at<t2, 4>::value, long int>::value, "type_at<t2, 4>");
	static_assert(utility::index_of<t2, double>::value == 1, "index_of<t2, double>");

	using t3 = typename utility::append<T1, T5>::value;
	static_assert(utility::length<t3>::value == 4, "length<t3>");
	static_assert(std::is_same<t3::tail::tail::tail::head, char>::value, "t3::tail::tail::tail::head");
	static_assert(std::is_same<typename utility::type_at<t3, 2>::value, double>::value, "type_at<t3, 2>");
	static_assert(utility::index_of<t3, double>::value == 2, "index_of<t3, double>");
}

void erase_checker()
{
	static_assert(std::is_same<typename utility::erase<T1, int>::value, TL::nulltype>::value, "erase<T1, int> == nulltype");
	static_assert(std::is_same<typename utility::erase<T1, int*>::value, T1>::value, "erase<T1, int*> == T1");
	static_assert(std::is_same<typename utility::erase<T5, double>::value, TL::type_list<int, TL::type_list<char>>>::value, "erase<T5, double> == type_list<int, type_list<char>>");

	using t1 = typename utility::erase<T3, double>::value;
	static_assert(utility::length<t1>::value == 1, "length<t1>");
	static_assert(std::is_same<t1::tail, TL::nulltype>::value, "t1::tail");

	using t2 = typename utility::erase<T5, char>::value;
	static_assert(utility::length<t2>::value == 2, "length<t2>");
	static_assert(std::is_same<t2::tail::head, double>::value, "t2::tail::head");
	static_assert(std::is_same<typename utility::type_at<t2, 1>::value, double>::value, "type_at<t2, 1>");
	static_assert(utility::index_of<t2, char>::value == -1, "index_of<t2, char>");

	using t3 = typename utility::erase<T5, char*>::value;
	static_assert(utility::length<t3>::value == 3, "length<t3>");
	static_assert(std::is_same<t3::tail::tail::head, char>::value, "t3::tail::tail::head");
	static_assert(std::is_same<typename utility::type_at<t3, 1>::value, double>::value, "type_at<t3, 1>");
	static_assert(utility::index_of<t3, char>::value == 2, "index_of<t3, char>");

	using t4 = typename utility::erase<T5, char*>::value;
	using t41 = TL::type_list<int, TL::type_list<double, TL::type_list<char, TL::nulltype>>>;
	static_assert(std::is_same<t4, T5>::value, "t4 == T5");
	static_assert(!std::is_same<t4, t41>::value, "t4 != t41");
}

void erase_all_checker()
{
	static_assert(std::is_same<typename utility::erase_all<T1, int>::value, TL::nulltype>::value, "erase_all<T1, int> == nulltype");
	static_assert(std::is_same<typename utility::erase_all<T1, int*>::value, T1>::value, "erase_all<T1, int*> == T1");
	static_assert(std::is_same<typename utility::erase_all<T5, double>::value, TL::type_list<int, TL::type_list<char>>>::value,
		"erase_all<T5, double> == type_list<int, type_list<char>>");

	using t1 = typename utility::erase_all<T3, double>::value;
	static_assert(utility::length<t1>::value == 1, "length<t1>");
	static_assert(std::is_same<t1::tail, TL::nulltype>::value, "t1::tail");

	using t2 = typename utility::erase_all<T5, char>::value;
	static_assert(utility::length<t2>::value == 2, "length<t2>");
	static_assert(std::is_same<t2::tail::head, double>::value, "t2::tail::head");
	static_assert(std::is_same<typename utility::type_at<t2, 1>::value, double>::value, "type_at<t2, 1>");
	static_assert(utility::index_of<t2, char>::value == -1, "index_of<t2, char>");

	using t3 = typename utility::erase_all<T5, char*>::value;
	static_assert(utility::length<t3>::value == 3, "length<t3>");
	static_assert(std::is_same<t3::tail::tail::head, char>::value, "t3::tail::tail::head");
	static_assert(std::is_same<typename utility::type_at<t3, 1>::value, double>::value, "type_at<t3, 1>");
	static_assert(utility::index_of<t3, char>::value == 2, "index_of<t3, char>");

	using t4 = typename utility::erase_all<T5, char*>::value;
	using t41 = TL::type_list<int, TL::type_list<double, TL::type_list<char, TL::nulltype>>>;
	static_assert(std::is_same<t4, T5>::value, "t4 == T5");
	static_assert(!std::is_same<t4, t41>::value, "t4 != t41");

	using t5 = typename utility::append<T5, int, double, int, char>::value;
	using t51 = typename utility::erase_all<t5, int>::value;
	static_assert(utility::length<t51>::value == 4, "t51 length");
	static_assert(std::is_same<t51, TL::type_list<double, TL::type_list<char, TL::type_list<double, TL::type_list<char>>>>>::value,
		"t51 == type_list<double, type_list<char, type_list<double, type_list<char>>>>");
	static_assert(std::is_same<t51::tail::head, char>::value, "t51::tail::head");
	static_assert(std::is_same<typename utility::type_at<t51, 1>::value, char>::value, "type_at<t51, 1>");
	static_assert(utility::index_of<t51, double>::value == 0, "index_of<t51, double>");

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
