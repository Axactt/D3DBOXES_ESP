#pragma once
#include<Windows.h>
#include<d3d9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include"hackLogic.h"



//drawing filled rectangle function to be called in hookedEndscene
void DrawFillRect( IDirect3DDevice9* pDevice, int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b );

// Drawing lines here by Calling ID3DXLine interface
// and D3DXCreateLine function to get address of interface
void DrawLine( IDirect3DDevice9* pDevice, float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color );

// a DrawLine wrapper function using Vec2 object instead of floats, overload resolution to select function
void DrawLine( IDirect3DDevice9* pDevice, Vec2 src, Vec2 dst,  float width, bool antialias, D3DCOLOR color );