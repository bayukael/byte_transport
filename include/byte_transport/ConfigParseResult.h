#pragma once

#include "byte_transport/Config.h"

#include <optional>
#include <string>
#include <vector>
#include <memory>

namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Result of parsing a transport configuration.
   *
   * Holds the parsed @ref Config (or nullptr on failure) together with a list of
   * human-readable messages produced during parsing (warnings and/or errors).
   */
  struct ConfigParseResult {
    /** The parsed configuration, or nullptr when parsing failed. */
    std::unique_ptr<Config> config;

    /** Diagnostic messages produced during parsing (errors/warnings). */
    std::vector<std::string> messages;

    /**
     * @brief Whether parsing succeeded.
     * @return true when @ref config is non-null, false otherwise.
     */
    bool ok() const { return config != nullptr; }
  };
} // namespace pendarlab::lib::comm::byte_transport