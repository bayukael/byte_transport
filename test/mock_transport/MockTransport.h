#pragma once

#include <byte_transport/Transport.h>

namespace pendarlab::lib::comm::byte_transport
{
  class MockTransport : public Transport
  {
  public:
    ~MockTransport() = default;
    virtual int read(unsigned char* buf, unsigned int buf_size) override;
    virtual int write(const unsigned char* buf, unsigned int length) override;
  };
} // namespace pendarlab::lib::comm::byte_transport