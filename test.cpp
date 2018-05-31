/*
	Copyright (c) 2017 Sebastian Garth

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
#include "null"
#include <iostream>
#include <string>
using namespace
	std;
void
	verify_(string const& expression, bool condition)
{
	cout << "(" << expression << ") : ";
	if(condition)
		cout << "PASS";
	else
		cout << "FAIL";
	cout << endl;
}
#define verify(expression) verify_(#expression, expression)
int const&
	get_reference(bool good = true)
{
	static int const
		value = int();
	return good ? value : null;
}
int const&
	pass_reference(int const& value)
{
	return value;
}
int 
	main()
{
	int const
		data = get_reference(),
		& data_reference = data, 
		& null_reference = null, 
		* data_pointer = &data_reference, 
		* null_pointer = &null_reference;
	verify(data_reference != null);
	verify(null != data_reference);
	verify(null_reference == null);
	verify(null == null_reference);	
	verify(data_pointer != null);
	verify(null != data_pointer);
	verify(null_pointer == null);
	verify(null == null_pointer);	
	verify(get_reference(true) != null);
	verify(get_reference(false) == null);
	verify(pass_reference(data) != null);
	verify(pass_reference(data_reference) != null);	
	verify(pass_reference(null_reference) == null);	
	verify(pass_reference(null) == null);	
	verify(null == null);
	verify(null == null_t());
	verify(null_t() == null);
}
