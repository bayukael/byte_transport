#include "byte_transport/RegistryUser.h"

#include "byte_transport/TransportDefinition.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace pendarlab::lib::comm::byte_transport
{
  struct RegistryUser::RegistryUserImpl {
    const std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>>& registry;

    RegistryUserImpl(const std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>>& reg);
  };

  RegistryUser::RegistryUserImpl::RegistryUserImpl(
      const std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>>& reg) :
      registry(reg)
  {
  }

  RegistryUser::RegistryUser(const std::unordered_map<std::string, std::reference_wrapper<const TransportDefinition>>& reg) :
      d(std::make_unique<RegistryUserImpl>(reg))
  {
  }

  RegistryUser::RegistryUser(RegistryUser&&) noexcept = default;
  RegistryUser& RegistryUser::operator=(RegistryUser&&) noexcept = default;
  RegistryUser::~RegistryUser() = default;

  const TransportDefinition* RegistryUser::operator[](const std::string& key) const
  {
    auto it = d->registry.find(key);
    if (it == d->registry.end()) {
      return nullptr;
    }
    return &it->second.get();
  }

  std::vector<std::string> RegistryUser::showRegistered() const
  {
    std::vector<std::string> list_of_registered;
    for (auto [name_str, transport_definition] : d->registry) {
      list_of_registered.push_back(name_str);
    }
    return list_of_registered;
  }

  bool RegistryUser::isRegistered(const std::string& key) const
  {
    auto it = d->registry.find(key);
    if (it == d->registry.end()) {
      return false;
    }
    return true;
  }
} // namespace pendarlab::lib::comm::byte_transport