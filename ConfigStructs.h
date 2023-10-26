#ifndef CONFIG_STRUCTS_H__
#define CONFIG_STRUCTS_H__

#define CONFIG_STRUCT_NAME ConfigCamera
#define CONFIG_STRUCT_FIELDS \
    X_U32(Version) \
    X_STR(32, SerialNr)
#include "ConfigFormatGen.h"

#endif // CONFIG_STRUCTS_H__
