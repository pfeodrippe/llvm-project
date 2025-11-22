// Test for static const member address issue
// see https://github.com/llvm/llvm-project/issues/146956

// RUN: cat %s | clang-repl | FileCheck %s

extern "C" int printf(const char*, ...);

// Test 1: Static const member with in-class initializer
struct Foo {
  static int const bar { 5 };
};

// Taking the address should work
int const * p = &Foo::bar;
printf("Address test: %d\n", *p);
// CHECK: Address test: 5

// Test 2: Direct value access (this should already work)
int const i = Foo::bar;
printf("Value test: %d\n", i);
// CHECK-NEXT: Value test: 5

// Test 3: Multiple accesses to the same static member
int const * p2 = &Foo::bar;
printf("Second address test: %d\n", *p2);
// CHECK-NEXT: Second address test: 5

// Test 4: Different types
struct Bar {
  static double const pi { 3.14159 };
};

double const * pi_ptr = &Bar::pi;
printf("Pi test: %.2f\n", *pi_ptr);
// CHECK-NEXT: Pi test: 3.14

%quit
