

#include "fallment_co_origin.h"

#include <iostream>

using namespace fallment_co;

struct fac_data {
    long long n;
    long long s;
};

long long factorial(fallroutine<long long, fac_data>* fo, fac_data* user_data) {
    auto fac = user_data;

    switch (fo->get_state()) {
    case FoState::START:
        goto START;
        break;

    case FoState::GO:
        goto GO;
        break;

    case FoState::YIELD:
        goto YIELD;
        break;

    case FoState::STOP:
        goto STOP;
        break;
    }

START:
    fac->n = 10;
    fac->s = fac->n;
    fo->set_state(FoState::GO);
    return fac->s;

GO:
    if (fac->n <= 1) {
        fo->set_state(FoState::STOP);
        return -1;
    }
    fac->n--;
    fac->s *= fac->n;

    fo->set_state(FoState::YIELD);
    return fac->s;

YIELD:
    fo->set_state(FoState::GO);
    return factorial(fo, fac);

STOP:
    return -1;
}

int main(int argc, char* argv[]) {
    fac_data fac = {0, 0};
    auto task =
        std::bind(factorial, std::placeholders::_1, std::placeholders::_2);
    fallroutine<long long, fac_data> fo{task, &fac};

    while (fo.has_next()) {
        auto res = fo.next();
        if (res.has_value()) {
            std::cout << res.value() << " ";
        }
    }
    std::cout << "\n";

    return 0;
}