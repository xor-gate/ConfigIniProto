#ifndef CONFIG_INI_H__
#define CONFIG_INI_H__

#include "ConfigFormat.h"

void ConfigIniParse(void *Structure, const struct ConfigFormat *Format, const char *Data);
void ConfigIniWrite(char *Buffer, const size_t BufferLen, const struct ConfigFormat *Format, void *Structure);

#endif // CONFIG_INI_H__
