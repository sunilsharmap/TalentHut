#include <stdbool.h>
#include <stdio.h>

/* This is the enum declaration where we want to have more details of the enum.
 * Here we have name, enum_type and enum_string parameters used to define an
 * enum JsonType. This is useful if you want to get the enum_type or
 * enum_string.
 */
#define JSON_TYPES(XX)                                                         \
    XX(JSON_NULL, "null", "JSON_NULL")                                         \
    XX(JSON_OBJECT, "object", "JSON_OBJECT")                                   \
    XX(JSON_ARRAY, "array", "JSON_ARRAY")                                      \
    XX(JSON_INT64, "int64", "JSON_INT64")                                      \
    XX(JSON_UINT64, "uint64", "JSON_UINT64")                                   \
    XX(JSON_UINT128, "uint128", "JSON_UINT128")                                \
    XX(JSON_DOUBLE, "double", "JSON_DOUBLE")                                   \
    XX(JSON_STRING, "string", "JSON_STRING")                                   \
    XX(JSON_TRUE, "true", "JSON_TRUE")                                         \
    XX(JSON_FALSE, "false", "JSON_FALSE")

#define enum_type(name, type, string) name,

typedef enum { JSON_TYPES(enum_type) } JsonType;

#undef enum_type

#define switch_case(name, x, y)                                                \
    case name:                                                                 \
        return y;

static const char *get_enum_string(JsonType type)
{
    switch (type) {
        JSON_TYPES(switch_case)
    default:
        return "unknown enum string";
    }
}

#undef switch_case

#define switch_case(name, x, y)                                                \
    case name:                                                                 \
        return x;

static const char *get_enum_type(JsonType type)
{
    switch (type) {
        JSON_TYPES(switch_case)
    default:
        return "unknown enum type";
    }
}

#undef switch_case

int main()
{
    JsonType json_type = JSON_UINT64;
    printf("%s enum value is %d and is of type '%s'.\n",
           get_enum_string(json_type), json_type, get_enum_type(json_type));

    return 0;
}