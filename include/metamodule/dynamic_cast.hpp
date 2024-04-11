#pragma once

namespace rack {
#define dynamic_cast rack::stub_dynamic_cast

template <typename T> T stub_dynamic_cast(void *p) {
  return reinterpret_cast<T>(p);
}

} // namespace rack
