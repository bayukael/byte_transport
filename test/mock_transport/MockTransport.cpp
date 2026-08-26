#include "mock_transport/MockTransport.h"
namespace pendarlab::lib::comm::byte_transport
{
  int MockTransport::read(unsigned char* buf, unsigned int buf_size)
  {
    return 42;
  }

  int MockTransport::write(const unsigned char* buf, unsigned int length)
  {
    return 42;
  }
} // namespace pendarlab::lib::comm::byte_transport