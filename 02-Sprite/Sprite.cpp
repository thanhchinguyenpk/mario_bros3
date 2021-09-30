#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / (float)tex->getWidth(); // vị trí của vùng vẽ trên text bự
	sprite.TexCoord.y = this->top / (float)tex->getHeight();

	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth(); // vị trí trên phần vẽ
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);//*3 dòng này


	//D3DXMatrixScaling(&this->matScaling, -1.0f, 1.0f, 1.0f);

	//D3DXMatrixRotationX(&this->matScaling, 6.28319f);
	
	//D3DXMatrixTranslation(&this->matScaling, 16.0f, 16.0f, 1.0f);
}

void CSprite::Draw(float x, float y)
{
	CGame* g = CGame::GetInstance();

	D3DXMATRIX matTranslation;
	//D3DXMatrixTranslation(&matTranslation, (g->GetBackBufferWidth() - x), (g->GetBackBufferHeight() - y), 0.1f); // -x lật ngược vị trí theo chiều âm
	//D3DXMatrixTranslation(&matTranslation, -x+200, (g->GetBackBufferHeight() - y), 0.1f); // -x lật ngược vị trí theo chiều âm
	D3DXMatrixTranslation(&matTranslation, -x + 200, (g->GetBackBufferHeight() - y), 0.1f); // -x lật ngược vị trí theo chiều âm

	
	this->sprite.matWorld = (this->matScaling * matTranslation);
	//D3DXMatrixTranslation(&this->sprite.matWorld, 0.0f, -0.5f, 0.0f);
	
	// 
	//D3DXMatrixTransformation2D(&this->sprite.matWorld, &D3DXVECTOR2(1, 1), 0,
	//	&D3DXVECTOR2(3.0f * 1, 3.0f * 1), NULL, 0.0f, NULL);

	/*D3DXMATRIX oldTransform, middleTransform;
	oldTransform = this->sprite.matWorld;
	int nx = -1;
	D3DXMatrixTransformation2D(&middleTransform, &D3DXVECTOR2(100,100), 0,
		&D3DXVECTOR2(3.0f  , 3.0f * 1), NULL, 0.0f, NULL);
	D3DXMATRIX newTransform = oldTransform * middleTransform;

	this->sprite.matWorld = newTransform;
	*/
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
	//g->GetSpriteHandler()->d
	//this->sprite.matWorld = oldTransform;
}

void CSprite::DrawMap(float x, float y)
{
	CGame* g = CGame::GetInstance();

	D3DXMATRIX matTranslation;
	//D3DXMatrixTranslation(&matTranslation, (g->GetBackBufferWidth() - x), (g->GetBackBufferHeight() - y), 0.1f); // -x lật ngược vị trí theo chiều âm
	D3DXMatrixTranslation(&matTranslation, x, (g->GetBackBufferHeight() - y), 0.1f); // -x lật ngược vị trí theo chiều âm


	this->sprite.matWorld = (this->matScaling * matTranslation);
	//D3DXMatrixTranslation(&this->sprite.matWorld, 0.0f, -0.5f, 0.0f);

	// 
	//D3DXMatrixTransformation2D(&this->sprite.matWorld, &D3DXVECTOR2(1, 1), 0,
	//	&D3DXVECTOR2(3.0f * 1, 3.0f * 1), NULL, 0.0f, NULL);

	/*D3DXMATRIX oldTransform, middleTransform;
	oldTransform = this->sprite.matWorld;
	int nx = -1;
	D3DXMatrixTransformation2D(&middleTransform, &D3DXVECTOR2(100,100), 0,
		&D3DXVECTOR2(3.0f  , 3.0f * 1), NULL, 0.0f, NULL);
	D3DXMATRIX newTransform = oldTransform * middleTransform;

	this->sprite.matWorld = newTransform;
	*/
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
	//g->GetSpriteHandler()->d
	//this->sprite.matWorld = oldTransform;
}

