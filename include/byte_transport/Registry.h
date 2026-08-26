#pragma once

#include "byte_transport/RegistryAdminAccess.h"

#include <memory>

namespace pendarlab::lib::comm::byte_transport
{
  class Registry : public RegistryAdminAccess
  {
  public:
    Registry();
    Registry(Registry&&) noexcept;            // Declare move constructor which will be defined as default
    Registry& operator=(Registry&&) noexcept; // Declare move assignment which will be defined as default
    ~Registry();

    virtual bool addTransportDefinition(const std::string& key, const TransportDefinition&) override;
    virtual bool removeTransportDefinition(const std::string& key) override;
    virtual std::unique_ptr<RegistryUserAccess> createUser() override;
    virtual const TransportDefinition* operator[](const std::string& key) const override; // Be careful when it returns nullptr
    virtual std::vector<std::string> showRegistered() const override;
    virtual bool isRegistered(const std::string& key) const override;

  private:
    struct RegistryImpl;
    std::unique_ptr<RegistryImpl> d;
  };
} // namespace pendarlab::lib::comm::byte_transport