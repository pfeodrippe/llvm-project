// RUN: cat %s | clang-repl | FileCheck %s

extern "C" int printf(const char*, ...);

struct Foo { static int const bar { 5 }; };

// Taking the address of a static const member with in-class initializer
// should materialize the symbol and allow dereferencing
int const * p = &Foo::bar;
printf("Address test: %d\n", *p);
// CHECK: Address test: 5

%quit
