#include "animation.h"
#include "framework.h"
#include "utils.h"
#include "bass.h"


Bass::Bass()
{

}

HCHANNEL* Bass::getChannel(const char* name)
{
	auto it = channels_by_name.find(name);
	if (it == channels_by_name.end()) {
		HSAMPLE hSample;
		hSample = BASS_SampleLoad(false, name, 0, 0, 3, 0);
		channels_by_name[name] = new HSAMPLE();
		*channels_by_name[name] = BASS_SampleGetChannel(hSample, false);
	}
	return channels_by_name[name];
}

void Bass::playChannel(const char* name, float vol, bool loop) {
	HCHANNEL hSampleChannel = *getChannel(name);
	BASS_ChannelSetAttribute(hSampleChannel, BASS_ATTRIB_VOL, vol);
	if (loop)
		BASS_ChannelFlags(hSampleChannel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	BASS_ChannelPlay(hSampleChannel, true);
}

void Bass::stopChannel(const char* name) {
	HCHANNEL hSampleChannel = *getChannel(name);
	BASS_ChannelPause(hSampleChannel);
}



