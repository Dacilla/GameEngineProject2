#include "SoundManager.h"


SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	//delete all sound effects properly
	for (SoundListing listing : sounds)
	{
		Mix_FreeChunk(listing.sound);
	}
}

void SoundManager::loadSound(string name, string file)
{
	SoundListing listing;
	listing.name = name;
	listing.sound = Mix_LoadWAV(file.c_str());

	//add listing to our list of sounds
	sounds.push_back(listing);
}

void SoundManager::playSound(string name)
{
	//loop through sound listings
	for (SoundListing listing : sounds)
	{
		//does this listing match the name we are searching
		if (listing.name == name)
		{
			//params:
			//channel to play on, e.g. if put 1 and a sound is playing on 1,
			//that sound will be stopped and replaced with this one
			//		(-1 for any free channel)
			//sound file to play
			//how many times to loop
			Mix_PlayChannel(-1, listing.sound, 0);
			break; //exit loop so we don't keep looking after we've found it
		}
	}
}

//initialised static sound manager
SoundManager SoundManager::soundManager;
