#include <string> 

struct Foo;

int foo(); 

struct __attribute__((annotate("reflect-class"))) Foo {
  __attribute__((annotate("reflect-property")))
  int bar;
};
