#pragma once
#include "stdafx.h"
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
	FVector2D m_ImageOffset;
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
	void LoadFile(string strPath);
	void LoadFolder(string strPath);
	void LoadAll();

public:
	void Release();
	void Initialize(HWND hGameWindow);
	UResourceManager();
	~UResourceManager();

private:
	unordered_map<string, UImage*> m_Images;
	unordered_map<string, USound*> m_Sounds;
	HWND m_hWnd;
};

