// Original from https://natecraun.net/articles/struct-iteration-through-abuse-of-the-c-preprocessor.html
#include <stdint.h>
#include "ConfigFormat.h"

/* Error Checking */
#ifndef CONFIG_STRUCT_NAME
    #error "Did not define CONFIG_STRUCT_NAME before including ConfigFormat.h"
#endif

#ifndef CONFIG_STRUCT_FIELDS
    #error "Did not define CONFIG_STRUCT_FIELDS before including ConfigFormat.h"
#endif

#define STR_NOEXPAND(A) #A
#define STR(A) STR_NOEXPAND(A)

#define CAT_NOEXPAND(A, B) A ## B
#define CAT(A, B) CAT_NOEXPAND(A, B)

struct CONFIG_STRUCT_NAME {
    #define X(L, R) L R;
    CONFIG_STRUCT_FIELDS
    #undef X
};

static const struct ConfigFormat CAT(CONFIG_STRUCT_NAME, Format) = {

    .struct_name = STR(CONFIG_STRUCT_NAME),

    .num_members = (
        #define X(L, R) 1 +
        CONFIG_STRUCT_FIELDS
        #undef X
    0),

    .struct_size = sizeof(struct CONFIG_STRUCT_NAME),

    .packed_size = (
        #define X(L, R) sizeof(L) +
        CONFIG_STRUCT_FIELDS
        #undef X
    0),

    .offsets = (size_t[]){
        #define X(L, R) offsetof(struct CONFIG_STRUCT_NAME, R),
        CONFIG_STRUCT_FIELDS
        #undef X
    },

    .sizes = (size_t []){
        #define X(L, R) sizeof(L),
        CONFIG_STRUCT_FIELDS
        #undef X
    },

    .types = (enum ConfigFormatFieldTypes []){
	#define X(L, R) CONFIG_FORMAT_FIELD_TYPE_U32,
	CONFIG_STRUCT_FIELDS
	#undef X
    },

    .names = (char const *[]){
        #define X(L, R) #R,
        CONFIG_STRUCT_FIELDS
        #undef X
    },
};

#undef CONFIG_STRUCT_FIELDS
#undef CONFIG_STRUCT_NAME
#undef STR_NOEXPAND
#undef STR
#undef CAT_NOEXPAND
#undef CAT
