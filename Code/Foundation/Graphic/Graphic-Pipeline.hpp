// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2019 Agustin L. Alvarez. All rights reserved.
//
// This work is licensed under the terms of the Apache License, Version 2.0.
//
// See <https://opensource.org/licenses/Apache-2.0>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Core/Core.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class BlendFactor      : UInt8
    {
        /// Taken constantly as (0, 0, 0, 0).
        Zero,

        /// Taken constantly as (1, 1, 1, 1).
        One,

        /// Taken from the source as (R, G, B, A).
        SrcColor,

        /// Taken from the source as (1 - R, 1 - G, 1 - B, 1 - A).
        OneMinusSrcColor,

        /// Taken from the source as (A, A, A, A).
        SrcAlpha,

        /// Taken from the source as (1 - A, 1 - A, 1 - A, 1 - A).
        OneMinusSrcAlpha,

        /// Taken from the destination as (A, A, A, A).
        DstColor,

        /// Taken from the destination as (1 - A, 1 - A, 1 - A, 1 - A).
        OneMinusDstColor,

        /// Taken from the destination as (R, G, B, A).
        DstAlpha,

        /// Taken from the destination as (1 - R, 1 - G, 1 - B, 1 - A).
        OneMinusDstAlpha,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class BlendFunction    : UInt8
    {
        /// Adds the source factor to the destination factor.
        Add,

        /// Subtracts the source factor from the destination factor.
        Subtract,

        /// Subtracts the destination factor from the source factor.
        ReverseSubtract,

        /// Component-wise minimum value of the source and destination factor.
        Min,

        /// Component-wise maximum value of the source and destination factor.
        Max,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class BlendMask        : UInt8
    {
        /// R | G | B | A
        RGBA = 0b00001111,

        /// R | G | B | ~
        RGB  = 0b00000111,

        /// R | G | ~ | A
        RGA  = 0b00001011,

        /// R | ~ | B | A
        RBA  = 0b00001101,

        /// R | G | ~ | ~
        RG   = 0b00000011,

        /// R | ~ | B | ~
        RB   = 0b00000101,

        /// R | ~ | ~ | A
        RA   = 0b00001001,

        /// R | ~ | ~ | ~
        R    = 0b00000001,

        /// ~ | G | B | A
        GBA  = 0b00001110,

        /// ~ | G | B | ~
        GB   = 0b00000110,

        /// ~ | G | ~ | A
        GA   = 0b00001010,

        /// ~ | G | ~ | ~.
        G    = 0b00000010,

        /// ~ | ~ | B | A
        BA   = 0b00001100,

        /// ~ | ~ | B | ~
        B    = 0b00000100,

        /// ~ | ~ | ~ | A
        A    = 0b00001000,

        /// ~ | ~ | ~ | ~
        None = 0b00000000,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class Clear            : UInt8
    {
        // [Missing Documentation]
        COLOR   = 0b00000001,

        // [Missing Documentation]
        DEPTH   = 0b00000010,

        // [Missing Documentation]
        STENCIL = 0b00000100,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class Phase            : UInt8
    {
        // [Missing Documentation]
        VS,

        // [Missing Documentation]
        FS,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class TestAction       : UInt8
    {
        // [Missing Documentation]
        Keep,

        // [Missing Documentation]
        Replace,

        // [Missing Documentation]
        Zero,

        // [Missing Documentation]
        Decrease,

        // [Missing Documentation]
        DecreaseClamp,

        // [Missing Documentation]
        Invert,

        // [Missing Documentation]
        Increase,

        // [Missing Documentation]
        IncreaseClamp,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class TestCondition    : UInt8
    {
        // [Missing Documentation]
        Always,

        // [Missing Documentation]
        Never,

        // [Missing Documentation]
        Greater,

        // [Missing Documentation]
        GreaterEqual,

        // [Missing Documentation]
        Equal,

        // [Missing Documentation]
        NotEqual,

        // [Missing Documentation]
        Less,

        // [Missing Documentation]
        LessEqual,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class TextureEdge      : UInt8
    {
        // [Missing Documentation]
        Clamp,

        // [Missing Documentation]
        ClampMirror,

        // [Missing Documentation]
        Repeat,

        // [Missing Documentation]
        RepeatMirror,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class TextureFilter    : UInt8
    {
        // [Missing Documentation]
        MinNearestMagNearest,

        // [Missing Documentation]
        MinNearestMagNearestMipNearest,

        // [Missing Documentation]
        MinNearestMagNearestMipLinear,

        // [Missing Documentation]
        MinNearestMagLinear,

        // [Missing Documentation]
        MinNearestMagLinearMipNearest,

        // [Missing Documentation]
        MinNearestMagLinearMipLinear,

        // [Missing Documentation]
        MinLinearMagNearest,

        // [Missing Documentation]
        MinLinearMagNearestMipNearest,

        // [Missing Documentation]
        MinLinearMagNearestMipLinear,

        // [Missing Documentation]
        MinLinearMagLinear,

        // [Missing Documentation]
        MinLinearMagLinearMipNearest,

        // [Missing Documentation]
        MinLinearMagLinearMipLinear,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    enum class TextureFormat    : UInt8
    {
        // [Missing Documentation]
        BC1_UINT_NORMALISED,

        // [Missing Documentation]
        BC1_UINT_NORMALISED_NON_LINEAL,

        // [Missing Documentation]
        BC2_UINT_NORMALISED,

        // [Missing Documentation]
        BC2_UINT_NORMALISED_NON_LINEAL,

        // [Missing Documentation]
        BC3_UINT_NORMALISED,

        // [Missing Documentation]
        BC3_UINT_NORMALISED_NON_LINEAL,

        // [Missing Documentation]
        BC4_UINT_NORMALISED,

        // [Missing Documentation]
        BC5_UINT_NORMALISED,

        // [Missing Documentation]
        BC7_UINT_NORMALISED,

        // [Missing Documentation]
        BC7_UINT_NORMALISED_NON_LINEAL,

        // [Missing Documentation]
        R8_SINT,

        // [Missing Documentation]
        R8_SINT_NORMALISED,

        // [Missing Documentation]
        R8_UINT,

        // [Missing Documentation]
        R8_UINT_NORMALISED,

        // [Missing Documentation]
        R16_SINT,

        // [Missing Documentation]
        R16_SINT_NORMALISED,

        // [Missing Documentation]
        R16_UINT,

        // [Missing Documentation]
        R16_UINT_NORMALISED,

        // [Missing Documentation]
        R16_FLOAT,

        // [Missing Documentation]
        R32_SINT,

        // [Missing Documentation]
        R32_UINT,

        // [Missing Documentation]
        R32_FLOAT,

        // [Missing Documentation]
        RG8_SINT,

        // [Missing Documentation]
        RG8_SINT_NORMALISED,

        // [Missing Documentation]
        RG8_UINT,

        // [Missing Documentation]
        RG8_UINT_NORMALISED,

        // [Missing Documentation]
        RG16_SINT,

        // [Missing Documentation]
        RG16_SINT_NORMALISED,

        // [Missing Documentation]
        RG16_UINT,

        // [Missing Documentation]
        RG16_UINT_NORMALISED,

        // [Missing Documentation]
        RG16_FLOAT,

        // [Missing Documentation]
        RG32_SINT,

        // [Missing Documentation]
        RG32_UINT,

        // [Missing Documentation]
        RG32_FLOAT,

        // [Missing Documentation]
        RGBA8_SINT,

        // [Missing Documentation]
        RGBA8_SINT_NORMALISED,

        // [Missing Documentation]
        RGBA8_UINT,

        // [Missing Documentation]
        RGBA8_UINT_NORMALISED,

        // [Missing Documentation]
        RGBA8_UINT_NORMALISED_NON_LINEAL,

        // [Missing Documentation]
        RGBA16_SINT,

        // [Missing Documentation]
        RGBA16_SINT_NORMALISED,

        // [Missing Documentation]
        RGBA16_UINT,

        // [Missing Documentation]
        RGBA16_UINT_NORMALISED,

        // [Missing Documentation]
        RGBA16_FLOAT,

        // [Missing Documentation]
        RGBA32_SINT,

        // [Missing Documentation]
        RGBA32_UINT,

        // [Missing Documentation]
        RGBA32_FLOAT,

        // [Missing Documentation]
        D16_UINT_NORMALISED,

        // [Missing Documentation]
        D16_FLOAT,

        // [Missing Documentation]
        D32_UINT_NORMALISED,

        // [Missing Documentation]
        D32_FLOAT,

        // [Missing Documentation]
        D24X8_UINT_NORMALISED,

        // [Missing Documentation]
        D24X8_FLOAT,

        // [Missing Documentation]
        D24S8_UINT_NORMALISED,
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    struct Sampler
    {
        // [Missing Documentation]
        TextureEdge   EdgeX  = TextureEdge::Repeat;

        // [Missing Documentation]
        TextureEdge   EdgeY  = TextureEdge::Repeat;

        // [Missing Documentation]
        TextureFilter Filter = TextureFilter::MinLinearMagLinear;
    };

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    struct State
    {
        // [Missing Documentation]
        BlendFactor   ColorSrcFactor  = BlendFactor::One;

        // [Missing Documentation]
        BlendFactor   ColorDstFactor  = BlendFactor::Zero;

        // [Missing Documentation]
        BlendFunction ColorEquation   = BlendFunction::Add;

        // [Missing Documentation]
        BlendFactor   AlphaSrcFactor  = BlendFactor::One;

        // [Missing Documentation]
        BlendFactor   AlphaDstFactor  = BlendFactor::Zero;

        // [Missing Documentation]
        BlendFunction AlphaEquation   = BlendFunction::Add;

        // [Missing Documentation]
        BlendMask     Mask            = BlendMask::RGBA;

        // [Missing Documentation]
        TestCondition DepthFunction   = TestCondition::LessEqual;

        // [Missing Documentation]
        Bool          DepthMask       = true;

        // [Missing Documentation]
        TestCondition StencilFunction = TestCondition::Always;

        // [Missing Documentation]
        TestAction    StencilOpFail   = TestAction::Keep;

        // [Missing Documentation]
        TestAction    StencilOpFailZ  = TestAction::Keep;

        // [Missing Documentation]
        TestAction    StencilOpPass   = TestAction::Keep;
    };
}