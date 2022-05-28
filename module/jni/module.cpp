#include <cstdlib>
#include <string>
#include <android/log.h>

#include "zygisk.hpp"
#include "module.h"

namespace denylist {

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
        if ((api->getFlags() & zygisk::PROCESS_ON_DENYLIST) != 0) {
            api->setOption(zygisk::FORCE_DENYLIST_UNMOUNT);
        }
        api->setOption(zygisk::DLCLOSE_MODULE_LIBRARY);
    }
};

}

REGISTER_ZYGISK_MODULE(denylist::DenylistUnmount)
