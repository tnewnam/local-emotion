#ifndef hkd3d
#define hkd3d

#pragma once
#include "stdafx.h"


#define MSB (1<<15)
#define LSB 1

template <typename T> T Read(DWORD offset);

class Hooked_D3D9
{
public:
	void Render();
	void Reset();
	void Initialize(LPDIRECT3DDEVICE9 pDevice);
	void CleanUp();

	void _DrawText(ID3DXFont* pFont, const char* text, float x, float y, D3DCOLOR color);
	void _DrawLine(ID3DXLine* pLine, float x1, float y1, float x2, float y2, D3DCOLOR color);
	void _DrawRect(ID3DXLine* pLine, float x, float y, float width, float height, D3DCOLOR color);
	void _DrawRectFilled(LPDIRECT3DDEVICE9 pDevice, int x, int y, int width, int height, D3DCOLOR color);


private:
	//void _cleanup(item* items, int count);

	void HandleInput();
	void RenderEsp();
	void RenderItemEsp();
	void RenderDroppedItemEsp();
	void RenderCoords();
	void SpeedRun();
	void EscapeUp();
	void ComeBack();
	void Elevate();
	void NoRecoil();
	void RenderDeadEsp();
	int GetDistance(D3DXVECTOR3 one, D3DXVECTOR3 two);

	ID3DXFont* m_textFont;
	ID3DXLine* m_rectLine;
	IDirect3DDevice9* m_device;

};

#endif