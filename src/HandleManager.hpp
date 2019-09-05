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

#pragma once

#include <PluginSDK.h>

#include "Singleton.hpp"

#include <memory>
#include <string>
#include <unordered_set>

#include "ini.hpp"


struct Handle
{
	Handle(std::string const &filename) : File(filename)
	{ }

	mINI::INIFile File;
	mINI::INIStructure Data;
};

using Handle_t = Handle *;

class HandleManager : public Singleton<HandleManager>
{
	friend class Singleton<HandleManager>;
private:
	HandleManager() = default;
	~HandleManager();

private:
	std::unordered_set<Handle_t> _handles;

public:
	Handle_t Create(std::string const &filename);
	bool Destroy(Handle_t handle);
	inline bool IsValid(Handle_t handle)
	{
		return _handles.find(handle) != _handles.end();
	}
};
