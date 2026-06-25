#include "byte_transport/Registry.h"

#include "byte_transport/RegistryUser.h"
#include "byte_transport/RegistryUserAccess.h"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace pendarlab::lib::comm::byte_transport
{
  struct Registry::RegistryImpl {
    std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>> registry;
  };

  Registry::Registry() : d(std::make_unique<RegistryImpl>())
  {
  }

  Registry::Registry(Registry&&) noexcept = default;
  Registry& Registry::operator=(Registry&&) noexcept = default;
  Registry::~Registry() = default;

  bool Registry::addTransportDefinition(const std::string& key, const TransportDefinition& transport_def)
  {
    auto it = d->registry.find(key);
    if (it != d->registry.end()) {
      return false;
    }
    d->registry.emplace(key, std::cref(transport_def));
    return true;
  }

  bool Registry::removeTransportDefinition(const std::string& key)
  {
    auto it = d->registry.find(key);
    if (it == d->registry.end()) {
      return false;
    }
    d->registry.erase(key);
    return true;
  }

  const TransportDefinition* Registry::operator[](const std::string& key) const
  {
    auto it = d->registry.find(key);
    if (it == d->registry.end()) {
      return nullptr;
    }
    return &it->second.get();
  }

  std::unique_ptr<RegistryUserAccess> Registry::createUser()
  {
    return std::make_unique<RegistryUser>(d->registry);
  }

  std::vector<std::string> Registry::showRegistered() const
  {
    std::vector<std::string> list_of_registered;
    for (auto [name_str, transport_definition] : d->registry) {
      list_of_registered.push_back(name_str);
    }
    return list_of_registered;
  }

  bool Registry::isRegistered(const std::string& key) const
  {
    auto it = d->registry.find(key);
    if (it == d->registry.end()) {
      return false;
    }
    return true;
  }

} // namespace pendarlab::lib::comm::byte_transport