#pragma once

#include "byte_transport/Config.h"
#include "byte_transport/ConfigParseResult.h"
#include "byte_transport/Transport.h"

#include <memory>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  class TransportDefinition
  {
  public:
    virtual ~TransportDefinition() = default;
    virtual ConfigParseResult parseConfig(const std::unordered_map<std::string, std::string>& cfg) const = 0;
    virtual std::unique_ptr<Transport> create(const Config& cfg) const = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport