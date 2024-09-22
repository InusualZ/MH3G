#include "version.h"

#include "revolution\os.h"
#include "revolution\stdio.h"

namespace version {

const SemVer MOD_VERSION = {0, 0, 1};

static char s_version_str[16];

void init() {
    sprintf(s_version_str, "%d.%d.%d", MOD_VERSION.major, MOD_VERSION.minor, MOD_VERSION.patch);
    OSReport("[MH3G] MH3G Mod v%s loaded\n", get_version_str());
}

s32 compare(const SemVer& v1, const SemVer& v2) {
    if (v1.major < v2.major) return -1;
    if (v1.major > v2.major) return 1;
    if (v1.minor < v2.minor) return -1;
    if (v1.minor > v2.minor) return 1;
    if (v1.patch < v2.patch) return -1;
    if (v1.patch > v2.patch) return 1;
    return 0;
}

const char* get_version_str() { return s_version_str; }

}
