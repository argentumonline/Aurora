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

#include "Driver.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic
{
	class Service final
	{
	public:

		Service(IDriver * driver) : mDriver(driver)
		{
			EASTL_ASSERT(mDriver != nullptr)
		}

		~Service()
		{
			delete mDriver;
		}

		inline Bool Initialise(UInt window, UInt16 width, UInt16 height)
		{
			EASTL_ASSERT(window != 0)
			EASTL_ASSERT(width > 0)
			EASTL_ASSERT(height > 0)

			return mDriver->Initialise(window, width, height);
		}

		inline void Reset(UInt16 width, UInt16 height)
		{
			EASTL_ASSERT(width > 0)
			EASTL_ASSERT(height > 0)

			mDriver->Reset(width, height);
		}

		inline UInt16 CreateBuffer(Bool geometry, UInt32 capacity, Span<UInt8> data)
		{
			EASTL_ASSERT(capacity > 0)

			const UInt16 id = mAllocatorBuffer.Allocate();

			if (id && mDriver->CreateBuffer(id, geometry, capacity, data))
			{
				return id;
			}
			else
			{
				mAllocatorBuffer.Free(id);
			}
			return 0;
		}

		inline void UpdateBuffer(UInt16 id, Bool discard, UInt32 offset, Span<UInt8> data)
		{
			EASTL_ASSERT(id != 0)

			mDriver->UpdateBuffer(id, discard, offset, data);
		}

		inline void DeleteBuffer(UInt16 id)
		{
			EASTL_ASSERT(id != 0)

			mDriver->DeleteBuffer(mAllocatorBuffer.Free(id));
		}

		inline UInt16 CreateDescriptor(Span<UInt16> textures, Span<UInt16> samplers)
		{
			EASTL_ASSERT(!textures.empty())
			EASTL_ASSERT(!samplers.empty())

			const UInt16 id = mAllocatorDescriptor.Allocate();

			if (id && mDriver->CreateDescriptor(id, textures, samplers))
			{
				return id;
			}
			else
			{
				mAllocatorDescriptor.Free(id);
			}
			return 0;
		}

		inline void DeleteDescriptor(UInt16 id)
		{
			EASTL_ASSERT(id != 0)

			mDriver->DeleteDescriptor(mAllocatorDescriptor.Free(id));
		}

		inline UInt16 CreatePass(UInt window, UInt16 width, UInt16 height)
		{
			EASTL_ASSERT(window != 0)
			EASTL_ASSERT(width > 0)
			EASTL_ASSERT(height > 0)

			const UInt16 id = mAllocatorPass.Allocate();

			if (id && mDriver->CreatePass(id, window, width, height))
			{
				return id;
			}
			else
			{
				mAllocatorPass.Free(id);
			}
			return 0;
		}

		inline UInt16 CreatePass(Span<UInt16> color, UInt16 depth)
		{
			EASTL_ASSERT(!color.empty())

			const UInt16 id = mAllocatorPass.Allocate();

			if (id && mDriver->CreatePass(id, color, depth))
			{
				return id;
			}
			else
			{
				mAllocatorPass.Free(id);
			}
			return 0;
		}

		inline void DeletePass(UInt16 id)
		{
			EASTL_ASSERT(id != 0)

			mDriver->DeletePass(mAllocatorPass.Free(id));
		}

		inline UInt16 CreatePipeline(Span<UInt8> vertex, Span<UInt8> pixel, const Descriptor & states)
		{
			EASTL_ASSERT(!vertex.empty())
			EASTL_ASSERT(!pixel.empty())
			EASTL_ASSERT(!states.mInputLayout.empty())

			const UInt16 id = mAllocatorPipeline.Allocate();

			if (id && mDriver->CreatePipeline(id, vertex, pixel, states))
			{
				return id;
			}
			else
			{
				mAllocatorPipeline.Free(id);
			}
			return 0;
		}

		inline void DeletePipeline(UInt16 id)
		{
			EASTL_ASSERT(id != 0)

			mDriver->DeletePipeline(mAllocatorPipeline.Free(id));
		}

		inline UInt16 CreateSampler(TextureBorder edgeX, TextureBorder edgeY, TextureFilter filter)
		{
			const UInt16 id = mAllocatorSampler.Allocate();

			if (id && mDriver->CreateSampler(id, edgeX, edgeY, filter))
			{
				return id;
			}
			else
			{
				mAllocatorSampler.Free(id);
			}
			return 0;
		}

		inline void DeleteSampler(UInt16 id)
		{
			EASTL_ASSERT(id != 0)

			mDriver->DeleteSampler(mAllocatorSampler.Free(id));
		}

		inline UInt16 CreateTexture(TextureFormat format, TextureLayout layout, UInt16 width, UInt16 height, UInt8 mipmap, Span<UInt8> data)
		{
			EASTL_ASSERT(width > 0)
			EASTL_ASSERT(height > 0)
			EASTL_ASSERT(mipmap < kMaxDrawMipmap)

			const UInt16 id = mAllocatorTexture.Allocate();

			if (id && mDriver->CreateTexture(id, format, layout, width, height, mipmap, data))
			{
				return id;
			}
			else
			{
				mAllocatorTexture.Free(id);
			}
			return 0;
		}

		inline void UpdateTexture(UInt16 id, UInt8 level, Rect offset, UInt32 pitch, Span<UInt8> data)
		{
			EASTL_ASSERT(id > 0)
			EASTL_ASSERT(level < kMaxDrawMipmap)
			EASTL_ASSERT(!data.empty())

			mDriver->UpdateTexture(id, level, offset, pitch, data);
		}

		inline void DeleteTexture(UInt16 id)
		{
			EASTL_ASSERT(id != 0)

			mDriver->DeleteTexture(mAllocatorTexture.Free(id));
		}

		inline void Prepare(UInt16 id, Rect viewport, Clear target, UInt32 color, Float32 depth, UInt8 stencil)
		{
			mDriver->Prepare(id, viewport, target, color, depth, stencil);
		}

		inline void Submit(Span<Submission> submissions)
		{
			EASTL_ASSERT(submissions.size() > 0)

			mDriver->Submit(submissions);
		}

		inline void Commit()
		{
			mDriver->Commit();
		}

	private:

		// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		IDriver 				   * mDriver;

		// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		Handles<kMaxCacheBuffer> 	 mAllocatorBuffer;
		Handles<kMaxCacheDescriptor> mAllocatorDescriptor;
		Handles<kMaxCachePass>       mAllocatorPass;
		Handles<kMaxCachePipeline>   mAllocatorPipeline;
		Handles<kMaxCacheSampler>    mAllocatorSampler;
		Handles<kMaxCacheTexture>    mAllocatorTexture;
	};
}