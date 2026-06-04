#pragma once

#include "byte_transport/ByteTransport.h"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pendarlab::lib::comm
{
  class ByteTransportFactory
  {
  public:
    struct ValidationResult {
      bool ok;
      std::vector<std::string> msg;
    };
    using CreatorFn = std::function<std::unique_ptr<ByteTransport>(const std::unordered_map<std::string, std::string>&)>;
    using ValidatorFn = std::function<ValidationResult(const std::unordered_map<std::string, std::string>&)>;

    static ByteTransportFactory& instance();
    static std::unique_ptr<ByteTransport> create(const std::string& type, const std::unordered_map<std::string, std::string>& config);
    static ValidationResult validateConfig(const std::string& type, const std::unordered_map<std::string, std::string>& config);
    static void registerByteTransport(const std::string& type, CreatorFn creator_fn, ValidatorFn validator_fn);
    static std::vector<std::string> showRegistered();
    static bool isRegistered(const std::string& type);

  private:
    struct ByteTransportFactoryImpl;
    static std::unique_ptr<ByteTransportFactoryImpl> p_impl_;
    ByteTransportFactory();
  };
} // namespace pendarlab::lib::comm

#define REGISTER_BYTE_TRANSPORT(NAME, CREATOR_FN, VALIDATOR_FN)                                                     \
  namespace                                                                                                         \
  {                                                                                                                 \
    const bool registered_##__COUNTER__ = []() {                                                                    \
      pendarlab::lib::comm::ByteTransportFactory::instance().registerByteTransport(NAME, CREATOR_FN, VALIDATOR_FN); \
      return true;                                                                                                  \
    }();                                                                                                            \
  }
