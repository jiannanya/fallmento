#include "fallment_co.h"

#include <iostream>

using namespace fallment_co;

// struct fac_data {
//     long long n;
//     long long s;
// };

// struct ret {
//     long long i;
// };

// ret factorial(fallroutine<ret, fac_data>* fo, fac_data* user_data) {
//     auto fac = user_data;

//     FO_BEGIN(fo)

//     while (fac->n > 1) {
//         FO_YIELD(fo, ret{fac->s})
//         fac->n--;
//         fac->s *= fac->n;
//     }

//     FO_RETURN(fo, ret{fac->s});
// }

// int main(int argc, char* argv[]) {
//     fac_data fac = {10, 10};
//     auto task =
//         std::bind(factorial, std::placeholders::_1, std::placeholders::_2);
//     fallroutine<ret, fac_data> fo{task, &fac};

//     while (fo.has_next()) {
//         auto res = fo.next();
//         if (res.has_value()) {
//             std::cout << res.value().i << " ";
//         }
//     }
//     std::cout << "\n";

//     return 0;
// }
struct user {};

int test_mult_yield(fallroutine<int, user>* fo, user* user_data) {
    FO_BEGIN(fo)

    FO_YIELD(fo, 1)
    FO_YIELD(fo, 2)
    FO_YIELD(fo, 3)

    FO_RETURN(fo, 0)
}

int main(int argc, char* argv[]) {
    user u{};
    auto task = std::bind(test_mult_yield, std::placeholders::_1,
                          std::placeholders::_2);
    fallroutine<int, user> fo{task, &u};

    while (fo.has_next()) {
        auto res = fo.next();
        if (res.has_value()) {
            std::cout << res.value() << " ";
        }
    }
    std::cout << "\n";

    return 0;
}
