#pragma once

#include "Sprites.h"
#include <string>

class TextAndNumber
{

	LPSPRITE textSpr=NULL;
public:
	void Render(float posX, float posY, string str);
	string FillZeroString(string str, int MaxStringLenght);

	TextAndNumber();

	~TextAndNumber();
};

