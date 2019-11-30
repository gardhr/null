[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/gardhr/null/master/LICENSE.MIT)
# null
Discover the power of ''null'' with this compact little C++ library!

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
All modern programming languages support some notion of "nullness". In C++ however that designation really only seems to apply to pointers. Or does it? Well just a bit of operater overloading and we can extend the concept to references! The result speaks for itself: Code interfaces drastically simplified. Best of all it can be used as a drop-in replacement wherever NULL is used in your programs too.

## Portability
Compiles with pretty much any C++ compiler (even the older ones) and no dependancies whatsoever. The library itself is declared by default in an anonymous namespace but if `null` and/or `null_t` are already defined in your project a custom namespace can be specified with a simple #define directive, as described [here](#defining-a-custom-namespace-for-the-library).
## Usage
Simply include either the `null.hpp` or `null` header in your program and you're good to go. Note that if you are wrapping the library in a custom namespace then `null.hpp` should be included as it doesn't import the `null_t` class or global `null` object into the current namespace (whereas the `null` header does). 
## Examples
### Defining a custom namespace for the library
If existing identifiers have already been defined for either `null_t` or `null` then simply place a #define before including the library (being sure to use `null.hpp` (as explained [above](#usage))):
```cpp
#define GARDHR_NULL_NAMESPACE foo
#include "null.hpp"
int& empty = foo::null;
/*...*/
```
### Interoperability with pointers
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
Iterating through a container of objects is a classic example of an instance where one often ends up re-writing boilerplate code, faced with the conundrum of whether to return a complex iterator, a pointer to the actual data, etc. By embracing the null-reference idiom the tendency to simplify code interfaces becomes much more natural:
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
    int first = 561, second = 1105, third = 1729, nope = 42;
    int integers[] = { first, second, third };
    print(find(integers, first));  // 561
    print(find(integers, second)); // 1105
    print(find(integers, nope));   // ((null))
    print(find(integers, third));  // 1729
}
```
## Safety
The consequence of accessing a null reference is essentially the same as when dereferencing a NULL pointer: sudden and instant program termination! And so of course you should ALWAYS test any variable that might possibly be invalid (ie: null) before manipulating it. ;)
## License
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

This library is released under the [MIT License](http://opensource.org/licenses/MIT).
