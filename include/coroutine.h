#ifndef COROUTINE_H
#define COROUTINE_H
#include "coroutine.h"

namespace Study
{
    class Cotoutine
    {
        static long create(coroutine_func_t fn, void* args = nullptr);
    };
}

#endif // !COROUTINE_H