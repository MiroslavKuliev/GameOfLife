#pragma once

#include "wx/wx.h"
#include <fstream>

struct settings
{
	int sizeGrid = 30; 
	int interval = 50;
	int colorDeadCells = 1;
	int colorLivingCells = 2;

	void SaveData()
	{
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(settings));
		file.close();
	}

	void LoadData()
	{
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(settings));
		file.close();
	}
};