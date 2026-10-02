#pragma once

#include "byte_transport/Config.h"
#include "byte_transport/ConfigParseResult.h"
#include "byte_transport/Transport.h"

#include <memory>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Abstract factory/descriptor for a transport type.
   *
   * A TransportDefinition encapsulates everything needed to handle one transport type:
   * parsing its textual configuration (a map of key/value strings) and creating concrete
   * Transport instances from a parsed Config. Transport plugins implement this interface;
   * definitions are registered with a Registry under a string key.
   */
  class TransportDefinition
  {
  public:
    /// Default virtual destructor.
    virtual ~TransportDefinition() = default;

    /**
     * @brief Parse a raw key/value configuration into a typed Config.
     * @param cfg Map of configuration keys to their string values.
     * @return A ConfigParseResult holding the parsed Config on success (ok() == true),
     *         or nullptr with diagnostic messages on failure.
     */
    virtual ConfigParseResult parseConfig(const std::unordered_map<std::string, std::string>& cfg) const = 0;

    /**
     * @brief Create a new Transport instance from a parsed configuration.
     * @param cfg Parsed configuration produced by parseConfig().
     * @return A unique_ptr to the created Transport.
     */
    virtual std::unique_ptr<Transport> create(const Config& cfg) const = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport