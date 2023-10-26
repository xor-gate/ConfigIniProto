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
	#define X_U32(L) uint32_t L;
	#define X_STR(L, R) char R[L];
	CONFIG_STRUCT_FIELDS
	#undef X_U32
	#undef X_STR
};

static const struct ConfigFormat CAT(CONFIG_STRUCT_NAME, Format) = {

    .struct_name = STR(CONFIG_STRUCT_NAME),

    .num_members = (
        #define X_U32(L) 1 +
	#define X_STR(L, R) 1+
        CONFIG_STRUCT_FIELDS
        #undef X_U32
	#undef X_STR
    0),

    .struct_size = sizeof(struct CONFIG_STRUCT_NAME),

    .packed_size = (
        #define X_U32(L) sizeof(uint32_t) +
        #define X_STR(L, R) L +
        CONFIG_STRUCT_FIELDS
        #undef X_U32
	#undef X_STR
    0),

    .offsets = (size_t[]){
        #define X_U32(L) offsetof(struct CONFIG_STRUCT_NAME, L),
	#define X_STR(L, R) offsetof(struct CONFIG_STRUCT_NAME, R)
        CONFIG_STRUCT_FIELDS
        #undef X_U32
	#undef X_STR
    },

    .sizes = (size_t []){
        #define X_U32(L) sizeof(uint32_t),
	#define X_STR(L, R) L,
        CONFIG_STRUCT_FIELDS
        #undef X_U32
	#undef X_STR
    },

    .types = (enum ConfigFormatFieldTypes []){
	#define X_U32(L) CONFIG_FORMAT_FIELD_TYPE_U32,
	#define X_STR(L, R) CONFIG_FORMAT_FIELD_TYPE_STR,
	CONFIG_STRUCT_FIELDS
	#undef X_U32
	#undef X_STR
    },

    .names = (char const *[]){
        #define X_U32(R) #R,
        #define X_STR(L, R) #R,
        CONFIG_STRUCT_FIELDS
        #undef X_U32
	#undef X_STR
    },
};

#undef CONFIG_STRUCT_FIELDS
#undef CONFIG_STRUCT_NAME
#undef STR_NOEXPAND
#undef STR
#undef CAT_NOEXPAND
#undef CAT
