#pragma once
#include "stdafx.h"
#include "FMod/fmod.hpp"
#include "EngineSubsystem.h"

class UImage
{
	friend class UResourceManager;

public:
	void LoadFile(string strPath);
	BITMAP m_BitmapInfo;
	HDC getDC() const;

public:
	void Release();
	void Initialize(HWND hGameWindow);
	UImage() = default;
	~UImage();

private:
	HWND m_hGameWindow;
	HDC m_hDC;
	HBITMAP m_hBitmap;
};

class USound
{
public:
	void LoadFile(string strPath);

public:
	FMOD::Sound* m_hSoundHandle;
};

class UResourceManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	HDC GetImageDC(string strKey);
	UImage* GetImage(string strKey);
	void LoadFile(string strPath);
	void LoadFolder(string strPath);
	void LoadAll();

public:
	void Release();
	void Initialize(HWND hGameWindow);
	UResourceManager();
	~UResourceManager();

public:
	unordered_map<string, UImage*> m_Images;
	unordered_map<string, USound*> m_Sounds;
	HWND m_hWnd;
};

