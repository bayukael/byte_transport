#pragma once

#include "byte_transport/Config.h"
namespace pendarlab::lib::comm::byte_transport
{
  class Transport
  {
  public:
    Transport();
    Transport(const Config& config);
    virtual ~Transport() = default;
    virtual int read(unsigned char* buf, unsigned int buf_size) = 0;
    virtual int write(const unsigned char* buf, unsigned int length) = 0;
  };
} // namespace pendarlab::lib::comm::byte_transport