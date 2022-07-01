#include <cstdlib>
#include <string>
#include <android/log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "zygisk.hpp"
#include "module.h"

namespace denylist {

#define WHITELIST_FILE "/data/adb/modules/denylist_unmount/whitelist"

class DenylistUnmount : public zygisk::ModuleBase {
public:
    void onLoad(zygisk::Api *api, JNIEnv *env) override {
        this->api = api;
        this->env = env;
    }

    void preAppSpecialize(zygisk::AppSpecializeArgs *args) override {
        const char *rawProcess = env->GetStringUTFChars(args->nice_name, nullptr);
        if (rawProcess == nullptr) {
            return;
        }

        std::string process(rawProcess);
        env->ReleaseStringUTFChars(args->nice_name, rawProcess);

        preSpecialize(process);
    }

    void preServerSpecialize(zygisk::ServerSpecializeArgs *args) override {
        // Never tamper with system_server
        api->setOption(zygisk::DLCLOSE_MODULE_LIBRARY);
    }

private:
    zygisk::Api *api;
    JNIEnv *env;
    

    void preSpecialize(std::string process) {
        struct stat whitelist;
        bool whitelist_mode = false;
        uint32_t flags = api->getFlags();

        if (stat(WHITELIST_FILE, &whitelist) == 0) {
            whitelist_mode = true;
            LOGD("Whitelist mode");
        }

        if ((flags & zygisk::PROCESS_ON_DENYLIST) != 0 ||
            (whitelist_mode && (flags & zygisk::PROCESS_GRANTED_ROOT) == 0)) {
            api->setOption(zygisk::FORCE_DENYLIST_UNMOUNT);
        }
        api->setOption(zygisk::DLCLOSE_MODULE_LIBRARY);
    }
};

}

REGISTER_ZYGISK_MODULE(denylist::DenylistUnmount)
