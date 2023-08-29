#pragma once
#include "std.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment( lib, "fmod_vc.lib")


class Sound
{
public:
	std::wstring   m_csName;
	std::wstring   m_csPath;
public:
	FMOD::System* m_pSystem;
	//  사운드파일단위로 필요하다.
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
public:
	void  SetName(std::wstring key)
	{
		m_csName = key;
	};
	void  Set(FMOD::System* pSystem) { m_pSystem = pSystem; }
	bool  Load(std::wstring filename);
	bool  Init();
	bool  Frame();
	bool  Release();
public:
	void  Play(bool bLoop = true);
	void  PlayEffect();
	void  Stop();
	void  Paused();
	void  Volume();
	void  VolumeUp();
	void  VolumeDown();
};

class SoundMgr
{
	FMOD::System* m_pSystem;
	using tList = std::map< std::wstring,
		std::unique_ptr<Sound>>;
public:
	static SoundMgr& GetInstance()
	{
		static SoundMgr input;
		return input;
	}
	tList   m_list;
public:
	bool  Frame();
	bool  Release();
	Sound* Load(std::wstring szFilepath);
	Sound* GetPtr(std::wstring key);
	bool  Get(std::wstring key, Sound& ret);
private:
	SoundMgr();
public:
	virtual ~SoundMgr();
};

#define I_Sound SoundMgr::GetInstance()
