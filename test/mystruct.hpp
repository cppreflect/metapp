#include <string> 

struct Foo;

int foo(); 

struct Bar { 
  struct __attribute__((annotate("reflect-class"))) Foo {
    __attribute__((annotate("reflect-property")))
    int bar;
    __attribute__((annotate("reflect-property")))
    int foo;
    __attribute__((annotate("reflect-property")))
    std::string mail;
  };
};
