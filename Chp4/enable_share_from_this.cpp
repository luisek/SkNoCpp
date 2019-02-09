#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

class Y: public enable_shared_from_this<Y>
{
public:

    shared_ptr<Y> f()
    {
        return shared_from_this();
    }
};

int main()
{
    shared_ptr<Y> p(new Y);
    shared_ptr<Y> q = p->f();
    assert(p == q);

    assert(!(p < q || q < p)); // p and q must share ownership
}