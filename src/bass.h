#pragma once
#include "extra/bass.h"


//This class contains the bone structure hierarchy
class Bass {
public:

	std::map<const char*, HCHANNEL*, cmp_str> channels_by_name;	//map to get the bone index from its name, required to extract the final bones array

	Bass();

	HCHANNEL* Bass::getChannel(const char* name);//returns the bone pointer
	void playChannel(const char* name, float vol, bool loop);
	void Bass::stopChannel(const char* name);
};

