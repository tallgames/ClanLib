/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "Sound/precomp.h"
#include "API/Sound/soundoutput.h"
#include "API/Sound/soundoutput_description.h"
#include "API/Sound/soundfilter.h"
#include "API/Sound/sound.h"
#include "API/Core/System/thread.h"
#include "soundoutput_impl.h"

#ifdef WIN32
#include "Win32/soundoutput_win32.h"
#else
#ifdef __APPLE__
#include "MacOSX/soundoutput_macosx.h"
#else
#include "Unix/soundoutput_oss.h"
#endif
#endif

#ifdef HAVE_ALSA_ASOUNDLIB_H
#include "Unix/soundoutput_alsa.h"
#endif

namespace clan
{

/////////////////////////////////////////////////////////////////////////////
// SoundOutput construction:

SoundOutput::SoundOutput()
{
}

SoundOutput::SoundOutput(int mixing_frequency, int latency)
{
	SoundOutput_Description desc;
	desc.set_mixing_frequency(mixing_frequency);
	desc.set_mixing_latency(latency);
	operator =(SoundOutput(desc));
}

SoundOutput::SoundOutput(const SoundOutput_Description &desc)
{
#ifdef WIN32
	std::shared_ptr<SoundOutput_Impl> soundoutput_impl(new SoundOutput_Win32(desc.get_mixing_frequency(), desc.get_mixing_latency()));
	impl = soundoutput_impl;
#else
#ifdef __APPLE__
	std::shared_ptr<SoundOutput_Impl> soundoutput_impl(new SoundOutput_MacOSX(desc.get_mixing_frequency(), desc.get_mixing_latency()));
	impl = soundoutput_impl;
#else
#if defined(__linux__) && defined(HAVE_ALSA_ASOUNDLIB_H)
	// Try building ALSA

	std::shared_ptr<SoundOutput_Impl> alsa_impl(new SoundOutput_alsa(desc.get_mixing_frequency(), desc.get_mixing_latency()));
	if ( ( (SoundOutput_alsa *) (alsa_impl.get()))->handle)
	{
		impl = alsa_impl;
	}
	else
	{
		alsa_impl.reset();
	}

	if (!impl)
	{
		std::shared_ptr<SoundOutput_Impl> soundoutput_impl(new SoundOutput_OSS(desc.get_mixing_frequency(), desc.get_mixing_latency()));
		impl = soundoutput_impl;
	}
#else
    std::shared_ptr<SoundOutput_Impl> soundoutput_impl(new SoundOutput_OSS(desc.get_mixing_frequency(), desc.get_mixing_latency()));
    impl = soundoutput_impl;
#endif
#endif
#endif
	Sound::select_output(*this);
}

SoundOutput::~SoundOutput()
{
}

SoundOutput::SoundOutput(const std::weak_ptr<SoundOutput_Impl> impl)
: impl(impl.lock())
{
}
/////////////////////////////////////////////////////////////////////////////
// SoundOutput attributes:

void SoundOutput::throw_if_null() const
{
	if (!impl)
		throw Exception("SoundOutput is null");
}

const std::string &SoundOutput::get_name() const
{
	MutexSection mutex_lock(&impl->mutex);
	return impl->name;
}

int SoundOutput::get_mixing_frequency() const
{
	MutexSection mutex_lock(&impl->mutex);
	return impl->mixing_frequency;
}

int SoundOutput::get_mixing_latency() const
{
	MutexSection mutex_lock(&impl->mutex);
	return impl->mixing_latency;
}

float SoundOutput::get_global_volume() const
{
	MutexSection mutex_lock(&impl->mutex);
	return impl->volume;
}

float SoundOutput::get_global_pan() const
{
	MutexSection mutex_lock(&impl->mutex);
	return impl->pan;
}

/////////////////////////////////////////////////////////////////////////////
// SoundOutput operations:

void SoundOutput::stop_all()
{
}
	
void SoundOutput::set_global_volume(float volume)
{
	if (impl)
	{
		MutexSection mutex_lock(&impl->mutex);
		impl->volume = volume;
	}
}

void SoundOutput::set_global_pan(float pan)
{
	if (impl)
	{
		MutexSection mutex_lock(&impl->mutex);
		impl->pan = pan;
	}
}

void SoundOutput::add_filter(SoundFilter &filter)
{
	if (impl)
	{
		MutexSection mutex_lock(&impl->mutex);
		impl->filters.push_back(filter);
	}
}

void SoundOutput::remove_filter(SoundFilter &filter)
{
	if (impl)
	{
		MutexSection mutex_lock(&impl->mutex);
		for (std::vector<SoundFilter>::size_type i=0; i<impl->filters.size(); i++)
		{
			if (impl->filters[i] == filter)
			{
				impl->filters.erase(impl->filters.begin()+i);
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// SoundOutput implementation:

}
