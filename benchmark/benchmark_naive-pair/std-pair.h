
#pragma once
//#ifndef RC_INVOKED
#include <xstddef>
#include <iosfwd>
#include <type_traits>

//#pragma pack(push,_CRT_PACKING)
//#pragma warning(push,_STL_WARNING_LEVEL)
//#pragma warning(disable: _STL_DISABLED_WARNINGS)
//_STL_DISABLE_CLANG_WARNINGS
 //#pragma push_macro("new")
 //#undef new

using namespace std;

//_STD_BEGIN
namespace MSVC_STD {

template<class _Ty1, class _Ty2>
struct pair
{	// store a pair of values
	using first_type = _Ty1;
	using second_type = _Ty2;

	template<class _Uty1 = _Ty1,
		class _Uty2 = _Ty2,
		enable_if_t<conjunction_v<
			is_default_constructible<_Uty1>,
			is_default_constructible<_Uty2>,
			_Is_implicitly_default_constructible<_Uty1>,
			_Is_implicitly_default_constructible<_Uty2>
		>, int> = 0>
		constexpr pair()
			_NOEXCEPT_COND(is_nothrow_default_constructible_v<_Uty1>
				&& is_nothrow_default_constructible_v<_Uty2>)	// strengthened
		: first(), second()
		{
		}

	template<class _Uty1 = _Ty1,
		class _Uty2 = _Ty2,
		enable_if_t<conjunction_v<
			is_default_constructible<_Uty1>,
			is_default_constructible<_Uty2>,
			negation<conjunction<
				_Is_implicitly_default_constructible<_Uty1>,
				_Is_implicitly_default_constructible<_Uty2>>>
		>, int> = 0>
		constexpr explicit pair()
			_NOEXCEPT_COND(is_nothrow_default_constructible_v<_Uty1>
				&& is_nothrow_default_constructible_v<_Uty2>)	// strengthened
		: first(), second()
		{
		}

	template<class _Uty1 = _Ty1,
		class _Uty2 = _Ty2,
		enable_if_t<conjunction_v<
			is_copy_constructible<_Uty1>,
			is_copy_constructible<_Uty2>,
			is_convertible<const _Uty1&, _Uty1>,
			is_convertible<const _Uty2&, _Uty2>
		>, int> = 0>
		constexpr pair(const _Ty1& _Val1, const _Ty2& _Val2)
			_NOEXCEPT_COND(is_nothrow_copy_constructible_v<_Uty1>
				&& is_nothrow_copy_constructible_v<_Uty2>)	// strengthened
		: first(_Val1), second(_Val2)
		{
		}

	template<class _Uty1 = _Ty1,
		class _Uty2 = _Ty2,
		enable_if_t<conjunction_v<
			is_copy_constructible<_Uty1>,
			is_copy_constructible<_Uty2>,
			negation<conjunction<
				is_convertible<const _Uty1&, _Uty1>,
				is_convertible<const _Uty2&, _Uty2>>>
		>, int> = 0>
		constexpr explicit pair(const _Ty1& _Val1, const _Ty2& _Val2)
			_NOEXCEPT_COND(is_nothrow_copy_constructible_v<_Uty1>
				&& is_nothrow_copy_constructible_v<_Uty2>)	// strengthened
		: first(_Val1), second(_Val2)
		{
		}

	template<class _Other1,
		class _Other2,
		enable_if_t<conjunction_v<
			is_constructible<_Ty1, _Other1>,
			is_constructible<_Ty2, _Other2>,
			is_convertible<_Other1, _Ty1>,
			is_convertible<_Other2, _Ty2>
		>, int> = 0>
		constexpr pair(_Other1&& _Val1, _Other2&& _Val2)
			_NOEXCEPT_COND(is_nothrow_constructible_v<_Ty1, _Other1>
				&& is_nothrow_constructible_v<_Ty2, _Other2>)	// strengthened
		: first(_STD forward<_Other1>(_Val1)),
				second(_STD forward<_Other2>(_Val2))
		{
		}

	template<class _Other1,
		class _Other2,
		enable_if_t<conjunction_v<
			is_constructible<_Ty1, _Other1>,
			is_constructible<_Ty2, _Other2>,
			negation<conjunction<
				is_convertible<_Other1, _Ty1>,
				is_convertible<_Other2, _Ty2>>>
		>, int> = 0>
		constexpr explicit pair(_Other1&& _Val1, _Other2&& _Val2)
			_NOEXCEPT_COND(is_nothrow_constructible_v<_Ty1, _Other1>
				&& is_nothrow_constructible_v<_Ty2, _Other2>)	// strengthened
		: first(_STD forward<_Other1>(_Val1)),
				second(_STD forward<_Other2>(_Val2))
		{
		}

	pair(const pair&) = default;
	pair(pair&&) = default;

	template<class _Other1,
		class _Other2,
		enable_if_t<conjunction_v<
			is_constructible<_Ty1, const _Other1&>,
			is_constructible<_Ty2, const _Other2&>,
			is_convertible<const _Other1&, _Ty1>,
			is_convertible<const _Other2&, _Ty2>
		>, int> = 0>
		constexpr pair(const pair<_Other1, _Other2>& _Right)
			_NOEXCEPT_COND(is_nothrow_constructible_v<_Ty1, const _Other1&>
				&& is_nothrow_constructible_v<_Ty2, const _Other2&>)	// strengthened
		: first(_Right.first), second(_Right.second)
		{
		}

