#include "ConfigIni.h"
#include "ConfigFormat.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CONFIG_INI_MAX_KEY_LEN 64
#define CONFIG_INI_MAX_VALUE_LEN 128

static void ConfigIniParseKeyValue(void *Structure, const struct ConfigFormat *Format, const char *Key, const char *Value)
{
	const struct ConfigFormatField *Field = ConfigFormatGetFieldByName(Format, Key, Structure);
	printf("Parsed key=\"%s\", value=\"%s\"\n", Key, Value);
	if (!Field) {
		return;
	}
	printf("Found matching field in struct\n");
}

void ConfigIniParse(void *Structure, const struct ConfigFormat *Format, const char *Data)
{
	const char *Line = Data;

	while (*Line) {
		char Key[CONFIG_INI_MAX_KEY_LEN];
		char Value[CONFIG_INI_MAX_VALUE_LEN];
		size_t i = 0;

		// Parse Key
		while (*Line && *Line != '=') {
			if (i < CONFIG_INI_MAX_KEY_LEN - 1) {
				Key[i++] = *Line;
			}
			Line++;
		}
		Key[i] = '\0';

		if (*Line == '=') {
			i = 0;
			Line++; // Move past '='

			// Parse Value
			while (*Line && *Line != '\n') {
				if (i < CONFIG_INI_MAX_VALUE_LEN - 1) {
					Value[i++] = *Line;
				}
				Line++;
			}
			Value[i] = '\0';

			ConfigIniParseKeyValue(Structure, Format, Key, Value);
		}

		// Move to the next Line
		while (*Line && *Line != '\n') {
			Line++;
		}

		if (*Line == '\n') {
			Line++; // Move past '\n'
		}
	}
}
