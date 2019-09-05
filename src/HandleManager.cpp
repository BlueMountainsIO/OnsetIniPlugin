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

#include "HandleManager.hpp"


HandleManager::~HandleManager()
{
	for (auto &h : _handles)
		Destroy(h);
}

Handle_t HandleManager::Create(std::string const &filename)
{
	auto handle = new Handle(filename);
	handle->File.read(handle->Data);

	_handles.insert(handle);

	return handle;
}

bool HandleManager::Destroy(Handle_t handle)
{
	if (_handles.erase(handle) == 0)
		return false;

	delete handle;
	return true;
}