	template<class _Other1,
		class _Other2,
		enable_if_t<conjunction_v<
			is_constructible<_Ty1, const _Other1&>,
			is_constructible<_Ty2, const _Other2&>,
			negation<conjunction<
				is_convertible<const _Other1&, _Ty1>,
				is_convertible<const _Other2&, _Ty2>>>
		>, int> = 0>
		constexpr explicit pair(const pair<_Other1, _Other2>& _Right)
			_NOEXCEPT_COND(is_nothrow_constructible_v<_Ty1, const _Other1&>
				&& is_nothrow_constructible_v<_Ty2, const _Other2&>)	// strengthened
		: first(_Right.first), second(_Right.second)
		{
		}

	template<class _Other1,
		class _Other2,
		enable_if_t<conjunction_v<
			is_constructible<_Ty1, _Other1>,
			is_constructible<_Ty2, _Other2>,
			is_convertible<_Other1, _Ty1>,
			is_convertible<_Other2, _Ty2>
		>, int> = 0>
		constexpr pair(pair<_Other1, _Other2>&& _Right)
			_NOEXCEPT_COND(is_nothrow_constructible_v<_Ty1, _Other1>
				&& is_nothrow_constructible_v<_Ty2, _Other2>)	// strengthened
		: first(_STD forward<_Other1>(_Right.first)),
			second(_STD forward<_Other2>(_Right.second))
		{
		}

	template<class _Other1,
		class _Other2,
		enable_if_t<conjunction_v<
			is_constructible<_Ty1, _Other1>,
			is_constructible<_Ty2, _Other2>,
			negation<conjunction<
				is_convertible<_Other1, _Ty1>,
				is_convertible<_Other2, _Ty2>>>
		>, int> = 0>
		constexpr explicit pair(pair<_Other1, _Other2>&& _Right)
			_NOEXCEPT_COND(is_nothrow_constructible_v<_Ty1, _Other1>
				&& is_nothrow_constructible_v<_Ty2, _Other2>)	// strengthened
		: first(_STD forward<_Other1>(_Right.first)),
			second(_STD forward<_Other2>(_Right.second))
		{
		}

    // \note why do we delete the volatile pair copy assignment constructor?
	pair& operator=(const volatile pair&) = delete;


	template<class _Other1 = _Ty1, class _Other2 = _Ty2,
		enable_if_t<conjunction_v<
			is_assignable<_Ty1&, const _Other1&>,
			is_assignable<_Ty2&, const _Other2&>
		>, int> = 0>
		pair& operator=(const pair<_Other1, _Other2>& _Right)
			_NOEXCEPT_COND(is_nothrow_assignable_v<_Ty1&, const _Other1&>
				&& is_nothrow_assignable_v<_Ty2&, const _Other2&>)	// strengthened
		{
		first = _Right.first;
		second = _Right.second;
		return (*this);
		}

	template<class _Other1 = _Ty1, class _Other2 = _Ty2,
		enable_if_t<conjunction_v<
			is_assignable<_Ty1&, _Other1>,
			is_assignable<_Ty2&, _Other2>
		>, int> = 0>
		pair& operator=(pair<_Other1, _Other2>&& _Right)
			_NOEXCEPT_COND(is_nothrow_assignable_v<_Ty1&, _Other1>
				&& is_nothrow_assignable_v<_Ty2&, _Other2>)	// strengthened
		{
		first = _STD forward<_Other1>(_Right.first);
		second = _STD forward<_Other2>(_Right.second);
		return (*this);
		}

#if 0
	void swap(pair& _Right)
		_NOEXCEPT_COND(_Is_nothrow_swappable<_Ty1>::value
			&& _Is_nothrow_swappable<_Ty2>::value)
		{
		if (this != _STD addressof(_Right))
			{	// different, worth swapping
			_Swap_adl(first, _Right.first);
			_Swap_adl(second, _Right.second);
			}
		}
#endif

	_Ty1 first;		// the first stored value
	_Ty2 second;	// the second stored value
	};
#if 0
template<class _Ty1, class _Ty2>
	pair(_Ty1, _Ty2) -> pair<_Ty1, _Ty2>;

template<class _Ty1,
	class _Ty2,
	class = enable_if_t<_Is_swappable<_Ty1>::value && _Is_swappable<_Ty2>::value>> inline
	void swap(pair<_Ty1, _Ty2>& _Left, pair<_Ty1, _Ty2>& _Right)
		_NOEXCEPT_COND(_NOEXCEPT_OPER(_Left.swap(_Right)))
	{	// swap _Left and _Right pairs
	_Left.swap(_Right);
	}

template<class _Ty1,
	class _Ty2>
	_NODISCARD constexpr bool operator==(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	// test for pair equality
	return (_Left.first == _Right.first && _Left.second == _Right.second);
	}

template<class _Ty1,
	class _Ty2>
	_NODISCARD constexpr bool operator!=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	// test for pair inequality
	return (!(_Left == _Right));
	}

template<class _Ty1,
	class _Ty2>
	_NODISCARD constexpr bool operator<(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	// test if _Left < _Right for pairs
	return (_Left.first < _Right.first ||
		(!(_Right.first < _Left.first) && _Left.second < _Right.second));
	}

template<class _Ty1,
	class _Ty2>
	_NODISCARD constexpr bool operator>(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	// test if _Left > _Right for pairs
	return (_Right < _Left);
	}

template<class _Ty1,
	class _Ty2>
	_NODISCARD constexpr bool operator<=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	// test if _Left <= _Right for pairs
	return (!(_Right < _Left));
	}

template<class _Ty1,
	class _Ty2>
	_NODISCARD constexpr bool operator>=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	// test if _Left >= _Right for pairs
	return (!(_Left < _Right));
	}
#endif
} // namespace

// #pragma pop_macro("new")
// _STL_RESTORE_CLANG_WARNINGS
// #pragma warning(pop)
// #pragma pack(pop)
//#endif /* RC_INVOKED */
