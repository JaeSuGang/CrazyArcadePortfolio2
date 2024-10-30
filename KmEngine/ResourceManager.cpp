#include "stdafx.h"
#include "ResourceManager.h"

void UResourceManager::LoadFile(const char* lpszPath)
{
	string strPath = lpszPath;
	LOWER_STRING(strPath);
	std::filesystem::path Path = strPath;
	
	if (Path.extension().string() == ".bmp")
	{
		UImage* Image = new UImage{};
		Image->Initialize(m_hWnd);
		Image->LoadFile(lpszPath);

		pair<string, UImage*> PairToInsert{strPath, Image};
		m_Images.insert(PairToInsert);
		return;
	}
}

void UResourceManager::Release()
{
	auto ImageIter = m_Images.begin();
	while (ImageIter != m_Images.end())
	{
		SAFE_DELETE(ImageIter->second);
		++ImageIter;
	}

	auto SoundIter = m_Sounds.begin();
	while (SoundIter != m_Sounds.end())
	{
		SAFE_DELETE(SoundIter->second);
		++SoundIter;
	}
}

void UResourceManager::Initialize(HWND hGameWindow)
{
	m_hWnd = hGameWindow;
}

UResourceManager::~UResourceManager()
{
	this->Release();
}

void UImage::LoadFile(const char* lpszPath)
{
	HDC TempDC = GetDC(m_hGameWindow);
	m_hDC = CreateCompatibleDC(TempDC);
	m_hBitmap = (HBITMAP)LoadImage(0, lpszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (m_hBitmap == 0)
	{
		SHOW_ERROR(("UImage::LoadFile, 존재하지 않는 경로입니다, " + string(lpszPath)).c_str());
	}

	SelectObject(m_hDC, m_hBitmap);

	ReleaseDC(m_hGameWindow, TempDC);
}

void UImage::Release()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hDC);
}

void UImage::Initialize(HWND hGameWindow)
{
	m_hGameWindow = hGameWindow;
}

UImage::~UImage()
{
	this->Release();
}
