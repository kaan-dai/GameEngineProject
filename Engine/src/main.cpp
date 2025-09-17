//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "Game.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	int ValueReturn;

	Trace::out("\n");
	Azul::Game *poGame = new Azul::Game("Week 10", 2*400, 2*300);
	ValueReturn = poGame->wWinMain(hInstance, prevInstance, cmdLine, cmdShow);

	delete poGame;

	return ValueReturn;
}

// --- End of File ---
