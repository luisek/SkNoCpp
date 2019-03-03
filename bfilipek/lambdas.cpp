#include <iostream>
#include <string>
#include <functional>
using namespace std;

/*
[] ()   { code; }
^  ^  ^
|  |  |
|  |  optional: mutable, exception, trailing return, ...
|  |
|  parameter list
|
lambda introducer with capture list
*/


int global = 10;

void captureGlobals()
{
    cout <<"Globals...\n";
    cout <<global <<'\n';
    auto foo = [=]() mutable {++global;};
    foo();
    cout <<global <<'\n';
    []{++global;}();
    cout <<global <<'\n';
    //clang++ error ->error: global' cannot be captured because it does not have automatic storage duration
    //g++ warning -> warning: capture of variable ‘global’ with non-automatic storage duration
    [global]{++global;}();
}

void captureStatic()
{
    cout <<"Static...\n";
    static int static_int = 10;
    auto foo = [=]()mutable{++static_int;};
    foo();
    cout <<static_int <<'\n';
    []{++static_int;}();
    cout <<static_int <<'\n';
    //clang++ error: 'static_int' cannot be captured because it does not have automatic storage duration
    //g++ warning: capture of variable ‘static_int’ with non-automatic storage duration
    [static_int]{++static_int;}();
}

struct Baz
{
    function<void()> foo()
    {
        return [s=s]{cout <<s <<'\n';}; //s=s c++14 można też zrobić auto foo() ...
    }
    string s;
};

int main(int argc, char* argv[])
{
    int x = 10, y = 15;
    auto myLambda = [&x, &y](){++x; ++y;}; 
    /*
    domknięcie posiada usunięty default c-tor i usunięty default operator przypisania.
    dlatego nie można stworzyć kopii obiektu.
    decltype(myLambda) copyOfLambda;
    */
    myLambda();
    cout <<x <<' ' <<y <<endl;

    auto foo = [x,y]() mutable {++x; ++y;};
    foo();
    cout <<x <<' ' <<y <<'\n';
    captureGlobals();
    captureStatic();


//wiszące referencje !!!
    auto f1 = Baz{"ala"}.foo();
    auto f2 = Baz{"ula"}.foo();
    f1();
    f2();
//koniec już nie wiszą :P

    int const cx = 10;
    auto constLambda = [cx] () mutable {
        cout <<is_const<decltype(cx)>::value <<'\n';
        //cx = 11;
    };
    constLambda();

    return 0;
}