#pragma once

#include <byte_transport/TransportDefinition.h>
#include <memory>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  class MockTransportDefinition : public TransportDefinition
  {
  public:
    ~MockTransportDefinition() = default;
    virtual ConfigParseResult parseConfig(const std::unordered_map<std::string, std::string>& cfg) const override;
    virtual std::unique_ptr<Transport> create(const Config& cfg) const override;
  };
} // namespace pendarlab::lib::comm::byte_transport