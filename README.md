[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/gardhr/null/master/LICENSE.MIT)
# null
A compact null-reference library for C++

- [Motivation](#motivation)
- [Portability](#portability)
- [Usage](#usage)
- [Examples](#examples)
  - [Defining a custom namespace for the library](#defining-a-custom-namespace-for-the-library)
  - [Interoperability with pointers](#interoperability-with-pointers)
  - [Simplifying code interfaces](#simplifying-code-interfaces)
- [Safety](#safety)
- [License](#license)
## Motivation
As C++ doesn't directly support any notion of null references, the `null` library provides a very simple interface to allow the use of just such an idiom safely. It can be used as a drop-in replacement wherever NULL is used in your programs too.
## Portability
The null-reference library works with any C++ compiler (even older ones). It has no dependancies, so it can also be used in stand-alone (eg: embedded) environments where no standard header files are available. The library itself is by default declared in an anonymous namespace, but if `null` and/or `null_t` are already defined in your project, a custom namespace can be specified with a simple #define directive, as described [here](#defining-a-custom-namespace-for-the-library).
## Usage
Simply include either the `null.hpp` or `null` header in your program and you're ready to go. Note that if you are wrapping the library in a custom namespace then `null.hpp` should be included, as it doesn't import the `null_t` class or global `null` object into the current namespace (whereas the `null` header does). 
## Examples
### Defining a custom namespace for the library
If existing identifiers have already been defined for either `null_t` or `null`, then simply place a #define before including the library (being sure to use `null.hpp` (as explained [above](#usage))):
```cpp
#define GARDHR_NULL_NAMESPACE foo
#include "null.hpp"
int& empty = foo::null;
/*...*/
```
### Interoperability with pointers
The `null` object works just as easily with ordinary pointers as it does with references:
```cpp
#include "null"
#include <cassert>

using namespace std;

int main()
{
    int i = 42;
    int* p = null;
    int& r = i;
    int& n = null;
    assert(p == null);
    assert(r != null);
    assert(n == null);
    p = &r;
    assert(p != null);
    p = &n;
    assert(p == null);
}
```
### Simplifying code interfaces
Iterating through a container of objects is a classic example of an instance where one often ends up re-writing boilerplate code, faced with the conundrum of whether to return a complex iterator, a pointer to the actual data, or perhaps a boolean value with the actual return result passed in to the function. Embracing the null-reference idiom, the tendency to simplify code interfaces becomes much more natural:
```cpp
/*
    Some code interface, simplified
*/

#include "null"
#include <algorithm>
#include <iterator>

template <typename Value, typename Container>
Value& find(Container& container, const Value& value)
{
    auto end = std::end(container);
    auto pos = std::find(std::begin(container), end, value);
    if(pos != end)
        return *pos;
    return null;
}

/*
    A program that utilizes the simplified code interface 
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename Type>
void print(const Type& value)
{
    if(value != null)
        cout << value;
    else
        cout << "((null))";
    cout << endl;
}

int main()
{
    int integers[] = { 561, 1105, 1729 };
    vector<string> strings(2, "qux");
    print(find(integers, 561));
    print(find(integers, 42));    // null
    print(find(integers, 1729));
    print(find<string>(strings, "foo"));    // null
    print(find<string>(strings, "qux"));
}
```
## Safety
Obviously, working with null references (or at least what effectively act as such) means that you MUST ALWAYS test any variable that might possibly be invalid before manipulating it. This is really no different from the caveats of using ordinary pointers, so it almost goes without saying...but there you have it.
## License
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

This library is released under the [MIT License](http://opensource.org/licenses/MIT)