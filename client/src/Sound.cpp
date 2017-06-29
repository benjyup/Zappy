//
// Created by peixot_b on 31/05/17.
//

#include "Sound.hpp"
#include "irrKlang.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Sound::Sound()
{
  _soundEngine = irrklang::createIrrKlangDevice();
  _soundEngine->setSoundVolume(0.5);
}

Sound::~Sound()
{
  _soundEngine->drop();
}

irrklang::ISoundEngine *Sound::get_soundEngine() const
{
  return _soundEngine;
}

void			Sound::setGameMusic()
{
  _soundEngine->stopAllSounds();
  _soundEngine->play2D("./GFX/wave.ogg", true);
}

void			Sound::setVolume(irrklang::ik_f32 volume)
{
  _soundEngine->setSoundVolume(volume);
}

void			Sound::ejectSound()
{
  _soundEngine->play2D("./GFX/whoosh1.wav", false);
}

void			Sound::ritualSound()
{
  _soundEngine->play2D("./GFX/ammo_loop_off1.wav", false);
}

void			Sound::eatSound()
{
  _soundEngine->play2D("./GFX/RabbitEating.ogg", false);
}

void			Sound::lvlUpSound()
{
  _soundEngine->play2D("./GFX/chipquest.wav", false);
}