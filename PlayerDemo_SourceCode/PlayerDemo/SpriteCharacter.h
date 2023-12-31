#pragma once

#include <Windows.h>
#include <MyAccessHub.h>
#include <CharacterData.h>

#include <memory>
#include <vector>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;

enum class SPRITE_BLEND_MODE
{
	ALPHA_BLEND = 0,
};

enum class SPRITE_FILTER_MODE
{
	NoFilter = 0,
};

class SpriteCharacter : public CharacterData
{
private:
	class SpritePattern
	{
	public:
		XMFLOAT4	uv;
		XMUINT2	size;
	};

	const wchar_t*	index_id = L"Sprite";			 

	const wchar_t*	texture_id = nullptr;			
	std::vector<std::unique_ptr<SpritePattern>>		m_uvArray;	

	UINT		m_patternIndex;						

	SPRITE_BLEND_MODE		m_blendMode;
	SPRITE_FILTER_MODE		m_filterMode;


	XMFLOAT2 m_textureSize;

	XMFLOAT4 m_color;
	UINT	m_colorMix;
	UINT	m_alphaMix;

public:
	enum class COLOR_MIX_OP
	{
		MIX_MUL = 0,
		MIX_ADD = 1,
		MIX_DEC = 2,
		MIX_SET = 3,
		MIX_NONE = 4,
	};
	SpriteCharacter()
	{
		setPosition(0.0f, 0.0f, 0.0f);
		m_uvArray.clear();

		m_patternIndex = 0;

		m_blendMode = SPRITE_BLEND_MODE::ALPHA_BLEND;
		m_filterMode = SPRITE_FILTER_MODE::NoFilter;

	}

	void setTextureId(const wchar_t* texId);
	HRESULT setSpritePatterns(XMUINT4* patterns, UINT numOfPatterns);

	void changeBlendMode(SPRITE_BLEND_MODE mode)
	{
		m_blendMode = mode;
	}

	void changeFilterMode(SPRITE_FILTER_MODE mode)
	{
		m_filterMode = mode;
	}

	void setSpriteIndex(UINT idx)
	{
		m_patternIndex = idx;
	}

	const XMFLOAT4* getTextureUV(UINT index)
	{
		return &m_uvArray.at(index).get()->uv;
	}

	const XMFLOAT4* getTextureUV()
	{
		return &m_uvArray.at(m_patternIndex).get()->uv;
	}

	const XMUINT2* getSpriteSize(UINT index)
	{
		return &m_uvArray.at(index).get()->size;
	}

	const XMUINT2* getSpriteSize()
	{
		return &m_uvArray.at(m_patternIndex).get()->size;
	}

	const wchar_t* getTextureId()
	{
		return texture_id;
	}

	void setColor(float r, float g, float b, float a);
	void setColorMix(COLOR_MIX_OP op);	
	void setAlphaMix(COLOR_MIX_OP op);

	const XMFLOAT4* getColor();
	UINT	getColorMix();
	UINT	getAlphaMix();
};