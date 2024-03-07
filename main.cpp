#include <type_traits>
#include <iostream>

struct S{
    template<int Exp, typename T = double, typename enable = void>
    struct pow{
        constexpr T operator()(T bas){
            pow<Exp -1, T> next;    // recursive call to any of the power functions inside S struct
            return next(bas) * bas;
        }
    };

    template<typename T>
    struct pow<0, T>{
        constexpr T operator()(T bas){
            return bas == (T)0 ? (T)0 :(T)1;
        }
    };

    template<int Exp, typename T>   // negativa siffror
    struct pow<Exp, T, typename std::enable_if_t<Exp < 0>> {
        constexpr T operator()(T bas) {
            pow<Exp + 1, T> next;   // recursive call to any of the power functions inside S struct
            return next(bas) * 1 / bas;
        }
    };
};

int main(){
    S::pow<-4> result;
    std::cout<<result(3) << std::endl;
}