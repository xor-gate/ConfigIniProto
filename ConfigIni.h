#ifndef CONFIG_INI_H__
#define CONFIG_INI_H__

#include "ConfigFormat.h"

void ConfigIniParse(void *Structure, const struct ConfigFormat *Format, const char *Data);

#endif // CONFIG_INI_H__
