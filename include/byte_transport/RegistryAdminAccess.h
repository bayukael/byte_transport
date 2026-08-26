#pragma once
#include "byte_transport/RegistryUserAccess.h"
#include "byte_transport/TransportDefinition.h"

#include <memory>

namespace pendarlab::lib::comm::byte_transport
{
  class RegistryAdminAccess : public RegistryUserAccess
  {
  public:
    virtual ~RegistryAdminAccess() = default;
    
    virtual bool addTransportDefinition(const std::string& type, const TransportDefinition& ) = 0;
    virtual bool removeTransportDefinition(const std::string& type) = 0;
    virtual std::unique_ptr<RegistryUserAccess> createUser() = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport