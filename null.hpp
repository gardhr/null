/*
	Copyright (c) 2017, 2018 gardhr

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#ifndef GARDHR_NULL_INCLUDED
#define GARDHR_NULL_INCLUDED
#ifndef GARDHR_NULL_NAMESPACE
#define GARDHR_NULL_NAMESPACE
#endif
namespace GARDHR_NULL_NAMESPACE
{
/*
	Helper template to prevent multiple-translation-unit linker errors
*/
template <typename Null_t>
struct
	null_t_safe_static_null
{
	static Null_t const
		null;
};
template <typename Null_t>
Null_t const
	null_t_safe_static_null<Null_t>::null = Null_t();
struct
	null_t : null_t_safe_static_null<null_t>
{
	template <typename Type>
	inline operator Type&() const
	{
		return *((Type*)&null);
	}
	template <typename Type>
	inline operator Type*() const
	{
		return ((Type*)0);
	}
	inline static bool invalid(void const* address)
	{
		return address == ((void*)0) || address == &null;
	}
	template <typename Type>
	inline friend bool
		operator == (null_t const&, Type& reference)
	{
		return invalid(&reference);
	}
	template <typename Type>
	inline friend bool
		operator == (Type& reference, null_t const&)
	{
		return invalid(&reference);
	}
	template <typename Type>
	inline friend bool
		operator != (null_t const&, Type& reference)
	{
		return !invalid(&reference);
	}
	template <typename Type>
	inline friend bool
		operator != (Type& reference, null_t const&)
	{
		return !invalid(&reference);
	}
	template <typename Type>
	inline friend bool
		operator == (null_t const&, Type* address)
	{
		return invalid(address);
	}
	template <typename Type>
	inline friend bool
		operator == (Type* address, null_t const&)
	{
		return invalid(address);
	}
	template <typename Type>
	inline friend bool
		operator != (null_t const&, Type* address)
	{
		return !invalid(address);
	}
	template <typename Type>
	inline friend bool
		operator != (Type* address, null_t const&)
	{
		return !invalid(address);
	}
	inline friend bool
		operator == (null_t const&, null_t const&)
	{
		return true;
	}
	inline friend bool
		operator != (null_t const&, null_t const&)
	{
		return false;
	}
};
/*
	This is a static variable strictly in the sense that it only
	has internal linkage within any given translation unit.
*/
static null_t const&
	null = null_t::null;
}
#endif
