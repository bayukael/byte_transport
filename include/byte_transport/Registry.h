#pragma once

#include "byte_transport/RegistryAdminAccess.h"

#include <memory>

namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Concrete administrative registry for transport definitions.
   *
   * Stores registered TransportDefinitions keyed by name and provides both administrative
   * (add/remove) and user (lookup/query) operations. Implemented with the PIMPL idiom;
   * the impl is held via the @c d member.
   */
  class Registry : public RegistryAdminAccess
  {
  public:
    /// Construct an empty registry.
    Registry();

    /// Move constructor (default).
    Registry(Registry&&) noexcept;

    /// Move assignment operator (default).
    Registry& operator=(Registry&&) noexcept;

    /// Destructor.
    ~Registry();

    /// @copydoc RegistryAdminAccess::addTransportDefinition()
    virtual bool addTransportDefinition(const std::string& key, const TransportDefinition&) override;

    /// @copydoc RegistryAdminAccess::removeTransportDefinition()
    virtual bool removeTransportDefinition(const std::string& key) override;

    /// @copydoc RegistryAdminAccess::createUser()
    virtual std::unique_ptr<RegistryUserAccess> createUser() override;

    /// @copydoc RegistryUserAccess::operator[]()
    virtual const TransportDefinition* operator[](const std::string& key) const override;

    /// @copydoc RegistryUserAccess::showRegistered()
    virtual std::vector<std::string> showRegistered() const override;

    /// @copydoc RegistryUserAccess::isRegistered()
    virtual bool isRegistered(const std::string& key) const override;

  private:
    /// PIMPL implementation class.
    struct RegistryImpl;

    /// Pointer to the implementation.
    std::unique_ptr<RegistryImpl> d;
  };
} // namespace pendarlab::lib::comm::byte_transport