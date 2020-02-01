// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2017-2020 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Foundation/Graphic/Driver.hpp"
#include <d3d11_1.h>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic::Detail::Direct3D11
{
	class CDriver final : public IDriver
	{
	public:

		CDriver();

		~CDriver() override;

		Bool Initialise(UInt window, UInt16 width, UInt16 height) override;

		void Reset(UInt16 width, UInt16 height) override;

		Bool CreateBuffer(UInt16 id, Bool geometry, UInt32 capacity, Span<UInt8> data) override;

		void UpdateBuffer(UInt16 id, Bool discard, UInt32 offset, Span<UInt8> data) override;

		void DeleteBuffer(UInt16 id) override;

		Bool CreateDescriptor(UInt16 id, Span<UInt16> textures, Span<UInt16> samplers) override;

		void DeleteDescriptor(UInt16 id) override;

		Bool CreatePass(UInt16 id, UInt window, UInt16 width, UInt16 height) override;

		Bool CreatePass(UInt16 id, Span<UInt16> color, UInt16 depth) override;

		void DeletePass(UInt16 id) override;

		Bool CreatePipeline(UInt16 id, Span<UInt8> vertex, Span<UInt8> pixel, const Descriptor & states) override;

		void DeletePipeline(UInt16 id) override;

		Bool CreateSampler(UInt16 id, TextureBorder edgeX, TextureBorder edgeY, TextureFilter filter) override;

		void DeleteSampler(UInt16 id) override;

		Bool CreateTexture(UInt16 id, TextureFormat format, TextureLayout layout, UInt16 width, UInt16 height,
			UInt8 mipmap, Span<UInt8> data) override;

		void UpdateTexture(UInt16 id, UInt8 level, Rect offset, UInt32 pitch, Span<UInt8> data) override;

		void DeleteTexture(UInt16 id) override;

		void Prepare(UInt16 id, Rect viewport, Clear target, UInt32 color, Float32 depth, UInt8 stencil) override;

		void Submit(Span<Submission> submissions) override;

		void Commit() override;

	private:

		struct D3D11Texture
		{
			ID3D11Texture2D 		 * mTexture;
			ID3D11ShaderResourceView * mResource;
		};

		struct D3D11Sampler
		{
			ID3D11SamplerState       * mSampler;
		};

		struct D3D11Pipeline
		{
            ID3D11VertexShader       * mVS;
            ID3D11PixelShader        * mPS;
            ID3D11BlendState         * mBS;
            ID3D11DepthStencilState  * mDS;
            ID3D11RasterizerState    * mRS;
            ID3D11InputLayout        * mIL;
            UInt32					   mIS;
            D3D11_PRIMITIVE_TOPOLOGY   mTS;
		};

		struct D3D11Pass
		{
			IDXGISwapChain			 * mWindow;
			ID3D11RenderTargetView   * mColorAttachment[kMaxDrawColor];
			ID3D11DepthStencilView   * mDepthAttachment;
		};

		struct D3D11Descriptor
		{
			ID3D11SamplerState       * mSamplers[kMaxDrawResources];
			ID3D11ShaderResourceView * mTextures[kMaxDrawResources];
		};

		struct D3D11Buffer
		{
			ID3D11Buffer             * mBuffer;
		};

		Bool OnCreateTextureForWindow(D3D11Pass & pass, UInt16 width, UInt16 height);

	private:

        ID3D11Device1        * mDevice;
        ID3D11DeviceContext1 * mDeviceContext;
		IDXGIFactory1 		 * mFactory;
        IDXGISwapChain       * mQueue[kMaxCachePass];
        UInt32                 mQueueQuantity;
        D3D11Buffer            mListBuffer[kMaxCacheBuffer];
        D3D11Descriptor	       mListDescriptor[kMaxCacheDescriptor];
        D3D11Pass		       mListPass[kMaxCachePass];
        D3D11Pipeline	       mListPipeline[kMaxCachePipeline];
        D3D11Sampler           mListSampler[kMaxCacheSampler];
        D3D11Texture	       mListTexture[kMaxCacheTexture];
	};
}