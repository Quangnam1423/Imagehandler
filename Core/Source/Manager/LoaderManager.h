#pragma once

#include "../Singleton.h"
#include "../ImageInfo/BMPdefine.h"

#define LM LoaderManager::getInstance()

class LoaderManager : public Singleton<LoaderManager>
{
friend class Singleton<LoaderManager>;
public:
	LoaderManager() = default;
	~LoaderManager() = default;

	Image* loadBMP(const char* filePath);

};

