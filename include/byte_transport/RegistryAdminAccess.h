#pragma once
#include "byte_transport/RegistryUserAccess.h"
#include "byte_transport/TransportDefinition.h"

#include <memory>

namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Administrative (read-write) interface to a transport registry.
   *
   * Extends RegistryUserAccess with operations that mutate the registry: registering and
   * unregistering transport definitions, and handing out read-only user views.
   */
  class RegistryAdminAccess : public RegistryUserAccess
  {
  public:
    /// Default virtual destructor.
    virtual ~RegistryAdminAccess() = default;

    /**
     * @brief Register a transport definition under a key.
     * @param type The key under which the definition is registered.
     * @param definition The transport definition to register.
     * @return true on success, false if the key is already registered.
     */
    virtual bool addTransportDefinition(const std::string& type, const TransportDefinition& ) = 0;

    /**
     * @brief Remove a previously registered transport definition.
     * @param type The key of the definition to remove.
     * @return true if the definition was removed, false if it was not registered.
     */
    virtual bool removeTransportDefinition(const std::string& type) = 0;

    /**
     * @brief Create a read-only user view of the registry.
     * @return A unique_ptr to a RegistryUserAccess view that can be shared with clients.
     */
    virtual std::unique_ptr<RegistryUserAccess> createUser() = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport