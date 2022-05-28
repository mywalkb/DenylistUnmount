#!/usr/bin/env bash

set -euo pipefail

build_mode="${1:-release}"

cd "$(dirname "$0")"

pushd module
rm -fr libs
debug_mode=1
if [[ "$build_mode" == "release" ]]; then
    debug_mode=0
fi
/opt/android/sdk/ndk/24.0.8215888/ndk-build -j8 NDK_DEBUG=$debug_mode
popd

mkdir -p magisk/zygisk
for arch in armeabi-v7a arm64-v8a x86 x86_64
do
    cp "module/libs/$arch/libdenylist.so" "magisk/zygisk/$arch.so"
done

pushd magisk
version="$(grep '^version=' module.prop  | cut -d= -f2)"
rm -f "../denylist-$version.zip"
zip -r9 "../denylist-$version.zip" .
popd
