
# Denylist Unmount

![Build](https://shields.io/github/workflow/status/mywalkb/DenylistUnmount/Main?event=push&logo=github&label=Build) [![Download](https://img.shields.io/github/v/release/mywalkb/DenylistUnmount?color=orange&logoColor=orange&label=Download&logo=DocuSign)](https://github.com/mywalkb/DenylistUnmount/releases/latest) [![Total](https://shields.io/github/downloads/mywalkb/DenylistUnmount/total?logo=Bookmeter&label=Counts&logoColor=yellow&color=yellow)](https://github.com/mywalkb/DenylistUnmount/releases)


Magisk module to unmount the denylist processes

There is a better module [Shamiko](https://github.com/LSPosed/LSPosed.github.io/releases) but it's closed source.
This module unmount magisk and set some properties.

Is good for many cases. Magisk is hidden and can continue to inject code with LSPosed or other modules.

**Require Magisk v24.0+**

## How to use

- enable zygisk
- disable "Enforce DenyList"
- put app in DenyList

every app in denylist before start unmount magisk, so app can't detect magisk

## Whitelist based

Switch to whilelist: `setprop persist.unmount.white true`  
Turn off whilelist: `resetprop --delete persist.unmount.white`

Only app with granted root access will not have Magisk unmounted.  
Whitelist mode might slowed down system, only use if necessary

## Credits

- [Magisk](https://github.com/topjohnwu/Magisk/): makes all these possible
- [Safetynet-fix](https://github.com/kdrag0n/safetynet-fix): for the idea to unmount processes and inject code
- [Shamiko](https://github.com/LSPosed/LSPosed.github.io/releases): for the improvement in hiding strong parameters in getprop
