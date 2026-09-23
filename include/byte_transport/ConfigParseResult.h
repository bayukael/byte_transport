#pragma once

#include "byte_transport/Config.h"

#include <optional>
#include <string>
#include <vector>
#include <memory>

namespace pendarlab::lib::comm::byte_transport
{
  struct ConfigParseResult {
    std::unique_ptr<Config> config;
    std::vector<std::string> messages;

    bool ok() const { return config != nullptr; }
  };
} // namespace pendarlab::lib::comm::byte_transport