# sim808

Driver for SIM808 cellular module

<img src="data/sim808.png" style="width: 300px;" alt="sim808-photo">

![status](https://img.shields.io/badge/Status-Under_development-blue)

## Layout

```text
.
├── data                # Assets
├── include             # Core library headers
├── src                 # Core library sources
├── tests               # Unit tests for core library
└── tools               # Tools
    └── CommandLineTool # Command-line tool for testing the driver
```

## Prerequisites

- C++ compiler with `C++20` support
- CMake
- [non-Boost asio](https://think-async.com/Asio/)
- GTest (for unit tests only)

## Build

To build the driver, go to the project root directory and execute the
following commands:

```shell
# Prepare the build system
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_FLAGS="-std=c++20" \
      -S . -B build/debug

# Build
cmake --build build/debug --target Sim808
```

### Targets

| Name                     |        Description        | Since |
|:-------------------------|:-------------------------:|:-----:|
| `Sim808`                 |          Driver           | 0.1.0 |
| `Sim808.Tests`           | Unit tests for the driver | 0.1.0 |
| `Sim808.CommandLineTool` |           REPL            | 0.1.0 |

### Options

| Name                 |                    Description                     | Default | Since |
|:---------------------|:--------------------------------------------------:|:-------:|:-----:|
| `SIM808_BUILD_TESTS` |      Generates a build target for unit tests       |  `OFF`  | 0.1.0 |
| `SIM808_BUILD_CLT`   | Generates a build target for the command-line tool |  `OFF`  | 0.1.0 |

## Features

- [Short Message Service](include/Sim808/ShortMessages/Service.hpp) (SMS)
  - Retrieving a list of messages from the specified message storage
  - Sending messages

## Command-line tool

An auxiliary tool implemented for testing purposes that allows you to test driver
functionality from a command line.

Commands have the following syntax: `<command> [<parameter> = "..."[, ...]]`. There
are no spaces before and after the `=` sign (added to the top to avoid ambiguity for
fonts with ligatures).

**Example:**

```shell
sms:send to="+7xxxxxxxxxx" text="Hi!"
```

### Short Message Service (SMS)

|  Command   |      Description       |  Parameters  | Since |
|:----------:|:----------------------:|:------------:|:-----:|
| `sms:list` | Get a list of messages |     None     | 0.1.0 |
| `sms:send` |     Send a message     | `to`, `text` | 0.1.0 |

**Parameters:**

- `to` - receiver number
- `text` - message text

## Documentation

To generate docs, go to the project root directory and execute the following
command:

```shell
doxygen Doxyfile
```

Click [this](docs/html/index.html) to open index page.

## Author

Oleg E. Vorobiov <isnullxbh@gmail.com>

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE) for more information.
