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

#include <PluginSDK.h>
#include "Plugin.hpp"
#include "HandleManager.hpp"
#include "version.hpp"


hrzn::IServerPlugin* hrzn::Plugin::_instance = nullptr;


EXPORT(int) OnPluginGetApiVersion()
{
	return PLUGIN_API_VERSION;
}

EXPORT(void) OnPluginCreateInterface(hrzn::IBaseInterface *PluginInterface)
{
	hrzn::Plugin::Init(PluginInterface);
}

EXPORT(int) OnPluginStart()
{
	// initialize plugin singleton
	Plugin::Get();

	hrzn::Plugin::Get()->Log("ini-plugin: v" PLUGIN_VERSION " successfully loaded.");
	return PLUGIN_API_VERSION;
}

EXPORT(void) OnPluginStop()
{
	hrzn::Plugin::Get()->Log("ini-plugin: Unloading plugin...");

	HandleManager::Singleton::Destroy();
	Plugin::Singleton::Destroy();

	hrzn::Plugin::Get()->Log("ini-plugin: Plugin unloaded.");
	hrzn::Plugin::Destroy();
}

EXPORT(void) OnPluginTick(float DeltaSeconds)
{
	(void)DeltaSeconds; // unused
}

EXPORT(void) OnPackageLoad(const char *PackageName, lua_State *L)
{
	(void)PackageName; // unused

	for (auto const &f : Plugin::Get()->GetFunctions())
		Lua::RegisterPluginFunction(L, std::get<0>(f), std::get<1>(f));
}

EXPORT(void) OnPackageUnload(const char *PackageName)
{
	(void)PackageName; // unused
}
