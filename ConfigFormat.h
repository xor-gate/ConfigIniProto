#ifndef CONFIG_FORMAT_H__
#define CONFIG_FORMAT_H__

#include <stdlib.h>

enum ConfigFormatFieldTypes
{
	CONFIG_FORMAT_FIELD_TYPE_U32,
	CONFIG_FORMAT_FIELD_TYPE_STR
};

struct ConfigFormat {
	char const *struct_name;
	size_t num_members;
	size_t struct_size;
	size_t packed_size;
	size_t *offsets;
	size_t *sizes;
	enum ConfigFormatFieldTypes *types;
	char const **names;
};

struct ConfigFormatField {
	size_t offset;
	size_t size;
	enum ConfigFormatFieldTypes type;
	const char *name;
	void *value;
};

const struct ConfigFormatField *ConfigFormatGetFieldByName(const char *FieldName, const struct ConfigFormat *Format, void *Structure);
const struct ConfigFormatField *ConfigFormatGetFieldByNr(const size_t FieldNr, const struct ConfigFormat *Format, void *Structure);

#endif // CONFIG_FORMAT_H__
