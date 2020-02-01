// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2017-2020 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Driver.hpp"
#include <versionhelpers.h>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic::Detail::Direct3D11
{
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    template<typename T>
    static auto _Acquire(T *& pointer)
    {
        if (pointer != nullptr)
        {
            pointer->AddRef();
        }
        return pointer;
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    template<typename T>
    static void _Release(T *& pointer)
    {
        if (pointer != nullptr)
        {
            pointer->Release();
            pointer = nullptr;
        }
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	template<typename T, UInt32 Length>
	void _Release(T * (& pointer)[Length])
	{
		for (T * object : pointer)
		{
			_Release(object);
		}
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(BlendColor value)
    {
        return static_cast<D3D11_COLOR_WRITE_ENABLE>(value);
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(BlendFactor value)
    {
        static constexpr D3D11_BLEND sMapping[] = {
            D3D11_BLEND_ZERO,                       // BlendFactor::Zero
            D3D11_BLEND_ONE,                        // BlendFactor::One
            D3D11_BLEND_SRC_COLOR,                  // BlendFactor::SrcColor
            D3D11_BLEND_INV_SRC_COLOR,              // BlendFactor::OneMinusSrcColor
            D3D11_BLEND_DEST_COLOR,                 // BlendFactor::DstColor
            D3D11_BLEND_INV_DEST_COLOR,             // BlendFactor::OneMinusDstColor
            D3D11_BLEND_SRC_ALPHA,                  // BlendFactor::SrcAlpha
            D3D11_BLEND_INV_SRC_ALPHA,              // BlendFactor::OneMinusSrcAlpha
            D3D11_BLEND_DEST_ALPHA,                 // BlendFactor::DstAlpha
            D3D11_BLEND_INV_DEST_ALPHA              // BlendFactor::OneMinusDstAlpha
        };
        return sMapping[static_cast<UInt32>(value)];
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(BlendEquation value)
    {
        constexpr static D3D11_BLEND_OP sMapping[] = {
            D3D11_BLEND_OP_ADD,                     // BlendEquation::Add
            D3D11_BLEND_OP_SUBTRACT,                // BlendEquation::Subtract
            D3D11_BLEND_OP_REV_SUBTRACT,            // BlendEquation::ReverseSubtract
            D3D11_BLEND_OP_MIN,                     // BlendEquation::Min
            D3D11_BLEND_OP_MAX                      // BlendEquation::Max
        };
        return sMapping[static_cast<UInt32>(value)];
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(TestAction value)
    {
        constexpr static D3D11_STENCIL_OP sMapping[] = {
            D3D11_STENCIL_OP_KEEP,                  // TestAction::Keep
            D3D11_STENCIL_OP_REPLACE,               // TestAction::Replace
            D3D11_STENCIL_OP_ZERO,                  // TestAction::Zero
            D3D11_STENCIL_OP_DECR,                  // TestAction::Decrease
            D3D11_STENCIL_OP_DECR_SAT,              // TestAction::DecreaseOrWrap
            D3D11_STENCIL_OP_INVERT,                // TestAction::Invert
            D3D11_STENCIL_OP_INCR,                  // TestAction::Increase
            D3D11_STENCIL_OP_INCR_SAT               // TestAction::IncreaseOrWrap
        };
        return sMapping[static_cast<UInt32>(value)];
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(TestCondition value)
    {
        constexpr static D3D11_COMPARISON_FUNC sMapping[] = {
            D3D11_COMPARISON_ALWAYS,                // TestCondition::Always
            D3D11_COMPARISON_NEVER,                 // TestCondition::Never
            D3D11_COMPARISON_GREATER,               // TestCondition::Greater
            D3D11_COMPARISON_GREATER_EQUAL,         // TestCondition::GreaterEqual
            D3D11_COMPARISON_EQUAL,                 // TestCondition::Equal
            D3D11_COMPARISON_NOT_EQUAL,             // TestCondition::NotEqual
            D3D11_COMPARISON_LESS,                  // TestCondition::Less
            D3D11_COMPARISON_LESS_EQUAL             // TestCondition::LessEqual
        };
        return sMapping[static_cast<UInt32>(value)];
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(TextureBorder value)
    {
        constexpr static D3D11_TEXTURE_ADDRESS_MODE sMapping[] = {
            D3D11_TEXTURE_ADDRESS_WRAP,             // TextureBorder::Repeat
            D3D11_TEXTURE_ADDRESS_CLAMP,            // TextureBorder::Clamp
            D3D11_TEXTURE_ADDRESS_MIRROR            // TextureBorder::Mirror
        };
        return sMapping[static_cast<UInt32>(value)];
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _As(TextureFilter value)
    {
		constexpr static D3D11_FILTER sMapping[] = {
            D3D11_FILTER_MIN_MAG_MIP_POINT,                 // TextureFilter::MinPointMagPointMipPoint
            D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,          // TextureFilter::MinPointMagPointMipLinear
            D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,    // TextureFilter::MinPointMagLinearMipPoint
            D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,          // TextureFilter::MinPointMagLinearMipLinear
            D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,          // TextureFilter::MinLinearMagPointMipPoint
            D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,   // TextureFilter::MinLinearMagPointMipLinear
            D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,          // TextureFilter::MinLinearMagLinearMipPoint
            D3D11_FILTER_MIN_MAG_MIP_LINEAR,                // TextureFilter::MinLinearMagLinearMipLinear
        };
        return sMapping[static_cast<UInt32>(value)];
    }

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    template<Bool Resource>
    static auto _As(TextureFormat value)
	{
        constexpr static DXGI_FORMAT sMapping[] = {
            DXGI_FORMAT_BC1_UNORM,           // TextureFormat::BC1_UINT_NORMALISED
            DXGI_FORMAT_BC1_UNORM_SRGB,      // TextureFormat::BC1_UINT_NORMALISED_NON_LINEAL
            DXGI_FORMAT_BC2_UNORM,           // TextureFormat::BC2_UINT_NORMALISED
            DXGI_FORMAT_BC2_UNORM_SRGB,      // TextureFormat::BC2_UINT_NORMALISED_NON_LINEAL
            DXGI_FORMAT_BC3_UNORM,           // TextureFormat::BC3_UINT_NORMALISED
            DXGI_FORMAT_BC3_UNORM_SRGB,      // TextureFormat::BC3_UINT_NORMALISED_NON_LINEAL
            DXGI_FORMAT_BC4_UNORM,           // TextureFormat::BC4_UINT_NORMALISED
            DXGI_FORMAT_BC5_UNORM,           // TextureFormat::BC5_UINT_NORMALISED
            DXGI_FORMAT_BC7_UNORM,           // TextureFormat::BC7_UINT_NORMALISED
            DXGI_FORMAT_BC7_UNORM_SRGB,      // TextureFormat::BC7_UINT_NORMALISED_NON_LINEAL
            DXGI_FORMAT_R8_SINT,             // TextureFormat::R8_INT
            DXGI_FORMAT_R8_SNORM,            // TextureFormat::R8_INT_NORMALISED
            DXGI_FORMAT_R8_UINT,             // TextureFormat::R8_UINT
            DXGI_FORMAT_R8_UNORM,            // TextureFormat::R8_UINT_NORMALISED
            DXGI_FORMAT_R16_SINT,            // TextureFormat::R16_INT
            DXGI_FORMAT_R16_SNORM,           // TextureFormat::R16_INT_NORMALISED
            DXGI_FORMAT_R16_UINT,            // TextureFormat::R16_UINT
            DXGI_FORMAT_R16_UNORM,           // TextureFormat::R16_UINT_NORMALISED
            DXGI_FORMAT_R16_FLOAT,           // TextureFormat::R16_FLOAT
            DXGI_FORMAT_R32_SINT,            // TextureFormat::R32_INT
            DXGI_FORMAT_R32_UINT,            // TextureFormat::R32_UINT
            DXGI_FORMAT_R32_FLOAT,           // TextureFormat::R32_FLOAT
            DXGI_FORMAT_R8G8_SINT,           // TextureFormat::RG8_INT
            DXGI_FORMAT_R8G8_SNORM,          // TextureFormat::RG8_INT_NORMALISED
            DXGI_FORMAT_R8G8_UINT,           // TextureFormat::RG8_UINT
            DXGI_FORMAT_R8G8_UNORM,          // TextureFormat::RG8_UINT_NORMALISED
            DXGI_FORMAT_R16G16_SINT,         // TextureFormat::RG16_INT
            DXGI_FORMAT_R16G16_SNORM,        // TextureFormat::RG16_INT_NORMALISED
            DXGI_FORMAT_R16G16_UINT,         // TextureFormat::RG16_UINT
            DXGI_FORMAT_R16G16_UNORM,        // TextureFormat::RG16_UINT_NORMALISED
            DXGI_FORMAT_R16G16_FLOAT,        // TextureFormat::RG16_FLOAT
            DXGI_FORMAT_R32G32_SINT,         // TextureFormat::RG32_INT
            DXGI_FORMAT_R32G32_UINT,         // TextureFormat::RG32_UINT
            DXGI_FORMAT_R32G32_FLOAT,        // TextureFormat::RG32_FLOAT
            DXGI_FORMAT_R8G8B8A8_SINT,       // TextureFormat::RGBA8_INT
            DXGI_FORMAT_R8G8B8A8_SNORM,      // TextureFormat::RGBA8_INT_NORMALISED
            DXGI_FORMAT_R8G8B8A8_UINT,       // TextureFormat::RGBA8_UINT
            DXGI_FORMAT_R8G8B8A8_UNORM,      // TextureFormat::RGBA8_UINT_NORMALISED
            DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, // TextureFormat::RGBA8_UINT_NORMALISED_NON_LINEAL
            DXGI_FORMAT_R16G16B16A16_SINT,   // TextureFormat::RGBA16_INT
            DXGI_FORMAT_R16G16B16A16_SNORM,  // TextureFormat::RGBA16_INT_NORMALISED
            DXGI_FORMAT_R16G16B16A16_UINT,   // TextureFormat::RGBA16_UINT
            DXGI_FORMAT_R16G16B16A16_UNORM,  // TextureFormat::RGBA16_UINT_NORMALISED
            DXGI_FORMAT_R16G16B16A16_FLOAT,  // TextureFormat::RGBA16_FLOAT
            DXGI_FORMAT_R32G32B32A32_SINT,   // TextureFormat::RGBA32_INT
            DXGI_FORMAT_R32G32B32A32_UINT,   // TextureFormat::RGBA32_UINT
            DXGI_FORMAT_R32G32B32A32_FLOAT,  // TextureFormat::RGBA32_FLOAT
            DXGI_FORMAT_R16_TYPELESS,        // TextureFormat::D16_UINT_NORMALISED
            DXGI_FORMAT_R32_TYPELESS,        // TextureFormat::D16_FLOAT
            DXGI_FORMAT_R24G8_TYPELESS,      // TextureFormat::D32_UINT_NORMALISED
            DXGI_FORMAT_R32_TYPELESS,        // TextureFormat::D32_FLOAT
            DXGI_FORMAT_R24G8_TYPELESS,      // TextureFormat::D24X8_UINT_NORMALISED
            DXGI_FORMAT_R32_TYPELESS,        // TextureFormat::D24X8_FLOAT
            DXGI_FORMAT_R24G8_TYPELESS,      // TextureFormat::D24S8_UINT_NORMALISED
        };

        if constexpr (Resource)
        {
            switch (value)
            {
            case TextureFormat::D16_UINT_NORMALISED:
                return DXGI_FORMAT_R16_UNORM;
            case TextureFormat::D16_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case TextureFormat::D32_UINT_NORMALISED:
                return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            case TextureFormat::D32_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case TextureFormat::D24X8_UINT_NORMALISED:
                return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            case TextureFormat::D24X8_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case TextureFormat::D24S8_UINT_NORMALISED:
                return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            default:
            	break;
            }
        }
		return sMapping[static_cast<UInt32>(value)];
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	static auto _As(VertexElement value)
	{
        constexpr static D3D11_INPUT_ELEMENT_DESC sMapping[] = {
            {"POSITION", 0, DXGI_FORMAT_UNKNOWN, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR",    0, DXGI_FORMAT_UNKNOWN, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_UNKNOWN, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        return sMapping[static_cast<UInt32>(value)];
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	static auto _As(VertexFormat value)
	{
		constexpr static DXGI_FORMAT sMapping[] = {
			DXGI_FORMAT_R32_FLOAT,              // VertexFormat::Float1
			DXGI_FORMAT_R32G32_FLOAT,           // VertexFormat::Float2
			DXGI_FORMAT_R32G32B32_FLOAT,        // VertexFormat::Float3
			DXGI_FORMAT_R32G32B32A32_FLOAT,     // VertexFormat::Float4
			DXGI_FORMAT_R8G8B8A8_SINT,          // VertexFormat::Byte4
			DXGI_FORMAT_R8G8B8A8_SNORM,         // VertexFormat::Byte4Normalised
			DXGI_FORMAT_R16G16_SINT,            // VertexFormat::Short2
			DXGI_FORMAT_R16G16_SNORM,           // VertexFormat::Short2Normalised
			DXGI_FORMAT_R16G16B16A16_SINT,      // VertexFormat::Short4
			DXGI_FORMAT_R16G16B16A16_SNORM,     // VertexFormat::Short4Normalised
			DXGI_FORMAT_R8G8B8A8_UINT,          // VertexFormat::UByte4
			DXGI_FORMAT_R8G8B8A8_UNORM,         // VertexFormat::UByte4Normalised
			DXGI_FORMAT_R16G16_UINT,            // VertexFormat::UShort2
			DXGI_FORMAT_R16G16_UNORM,           // VertexFormat::UShort2Normalised
			DXGI_FORMAT_R16G16B16A16_UINT,      // VertexFormat::UShort4
			DXGI_FORMAT_R16G16B16A16_UNORM,     // VertexFormat::UShort4Normalised
		};
        return sMapping[static_cast<UInt32>(value)];
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	static auto _As(VertexTopology value)
	{
		constexpr static D3D11_PRIMITIVE_TOPOLOGY sMapping[] = {
			D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,       // VertexTopology::Point
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST,        // VertexTopology::Line
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,    // VertexTopology::Triangle
		};
        return sMapping[static_cast<UInt32>(value)];
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	static auto _Fill(const UInt8 * data, UInt8 mipmap, UInt16 width, UInt16 height, TextureFormat format)
    {
        constexpr static UInt8 sMapping[] = {
            4,
            4,
            8,
            8,
            8,
            8,
            4,
            8,
            8,
            8,
            8,
            8,
            8,
            8,
            16,
            16,
            16,
            16,
            16,
            32,
            32,
            32,
            16,
            16,
            16,
            16,
            32,
            32,
            32,
            32,
            32,
            64,
            64,
            64,
            32,
            32,
            32,
            32,
            32,
            64,
            64,
            64,
            64,
            64,
            128,
            128,
            128,
            16,
            32,
            32,
            32,
            32,
            32,
            32,
        };

        const UInt32 depth = sMapping[static_cast<UInt8>(format)];

		if (data != nullptr)
		{
			static D3D11_SUBRESOURCE_DATA sPointer[kMaxDrawMipmap];

			for (UInt32 level = 0; level < mipmap; ++level)
			{
				sPointer[level].pSysMem = data;
				sPointer[level].SysMemPitch = width * (depth / 8);
				sPointer[level].SysMemSlicePitch = 0;

				data   += (width * depth * height);
				width <<= 2u;
				height <<= 2u;
			}
			return static_cast<D3D11_SUBRESOURCE_DATA *>(& sPointer[0]);
		}
		return static_cast<D3D11_SUBRESOURCE_DATA *>(nullptr);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _Fill(Span<Attrib> value)
    {
        static D3D11_INPUT_ELEMENT_DESC sDescription[kMaxDrawAttrib];

        for (UInt32 i = 0, j = value.size(); i < j; ++i)
		{
            sDescription[i] 		  		  = _As(value[i].mElement);
            sDescription[i].SemanticIndex 	  = value[i].mIndex;
            sDescription[i].Format 			  = _As(value[i].mFormat);
      		sDescription[i].AlignedByteOffset = value[i].mOffset;
		}
        return static_cast<D3D11_INPUT_ELEMENT_DESC *>(& sDescription[0]);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static auto _Calculate(Span<Attrib> value)
	{
		constexpr static UInt32 sMapping[] = {
			4,              // VertexFormat::Float1
			8,              // VertexFormat::Float2
			12,             // VertexFormat::Float3
			16,             // VertexFormat::Float4
			4,              // VertexFormat::Byte4
			4,              // VertexFormat::Byte4Normalised
			4,              // VertexFormat::Short2
			4,              // VertexFormat::Short2Normalised
			16,             // VertexFormat::Short4
			16,             // VertexFormat::Short4Normalised
			4,              // VertexFormat::UByte4
			4,              // VertexFormat::UByte4Normalised
			4,              // VertexFormat::UShort2
			4,              // VertexFormat::UShort2Normalised
			16,             // VertexFormat::UShort4
			16,             // VertexFormat::UShort4Normalised
		};

		UInt32 stride = 0;

		for (const Attrib & attribute : value)
		{
			stride += sMapping[static_cast<UInt32>(attribute.mFormat)];
		}
		return stride;
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	CDriver::CDriver()
		: mDevice		  { nullptr },
		  mDeviceContext  { nullptr },
		  mFactory		  { nullptr },
		  mQueue		  { nullptr },
		  mQueueQuantity  { 0 },
		  mListBuffer	  { nullptr },
		  mListDescriptor { nullptr },
		  mListPass 	  { nullptr },
		  mListPipeline   { nullptr },
		  mListSampler	  { nullptr },
		  mListTexture    { nullptr }
	{
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	CDriver::~CDriver()
	{
		if (mDeviceContext)
		{
			mDeviceContext->ClearState();
		}
        for (auto Handle = 0u; Handle < kMaxCacheBuffer; ++Handle)
        {
            DeleteBuffer(Handle);
        }
        for (auto Handle = 0u; Handle < kMaxCacheDescriptor; ++Handle)
        {
            DeleteDescriptor(Handle);
        }
        for (auto Handle = 0u; Handle < kMaxCachePass; ++Handle)
        {
            DeletePass(Handle);
        }
        for (auto Handle = 0u; Handle < kMaxCachePipeline; ++Handle)
        {
            DeletePipeline(Handle);
        }
        for (auto Handle = 0u; Handle < kMaxCacheSampler; ++Handle)
        {
            DeleteSampler(Handle);
        }
        for (auto Handle = 0u; Handle < kMaxCacheTexture; ++Handle)
        {
            DeleteTexture(Handle);
        }

        _Release(mFactory);
        _Release(mDeviceContext);
        _Release(mDevice);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::Initialise(UInt window, UInt16 width, UInt16 height)
	{
		HRESULT error = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			reinterpret_cast<ID3D11Device **>(& mDevice),
			nullptr,
			reinterpret_cast<ID3D11DeviceContext **>(& mDeviceContext));

		if (SUCCEEDED(error))
		{
			error = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void **>(& mFactory));
		}

		if (SUCCEEDED(error))
		{
			return CreatePass(kDefault, window, width, height);
		}
		return false;
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::Reset(UInt16 width, UInt16 height)
	{
		if (mDeviceContext != nullptr)
		{
			mDeviceContext->ClearState();
		}

		_Release(mListPass[kDefault].mColorAttachment);
		_Release(mListPass[kDefault].mDepthAttachment);

		mListPass->mWindow->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

		OnCreateTextureForWindow(mListPass[kDefault], width, height);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreateBuffer(UInt16 id, Bool geometry, UInt32 capacity, Span<UInt8> data)
	{
		D3D11_SUBRESOURCE_DATA resource {
			data.data(), static_cast<UINT>(data.size())
		};
		const D3D11_BUFFER_DESC description = CD3D11_BUFFER_DESC(
			capacity,
			geometry ? D3D11_BIND_INDEX_BUFFER | D3D11_BIND_VERTEX_BUFFER : D3D11_BIND_CONSTANT_BUFFER,
			data.empty() ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE,
			data.empty() ? D3D11_CPU_ACCESS_WRITE : 0);
		return SUCCEEDED(
			mDevice->CreateBuffer(& description, (data.empty() ? nullptr : & resource), & mListBuffer[id].mBuffer));
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::UpdateBuffer(UInt16 id, Bool discard, UInt32 offset, Span<UInt8> data)
	{
        const D3D11_MAP          map = (discard ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE);
        D3D11_MAPPED_SUBRESOURCE mapped;

        if (FAILED(mDeviceContext->Map(mListBuffer[id].mBuffer, 0, map, 0, & mapped)))
        {
            return;
        }
        else
        {
            memcpy(static_cast<UInt8 *>(mapped.pData) + offset, data.data(), data.size());
        }
        mDeviceContext->Unmap(mListBuffer[id].mBuffer, 0);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::DeleteBuffer(UInt16 id)
	{
        _Release(mListBuffer[id].mBuffer);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreateDescriptor(UInt16 id, Span<UInt16> textures, Span<UInt16> samplers)
	{
		D3D11Descriptor & wrapper = mListDescriptor[id];

		for (UInt32 i = 0, j = textures.size(); i < j; ++i)
		{
			wrapper.mTextures[i] = _Acquire(mListTexture[textures[i]].mResource);
		}
		for (UInt32 i = 0, j = samplers.size(); i < j; ++i)
		{
			wrapper.mSamplers[i] = _Acquire(mListSampler[samplers[i]].mSampler);
		}
		return true;
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::DeleteDescriptor(UInt16 id)
	{
        D3D11Descriptor & wrapper = mListDescriptor[id];

        _Release(wrapper.mSamplers);
        _Release(wrapper.mTextures);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreatePass(UInt16 id, UInt window, UInt16 width, UInt16 height)
	{
		D3D11Pass & wrapper = mListPass[id];

		DXGI_SWAP_CHAIN_DESC info { 0 };
		info.BufferCount            = 2;
		info.BufferUsage            = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		info.Flags 			        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		info.BufferDesc.Format      = DXGI_FORMAT_B8G8R8A8_UNORM;
		info.BufferDesc.Width       = width;
		info.BufferDesc.Height      = height;
		info.SampleDesc             = { 1, 0 };
		info.BufferDesc.RefreshRate = { 1, 60 };
		info.SwapEffect = IsWindows10OrGreater() ? DXGI_SWAP_EFFECT_FLIP_DISCARD : DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

		if (FAILED(mFactory->CreateSwapChain(mDevice, & info, & wrapper.mWindow)))
		{
			return false;
		}
		else
		{
			mFactory->MakeWindowAssociation((HWND) window, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);
		}
		return OnCreateTextureForWindow(wrapper, width, height);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreatePass(UInt16 id, Span<UInt16> color, UInt16 depth)
	{
		D3D11Pass & wrapper = mListPass[id];

		for (UInt32 i = 0, j = color.size(); i < j; ++i)
		{
			const D3D11_RENDER_TARGET_VIEW_DESC view = CD3D11_RENDER_TARGET_VIEW_DESC(D3D11_RTV_DIMENSION_TEXTURE2D);
			mDevice->CreateRenderTargetView(mListTexture[color[i]].mTexture, & view, & wrapper.mColorAttachment[i]);
		}
		if (depth != 0)
		{
			const D3D11_DEPTH_STENCIL_VIEW_DESC view = CD3D11_DEPTH_STENCIL_VIEW_DESC(D3D11_DSV_DIMENSION_TEXTURE2D);
			mDevice->CreateDepthStencilView(mListTexture[depth].mTexture, & view, & wrapper.mDepthAttachment);
		}
		return true;
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::DeletePass(UInt16 id)
	{
        D3D11Pass & wrapper = mListPass[id];

        _Release(wrapper.mWindow);
        _Release(wrapper.mColorAttachment);
        _Release(wrapper.mDepthAttachment);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreatePipeline(UInt16 id, Span<UInt8> vertex, Span<UInt8> pixel, const Descriptor & states)
	{
		D3D11Pipeline & wrapper = mListPipeline[id];

		HRESULT error = mDevice->CreateVertexShader(vertex.data(), vertex.size(), nullptr, & wrapper.mVS);

		if (SUCCEEDED(error))
		{
			error = mDevice->CreatePixelShader(pixel.data(), pixel.size(), nullptr, & wrapper.mPS);
		}

		if (SUCCEEDED(error))
		{
			D3D11_BLEND_DESC Description = CD3D11_BLEND_DESC(CD3D11_DEFAULT());

			Description.RenderTarget[0].BlendEnable = !(
				       states.mBlendColorSrcFactor == BlendFactor::One
					&& states.mBlendAlphaSrcFactor == BlendFactor::One
					&& states.mBlendColorDstFactor == BlendFactor::Zero
					&& states.mBlendAlphaDstFactor == BlendFactor::Zero
					&& states.mBlendColorEquation == BlendEquation::Add
					&& states.mBlendAlphaEquation == BlendEquation::Add);
			Description.RenderTarget[0].SrcBlend              = _As(states.mBlendColorSrcFactor);
			Description.RenderTarget[0].DestBlend             = _As(states.mBlendColorDstFactor);
			Description.RenderTarget[0].BlendOp               = _As(states.mBlendColorEquation);
			Description.RenderTarget[0].SrcBlendAlpha         = _As(states.mBlendAlphaSrcFactor);
			Description.RenderTarget[0].DestBlendAlpha        = _As(states.mBlendAlphaDstFactor);
			Description.RenderTarget[0].BlendOpAlpha          = _As(states.mBlendAlphaEquation);
			Description.RenderTarget[0].RenderTargetWriteMask = _As(states.mBlendMask);

			error = mDevice->CreateBlendState(& Description, & wrapper.mBS);
		}

        if (SUCCEEDED(error))
        {
			D3D11_DEPTH_STENCIL_DESC Description = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

			Description.DepthEnable                  = (states.mDepthCondition != TestCondition::Always);
			Description.DepthFunc                    = _As(states.mDepthCondition);
			Description.DepthWriteMask               = static_cast<D3D11_DEPTH_WRITE_MASK>(states.mDepthMask);
			Description.StencilEnable                = (
				       states.mStencilCondition != TestCondition::Always
					|| states.mStencilOpFail    != TestAction::Keep
					|| states.mStencilOpFailZ   != TestAction::Keep
					|| states.mStencilOpPass    != TestAction::Keep);
			Description.StencilReadMask              = states.mStencilMask;
			Description.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			Description.FrontFace.StencilFunc        = _As(states.mStencilCondition);
			Description.FrontFace.StencilFailOp      = _As(states.mStencilOpFail);
			Description.FrontFace.StencilDepthFailOp = _As(states.mStencilOpFailZ);
			Description.FrontFace.StencilPassOp      = _As(states.mStencilOpPass);
			Description.BackFace.StencilFunc         = Description.FrontFace.StencilFunc;
			Description.BackFace.StencilFailOp       = Description.FrontFace.StencilFailOp;
			Description.BackFace.StencilDepthFailOp  = Description.FrontFace.StencilDepthFailOp;
			Description.BackFace.StencilPassOp       = Description.FrontFace.StencilPassOp;

			error = mDevice->CreateDepthStencilState(& Description, & wrapper.mDS);
		}

		if (SUCCEEDED(error))
		{
			D3D11_RASTERIZER_DESC description = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
			description.MultisampleEnable = true;
			description.ScissorEnable     = true;

			error = mDevice->CreateRasterizerState(& description, & wrapper.mRS);
		}

		if (SUCCEEDED(error))
		{
			wrapper.mTS = _As(states.mInputTopology);
		}
		if (SUCCEEDED(error))
		{
			const Span<Attrib> input = states.mInputLayout;

			error = mDevice->CreateInputLayout(_Fill(input), input.size(), vertex.data(), vertex.size(), & wrapper.mIL);

			wrapper.mIS = _Calculate(input);
		}

		if (SUCCEEDED(error))
		{
			return true;
		}
		else
		{
			DeletePipeline(id);
		}
		return false;
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::DeletePipeline(UInt16 id)
	{
		D3D11Pipeline & wrapper = mListPipeline[id];

		_Release(wrapper.mVS);
		_Release(wrapper.mPS);
		_Release(wrapper.mBS);
		_Release(wrapper.mDS);
		_Release(wrapper.mRS);
		_Release(wrapper.mIL);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreateSampler(UInt16 id, TextureBorder edgeX, TextureBorder edgeY, TextureFilter filter)
	{
        const D3D11_SAMPLER_DESC description = CD3D11_SAMPLER_DESC(
            _As(filter),
            _As(edgeX),
            _As(edgeY),
            D3D11_TEXTURE_ADDRESS_CLAMP,
            0,
            1,
            D3D11_COMPARISON_NEVER,
            nullptr,
            0,
            D3D11_FLOAT32_MAX);
        return SUCCEEDED(mDevice->CreateSamplerState(& description, & mListSampler[id].mSampler));
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::DeleteSampler(UInt16 id)
	{
        _Release(mListSampler[id].mSampler);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::CreateTexture(UInt16 id, TextureFormat format, TextureLayout layout, UInt16 width, UInt16 height,
		UInt8 mipmap, Span<UInt8> data)
	{
		D3D11_TEXTURE2D_DESC description = CD3D11_TEXTURE2D_DESC(_As<false>(format), width, height, 1, mipmap);
		description.Usage     = (data.empty() ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE);
		description.BindFlags = (layout != TextureLayout::Destination ? D3D11_BIND_SHADER_RESOURCE : 0);
		description.MiscFlags = (mipmap < 1 ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0);

		if (layout != TextureLayout::Source)
		{
			const Bool isDepth = static_cast<UInt8>(format) >= static_cast<UInt8>(TextureFormat::D16_FLOAT);
			description.BindFlags |= (isDepth ? D3D11_BIND_DEPTH_STENCIL : D3D11_BIND_RENDER_TARGET);
		}

        HRESULT error = S_OK;

        if (SUCCEEDED(error))
        {
            error = mDevice->CreateTexture2D(
            	& description, _Fill(data.data(), mipmap, width, height, format), & mListTexture[id].mTexture);
        }
        if (SUCCEEDED(error) && layout != TextureLayout::Destination)
        {
            const D3D11_SHADER_RESOURCE_VIEW_DESC view
            	= CD3D11_SHADER_RESOURCE_VIEW_DESC(D3D11_SRV_DIMENSION_TEXTURE2D, _As<true>(format), 0, mipmap);
            mDevice->CreateShaderResourceView(mListTexture[id].mTexture, & view, & mListTexture[id].mResource);
        }

        if (SUCCEEDED(error))
        {
            return true;
        }
        else
        {
            DeleteTexture(id);
        }
        return false;
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::UpdateTexture(UInt16 id, UInt8 level, Rect offset, UInt32 pitch, Span<UInt8> data)
	{
		const D3D11_BOX rect {
			offset.mLeft, offset.mTop, 0, offset.mRight, offset.mBottom, 0
		};
		mDeviceContext->UpdateSubresource(mListTexture[id].mTexture, level, & rect, data.data(), pitch, 0);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::DeleteTexture(UInt16 id)
	{
        D3D11Texture & wrapper = mListTexture[id];

        _Release(wrapper.mTexture);
        _Release(wrapper.mResource);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::Prepare(UInt16 id, Rect viewport, Clear target, UInt32 color, Float32 depth, UInt8 stencil)
	{
        D3D11Pass & wrapper = mListPass[id];

        if (target != Clear::Auxiliary)
        {
            Float32 normalised[4];
            normalised[0] = static_cast<Float32>(((color >> 24) & 255) / 255);
            normalised[1] = static_cast<Float32>(((color >> 16) & 255) / 255);
            normalised[2] = static_cast<Float32>(((color >> 8) & 255) / 255);
            normalised[3] = static_cast<Float32>((color & 255) / 255);

            for (UInt32 i = 0; i < kMaxDrawColor && wrapper.mColorAttachment[i] != nullptr; ++i)
			{
                mDeviceContext->ClearRenderTargetView(wrapper.mColorAttachment[i], normalised);
			}
        }
        if (target != Clear::Color)
        {
            mDeviceContext->ClearDepthStencilView(
            	wrapper.mDepthAttachment, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
        }

		if (wrapper.mWindow)
		{
        	mQueue[mQueueQuantity++] = wrapper.mWindow;
		}

        const D3D11_VIEWPORT rect {
            static_cast<FLOAT>(viewport.mLeft),
            static_cast<FLOAT>(viewport.mTop),
            static_cast<FLOAT>(viewport.mRight - viewport.mLeft),
            static_cast<FLOAT>(viewport.mBottom - viewport.mTop),
            0.0f,
            1.0f,
        };
        mDeviceContext->RSSetViewports(1, & rect);

        // Invalidate all bound textures before setting the attachments, because they cannot be use as an
        // attachment while bound as shader resource.
        ID3D11ShaderResourceView* const sEmptyResources[kMaxDrawResources] { nullptr };
		mDeviceContext->VSSetShaderResources(0, kMaxDrawResources, sEmptyResources);
		mDeviceContext->PSSetShaderResources(0, kMaxDrawResources, sEmptyResources);
		mDeviceContext->OMSetRenderTargets(kMaxDrawColor, wrapper.mColorAttachment, wrapper.mDepthAttachment);
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::Submit(Span<Submission> submissions)
	{
		Submission  empty { 0 }, & cache = empty;

		for (const Submission & current : submissions)
		{
			if (cache.mVBO.mBuffer != current.mVBO.mBuffer)
			{
				D3D11Buffer & wrapper = mListBuffer[current.mVBO.mBuffer];
				UINT stride = mListPipeline[current.mPipeline].mIS;
				UINT offset = 0;
				mDeviceContext->IASetVertexBuffers(0, 1, & wrapper.mBuffer, & stride, & offset);
			}

			if (cache.mIBO.mBuffer != current.mIBO.mBuffer)
			{
				D3D11Buffer & wrapper = mListBuffer[current.mIBO.mBuffer];
				mDeviceContext->IASetIndexBuffer(wrapper.mBuffer, DXGI_FORMAT_R16_UINT /* TODO */, 0);
			}

			for (auto i = 0; i < kMaxDrawConstant; ++i)
			{
				const Submission::Range & prev = cache.mCBO[i];
				const Submission::Range & next = current.mCBO[i];

				if (prev.mBuffer != next.mBuffer || prev.mOffset != next.mOffset || prev.mCount != next.mCount)
				{
					const D3D11Buffer & object = mListBuffer[next.mBuffer];

					mDeviceContext->VSSetConstantBuffers1(i, 1, & object.mBuffer, & next.mOffset, & next.mCount);
					mDeviceContext->PSSetConstantBuffers1(i, 1, & object.mBuffer, & next.mOffset, & next.mCount);
				}
			}

			{
				const UInt64 prev = * reinterpret_cast<const UInt64 *>(& cache.mScissor);
				const UInt64 next = * reinterpret_cast<const UInt64 *>(& current.mScissor);

				if (prev != next)
				{
					const RECT scissor {
						current.mScissor.mLeft, current.mScissor.mTop, current.mScissor.mRight, current.mScissor.mBottom
					};
					mDeviceContext->RSSetScissorRects(1, & scissor);
				}
			}

			if (cache.mPipeline != current.mPipeline)
			{
				const D3D11Pipeline & prev = mListPipeline[cache.mPipeline];
				const D3D11Pipeline & next = mListPipeline[current.mPipeline];

				if (prev.mVS != next.mVS)
				{
					mDeviceContext->VSSetShader(next.mVS, nullptr, 0);
				}
				if (prev.mPS != next.mPS)
				{
					mDeviceContext->PSSetShader(next.mPS, nullptr, 0);
				}
				if (prev.mBS != next.mBS)
				{
					mDeviceContext->OMSetBlendState(next.mBS, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
				}
				if (prev.mDS != next.mDS || cache.mStencil != current.mStencil)
				{
					mDeviceContext->OMSetDepthStencilState(next.mDS, current.mStencil);
				}
				if (prev.mRS != next.mRS)
				{
					mDeviceContext->RSSetState(next.mRS);
				}
			}
			else if (cache.mStencil != current.mStencil)
			{
				mDeviceContext->OMSetDepthStencilState(mListPipeline[current.mPipeline].mDS, current.mStencil);
			}

			if (cache.mDescriptor != current.mDescriptor)
			{
				const D3D11Descriptor & prev = mListDescriptor[cache.mDescriptor];
				const D3D11Descriptor & next = mListDescriptor[current.mDescriptor];

				{
					UInt8 min = kMaxDrawResources;
					UInt8 max = 0u;

					for (UInt32 i = 0; i < kMaxDrawResources && next.mTextures[i] != 0; ++i)
					{
						if (prev.mTextures[i] != next.mTextures[i])
						{
							min = min(i, min);
							max = max(i + 1, max);
						}
					}

					if (min != kMaxDrawResources && max != 0u)
					{
						const UInt8 range = max - min;

						mDeviceContext->VSSetShaderResources(min, range, next.mTextures);
						mDeviceContext->PSSetShaderResources(min, range, next.mTextures);
					}
				}
				{
					UInt8 min = kMaxDrawResources;
					UInt8 max = 0u;

					for (UInt32 i = 0; i < kMaxDrawResources && next.mSamplers[i] != 0; ++i)
					{
						if (prev.mSamplers[i] != next.mSamplers[i])
						{
							min = min(i, min);
							max = max(i + 1, max);
						}
					}

					if (min != kMaxDrawResources && max != 0u)
					{
						const UInt8 range = max - min;

						mDeviceContext->VSSetSamplers(min, range, next.mSamplers);
						mDeviceContext->PSSetSamplers(min, range, next.mSamplers);
					}
				}
			}

			if (current.mIBO.mBuffer != 0)
			{
				mDeviceContext->DrawIndexed(current.mIBO.mCount, current.mIBO.mOffset, current.mVBO.mOffset);
			}
			else
			{
				mDeviceContext->Draw(current.mVBO.mCount, current.mVBO.mOffset);
			}
			cache = current;
		}
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	void CDriver::Commit()
	{
		while (mQueueQuantity)
		{
            mQueue[--mQueueQuantity]->Present(0, 0);
		}
	}

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Bool CDriver::OnCreateTextureForWindow(D3D11Pass & pass, UInt16 width, UInt16 height)
	{
		ID3D11Texture2D * color;
		ID3D11Texture2D * depth;

		pass.mWindow->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(& color));
		mDevice->CreateRenderTargetView(color, nullptr, & pass.mColorAttachment[0]);

        D3D11_TEXTURE2D_DESC description { 0 };
        description.Width      = width;
        description.Height 	   = height;
        description.MipLevels  = 1;
        description.ArraySize  = 1;
        description.Format     = DXGI_FORMAT_D24_UNORM_S8_UINT;
        description.SampleDesc = { 1, 0 };
        description.Usage 		= D3D11_USAGE_DEFAULT;
        description.BindFlags 	= D3D11_BIND_DEPTH_STENCIL;
		mDevice->CreateTexture2D(& description, nullptr, & depth);
		mDevice->CreateDepthStencilView(depth, nullptr, & pass.mDepthAttachment);

		_Release(color);
		_Release(depth);
		return true;
	}
}