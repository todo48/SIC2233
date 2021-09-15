#pragma once

#include <windows.h>
#include "HighResolutionTimer.h"
#include "Audio/Audio.h"
#include "Graphics/Graphics.h"
#include "Input/input.h"

#if 0 //�E�B���h�E�̃T�C�Y
CONST LONG SCREEN_WIDTH{ 1920 };
CONST LONG SCREEN_HEIGHT{ 1080 };
#else
CONST LONG SCREEN_WIDTH{ 1280 }; //1280
CONST LONG SCREEN_HEIGHT{ 720 };// 720
#endif
CONST LPCWSTR APPLICATION_NAME{ L"���Ń_�[�r�[" };

class Framework
{
public:
	Framework(HWND hWnd);
	~Framework();

private:
	void Update(float elapsedTime/*Elapsed seconds from last frame*/);
	void Render(float elapsedTime/*Elapsed seconds from last frame*/);

	void CalculateFrameStats();

public:
	int Run();
	LRESULT CALLBACK HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	const HWND				hWnd;
	HighResolutionTimer		timer;
	Audio					audio;
	Graphics				graphics;
	Input					input;
};

