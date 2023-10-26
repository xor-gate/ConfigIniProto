#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ConfigFormat.h"
#include "ConfigStructs.h"
#include "ConfigIni.h"

void
print_buffer(unsigned char *buffer, size_t size)
{
    for (size_t j = 0; j < size; j++) {
        printf(" %02x", buffer[j]);
    }
}

size_t
struct_pack(struct ConfigFormat *fmt, void *structure, unsigned char *buffer)
{ 
    size_t pos = 0;

    for (size_t i = 0; i < fmt->num_members; i++) {
        memcpy(buffer+pos, ((unsigned char*)structure)+fmt->offsets[i], fmt->sizes[i]);
        pos += fmt->sizes[i];
    }

    return pos;
}

size_t
struct_unpack(struct ConfigFormat *fmt, unsigned char *buffer, void *structure)
{
    size_t pos = 0;

    for (size_t i = 0; i < fmt->num_members; i++) {
        memcpy(((unsigned char*)structure)+fmt->offsets[i], buffer+pos, fmt->sizes[i]);
        pos += fmt->sizes[i];
    }

    return pos;
}

void
struct_print(const struct ConfigFormat *fmt, void *structure)
{
    printf("%s:\n", fmt->struct_name);
    for (size_t i = 0; i < fmt->num_members; i++) {
        printf("\t%s: %zu %zu =", fmt->names[i], fmt->offsets[i], fmt->sizes[i]);
        print_buffer(((unsigned char*)structure)+fmt->offsets[i], fmt->sizes[i]);
        printf("\n");
    }
}


int
main(void)
{
	char IniBuffer[4096];

	struct ConfigCamera cc = {.Version = 1, .SerialNr = "123456"};

	printf("Written ini file:\n\n");
	ConfigIniWrite(IniBuffer, sizeof(IniBuffer), &ConfigCameraFormat, &cc);
	printf("%s", IniBuffer);

	memset(&cc, 0, sizeof(cc));

	ConfigIniParse(&cc, &ConfigCameraFormat, IniBuffer);
	struct_print(&ConfigCameraFormat, &cc);

	return 0;
}
