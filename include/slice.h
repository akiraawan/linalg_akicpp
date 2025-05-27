#ifndef SLICE_H
#define SLICE_H

#include <iostream>
#include <vector>
#include <optional>

namespace la {

class Slice {
public:
    std::optional<size_t> start;
    std::optional<size_t> end;

    Slice(std::optional<size_t> start = std::nullopt, std::optional<size_t> end = std::nullopt);
};

} // namespace la

#endif // SLICE_H