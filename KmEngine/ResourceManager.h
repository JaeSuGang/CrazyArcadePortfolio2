#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UImage
{
	friend class UResourceManager;

public:
	void LoadFile(const char* lpszPath);
	BITMAP m_BitmapInfo;
	HDC getDC() const { return m_hDC; }

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

};

class UResourceManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	HDC GetImageDC(string strKey);
	UImage* GetImage(string strKey);
	void LoadFile(const char* lpszPath);

public:
	void Release();
	void Initialize(HWND hGameWindow);
	~UResourceManager();

private:
	unordered_map<string, UImage*> m_Images;
	unordered_map<string, USound*> m_Sounds;
	HWND m_hWnd;
};

