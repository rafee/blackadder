/*-
 * Copyright (C) 2011  Oy L M Ericsson Ab, NomadicLab
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * See LICENSE and COPYING for more details.
 */

#include <blackadder.hpp>
extern "C" {
#include "blackadder_c.h"
}

//using namespace std;

/*
 * We use C macro magic to wrap the publish_*(), unpublish_*(),
 * subscribe_*() and unsubscribe_*() functions.
 */

_BA_FUNC_DEF(publish_scope)
_BA_FUNC_DEF(publish_info)
_BA_FUNC_DEF(unpublish_scope)
_BA_FUNC_DEF(unpublish_info)
_BA_FUNC_DEF(subscribe_scope)
_BA_FUNC_DEF(subscribe_info)
_BA_FUNC_DEF(unsubscribe_scope)
_BA_FUNC_DEF(unsubscribe_info)

_BA_FUNC_DEF_DATA(publish_data)

extern "C" ba_handle
ba_instance(int user_space)
{
    ba_handle ba = new (nothrow) _ba_handle;
    if (ba != NULL)
        ba->instance = Blackadder::Instance(user_space);
    return ba;
}

extern "C" void
ba_delete(ba_handle ba)
{
    if (ba != NULL) {
        if (ba->instance != NULL) {
            delete ((Blackadder *)ba->instance);
            ba->instance = NULL;
        }
        delete ba;
    }
}

extern "C" void
ba_disconnect(ba_handle ba)
{
    ((Blackadder *)ba->instance)->disconnect();
}

extern "C" void
ba_get_event(ba_handle ba, ba_event ev)
{
    ((Blackadder *)ba->instance)->getEvent(*((Event *)ev));
}

extern "C" ba_event
ba_event_new(void)
{
    return (ba_event)(new Event());
}

extern "C" void
ba_event_delete(ba_event ev)
{
    delete ((Event *)ev);
}

extern "C" void
ba_event_type(ba_event ev, unsigned char **type)
{
    *type = &((Event *)ev)->type;
}

extern "C" void
ba_event_id(ba_event ev, const char **id, unsigned int *id_len)
{
    *id = ((Event *)ev)->id.data();
    *id_len = ((Event *)ev)->id.length();
}

extern "C" void
ba_event_data(ba_event ev, void **data, unsigned int **data_len)
{
    *data = ((Event *)ev)->data;
    *data_len = &((Event *)ev)->data_len;
}

extern "C" const char*
chararray_to_hex(const char *str) {
	if (str == NULL) return NULL;
	string _s = chararray_to_hex(string(str));
	int _size = strlen(_s.c_str());
	char* ret = (char*)malloc(_size + 1); //Extra null termination char
	memcpy((void*)ret, (const void*)_s.c_str(), _size);
	// Manually add the null termination char
	ret[_size] = '\0';
	return ret;
}

extern "C" const char*
hex_to_chararray(const char *str) {
	if (str == NULL) return NULL;
	string _s = hex_to_chararray(string(str));
	int _size = strlen(_s.c_str());
	char* ret = (char*)malloc(_size + 1); //Extra null termination char
	memcpy((void*)ret, (const void*)_s.c_str(), _size);
	// Manually add the null termination char
	ret[_size] = '\0';
	return ret;
}

extern "C" Fnv64_t
ba_fnv1_64(const unsigned char *data, unsigned int n)
{
    return fnv1_64(data, n);
}

extern "C" Fnv64_t
ba_fnv1a_64(const unsigned char *data, unsigned int n)
{
    return fnv1a_64(data, n);
}

extern "C" char *
ba_fnv_chars(Fnv64_t *hash)
{
    return (char *)hash;
}
