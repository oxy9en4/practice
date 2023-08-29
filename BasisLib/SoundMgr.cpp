#include "SoundMgr.h"
#include "std.h"
#include <tchar.h>
#include "SWriter.h"
bool  Sound::Init()
{
	return true;
}
bool  Sound::Load(std::wstring filename)
{
	std::string file = wtm(filename);
	FMOD_RESULT hr = m_pSystem->createSound(file.c_str(),
		FMOD_DEFAULT, 0, &m_pSound);
	return true;
}
bool  Sound::Frame()
{
	TCHAR m_szBuffer[256] = { 0, };
	unsigned int ms = 0;
	unsigned int total = 0;
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	m_pSound->getLength(&total, FMOD_TIMEUNIT_MS);
	_stprintf_s(m_szBuffer, _T(" 경과시간[%02d:%02d:%02d], 파일크기[%02d:%02d:%02d]"),
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 % 60,
		total / 1000 / 60,
		total / 1000 % 60,
		total / 10 % 60);
	SWriter::GetInstance().AddText(m_szBuffer, 0, 100);
	return true;
}
bool  Sound::Release()
{
	if (m_pSound)m_pSound->release();

	return true;
}

void  Sound::Play(bool bLoop)
{
	if (m_pChannel == nullptr)
	{
		if (bLoop)m_pSound->setMode(FMOD_LOOP_NORMAL);
		else m_pSound->setMode(FMOD_LOOP_OFF);
		m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	}
	else
	{
		bool play;
		m_pChannel->isPlaying(&play);
		if (play == false)
		{
			if (bLoop)m_pSound->setMode(FMOD_LOOP_NORMAL);
			else m_pSound->setMode(FMOD_LOOP_OFF);
			m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		}
	}
}
void  Sound::PlayEffect()
{
	m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
}
void  Sound::Stop()
{
	m_pChannel->stop();
}
void  Sound::Paused()
{
	bool paused;
	m_pChannel->getPaused(&paused);
	m_pChannel->setPaused(!paused);
}
void  Sound::VolumeUp()
{
	float fVolume;
	m_pChannel->getVolume(&fVolume);
	fVolume += 0.33f * g_fSPF;
	fVolume = min(1.0f, fVolume);
	m_pChannel->setVolume(fVolume);
}
void  Sound::VolumeDown()
{
	float fVolume;
	m_pChannel->getVolume(&fVolume);
	fVolume -= 0.33f * g_fSPF;
	fVolume = max(0.0f, fVolume);
	m_pChannel->setVolume(fVolume);
}





Sound* SoundMgr::Load(std::wstring szPullfilePath)
{
	std::size_t found = szPullfilePath.find_last_of(L"/");
	std::wstring path = szPullfilePath.substr(0, found + 1);
	std::wstring key = szPullfilePath.substr(found + 1);
	Sound* data = GetPtr(key);
	if (data != nullptr)
	{
		return data;
	}
	std::unique_ptr<Sound> newData = std::make_unique<Sound>();
	newData->Set(m_pSystem);
	newData->SetName(key);
	//std::unique_ptr<Sound> copyData = std::move(newData);
	if (newData->Load(szPullfilePath))
	{
		m_list.insert(std::make_pair(key, std::move(newData)));
		return GetPtr(key);
	}
	return nullptr;
}
Sound* SoundMgr::GetPtr(std::wstring key)
{
	auto iter = m_list.find(key);
	if (m_list.end() == iter)
	{
		return nullptr;
	}
	return iter->second.get();
}
bool SoundMgr::Get(std::wstring key, Sound& ret)
{
	auto iter = m_list.find(key);
	if (m_list.end() == iter)
	{
		return false;
	}
	ret = *(iter->second);
	return true;
}
bool SoundMgr::Release()
{
	for (auto& data : m_list)
	{
		data.second->Release();
	}
	m_list.clear();

	m_pSystem->close();
	m_pSystem->release();
	return true;
}
bool SoundMgr::Frame()
{
	m_pSystem->update();
	for (auto& data : m_list)
	{
		data.second->Frame();
	}
	return true;
}
SoundMgr::SoundMgr()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
}
SoundMgr::~SoundMgr()
{
	Release();
}