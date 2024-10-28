#pragma once
#include "Object.h"

using std::unordered_map;

class UEngineSubsystem;
class UKeyManager;

class UEngine : public UObject
{
public:
	UKeyManager* GetKeyManager();

private:
	unordered_map<string, UEngineSubsystem*> m_Managers;
};

