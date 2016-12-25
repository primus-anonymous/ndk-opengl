#ifndef NDK_FILEREADER_H
#define NDK_FILEREADER_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>
#include "Png.h"

extern "C" {
#include "png.h"
#include <setjmp.h>
}

class AssetsReader {
private:

    AAssetManager* mgr;

public:

    AssetsReader( AAssetManager* mgr);

    Png readPng(const std::string &fileName);

    std::string readString(const std::string &fileName) const;

    virtual ~AssetsReader();
};

#endif //NDK_FILEREADER_H
