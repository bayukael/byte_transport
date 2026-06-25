#pragma once

#include "byte_transport/RegistryUserAccess.h"
#include "byte_transport/TransportDefinition.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  class RegistryUser : public RegistryUserAccess
  {
  public:
    RegistryUser(const std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>>& registry);
    RegistryUser(RegistryUser&&) noexcept;
    RegistryUser& operator=(RegistryUser&&) noexcept;
    ~RegistryUser();

    virtual const TransportDefinition* operator[](const std::string& key) const override; // Be careful when it returns nullptr
    virtual std::vector<std::string> showRegistered() const override;
    virtual bool isRegistered(const std::string& key) const override;

  private:
    struct RegistryUserImpl;
    std::unique_ptr<RegistryUserImpl> d;
  };
} // namespace pendarlab::lib::comm::byte_transport