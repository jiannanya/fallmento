#include "fallment_co_optimize.h"

#include <iostream>

using namespace fallment_co;

struct fac_data {
    long long n;
    long long s;
};

struct ret {
    long long i;
};

ret factorial(fallroutine<ret, fac_data>* fo, fac_data* user_data) {
    auto fac = user_data;

    fac->n = 10;
    fac->s = fac->n;

    FO_BEGIN(fo)

    if (fac->n <= 1) {
        FO_RETURN(fo, ret{fac->s})
    }

    FO_YIELD(fo, ret{fac->s})

    fac->n--;
    fac->s *= fac->n;

    FO_RETURN(fo, ret{fac->s});
}

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

int main(int argc, char* argv[]) {
    fac_data fac = {10, 10};
    auto task =
        std::bind(factorial, std::placeholders::_1, std::placeholders::_2);
    fallroutine<ret, fac_data> fo{task, &fac};

    while (fo.has_next()) {
        auto res = fo.next();
        if (res.has_value()) {
            std::cout << res.value().i << " ";
        }
    }
    std::cout << "\n";

    return 0;
}