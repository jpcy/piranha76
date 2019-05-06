#pragma once
#include "main.h"

namespace ddraw {

extern WrappedFunc g_DirectDrawCreateFunc;
extern WrappedFunc g_DirectDrawEnumerateA;

void Init();

} // namespace ddraw
