# Tang
Tang is a new template language library written in C++ as part of a
[YouTube series](https://www.youtube.com/playlist?list=PLZqirAnnqaCZ8lT8w7p2PUB7tqrId7d89).

## Syntax
The Tang syntax is a mixture of C++, PHP, and Python, with an emphasis on
seamlessly supporting Unicode characters in Utf-8 encodings, as well as HTML
encoding and percent encodings where applicable.

## How to use Tang
Depending on your perspective, you are either wanting to know how to use Tang
as part of a C++ project, or you want to know how to use Tang as a template
code editor.

### Using Tang: As a C++ library
**Warning!! - The language example represents the aspiration of what Tang will
become.  It's not there yet, though!**

This project compiles Tang into a shared library (`libghoti.io-tang.so`) so that it can
be included into your project as a library.  The `tang.hpp` header will contain
all necessary class information.  The library must be compiled and installed (see below) before this example will work.

A simple use case might be (in a file named `example.cpp`):

```C++
#include <iostream>
#include <ghoti.io/tang.hpp>

int main() {
  auto program = Tang::TangBase::make_shared().compileScript(R"(
    // Compute the nth number of the fibonacci sequence, where 1 is the first
    // number.  Use a very inefficient recursive solution, just to prove that
    // it works.  Also, this is only meant to be called for positive numbers.
    // It's just an example, after all!
    function fib(n) {
      if (n < 2)
        return n;
      return fib(n - 2) + fib(n - 1);
    }
    print(fib(10));
  )");
  std::cout << program.execute().out << std::endl;
  return 0;
}
```

Compile command:
```
g++ example.cpp `pkg-config --libs --cflags ghoti.io-tang` -o example
```

The output of the above program should be:
```
55
```

For more sophisticated use cases, check the Documentation (when it's finished).

### Using Tang: As a template designer.
Tang templates allow you to intersperse code into your templates using code
tags `<%` and `%>`.  There is also a shorthand code `<%=` to print the value
supplied without explicitly calling a `print` function.

**Warning!! - The following examples are the intended ideal, and are not yet
implemented.**

#### Example 1
Suppose a variable named `user` exists, and it is a string containg "Alice".

If this is your template:
```
Welcome, <%= user %>!
```

Then this will be your output:
```
Welcome, Alice!
```

#### Example 2
Suppose a variable named `users` exists, and it is a list of names: "Alice",
"Bob", "Carol", and "Frank".

If this is your template:
```
<ul>
<%
for (name : names) {
  print!("  <li>");
  print(name);
  print!("</li>\n");
}
</ul>
```

Then this will be your output:
```
<ul>
  <li>Alice</li>
  <li>Bob</li>
  <li>Carol</li>
  <li>Frank</li>
</ul>
```

Alternatively, the following code could have been used as well, although it
will include a few additional line breaks:
```
<ul>
<% for (name : names) { %>
  <li><%= name %></li>
<% } %>
</ul>
```

## Compiling Tang from source

The following instructions were written for Ubuntu 22.04.  The overall steps are straightforward, though.

  1. Install necessary packages (see below).
  1. Clone the repo.
  1. Run `make`
  1. Run `sudo make install`

### Install packages
First, the necessary packages must be installed.
```
sudo apt install g++ make bison flex build-essential pkgconf libgtest-dev googletest
```

Additional packages must be installed in order to create documentation and
enhance the build experience.
```
sudo apt install doxygen graphviz texlive-latex-base texlive-latex-extra cloc inotify-tools valgrind gdb
```

If you're working in the WSL, you can install the `wslu` package, so that you can view files (such as the documentation) using a cli command.
```
sudo apt install wslu
```

Example use:
```
wslview ./docs/html/index.html
```

### Compile source code
```
make
sudo make install
```

For additional `make` commands/options, run:
```
make help
```

