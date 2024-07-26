#include "fallmento.h"

#include <iostream>

using namespace fallmento;

struct prime_factor_data {
    int n;
    int f;
    int c;
};

int prime_factor(fallroutine<int, prime_factor_data>* fo,
                 prime_factor_data* user_data) {
    auto pf = user_data;

    FO_BEGIN(fo);

    pf->c = 2;
    while (pf->n > 1) {
        while (pf->n % pf->c == 0) {
            pf->n /= pf->c;
            pf->f = pf->c;
            FO_YIELD(fo, pf->f);
        }
        pf->c++;
    }

    FO_RETURN(fo, 0);
}

int main(int argc, char* argv[]) {
    prime_factor_data u{24, 0, 2};
    auto task =
        std::bind(prime_factor, std::placeholders::_1, std::placeholders::_2);
    fallroutine<int, prime_factor_data> fo{task, &u};

    while (fo.has_next()) {
        auto res = fo.next();
        if (res.has_value()) {
            std::cout << res.value() << " ";
        }
    }
    std::cout << "\n";

    return 0;
}