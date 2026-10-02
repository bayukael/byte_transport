#pragma once

namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Abstract base class for transport configuration objects.
   *
   * Concrete configuration classes are produced by TransportDefinition::parseConfig()
   * and stored (polymorphically) in a ConfigParseResult. A Config object holds the
   * parsed, type-specific settings that a transport needs to be created via
   * TransportDefinition::create().
   */
  class Config
  {
  public:
    /// Default virtual destructor (makes Config a polymorphic base).
    virtual ~Config() = default;
  };
} // namespace pendarlab::lib::comm::byte_transport