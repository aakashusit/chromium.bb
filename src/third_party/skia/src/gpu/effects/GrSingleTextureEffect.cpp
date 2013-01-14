/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "effects/GrSingleTextureEffect.h"
#include "gl/GrGLEffect.h"
#include "gl/GrGLSL.h"
#include "gl/GrGLTexture.h"
#include "GrBackendEffectFactory.h"
#include "GrTexture.h"

class GrGLSingleTextureEffect : public GrGLLegacyEffect {
public:
    GrGLSingleTextureEffect(const GrBackendEffectFactory& factory, const GrEffect&)
    : INHERITED (factory) {
    }

    virtual void emitVS(GrGLShaderBuilder* builder,
                        const char* vertexCoords) SK_OVERRIDE { }
    virtual void emitFS(GrGLShaderBuilder* builder,
                        const char* outputColor,
                        const char* inputColor,
                        const TextureSamplerArray& samplers) SK_OVERRIDE {
        builder->fFSCode.appendf("\t%s = ", outputColor);
        builder->appendTextureLookupAndModulate(&builder->fFSCode, inputColor, samplers[0]);
        builder->fFSCode.append(";\n");
    }

    static inline EffectKey GenKey(const GrEffect&, const GrGLCaps&) { return 0; }

private:

    typedef GrGLLegacyEffect INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

GrSingleTextureEffect::GrSingleTextureEffect(GrTexture* texture)
    : INHERITED(1)
    , fTextureAccess(texture) {
}

GrSingleTextureEffect::GrSingleTextureEffect(GrTexture* texture, bool bilerp)
    : INHERITED(1)
    , fTextureAccess(texture, bilerp) {
}

GrSingleTextureEffect::GrSingleTextureEffect(GrTexture* texture, const GrTextureParams& params)
    : INHERITED(1)
    , fTextureAccess(texture, params) {
}

GrSingleTextureEffect::~GrSingleTextureEffect() {
}

const GrTextureAccess& GrSingleTextureEffect::textureAccess(int index) const {
    GrAssert(0 == index);
    return fTextureAccess;
}

const GrBackendEffectFactory& GrSingleTextureEffect::getFactory() const {
    return GrTBackendEffectFactory<GrSingleTextureEffect>::getInstance();
}

///////////////////////////////////////////////////////////////////////////////

GR_DEFINE_EFFECT_TEST(GrSingleTextureEffect);

GrEffect* GrSingleTextureEffect::TestCreate(SkRandom* random,
                                            GrContext* context,
                                            GrTexture* textures[]) {
    int texIdx = random->nextBool() ? GrEffectUnitTest::kSkiaPMTextureIdx :
                                      GrEffectUnitTest::kAlphaTextureIdx;
    return SkNEW_ARGS(GrSingleTextureEffect, (textures[texIdx]));
}