#pragma once

#include "byte_transport/RegistryUserAccess.h"
#include "byte_transport/TransportDefinition.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Concrete read-only user view of a transport registry.
   *
   * Provides lookup and query operations over a snapshot of registered transport
   * definitions without allowing modification. Implemented with the PIMPL idiom; the
   * impl is held via the @c d member.
   */
  class RegistryUser : public RegistryUserAccess
  {
  public:
    /**
     * @brief Construct a user view from a registry map.
     * @param registry Map of keys to the registered TransportDefinitions to expose.
     */
    RegistryUser(const std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>>& registry);

    /// Move constructor.
    RegistryUser(RegistryUser&&) noexcept;

    /// Move assignment operator.
    RegistryUser& operator=(RegistryUser&&) noexcept;

    /// Destructor.
    ~RegistryUser();

    /// @copydoc RegistryUserAccess::operator[]()
    virtual const TransportDefinition* operator[](const std::string& key) const override;

    /// @copydoc RegistryUserAccess::showRegistered()
    virtual std::vector<std::string> showRegistered() const override;

    /// @copydoc RegistryUserAccess::isRegistered()
    virtual bool isRegistered(const std::string& key) const override;

  private:
    /// PIMPL implementation class.
    struct RegistryUserImpl;

    /// Pointer to the implementation.
    std::unique_ptr<RegistryUserImpl> d;
  };
} // namespace pendarlab::lib::comm::byte_transport