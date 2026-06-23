#pragma once

#include "byte_transport/Config.h"

#include <optional>
#include <string>
#include <vector>

namespace pendarlab::lib::comm::byte_transport
{
  struct ConfigParseResult {
    std::optional<Config> value;
    std::vector<std::string> messages;

    bool ok() const { return value.has_value(); }
  };
} // namespace pendarlab::lib::comm::byte_transport