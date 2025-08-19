cmake_minimum_required(VERSION 3.10)
project(OpenDAWLib LANGUAGES C)

# Find Cargo
find_program(CARGO cargo REQUIRED)

# Path to Rust crate (crate root = folder with Cargo.toml)
set(RUST_CRATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Output directory for Cargo builds
set(RUST_TARGET_DIR "${CMAKE_BINARY_DIR}/target")

if(UNIX AND NOT APPLE)
    set(RUST_LIB "${RUST_TARGET_DIR}/x86_64-unknown-linux-gnu/release/libopendawlib.a")
elseif(WIN32)
    set(RUST_LIB "${RUST_TARGET_DIR}/x86_64-pc-windows-msvc/release/opendawlib.lib")
endif()

if(UNIX AND NOT APPLE)
    # Build Rust library for linux
    add_custom_command(
        OUTPUT ${RUST_LIB}
        COMMAND ${CARGO} build --release --target x86_64-unknown-linux-gnu
        WORKING_DIRECTORY "${RUST_CRATE_DIR}"
        COMMENT "Building Rust library OpenDAWLib"
        VERBATIM
    )
elseif(WIN32)
    # Build Rust library for linux
    add_custom_command(
        OUTPUT ${RUST_LIB}
        COMMAND ${CARGO} build --release --target x86_64-pc-windows-msvc
        WORKING_DIRECTORY "${RUST_CRATE_DIR}"
        COMMENT "Building Rust library OpenDAWLib"
        VERBATIM
    )
endif()

# Custom target to wrap the command
add_custom_target(OpenDAWLib ALL
    DEPENDS ${RUST_LIB}
)

# Tell CMake about the built library
add_library(OpenDAWLibStatic STATIC IMPORTED GLOBAL)
set_target_properties(OpenDAWLibStatic PROPERTIES
    IMPORTED_LOCATION ${RUST_LIB}
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/headers"
)
