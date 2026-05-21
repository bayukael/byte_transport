#include "byte_transport/ByteTransportFactory.h"

namespace pendarlab::lib::comm
{
  using CreatorFn = std::function<std::unique_ptr<IByteTransport>(const std::unordered_map<std::string, std::string>&)>;
  using ValidatorFn = std::function<ByteTransportFactory::ValidationResult(const std::unordered_map<std::string, std::string>&)>;

  struct Descriptor {
    CreatorFn creator;
    ValidatorFn validator;
  };

  struct ByteTransportFactory::ByteTransportFactoryImpl {
    inline static std::unordered_map<std::string, Descriptor> registry;
  };

  std::unique_ptr<ByteTransportFactory::ByteTransportFactoryImpl> ByteTransportFactory::p_impl_;

  ByteTransportFactory& ByteTransportFactory::instance()
  {
    static ByteTransportFactory factory;
    return factory;
  }

  std::unique_ptr<IByteTransport> ByteTransportFactory::create(const std::string& type,
                                                               const std::unordered_map<std::string, std::string>& config)
  {
    auto& registry = p_impl_->registry;
    auto it = registry.find(type);
    if (it != registry.end()) {
      if (registry[type].creator) {
        return registry[type].creator(config);
      }
    }
    return nullptr;
  }

  ByteTransportFactory::ValidationResult ByteTransportFactory::validateConfig(const std::string& type,
                                                                              const std::unordered_map<std::string, std::string>& config)
  {
    auto& registry = p_impl_->registry;
    auto it = registry.find(type);
    ByteTransportFactory::ValidationResult result;
    if (it != registry.end()) {
      if (registry[type].validator) {
        return registry[type].validator(config);
      } else {
        result.msg = "[ByteTransportFactory]: Config validator is not found for type: " + type + "\n";
      }
    } else {
      result.msg = "[ByteTransportFactory]: The given type: " + type + " is not registered\n";
    }
    result.ok = false;
    return result;
  }

  void ByteTransportFactory::registerByteTransport(const std::string& type, CreatorFn creator_fn, ValidatorFn validator_fn)
  {
    auto& registry = p_impl_->registry;
    Descriptor desc;
    desc.creator = creator_fn;
    desc.validator = validator_fn;
    registry[type] = desc;
  }

  std::vector<std::string> ByteTransportFactory::showRegistered()
  {
    auto& registry = p_impl_->registry;
    std::vector<std::string> list_of_registered;
    for (auto [name_str, descriptor] : registry) {
      list_of_registered.push_back(name_str);
    }
    return list_of_registered;
  }

  bool ByteTransportFactory::isRegistered(const std::string& type){
    auto it = p_impl_->registry.find(type);
    if(it == p_impl_->registry.end()){
      return false;
    }
    return true;
  }

  ByteTransportFactory::ByteTransportFactory()
  {
  }
} // namespace pendarlab::lib::comm