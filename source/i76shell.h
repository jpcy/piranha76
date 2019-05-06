#pragma once

namespace i76shell {

HMODULE Load();
bool IsModule(HMODULE _module);
FARPROC GetProcAddress(const char *_name);

} // namespace i76shell
