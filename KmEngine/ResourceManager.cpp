#include "stdafx.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "SoundManager.h"

HDC UResourceManager::GetImageDC(string strKey)
{
	LOWER_STRING(strKey);

	auto ImageIter = m_Images.find(strKey);
	if (ImageIter == m_Images.end())
	{
		SHOW_ERROR(("UResourceManager::GetImageDC, 존재하지 않는 Key입니다, " + strKey).data());
	}
	return ImageIter->second->getDC();
}

UImage* UResourceManager::GetImage(string strKey)
{
	LOWER_STRING(strKey);

	auto ImageIter = m_Images.find(strKey);
	if (ImageIter == m_Images.end())
	{
		return nullptr;
	}
	return ImageIter->second;
}

void UResourceManager::LoadFile(string strPath)
{
	LOWER_STRING(strPath);
	std::filesystem::path Path = strPath;
	
	if (Path.extension().string() == ".bmp")
	{
		UImage* Image = new UImage{};
		Image->Initialize(m_hWnd);
		Image->LoadFile(strPath);

		pair<string, UImage*> PairToInsert{strPath, Image};
		m_Images.insert(PairToInsert);
		return;
	}

	else if (Path.extension().string() == ".wav")
	{
		USound* Sound = new USound{};
		Sound->LoadFile(strPath);

		pair<string, USound*> PairToInsert{ strPath, Sound };
		m_Sounds.insert(PairToInsert);
		return;
	}
}

void UResourceManager::LoadFolder(string strPath)
{
	LOWER_STRING(strPath);
	std::filesystem::path WorkingDirectory = std::filesystem::current_path();
	std::filesystem::path Path{ strPath };
	Path = std::filesystem::relative(Path, WorkingDirectory);
	std::filesystem::directory_iterator DirIter{ WorkingDirectory.string()+ "\\" + Path.string()};

	while (!DirIter._At_end())
	{
		std::filesystem::path ChildPath = *DirIter;
		ChildPath = std::filesystem::relative(ChildPath, WorkingDirectory);

		if (DirIter->is_directory())
		{
			LoadFolder(ChildPath.string());
		}

		if (ChildPath.extension().string() == ".bmp")
		{
			LoadFile(ChildPath.string());
		}

		else if (ChildPath.extension().string() == ".wav")
		{
			LoadFile(ChildPath.string());
		}

		++DirIter;
	}
}

void UResourceManager::LoadAll()
{
	std::filesystem::path WorkingDirectory = std::filesystem::current_path();
	LoadFolder(WorkingDirectory.string() + "\\Resources");
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

UResourceManager::UResourceManager()
	:
	m_hWnd{},
	m_Images{},
	m_Sounds{}
{
}

UResourceManager::~UResourceManager()
{
	this->Release();
}

void UImage::LoadFile(string strPath)
{
	HDC TempDC = GetDC(m_hGameWindow);
	m_hDC = CreateCompatibleDC(TempDC);
	m_hBitmap = (HBITMAP)LoadImageA(0, strPath.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObjectA(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);

	if (m_hBitmap == 0)
	{
		SHOW_ERROR(("UImage::LoadFile, 존재하지 않는 경로입니다, " + strPath).c_str());
	}

	SelectObject(m_hDC, m_hBitmap);

	ReleaseDC(m_hGameWindow, TempDC);
}

HDC UImage::getDC() const
{
	return m_hDC;
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

void USound::LoadFile(string strPath)
{
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();

	if (strPath.find("bgm") != string::npos)
		SoundManager->m_FModSystem->createSound(strPath.data(), FMOD_LOOP_NORMAL, nullptr, &m_hSoundHandle);
	else
		SoundManager->m_FModSystem->createSound(strPath.data(), FMOD_LOOP_OFF, nullptr, &m_hSoundHandle);
}
