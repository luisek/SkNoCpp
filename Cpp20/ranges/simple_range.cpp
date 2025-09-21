#include <iostream>
#include <ranges>


using namespace std;

template <view Inner> requires forward_range<Inner>
class FistItemView : public view_interface<FirstItemView<Inner>> {
    [[no_unique_address]] Inner inner;

public:
    constexpr FirstItemView(Inner inner_) : inner(std::move(inner_)){}
    constexpr auto begin() {
        return std::ranges::begin(inner);
    }
    constexpr auto end() {
        return empty(inner) ? begin() : next(begin());
    }
    constexpr std::size_t size() {
        return empty(inner) ? 0 : 1;
    }
};

template <forward_range Range>
FirstItemView(Range&&) -> FirstItemView<views::all_t<Range>>;
struct First : range_adaptor_closure<First> {
    constexpr auto operator()(forward_range auto&& rang) const {return FirstItemView{std::move(rang)};}
};

int main()
{}