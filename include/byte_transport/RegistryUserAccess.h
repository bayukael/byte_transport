#pragma once

#include <byte_transport/ConfigParseResult.h>
#include <byte_transport/Transport.h>
#include <byte_transport/TransportDefinition.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pendarlab::lib::comm::byte_transport
{
  class RegistryUserAccess
  {
  public:
    virtual ~RegistryUserAccess() = default;
    
    virtual const TransportDefinition* operator[](const std::string& type) const = 0; // Be careful when it returns nullptr
    virtual std::vector<std::string> showRegistered() const = 0;
    virtual bool isRegistered(const std::string& type) const = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport
