#pragma once
#include <Windows.h>
#include <d3d12.h>

#include <vector>
#include <unordered_map>

#include <memory>
#include <wrl/client.h>

#include <string>

#include <DirectXTex.h>

using Microsoft::WRL::ComPtr;


struct Texture2DContainer
{
	ComPtr<ID3D12Resource> m_pTexture;
	ComPtr<ID3D12Resource> m_pTextureUploadHeap;

	bool m_uploaded = false;

	std::unique_ptr<uint8_t[]> m_wicData;
	D3D12_SUBRESOURCE_DATA m_subresouceData;

	DirectX::TexMetadata	m_metaData;		
	DirectX::ScratchImage	m_scImage;		

	float fWidth;
	float fHeight;
	DXGI_FORMAT texFormat;
};

class TextureManager
{
private:
	std::unordered_map<std::wstring, std::unique_ptr<Texture2DContainer>> m_textureDB;

	HRESULT CreateTextureFromFile(ID3D12Device* g_pD3D, Texture2DContainer* txbuff, const wchar_t* filename, bool genMipmap = false);
	void	ReleaseTexObj(Texture2DContainer* txbuff);
	void	DestructTextureManager(void);

public:

	HRESULT InitTextureManager(void);

	HRESULT CreateTextureFromFile(ID3D12Device* pD3D, std::wstring labelName, const wchar_t* filename);

	HRESULT UploadCreatedTextures(ID3D12Device* pD3D, ID3D12GraphicsCommandList* pCmdList, ID3D12CommandQueue* pCmdQueue);

	void ReleaseTexture(std::wstring labelName);
	void ReleaseAllTextures(void);

	void CreateTextureSRV(ID3D12Device* pD3D, ID3D12DescriptorHeap* pSrvHeap, UINT slotNo, std::wstring texLabel);
	void CreateTextureSRV(ID3D12Device* pD3D, ID3D12DescriptorHeap* pSrvHeap, UINT slotNo, Texture2DContainer* txbuff);

	Texture2DContainer* GetTexture(std::wstring labelName);

	~TextureManager();
};
