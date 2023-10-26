#include "ConfigIni.h"
#include "ConfigFormat.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define CONFIG_INI_MAX_KEY_LEN   64
#define CONFIG_INI_MAX_VALUE_LEN 128

// A safe snprintf which returns the remaining buffer size
static void snprintf_s(char *restrict buffer, size_t *bufsz, const char *restrict format, ...)
{
	if (!bufsz) {
		return;
	}

	va_list ap;

	va_start(ap, format);
	*bufsz -= vsnprintf(buffer, *bufsz, format, ap);
	va_end(ap);
}

static void ConfigIniParseKeyValue(void *Structure, const struct ConfigFormat *Format, const char *Key, const char *Value)
{
	const struct ConfigFormatField *Field;

	Field = ConfigFormatGetFieldByName(Key, Format, Structure);
	if (!Field) {
		return;
	}

	switch (Field->type) {
	case CONFIG_FORMAT_FIELD_TYPE_U32:
		*((uint32_t*)Field->value) = (uint32_t)atoi(Value);
		break;
	case CONFIG_FORMAT_FIELD_TYPE_STR:
		snprintf((char *)Field->value, Field->size, "%s", Value);
		break;
	}
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

void ConfigIniWrite(char *Buffer, const size_t BufferLen, const struct ConfigFormat *Format, void *Structure)
{
	size_t BufferRemSize = BufferLen;

	for (size_t FieldNr = 0; FieldNr < Format->num_members; FieldNr++) {
		const struct ConfigFormatField *Field = ConfigFormatGetFieldByNr(FieldNr, Format, Structure);
		if (!Field) {
			break;
		}

		switch (Field->type) {
		case CONFIG_FORMAT_FIELD_TYPE_U32:
			snprintf_s(&Buffer[BufferLen-BufferRemSize], &BufferRemSize, "%s=%"PRIu32"\n", Field->name, *((uint32_t*)Field->value));
			break;
		case CONFIG_FORMAT_FIELD_TYPE_STR:
			snprintf_s(&Buffer[BufferLen-BufferRemSize], &BufferRemSize, "%s=%s\n", Field->name, (char*)Field->value);
			break;
		}
	}
}
