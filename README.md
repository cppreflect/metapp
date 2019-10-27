# Metapp

Metapp is a lightweight side compiler, a tool for static reflection 
and code generation. It is intended for C++ and is based on LLVM and 
Clangs libtooling.

It's inpired on regen, cxxctp and metareflect, out of which only cxxctp seems
in active development. It is intended to support the custom templating engine
of regen, the user pluggable features of cxxctp and combine them with the 
approach of metareflect and utilize the most of Clangs libtooling. 

It was forked from the great work of 
[Metareflect](https://github.com/leandros/metareflect), 
the project seems now inactive.

# Getting Started

## Annotating Your Classes

Every class which you want to be reflected needs to be annotated.

**point.hxx:**
    CLASS() Point
    {
    public:
        PROPERTY()
        int x;

        PROPERTY()
        int y;

        PROPERTY()
        int z;

        FUNCTION()
        size_t Hash() const
        {
            return x ^ y ^ z;
        }
    };

**point.cxx:**

    #include "point.hxx"
    #include "point.generated.hxx"

    /* rest of the code */


For a full example take a look at our [`/example`](/example).

# Contributing

Any contribution is welcome. Take a look at the [open tickets](https://github.com/cppreflect/metapp/issues) to get
started with the development of metapp.

## Requirements

- A clone of the LLVM source code, including clang and clang-extra-tools.
  See [LLVM_SETUP](/LLVM_SETUP.md) how to setup LLVM for development.
- A clone of the metapp repository
- A beefy computer, otherwise compiling LLVM will take some time

## Getting Started

Once you've cloned the LLVM repo (by following the guide at [LLVM_SETUP](/LLVM_SETUP.md)),
navigate to `path/to/llvm/tools/clang/tools/extra/metapp/metapp`.
The directory contains the source code for metapp and anything you need
to get started developing metapp.

The following resources give an insight into how to develop an libtooling application:

- [Clang Documentation on LibTooling](https://clang.llvm.org/docs/LibTooling.html)
- [Using ASTMatchers in LibTooling](https://clang.llvm.org/docs/LibASTMatchersTutorial.html)

To contribute your changes back, please open a pull request! We welcome any contribution.

# License

[MIT License](/LICENSE)
