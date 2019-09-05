/*
Copyright (C) 2019 Blue Mountains GmbH

This program is free software: you can redistribute it and/or modify it under the terms of the Onset
Open Source License as published by Blue Mountains GmbH.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the Onset Open Source License for more details.

You should have received a copy of the Onset Open Source License along with this program. If not,
see https://bluemountains.io/Onset_OpenSourceSoftware_License.txt
*/

#include "Plugin.hpp"
#include "HandleManager.hpp"

#include <string>


#ifdef LUA_DEFINE
# undef LUA_DEFINE
#endif
#define LUA_DEFINE(name) Define(#name, [](lua_State *L) -> int


Handle_t LuaGetHandle(lua_State *state, int idx)
{
	int type = lua_type(state, idx);
	if (type == LUA_TLIGHTUSERDATA)
	{
		return static_cast<Handle *>(lua_touserdata(state, idx));
	}
	else
	{
		luaL_argerror(state, idx, "expected light userdata argument");
	}
	return nullptr;
}

Plugin::Plugin()
{
	LUA_DEFINE(ini_open)
	{
		std::string filename;
		Lua::ParseArguments(L, filename);

		auto handle = HandleManager::Get()->Create(filename);

		lua_pushlightuserdata(L, handle);
		return 1;
	});

	LUA_DEFINE(ini_close)
	{
		auto handle = LuaGetHandle(L, 1);

		if (!HandleManager::Get()->IsValid(handle))
			return 0;

		HandleManager::Get()->Destroy(handle);
		return 0;
	});

	LUA_DEFINE(ini_read)
	{
		auto handle = LuaGetHandle(L, 1);

		if (!HandleManager::Get()->IsValid(handle))
			return 0;

		std::string section, key;
		Lua::ParseArguments<2>(L, section, key);

		if (!handle->Data.has(section))
			return 0;

		auto &keys = handle->Data[section];
		if (!keys.has(key))
			return 0;

		return Lua::ReturnValues(L, keys[key]);
	});

	LUA_DEFINE(ini_write)
	{
		auto handle = LuaGetHandle(L, 1);

		if (!HandleManager::Get()->IsValid(handle))
			return 0;

		std::string section, key, value;
		Lua::ParseArguments<2>(L, section, key, value);

		handle->Data[section][key] = value;
		handle->File.write(handle->Data, true);

		return 0;
	});
}
