#include <iostream>
#include <variant>
#include <vector>

using namespace std;

class NotSimple
{
public:
   NotSimple(int i, float f)
   {}
};

class MyType
{
public:
    MyType()
    {
        cout<<__PRETTY_FUNCTION__ <<endl;
    }
    ~MyType()
    {
        cout<<__PRETTY_FUNCTION__ <<endl;
    }
};

class MyOtherType
{
public:
    MyOtherType()
    {
        cout<<__PRETTY_FUNCTION__ <<endl;
    }
    ~MyOtherType()
    {
        cout<<__PRETTY_FUNCTION__ <<endl;
    }
};

int main()
{
    variant<int, int, int> ii;
    variant<monostate, NotSimple, int> okInit;
    cout <<"index: " <<okInit.index() <<endl;
    okInit = NotSimple{1,1.2f};
    if(const auto value = get_if<NotSimple>(&okInit))
    {
        cout <<"NotSimple: " <<endl;
    }

    variant<long, float, string> logFloatString{
        in_place_index<1>, 7.6
    };

    variant<vector<int>, string, int> vectStrInt {
        in_place_index<0>, {1,2,3,4,5,6}
    };

    variant<int, float> intFloat{in_place_index<0>, 10.5};

    variant<MyType, MyOtherType, string> myTypeOtherTypeString;

    cout <<"index: " <<myTypeOtherTypeString.index() <<endl;
    myTypeOtherTypeString = "YOLO string";
    myTypeOtherTypeString = MyOtherType{};


    return 0;
}