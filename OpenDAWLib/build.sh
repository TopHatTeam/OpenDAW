#!/bin/sh

rm -rf /target
cargo clean
cargo build --release --target x86_64-unknown-linux-gnu
# rustc --crate-type=staticlib src/lib.rs -o bin/opendawlib.a