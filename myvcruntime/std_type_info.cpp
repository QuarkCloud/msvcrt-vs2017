//
// std_type_info.cpp
//
//       Copyright (c) Microsoft Corporation. All rights reserved.
//
// Definitions of the std::type_info implementation functions, used for
// Run-Time Type Information (RTTI).
//
#include <vcruntime_internal.h>
#include <vcruntime_string.h>
#include <vcruntime_typeinfo.h>
//#include <undname.h>





extern "C" int __cdecl __std_type_info_compare(
    __std_type_info_data const* const lhs,
    __std_type_info_data const* const rhs
    )
{
    if (lhs == rhs)
    {
        return 0;
    }

    return strcmp(lhs->_DecoratedName + 1, rhs->_DecoratedName + 1);
}

extern "C" size_t __cdecl __std_type_info_hash(
    __std_type_info_data const* const data
    )
{
    // FNV-1a hash function for the undecorated name

    #ifdef _WIN64
    static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
    size_t const fnv_offset_basis = 14695981039346656037ULL;
    size_t const fnv_prime        = 1099511628211ULL;
    #else
    static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
    size_t const fnv_offset_basis = 2166136261U;
    size_t const fnv_prime        = 16777619U;
    #endif

    size_t value = fnv_offset_basis;
    for (char const* it = data->_DecoratedName + 1; *it != '\0'; ++it)
    {
        value ^= static_cast<size_t>(static_cast<unsigned char>(*it));
        value *= fnv_prime;
    }

    #ifdef _WIN64
    static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
    value ^= value >> 32;
    #else
    static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
    #endif

    return value;
}

extern "C" char const* __cdecl __std_type_info_name(
    __std_type_info_data* const data,
    __type_info_node*     const root_node
    )
{
	return NULL;
}

// This function is called during module unload to clean up all of the undecorated
// name strings that were allocated by calls to name().
extern "C" void __cdecl __std_type_info_destroy_list(
    __type_info_node* const root_node
    )
{
    PSLIST_ENTRY current_node = InterlockedFlushSList(&root_node->_Header);
    while (current_node)
    {
        PSLIST_ENTRY const next_node = current_node->Next;
        _free_crt(current_node);
        current_node = next_node;
    }
}
