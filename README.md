# Denylist Unmount

Magisk module to unmount the denylist processes

There is a better module [Shamiko](https://github.com/LSPosed/LSPosed.github.io/releases) but it's closed source.
This module unmount magisk and set some properties.

Is good for many cases. Magisk is hidden and can continue to inject code with LSPosed or other modules.

**Require Magisk v24.0+**

## How to use

- enable zygisk
- disable enforce zygisk
- put app in denylist

every app in denylist before start unmount magisk, so app can't detect magisk

## Credits

- [Magisk](https://github.com/topjohnwu/Magisk/): makes all these possible
- [Safetynet-fix](https://github.com/kdrag0n/safetynet-fix): for the idea to unmount processes and inject code
- [Shamiko](https://github.com/LSPosed/LSPosed.github.io/releases): for the improvement in hiding strong parameters in getprop
