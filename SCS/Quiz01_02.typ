#set page(header: [#h(1fr)BUPT SCS-SE C++ QUIZ#h(1fr)], footer: [#h(1fr)#context counter(page).display()#h(1fr)])

#set text(font: "LXGW WenKai")

#align(center, text(17pt)[*BUPT SCS-SE C++ Quiz -- Unit 01/02 Overview and Basics*])

+ C++ supports 4 programming paradigms:: #underline[    #strong[#emph[   SP]]   ], #underline[   #strong[#emph[OOP]]   ],#underline[   #strong[#emph[FP]]   ] and #underline[   #strong[#emph[GP]]   ].

#block[
#set enum(numbering: "1.", start: 2)
+ When we say "modern c++", we usually refer to (#strong[#emph[C]])
]

A. C++98 B. C++03 C. C++11 D. C++17 E. C++20

3.( F ) T/F: A C++ IDE usually does not include a compiler.

4.( T ) T/F: The extensions of C++ source files can be cpp or cxx.

5.( F ) T/F: Special characters like TAB and page break are recommended
in source files

#block[
#set enum(numbering: "1.", start: 6)
+ Please point out the irregularities and errors in the following code
]

```cpp
#include #strike["iostream.h"]                     -> use `<iostream>`instead
using namespace #strike[standard];                 -> use `std` instead of `standard`
#strike[void] main() {                             -> use `int` instead of `void`
 cout << "I am okay.#strike[\n]" << endl;          -> delete `'\n'`
}
```

#block[
#set enum(numbering: "1.", start: 7)
+ Please complete the following code
]

```cpp
#include <iostream>
namespace aloha { 
char* s = "Hello"; 
}

__int____ main() { 
// output the string in namespace aloha 
std::cout << aloha::s << std::endl;
return 0;
}
```

#block[
#set enum(numbering: "1.", start: 8)
+ Write a program. Ask the user to input a number and save the number in
  variable n.~
]

Print n lines of star “\*“. You decide the length of the line. You must
use C++

programming style.

```cpp
#include <bits/stdc++.h>

int main(){
    int num;
    std::cout << "plz input an integer" << std::endl;
    std::cin >> num;
    for (int i = 0; i < num; i ++){
        std::cout << "********" << std::endl;
    }
    return 0;
}
```

#block[
#set enum(numbering: "1.", start: 9)
+ Use your IDE to debug the program in quiz 8. Try "breakpoint", "step
  in", "step over", "watch" in debugging. Modify the value of variable "n" in "watch" window
and see what happens. Write down your own understandings of the above 4 debug
techniques.
]
- *breakpoint*: Set the breakpoint can break the program when it runs to the
breakpoint.

- *step in*: Execute the current line and the cursor would be passed to the
next one.

- *step over*: Alike `step in`, yet it would NOT pass the cursor to the
function cell it meets.

- *watch*: Values of arguments could be seen easily here. Easily to find out
if the value of an argument is right.

- *Other debug techniques you have tried*: Refer to LOGS; Step out;
