#include "mock_transport/MockTransportDefinition.h"
#include "mock_transport/MockTransport.h"

#include <memory>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  ConfigParseResult MockTransportDefinition::parseConfig(const std::unordered_map<std::string, std::string>& cfg) const
  {
    ConfigParseResult result;
    result.config = Config();
    result.messages.push_back("mock succeeded");
    return result;
  }

  std::unique_ptr<Transport> MockTransportDefinition::create(const Config& cfg) const{
    return std::make_unique<MockTransport>();
  }
} // namespace pendarlab::lib::comm::byte_transport