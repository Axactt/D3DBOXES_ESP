#include<Windows.h>
#include<d3d9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#include<cmath>
#include "drawLogic.h"
#pragma comment(lib, "d3dx9.lib")

// Drawing lines here by Calling ID3DXLine interface
// and D3DXCreateLine function to get address of interface
void DrawLine( IDirect3DDevice9 * pDevice, float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color )
{
	ID3DXLine* pLine {}; // Interface implements line drawing using textured triangles
	D3DXCreateLine( pDevice, &pLine );
	D3DXVECTOR2 line[] = { D3DXVECTOR2( x1,y1 ),D3DXVECTOR2( x2,y2 ) };
	pLine->SetWidth( width );
	if (antialias)
		pLine->SetAntialias( 1 );
	pLine->Begin(); // exception is being thrown here when game is crashing on unhook
	pLine->Draw( line, 2, color );
	pLine->End();
	pLine->Release();
}


//drawing filled rectangle function to be called in hookedEndscene
void DrawFillRect( IDirect3DDevice9* pDevice, int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b )
{
	D3DCOLOR rectColor = D3DCOLOR_XRGB( r, g, b );	//No point in using alpha because clear & alpha dont work!
	D3DRECT BarRect = { x, y, x + w, y + h };

	pDevice->Clear( 1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, rectColor, 0, 0 );
}
// a Drawline function wrapper to take Vec2 objects as parameters
void DrawLine( IDirect3DDevice9* pDevice, Vec2 src, Vec2 dst, float width, bool antialias, D3DCOLOR color )
{

	DrawLine( pDevice, src.x, src.y, dst.x, dst.y,  width,  antialias,  color );

}
 // drawing 2d boxes around the entities 
void DrawEspBox2D( IDirect3DDevice9* pDevice, Vec2 top, Vec2 bottom, int thickness, bool antialias, D3DCOLOR color )
{
	int height = std::abs(top.y - bottom.y);

	Vec2 topLeft {};
	topLeft.x = top.x - height / 4;
	topLeft.y = top.y;
	Vec2 topRight {};
	topRight.x = top.x + height / 4;
	topRight.y = top.y;
	Vec2 bottomLeft {};
	bottomLeft.x = bottom.x - height / 4;
	bottomLeft.y = bottom.y;
	Vec2 bottomRight {};
	bottomRight.x = bottom.x + height / 4;
	bottomRight.y = bottom.y;

	DrawLine( pDevice, topLeft, topRight, thickness,false, color );
	DrawLine( pDevice, bottomLeft, bottomRight, thickness, false, color );
	DrawLine( pDevice, topLeft, bottomLeft, thickness, false, color );
	DrawLine( pDevice, topRight, bottomRight, thickness, false, color );

}
