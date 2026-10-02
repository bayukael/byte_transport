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
  /**
   * @brief Read-only interface to a transport registry.
   *
   * Exposes the querying operations of a registry without allowing modification.
   * Instances are obtained via RegistryAdminAccess::createUser(). This is the interface
   * meant to be shared with components that only need to look up and use registered
   * transport definitions.
   */
  class RegistryUserAccess
  {
  public:
    /// Default virtual destructor.
    virtual ~RegistryUserAccess() = default;

    /**
     * @brief Look up a registered transport definition by key.
     * @param type The registration key to look up.
     * @return Pointer to the matching TransportDefinition, or nullptr if not registered.
     * @note The returned pointer is owned by the registry; do not delete it. Be careful
     *       to check for a null return value.
     */
    virtual const TransportDefinition* operator[](const std::string& type) const = 0;

    /**
     * @brief List the keys of all registered transport definitions.
     * @return Vector of registered keys.
     */
    virtual std::vector<std::string> showRegistered() const = 0;

    /**
     * @brief Check whether a transport type is registered.
     * @param type The registration key to check.
     * @return true if the key is registered, false otherwise.
     */
    virtual bool isRegistered(const std::string& type) const = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport
