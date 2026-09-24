# byte_transport

A library for registering and looking up transport implementations (e.g. serial, TCP, USB) behind a common interface so that users can easily switch between different transport implementations without any changes in their code. This library does not provide the transport implementations, though. Users need to provide with their own transport implementation.

## What it does

`byte_transport` provides a `Registry` that maps a string type name (e.g. `"serial"`) to a `TransportDefinition`. A transport plugin implements `TransportDefinition`, and a `RegistryUserAccess` (created from the registry) lets read-only consumers look up definitions without being able to modify them.

The registry is used to:
- **add** a `TransportDefinition` under a type name
- **remove** a definition by type name
- **look up** a definition via `operator[]` (returns `nullptr` if not registered)
- **list** registered type names
- **check** whether a type name is registered

Looked-up definitions let callers `parseConfig()` a set of key/value strings into a typed `Config`, then `create()` a concrete `Transport`.

## Architecture

Public headers live in `include/byte_transport/` and use the namespace `pendarlab::lib::comm::byte_transport`.

- `Transport` — abstract read/write interface for a transport.
- `Config` — polymorphic base for transport-specific configuration.
- `ConfigParseResult` — result of parsing config: holds a `std::unique_ptr<Config>` plus a list of messages; `ok()` is `true` only when `config != nullptr`.
- `TransportDefinition` — plugin interface: `parseConfig()` + `create()`. Implement this to add a new transport.
- `Registry` (`RegistryAdminAccess`) — admin interface to add/remove definitions and create user handles.
- `RegistryUserAccess` — read-only interface returned by `Registry::createUser()`.

`Registry` uses the PIMPL idiom (impl member `d`). `addTransportDefinition()` fails (returns `false`) if the type name is already registered; `removeTransportDefinition()` returns `false` if the type name is not registered.

## Quick start (build)

Requires CMake >= 3.13 and GoogleTest (`find_package(GTest CONFIG REQUIRED)`).

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/ByteTransportTest    # GoogleTest runner
```

Run a single test:

```bash
./build/ByteTransportTest --gtest_filter='*RegistryInitialTest*'
```

There are no lint/format targets; building and running `ByteTransportTest` is the only verification.

## Install

Install the library into a versioned subdirectory of the given prefix. The version is appended automatically, so each release coexists under its own directory (e.g. `<prefix>/1.0.0/`).

```bash
cmake -S . -B build -G Ninja
cmake --install build --prefix <prefix>
```

This installs to `<prefix>/1.0.0/` with this layout:

```
<prefix>/1.0.0/
  include/byte_transport/          # public headers
  lib/libpendarlab-byte_transport.so -> .so.1 -> .so.1.0.0
  lib/cmake/PendarlabByteTransport # CMake package config
```

Bump the version in `CMakeLists.txt` (`project(... VERSION ...)`) and reinstall to produce a new versioned directory; switching between installed versions is done by pointing `CMAKE_PREFIX_PATH` at the desired version (see below).

## Using the library from another project

The library installs as the CMake package `PendarlabByteTransport` (exported target `pendarlab::ByteTransport`). Point `CMAKE_PREFIX_PATH` at the version you want and request it from `find_package`:

```bash
cmake -S my_app -B build -DCMAKE_PREFIX_PATH=<prefix>/1.0.0
```

```cmake
find_package(PendarlabByteTransport 1.0.0 REQUIRED)
target_link_libraries(my_app PRIVATE pendarlab::ByteTransport)
```

Example usage:

```cpp
#include <byte_transport/Registry.h>
#include <memory>

using namespace pendarlab::lib::comm::byte_transport;

// A registry holds TransportDefinition objects by type name.
Registry registry;
// registry.addTransportDefinition("serial", my_serial_definition);

// Read-only consumers get a user handle.
std::unique_ptr<RegistryUserAccess> user = registry.createUser();

if (user->isRegistered("serial")) {
  const TransportDefinition* def = (*user)["serial"]; // nullptr if absent
  // ConfigParseResult parsed = def->parseConfig(config_map);
  // std::unique_ptr<Transport> transport = def->create(parsed.config);
}
```

## Adding a transport plugin

1. Subclass `TransportDefinition`.
2. Implement `parseConfig()` — turn a `std::unordered_map<std::string, std::string>` into a `ConfigParseResult` (set `config`, and/or push messages; `ok()` reflects `config != nullptr`).
3. Implement `create()` — return a `std::unique_ptr<Transport>` built from the parsed `Config`.
4. Register an instance with the registry under a type name.

See `test/mock_transport/MockTransportDefinition.cpp` for a minimal example.

## Tests

`test/byte_transport_test.cpp` uses GoogleTest and the mock transport in `test/mock_transport/` (which is a build target, not a test). Coverage includes add/remove semantics, duplicate registration rejection, listing, and the read-only user view.
