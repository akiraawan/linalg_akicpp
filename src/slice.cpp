#include "slice.h"
#include <vector>
#include <optional>

namespace la {

Slice::Slice(std::optional<size_t> start, std::optional<size_t> end)
    : start(start), end(end) {}

}