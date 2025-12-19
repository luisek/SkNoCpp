#include <iostream>
#include <string>
#include <vector>

using namespace std;

// avoid const std::string return it will disable move
auto getData() -> string { return "data"; }

void swal(std::string &a, std::string &b) {
  auto tmp = move(a);
  a = move(b);
  b = move(tmp);
}

int main() {
  vector<string> coll;
  coll.reserve(3);

  {
    auto s{getData()};
    coll.push_back(s); // kopiuje nie robi move

    coll.push_back(getData()); // uzyje move 1zasada - unikaj nazw wtedy
                               // zadziała move sematic

    coll.push_back(move(s)); // s nie jest juz potrzebne
    // po move s jest valid but unspecified state
  }

  {
    vector<string> allRows;
    string row;
    while (std::getline(cin, row)) {
      if (row == "end")
        break;
      allRows.push_back(move(row));
    }
    for (const auto &item : allRows) {
      cout << item << endl;
    }
  }
}