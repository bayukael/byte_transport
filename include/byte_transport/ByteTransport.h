#pragma once

namespace pendarlab::lib::comm
{
  class ByteTransport
  {
  public:
    virtual ~ByteTransport() = default;
    virtual int read(unsigned char* buf, unsigned int buf_size) = 0;
    virtual int write(const unsigned char* buf, unsigned int length) = 0;
  };
} // namespace pendarlab::lib::comm