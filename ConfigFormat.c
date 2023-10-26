#include "ConfigFormat.h"
#include <string.h>

static struct ConfigFormatField Field;

static void ConfigFormatCopyField(const size_t FieldNr, const struct ConfigFormat *Format, void *Structure)
{
	Field.offset = Format->offsets[FieldNr];
	Field.size = Format->sizes[FieldNr];
	Field.type = Format->types[FieldNr];
	Field.name = Format->names[FieldNr];
	Field.value = Structure+Field.offset;
}

const struct ConfigFormatField *ConfigFormatGetFieldByName(const char *FieldName, const struct ConfigFormat *Format, void *Structure)
{
	for (size_t FieldNr = 0; FieldNr < Format->num_members; FieldNr++) {
		if (strcmp(FieldName, Format->names[FieldNr]) != 0) {
			continue;
		}

		ConfigFormatCopyField(FieldNr, Format, Structure);
		return &Field;
	}

	return NULL;
}

const struct ConfigFormatField *ConfigFormatGetFieldByNr(const size_t FieldNr, const struct ConfigFormat *Format, void *Structure)
{
	if (FieldNr > Format->num_members) {
		return NULL;
	}

	ConfigFormatCopyField(FieldNr, Format, Structure);
	return &Field;
}
