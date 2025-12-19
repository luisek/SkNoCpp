#include <iostream>
using namespace std;

class C {
public:
  C() { cout << __PRETTY_FUNCTION__ << endl; }
  C(const C &) { cout << __PRETTY_FUNCTION__ << endl; }
  C(const C &&) { cout << __PRETTY_FUNCTION__ << endl; }
  ~C() { cout << __PRETTY_FUNCTION__ << endl; }

  C operator=(const C &) {
    cout << __PRETTY_FUNCTION__ << endl;
    return *this;
  }
  C operator=(const C &&) {
    cout << __PRETTY_FUNCTION__ << endl;
    return *this;
  }
};

void foo(const C &c) { cout << __PRETTY_FUNCTION__ << endl; }
void foo(C &c) { cout << __PRETTY_FUNCTION__ << endl; }
void foo(C &&c) { cout << __PRETTY_FUNCTION__ << endl; }

template <typename T> auto printFoo(T &&item) { foo(forward<T>(item)); }

int main() {

  C c;
  const C cc;
  printFoo(c);
  printFoo(cc);
  printFoo(C{});
  printFoo(move(cc)); // nie ma to sensu const nie bedzie move
  printFoo(move(c));
  return 0;
}