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

#include "Foundation/Core/Core.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic
{
    enum
    {
        kDefault            = 0x00000000,
        kMaxCacheBuffer     = 0x00000080,
        kMaxCacheDescriptor = 0x00001000,
        kMaxCachePass       = 0x00000080,
        kMaxCachePipeline   = 0x00000100,
        kMaxCacheSampler    = 0x00000040,
        kMaxCacheTexture    = 0x00001000,
        kMaxDrawAttrib      = 0x00000010,
        kMaxDrawColor       = 0x00000004,
        kMaxDrawConstant    = 0x00000004,
        kMaxDrawMipmap      = 0x00000010,
        kMaxDrawResources   = 0x00000008,
    };

    enum class BlendColor
    {
        RGBA = 0b00001111,
        RGB  = 0b00001110,
        RGA  = 0b00001101,
        RBA  = 0b00001011,
        RG   = 0b00001100,
        RB   = 0b00001010,
        RA   = 0b00001001,
        R    = 0b00001000,
        GBA  = 0b00000111,
        GB   = 0b00000110,
        GA   = 0b00000101,
        G    = 0b00000100,
        BA   = 0b00000011,
        B    = 0b00000010,
        A    = 0b00000001,
        None = 0b00000000,
    };

    enum class BlendFactor
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
    };

    enum class BlendEquation
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max,
    };

    enum class Clear
    {
        Color,
        Auxiliary,
        All,
    };

    enum class TestAction
    {
        Keep,
        Replace,
        Zero,
        Decrease,
        DecreaseOrWrap,
        Invert,
        Increase,
        IncreaseOrWrap,
    };

    enum class TestCondition
    {
        Always,
        Never,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual,
        Less,
        LessEqual,
    };

    enum class TextureBorder
    {
        Repeat,
        Clamp,
        Mirror,
    };

    enum class TextureFilter
    {
        MinPointMagPointMipPoint,
        MinPointMagPointMipLinear,
        MinPointMagLinearMipPoint,
        MinPointMagLinearMipLinear,
        MinLinearMagPointMipPoint,
        MinLinearMagPointMipLinear,
        MinLinearMagLinearMipPoint,
        MinLinearMagLinearMipLinear,
    };

    enum class TextureFormat
    {
        BC1_UINT_NORMALISED,
        BC1_UINT_NORMALISED_NON_LINEAL,
        BC2_UINT_NORMALISED,
        BC2_UINT_NORMALISED_NON_LINEAL,
        BC3_UINT_NORMALISED,
        BC3_UINT_NORMALISED_NON_LINEAL,
        BC4_UINT_NORMALISED,
        BC5_UINT_NORMALISED,
        BC7_UINT_NORMALISED,
        BC7_UINT_NORMALISED_NON_LINEAL,
        R8_INT,
        R8_INT_NORMALISED,
        R8_UINT,
        R8_UINT_NORMALISED,
        R16_INT,
        R16_INT_NORMALISED,
        R16_UINT,
        R16_UINT_NORMALISED,
        R16_FLOAT,
        R32_INT,
        R32_UINT,
        R32_FLOAT,
        RG8_INT,
        RG8_INT_NORMALISED,
        RG8_UINT,
        RG8_UINT_NORMALISED,
        RG16_INT,
        RG16_INT_NORMALISED,
        RG16_UINT,
        RG16_UINT_NORMALISED,
        RG16_FLOAT,
        RG32_INT,
        RG32_UINT,
        RG32_FLOAT,
        RGBA8_INT,
        RGBA8_INT_NORMALISED,
        RGBA8_UINT,
        RGBA8_UINT_NORMALISED,
        RGBA8_UINT_NORMALISED_NON_LINEAL,
        RGBA16_INT,
        RGBA16_INT_NORMALISED,
        RGBA16_UINT,
        RGBA16_UINT_NORMALISED,
        RGBA16_FLOAT,
        RGBA32_INT,
        RGBA32_UINT,
        RGBA32_FLOAT,
        D16_UINT_NORMALISED,
        D16_FLOAT,
        D32_UINT_NORMALISED,
        D32_FLOAT,
        D24X8_UINT_NORMALISED,
        D24X8_FLOAT,
        D24S8_UINT_NORMALISED,
    };

    enum class TextureLayout
    {
        Source,
        Destination,
        Dual,
    };

    enum class VertexElement
    {
        Position,
        Color,
        Texture,
    };

    enum class VertexFormat
    {
        Float1,
        Float2,
        Float3,
        Float4,
        Byte4,
        Byte4Normalised,
        Short2,
        Short2Normalised,
        Short4,
        Short4Normalised,
        UByte4,
        UByte4Normalised,
        UShort2,
        UShort2Normalised,
        UShort4,
        UShort4Normalised,
    };

    enum class VertexTopology
    {
        Point,
        Line,
        Triangle,
    };

    struct Attrib
    {
        VertexElement mElement = VertexElement::Position;
        UInt32        mIndex   = 0;
        VertexFormat  mFormat  = VertexFormat::Float4;
        UInt32        mOffset  = 0;
    };

    struct Descriptor
    {
        BlendFactor    mBlendColorSrcFactor = BlendFactor::One;
        BlendFactor    mBlendColorDstFactor = BlendFactor::Zero;
        BlendEquation  mBlendColorEquation  = BlendEquation::Add;
        BlendFactor    mBlendAlphaSrcFactor = BlendFactor::One;
        BlendFactor    mBlendAlphaDstFactor = BlendFactor::Zero;
        BlendEquation  mBlendAlphaEquation  = BlendEquation::Add;
        BlendColor     mBlendMask           = BlendColor::RGBA;
        Bool           mDepthMask           = true;
        TestCondition  mDepthCondition      = TestCondition::LessEqual;
        UInt8          mStencilMask         = 0b11111111;
        TestCondition  mStencilCondition    = TestCondition::Always;
        TestAction     mStencilOpFail       = TestAction::Keep;
        TestAction     mStencilOpFailZ      = TestAction::Keep;
        TestAction     mStencilOpPass       = TestAction::Keep;
        Span<Attrib>   mInputLayout         = { };
        VertexTopology mInputTopology       = VertexTopology::Triangle;
    };

    struct Rect
    {
        UInt16 mLeft = 0, mTop = 0, mRight = UINT16_MAX, mBottom = UINT16_MAX;
    };

    struct Submission
    {
        struct Range
        {
            UInt16 mBuffer = 0;
            UInt32 mOffset = 0;
            UInt32 mCount  = 0;
        };

        Range  mVBO                   {   };
        Range  mIBO                   {   };
        Range  mCBO[kMaxDrawConstant] {   };
        Rect   mScissor               {   };
        UInt16 mPipeline              { 0 };
        UInt16 mDescriptor            { 0 };
        UInt8  mStencil               { 0b11111111 };
    };
}