#pragma once

#include "byte_transport/Config.h"
namespace pendarlab::lib::comm::byte_transport
{
  /**
   * @brief Abstract base class for byte transport implementations.
   *
   * Concrete transports are instantiated by TransportDefinition::create() and provide
   * low-level byte-oriented read/write access over a particular medium (e.g. serial,
   * TCP, CAN). Reads and writes operate on raw byte buffers.
   */
  class Transport
  {
  public:
    /// Default constructor.
    Transport(){};

    /**
     * @brief Construct a transport from configuration.
     * @param config Configuration previously parsed by TransportDefinition::parseConfig().
     */
    Transport(const Config& config){};

    /// Default virtual destructor.
    virtual ~Transport() = default;

    /**
     * @brief Read bytes from the transport into a buffer.
     * @param buf      Destination buffer receiving the read bytes.
     * @param buf_size Capacity of @p buf in bytes.
     * @return Number of bytes read, or a negative value on error.
     */
    virtual int read(unsigned char* buf, unsigned int buf_size) = 0;

    /**
     * @brief Write bytes to the transport.
     * @param buf    Source buffer containing the bytes to write.
     * @param length Number of bytes to write.
     * @return Number of bytes written, or a negative value on error.
     */
    virtual int write(const unsigned char* buf, unsigned int length) = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport