#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  // it will not compile due to assign to read-only variable
  // it is stateless lambda - it will always produce the same result for every
  // call
  //    auto changed1 = [prev = 0](auto val) {
  //      bool changed = prev != val;
  //      prev = val;
  //      return changed;
  //    };
  auto changed = [prev = 0](auto val) mutable {
    bool changed = prev != val;
    prev = val;
    return changed;
  };

  std::vector<int> coll{7, 42, 42, 0, 3, 3, 7};
  std::copy_if(coll.begin(), coll.end(),
               std::ostream_iterator<int>{std::cout, " "}, changed1);
  std::cout << std::endl;

  std::copy_if(coll.begin(), coll.end(),
               std::ostream_iterator<int>{std::cout, " "}, changed);

  /*
   Standard algorithms take callables by value
   * operate on a copy of 'changed'
  */
  std::cout << std::endl;
  changed(7); //<= change the state of lambda
  std::copy_if(coll.begin(), coll.end(),
               std::ostream_iterator<int>{std::cout, " "}, changed);

  std::cout << std::endl;
}