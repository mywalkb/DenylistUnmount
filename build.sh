#!/usr/bin/env bash

set -euo pipefail

build_mode="${1:-release}"

cd "$(dirname "$0")"

pushd module
rm -fr libs obj
debug_mode=1
if [[ "$build_mode" == "release" ]]; then
    debug_mode=0
fi
ndk-build -j4 NDK_DEBUG=$debug_mode
popd

sumfile() {
    SUM=$(sha256sum "$1" | awk '{print $1}')
    echo -n $SUM > "$1.sha256"
}

mkdir -p magisk/zygisk
for arch in armeabi-v7a arm64-v8a x86 x86_64
do
    cp "module/libs/$arch/libdenylist.so" "magisk/zygisk/$arch.so"
    sumfile "magisk/zygisk/$arch.so"
done

pushd magisk
for FILE in module.prop service.sh customize.sh verify.sh sepolicy.rule
do
    sumfile $FILE
done

version="$(grep '^version=' module.prop  | cut -d= -f2)"
rm -f "../denylist-$version.zip"
zip -r9 "../denylist-$version.zip" .
popd
