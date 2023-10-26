#include "ConfigFormat.h"
#include <string.h>

const struct ConfigFormatField *ConfigFormatGetFieldByName(const struct ConfigFormat *Format, const char *Name, void *Structure)
{
	static struct ConfigFormatField Field;

	for (size_t n = 0; n < Format->num_members; n++) {
		if (strcmp(Name, Format->names[n]) != 0) {
			continue;
		}

		Field.offset = Format->offsets[n];
		Field.size = Format->sizes[n];
		Field.type = Format->types[n];
		Field.name = Format->names[n];
		Field.value = Structure+Field.offset;

		return &Field;
	}

	return NULL;
}
