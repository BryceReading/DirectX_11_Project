#ifndef IndicesBuffer_h__
#define IndicesBuffer_h__
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

class IndexBuffer
{
private:
	IndexBuffer(const IndexBuffer& rhs);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT buffSize = 0; 
public:
	IndexBuffer() {}

	ID3D11Buffer* Get() const
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf()const
	{
		return buffer.GetAddressOf();
	}

	UINT BufferSize() const
	{
		return this->buffSize;
	}

	HRESULT Initialize(ID3D11Device* device, DWORD* data, UINT indiNum)
	{
		this->buffSize = indiNum;
		// Index data load 
		D3D11_BUFFER_DESC indexBuffDesc;
		ZeroMemory(&indexBuffDesc, sizeof(indexBuffDesc));
		indexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBuffDesc.ByteWidth = sizeof(DWORD) * indiNum;
		indexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBuffDesc.CPUAccessFlags = 0;
		indexBuffDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = data;
		HRESULT hr = device->CreateBuffer(&indexBuffDesc, &indexData, buffer.GetAddressOf());
		
		return hr;
	}
};

#endif // !IndicesBuffer_h__

