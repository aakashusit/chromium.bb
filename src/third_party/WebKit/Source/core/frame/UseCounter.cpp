
/*
 * Copyright (C) 2012 Google, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY GOOGLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "core/frame/UseCounter.h"

#include "core/css/CSSStyleSheet.h"
#include "core/css/StyleSheetContents.h"
#include "core/dom/Document.h"
#include "core/dom/ExecutionContext.h"
#include "core/frame/DOMWindow.h"
#include "core/frame/FrameHost.h"
#include "core/frame/PageConsole.h"
#include "public/platform/Platform.h"

namespace WebCore {

static int totalPagesMeasuredCSSSampleId() { return 1; }

int UseCounter::m_muteCount = 0;

// FIXME : This mapping should be autogenerated. This function should
//         be moved to a separate file and a script run at build time
//         to detect new values in CSSPropertyID and add them to the
//         end of this function. This file would be checked in.
//         https://code.google.com/p/chromium/issues/detail?id=234940
int UseCounter::mapCSSPropertyIdToCSSSampleIdForHistogram(int id)
{
    CSSPropertyID cssPropertyID = convertToCSSPropertyID(id);

    switch (cssPropertyID) {
    // Begin at 2, because 1 is reserved for totalPagesMeasuredCSSSampleId.
    case CSSPropertyColor: return 2;
    case CSSPropertyDirection: return 3;
    case CSSPropertyDisplay: return 4;
    case CSSPropertyFont: return 5;
    case CSSPropertyFontFamily: return 6;
    case CSSPropertyFontSize: return 7;
    case CSSPropertyFontStyle: return 8;
    case CSSPropertyFontVariant: return 9;
    case CSSPropertyFontWeight: return 10;
    case CSSPropertyTextRendering: return 11;
    case CSSPropertyWebkitFontFeatureSettings: return 12;
    case CSSPropertyFontKerning: return 13;
    case CSSPropertyWebkitFontSmoothing: return 14;
    case CSSPropertyFontVariantLigatures: return 15;
    case CSSPropertyWebkitLocale: return 16;
    case CSSPropertyWebkitTextOrientation: return 17;
    case CSSPropertyWebkitWritingMode: return 18;
    case CSSPropertyZoom: return 19;
    case CSSPropertyLineHeight: return 20;
    case CSSPropertyBackground: return 21;
    case CSSPropertyBackgroundAttachment: return 22;
    case CSSPropertyBackgroundClip: return 23;
    case CSSPropertyBackgroundColor: return 24;
    case CSSPropertyBackgroundImage: return 25;
    case CSSPropertyBackgroundOrigin: return 26;
    case CSSPropertyBackgroundPosition: return 27;
    case CSSPropertyBackgroundPositionX: return 28;
    case CSSPropertyBackgroundPositionY: return 29;
    case CSSPropertyBackgroundRepeat: return 30;
    case CSSPropertyBackgroundRepeatX: return 31;
    case CSSPropertyBackgroundRepeatY: return 32;
    case CSSPropertyBackgroundSize: return 33;
    case CSSPropertyBorder: return 34;
    case CSSPropertyBorderBottom: return 35;
    case CSSPropertyBorderBottomColor: return 36;
    case CSSPropertyBorderBottomLeftRadius: return 37;
    case CSSPropertyBorderBottomRightRadius: return 38;
    case CSSPropertyBorderBottomStyle: return 39;
    case CSSPropertyBorderBottomWidth: return 40;
    case CSSPropertyBorderCollapse: return 41;
    case CSSPropertyBorderColor: return 42;
    case CSSPropertyBorderImage: return 43;
    case CSSPropertyBorderImageOutset: return 44;
    case CSSPropertyBorderImageRepeat: return 45;
    case CSSPropertyBorderImageSlice: return 46;
    case CSSPropertyBorderImageSource: return 47;
    case CSSPropertyBorderImageWidth: return 48;
    case CSSPropertyBorderLeft: return 49;
    case CSSPropertyBorderLeftColor: return 50;
    case CSSPropertyBorderLeftStyle: return 51;
    case CSSPropertyBorderLeftWidth: return 52;
    case CSSPropertyBorderRadius: return 53;
    case CSSPropertyBorderRight: return 54;
    case CSSPropertyBorderRightColor: return 55;
    case CSSPropertyBorderRightStyle: return 56;
    case CSSPropertyBorderRightWidth: return 57;
    case CSSPropertyBorderSpacing: return 58;
    case CSSPropertyBorderStyle: return 59;
    case CSSPropertyBorderTop: return 60;
    case CSSPropertyBorderTopColor: return 61;
    case CSSPropertyBorderTopLeftRadius: return 62;
    case CSSPropertyBorderTopRightRadius: return 63;
    case CSSPropertyBorderTopStyle: return 64;
    case CSSPropertyBorderTopWidth: return 65;
    case CSSPropertyBorderWidth: return 66;
    case CSSPropertyBottom: return 67;
    case CSSPropertyBoxShadow: return 68;
    case CSSPropertyBoxSizing: return 69;
    case CSSPropertyCaptionSide: return 70;
    case CSSPropertyClear: return 71;
    case CSSPropertyClip: return 72;
    case CSSPropertyWebkitClipPath: return 73;
    case CSSPropertyContent: return 74;
    case CSSPropertyCounterIncrement: return 75;
    case CSSPropertyCounterReset: return 76;
    case CSSPropertyCursor: return 77;
    case CSSPropertyEmptyCells: return 78;
    case CSSPropertyFloat: return 79;
    case CSSPropertyFontStretch: return 80;
    case CSSPropertyHeight: return 81;
    case CSSPropertyImageRendering: return 82;
    case CSSPropertyLeft: return 83;
    case CSSPropertyLetterSpacing: return 84;
    case CSSPropertyListStyle: return 85;
    case CSSPropertyListStyleImage: return 86;
    case CSSPropertyListStylePosition: return 87;
    case CSSPropertyListStyleType: return 88;
    case CSSPropertyMargin: return 89;
    case CSSPropertyMarginBottom: return 90;
    case CSSPropertyMarginLeft: return 91;
    case CSSPropertyMarginRight: return 92;
    case CSSPropertyMarginTop: return 93;
    case CSSPropertyMaxHeight: return 94;
    case CSSPropertyMaxWidth: return 95;
    case CSSPropertyMinHeight: return 96;
    case CSSPropertyMinWidth: return 97;
    case CSSPropertyOpacity: return 98;
    case CSSPropertyOrphans: return 99;
    case CSSPropertyOutline: return 100;
    case CSSPropertyOutlineColor: return 101;
    case CSSPropertyOutlineOffset: return 102;
    case CSSPropertyOutlineStyle: return 103;
    case CSSPropertyOutlineWidth: return 104;
    case CSSPropertyOverflow: return 105;
    case CSSPropertyOverflowWrap: return 106;
    case CSSPropertyOverflowX: return 107;
    case CSSPropertyOverflowY: return 108;
    case CSSPropertyPadding: return 109;
    case CSSPropertyPaddingBottom: return 110;
    case CSSPropertyPaddingLeft: return 111;
    case CSSPropertyPaddingRight: return 112;
    case CSSPropertyPaddingTop: return 113;
    case CSSPropertyPage: return 114;
    case CSSPropertyPageBreakAfter: return 115;
    case CSSPropertyPageBreakBefore: return 116;
    case CSSPropertyPageBreakInside: return 117;
    case CSSPropertyPointerEvents: return 118;
    case CSSPropertyPosition: return 119;
    case CSSPropertyQuotes: return 120;
    case CSSPropertyResize: return 121;
    case CSSPropertyRight: return 122;
    case CSSPropertySize: return 123;
    case CSSPropertySrc: return 124;
    case CSSPropertySpeak: return 125;
    case CSSPropertyTableLayout: return 126;
    case CSSPropertyTabSize: return 127;
    case CSSPropertyTextAlign: return 128;
    case CSSPropertyTextDecoration: return 129;
    case CSSPropertyTextIndent: return 130;
    /* Removed CSSPropertyTextLineThrough - 131 */
    case CSSPropertyTextLineThroughColor: return 132;
    case CSSPropertyTextLineThroughMode: return 133;
    case CSSPropertyTextLineThroughStyle: return 134;
    case CSSPropertyTextLineThroughWidth: return 135;
    case CSSPropertyTextOverflow: return 136;
    /* Removed CSSPropertyTextOverline - 137 */
    case CSSPropertyTextOverlineColor: return 138;
    case CSSPropertyTextOverlineMode: return 139;
    case CSSPropertyTextOverlineStyle: return 140;
    case CSSPropertyTextOverlineWidth: return 141;
    case CSSPropertyTextShadow: return 142;
    case CSSPropertyTextTransform: return 143;
    /* Removed CSSPropertyTextUnderline - 144 */
    case CSSPropertyTextUnderlineColor: return 145;
    case CSSPropertyTextUnderlineMode: return 146;
    case CSSPropertyTextUnderlineStyle: return 147;
    case CSSPropertyTextUnderlineWidth: return 148;
    case CSSPropertyTop: return 149;
    case CSSPropertyTransition: return 150;
    case CSSPropertyTransitionDelay: return 151;
    case CSSPropertyTransitionDuration: return 152;
    case CSSPropertyTransitionProperty: return 153;
    case CSSPropertyTransitionTimingFunction: return 154;
    case CSSPropertyUnicodeBidi: return 155;
    case CSSPropertyUnicodeRange: return 156;
    case CSSPropertyVerticalAlign: return 157;
    case CSSPropertyVisibility: return 158;
    case CSSPropertyWhiteSpace: return 159;
    case CSSPropertyWidows: return 160;
    case CSSPropertyWidth: return 161;
    case CSSPropertyWordBreak: return 162;
    case CSSPropertyWordSpacing: return 163;
    case CSSPropertyWordWrap: return 164;
    case CSSPropertyZIndex: return 165;
    case CSSPropertyWebkitAnimation: return 166;
    case CSSPropertyWebkitAnimationDelay: return 167;
    case CSSPropertyWebkitAnimationDirection: return 168;
    case CSSPropertyWebkitAnimationDuration: return 169;
    case CSSPropertyWebkitAnimationFillMode: return 170;
    case CSSPropertyWebkitAnimationIterationCount: return 171;
    case CSSPropertyWebkitAnimationName: return 172;
    case CSSPropertyWebkitAnimationPlayState: return 173;
    case CSSPropertyWebkitAnimationTimingFunction: return 174;
    case CSSPropertyWebkitAppearance: return 175;
    case CSSPropertyWebkitAspectRatio: return 176;
    case CSSPropertyWebkitBackfaceVisibility: return 177;
    case CSSPropertyWebkitBackgroundClip: return 178;
    case CSSPropertyWebkitBackgroundComposite: return 179;
    case CSSPropertyWebkitBackgroundOrigin: return 180;
    case CSSPropertyWebkitBackgroundSize: return 181;
    case CSSPropertyWebkitBorderAfter: return 182;
    case CSSPropertyWebkitBorderAfterColor: return 183;
    case CSSPropertyWebkitBorderAfterStyle: return 184;
    case CSSPropertyWebkitBorderAfterWidth: return 185;
    case CSSPropertyWebkitBorderBefore: return 186;
    case CSSPropertyWebkitBorderBeforeColor: return 187;
    case CSSPropertyWebkitBorderBeforeStyle: return 188;
    case CSSPropertyWebkitBorderBeforeWidth: return 189;
    case CSSPropertyWebkitBorderEnd: return 190;
    case CSSPropertyWebkitBorderEndColor: return 191;
    case CSSPropertyWebkitBorderEndStyle: return 192;
    case CSSPropertyWebkitBorderEndWidth: return 193;
    case CSSPropertyWebkitBorderFit: return 194;
    case CSSPropertyWebkitBorderHorizontalSpacing: return 195;
    case CSSPropertyWebkitBorderImage: return 196;
    case CSSPropertyWebkitBorderRadius: return 197;
    case CSSPropertyWebkitBorderStart: return 198;
    case CSSPropertyWebkitBorderStartColor: return 199;
    case CSSPropertyWebkitBorderStartStyle: return 200;
    case CSSPropertyWebkitBorderStartWidth: return 201;
    case CSSPropertyWebkitBorderVerticalSpacing: return 202;
    case CSSPropertyWebkitBoxAlign: return 203;
    case CSSPropertyWebkitBoxDirection: return 204;
    case CSSPropertyWebkitBoxFlex: return 205;
    case CSSPropertyWebkitBoxFlexGroup: return 206;
    case CSSPropertyWebkitBoxLines: return 207;
    case CSSPropertyWebkitBoxOrdinalGroup: return 208;
    case CSSPropertyWebkitBoxOrient: return 209;
    case CSSPropertyWebkitBoxPack: return 210;
    case CSSPropertyWebkitBoxReflect: return 211;
    case CSSPropertyWebkitBoxShadow: return 212;
    // CSSPropertyWebkitColumnAxis was 214
    case CSSPropertyWebkitColumnBreakAfter: return 215;
    case CSSPropertyWebkitColumnBreakBefore: return 216;
    case CSSPropertyWebkitColumnBreakInside: return 217;
    case CSSPropertyWebkitColumnCount: return 218;
    case CSSPropertyWebkitColumnGap: return 219;
    // CSSPropertyWebkitColumnProgression was 220
    case CSSPropertyWebkitColumnRule: return 221;
    case CSSPropertyWebkitColumnRuleColor: return 222;
    case CSSPropertyWebkitColumnRuleStyle: return 223;
    case CSSPropertyWebkitColumnRuleWidth: return 224;
    case CSSPropertyWebkitColumnSpan: return 225;
    case CSSPropertyWebkitColumnWidth: return 226;
    case CSSPropertyWebkitColumns: return 227;
#if defined(ENABLE_CSS_BOX_DECORATION_BREAK) && ENABLE_CSS_BOX_DECORATION_BREAK
    case CSSPropertyWebkitBoxDecorationBreak: return 228;
#endif
#if defined(ENABLE_CSS_FILTERS) && ENABLE_CSS_FILTERS
    case CSSPropertyWebkitFilter: return 229;
#endif
    case CSSPropertyAlignContent: return 230;
    case CSSPropertyAlignItems: return 231;
    case CSSPropertyAlignSelf: return 232;
    case CSSPropertyFlex: return 233;
    case CSSPropertyFlexBasis: return 234;
    case CSSPropertyFlexDirection: return 235;
    case CSSPropertyFlexFlow: return 236;
    case CSSPropertyFlexGrow: return 237;
    case CSSPropertyFlexShrink: return 238;
    case CSSPropertyFlexWrap: return 239;
    case CSSPropertyJustifyContent: return 240;
    case CSSPropertyWebkitFontSizeDelta: return 241;
    case CSSPropertyGridTemplateColumns: return 242;
    case CSSPropertyGridTemplateRows: return 243;
    case CSSPropertyGridColumnStart: return 244;
    case CSSPropertyGridColumnEnd: return 245;
    case CSSPropertyGridRowStart: return 246;
    case CSSPropertyGridRowEnd: return 247;
    case CSSPropertyGridColumn: return 248;
    case CSSPropertyGridRow: return 249;
    case CSSPropertyGridAutoFlow: return 250;
    case CSSPropertyWebkitHighlight: return 251;
    case CSSPropertyWebkitHyphenateCharacter: return 252;
    case CSSPropertyWebkitLineBoxContain: return 257;
    // case CSSPropertyWebkitLineAlign: return 258;
    case CSSPropertyWebkitLineBreak: return 259;
    case CSSPropertyWebkitLineClamp: return 260;
    // case CSSPropertyWebkitLineGrid: return 261;
    // case CSSPropertyWebkitLineSnap: return 262;
    case CSSPropertyWebkitLogicalWidth: return 263;
    case CSSPropertyWebkitLogicalHeight: return 264;
    case CSSPropertyWebkitMarginAfterCollapse: return 265;
    case CSSPropertyWebkitMarginBeforeCollapse: return 266;
    case CSSPropertyWebkitMarginBottomCollapse: return 267;
    case CSSPropertyWebkitMarginTopCollapse: return 268;
    case CSSPropertyWebkitMarginCollapse: return 269;
    case CSSPropertyWebkitMarginAfter: return 270;
    case CSSPropertyWebkitMarginBefore: return 271;
    case CSSPropertyWebkitMarginEnd: return 272;
    case CSSPropertyWebkitMarginStart: return 273;
    // CSSPropertyWebkitMarquee was 274.
    // CSSPropertyInternalMarquee* were 275-279.
    case CSSPropertyWebkitMask: return 280;
    case CSSPropertyWebkitMaskBoxImage: return 281;
    case CSSPropertyWebkitMaskBoxImageOutset: return 282;
    case CSSPropertyWebkitMaskBoxImageRepeat: return 283;
    case CSSPropertyWebkitMaskBoxImageSlice: return 284;
    case CSSPropertyWebkitMaskBoxImageSource: return 285;
    case CSSPropertyWebkitMaskBoxImageWidth: return 286;
    case CSSPropertyWebkitMaskClip: return 287;
    case CSSPropertyWebkitMaskComposite: return 288;
    case CSSPropertyWebkitMaskImage: return 289;
    case CSSPropertyWebkitMaskOrigin: return 290;
    case CSSPropertyWebkitMaskPosition: return 291;
    case CSSPropertyWebkitMaskPositionX: return 292;
    case CSSPropertyWebkitMaskPositionY: return 293;
    case CSSPropertyWebkitMaskRepeat: return 294;
    case CSSPropertyWebkitMaskRepeatX: return 295;
    case CSSPropertyWebkitMaskRepeatY: return 296;
    case CSSPropertyWebkitMaskSize: return 297;
    case CSSPropertyWebkitMaxLogicalWidth: return 298;
    case CSSPropertyWebkitMaxLogicalHeight: return 299;
    case CSSPropertyWebkitMinLogicalWidth: return 300;
    case CSSPropertyWebkitMinLogicalHeight: return 301;
    // WebkitNbspMode has been deleted, was return 302;
    case CSSPropertyOrder: return 303;
    case CSSPropertyWebkitPaddingAfter: return 304;
    case CSSPropertyWebkitPaddingBefore: return 305;
    case CSSPropertyWebkitPaddingEnd: return 306;
    case CSSPropertyWebkitPaddingStart: return 307;
    case CSSPropertyWebkitPerspective: return 308;
    case CSSPropertyWebkitPerspectiveOrigin: return 309;
    case CSSPropertyWebkitPerspectiveOriginX: return 310;
    case CSSPropertyWebkitPerspectiveOriginY: return 311;
    case CSSPropertyWebkitPrintColorAdjust: return 312;
    case CSSPropertyWebkitRtlOrdering: return 313;
    case CSSPropertyWebkitRubyPosition: return 314;
    case CSSPropertyWebkitTextCombine: return 315;
    case CSSPropertyWebkitTextDecorationsInEffect: return 316;
    case CSSPropertyWebkitTextEmphasis: return 317;
    case CSSPropertyWebkitTextEmphasisColor: return 318;
    case CSSPropertyWebkitTextEmphasisPosition: return 319;
    case CSSPropertyWebkitTextEmphasisStyle: return 320;
    case CSSPropertyWebkitTextFillColor: return 321;
    case CSSPropertyWebkitTextSecurity: return 322;
    case CSSPropertyWebkitTextStroke: return 323;
    case CSSPropertyWebkitTextStrokeColor: return 324;
    case CSSPropertyWebkitTextStrokeWidth: return 325;
    case CSSPropertyWebkitTransform: return 326;
    case CSSPropertyWebkitTransformOrigin: return 327;
    case CSSPropertyWebkitTransformOriginX: return 328;
    case CSSPropertyWebkitTransformOriginY: return 329;
    case CSSPropertyWebkitTransformOriginZ: return 330;
    case CSSPropertyWebkitTransformStyle: return 331;
    case CSSPropertyWebkitTransition: return 332;
    case CSSPropertyWebkitTransitionDelay: return 333;
    case CSSPropertyWebkitTransitionDuration: return 334;
    case CSSPropertyWebkitTransitionProperty: return 335;
    case CSSPropertyWebkitTransitionTimingFunction: return 336;
    case CSSPropertyWebkitUserDrag: return 337;
    case CSSPropertyWebkitUserModify: return 338;
    case CSSPropertyWebkitUserSelect: return 339;
    // case CSSPropertyWebkitFlowInto: return 340;
    // case CSSPropertyWebkitFlowFrom: return 341;
    // case CSSPropertyWebkitRegionFragment: return 342;
    // case CSSPropertyWebkitRegionBreakAfter: return 343;
    // case CSSPropertyWebkitRegionBreakBefore: return 344;
    // case CSSPropertyWebkitRegionBreakInside: return 345;
    // case CSSPropertyShapeInside: return 346;
    case CSSPropertyShapeOutside: return 347;
    case CSSPropertyShapeMargin: return 348;
    case CSSPropertyShapePadding: return 349;
    case CSSPropertyWebkitWrapFlow: return 350;
    case CSSPropertyWebkitWrapThrough: return 351;
    // CSSPropertyWebkitWrap was 352.
#if defined(ENABLE_TOUCH_EVENTS) && ENABLE_TOUCH_EVENTS
    case CSSPropertyWebkitTapHighlightColor: return 353;
#endif
#if defined(ENABLE_DRAGGABLE_REGION) && ENABLE_DRAGGABLE_REGION
    case CSSPropertyWebkitAppRegion: return 354;
#endif
    case CSSPropertyClipPath: return 355;
    case CSSPropertyClipRule: return 356;
    case CSSPropertyMask: return 357;
    case CSSPropertyEnableBackground: return 358;
    case CSSPropertyFilter: return 359;
    case CSSPropertyFloodColor: return 360;
    case CSSPropertyFloodOpacity: return 361;
    case CSSPropertyLightingColor: return 362;
    case CSSPropertyStopColor: return 363;
    case CSSPropertyStopOpacity: return 364;
    case CSSPropertyColorInterpolation: return 365;
    case CSSPropertyColorInterpolationFilters: return 366;
    case CSSPropertyColorProfile: return 367;
    case CSSPropertyColorRendering: return 368;
    case CSSPropertyFill: return 369;
    case CSSPropertyFillOpacity: return 370;
    case CSSPropertyFillRule: return 371;
    case CSSPropertyMarker: return 372;
    case CSSPropertyMarkerEnd: return 373;
    case CSSPropertyMarkerMid: return 374;
    case CSSPropertyMarkerStart: return 375;
    case CSSPropertyMaskType: return 376;
    case CSSPropertyShapeRendering: return 377;
    case CSSPropertyStroke: return 378;
    case CSSPropertyStrokeDasharray: return 379;
    case CSSPropertyStrokeDashoffset: return 380;
    case CSSPropertyStrokeLinecap: return 381;
    case CSSPropertyStrokeLinejoin: return 382;
    case CSSPropertyStrokeMiterlimit: return 383;
    case CSSPropertyStrokeOpacity: return 384;
    case CSSPropertyStrokeWidth: return 385;
    case CSSPropertyAlignmentBaseline: return 386;
    case CSSPropertyBaselineShift: return 387;
    case CSSPropertyDominantBaseline: return 388;
    case CSSPropertyGlyphOrientationHorizontal: return 389;
    case CSSPropertyGlyphOrientationVertical: return 390;
    case CSSPropertyKerning: return 391;
    case CSSPropertyTextAnchor: return 392;
    case CSSPropertyVectorEffect: return 393;
    case CSSPropertyWritingMode: return 394;
    // CSSPropertyWebkitSvgShadow has been removed, was return 395;
#if defined(ENABLE_CURSOR_VISIBILITY) && ENABLE_CURSOR_VISIBILITY
    case CSSPropertyWebkitCursorVisibility: return 396;
#endif
    // CSSPropertyImageOrientation has been removed, was return 397;
    // CSSPropertyImageResolution has been removed, was return 398;
#if defined(ENABLE_CSS_COMPOSITING) && ENABLE_CSS_COMPOSITING
    case CSSPropertyWebkitBlendMode: return 399;
    case CSSPropertyWebkitBackgroundBlendMode: return 400;
#endif
    case CSSPropertyTextDecorationLine: return 401;
    case CSSPropertyTextDecorationStyle: return 402;
    case CSSPropertyTextDecorationColor: return 403;
    case CSSPropertyTextAlignLast: return 404;
    case CSSPropertyTextUnderlinePosition: return 405;
    case CSSPropertyMaxZoom: return 406;
    case CSSPropertyMinZoom: return 407;
    case CSSPropertyOrientation: return 408;
    case CSSPropertyUserZoom: return 409;
    // CSSPropertyWebkitDashboardRegion was 410.
    // CSSPropertyWebkitOverflowScrolling was 411.
    case CSSPropertyWebkitAppRegion: return 412;
    case CSSPropertyWebkitFilter: return 413;
    case CSSPropertyWebkitBoxDecorationBreak: return 414;
    case CSSPropertyWebkitTapHighlightColor: return 415;
    case CSSPropertyBufferedRendering: return 416;
    case CSSPropertyGridAutoRows: return 417;
    case CSSPropertyGridAutoColumns: return 418;
    case CSSPropertyBackgroundBlendMode: return 419;
    case CSSPropertyMixBlendMode: return 420;
    case CSSPropertyTouchAction: return 421;
    case CSSPropertyGridArea: return 422;
    case CSSPropertyGridTemplateAreas: return 423;
    case CSSPropertyAnimation: return 424;
    case CSSPropertyAnimationDelay: return 425;
    case CSSPropertyAnimationDirection: return 426;
    case CSSPropertyAnimationDuration: return 427;
    case CSSPropertyAnimationFillMode: return 428;
    case CSSPropertyAnimationIterationCount: return 429;
    case CSSPropertyAnimationName: return 430;
    case CSSPropertyAnimationPlayState: return 431;
    case CSSPropertyAnimationTimingFunction: return 432;
    case CSSPropertyObjectFit: return 433;
    case CSSPropertyPaintOrder: return 434;
    case CSSPropertyMaskSourceType: return 435;
    case CSSPropertyIsolation: return 436;
    case CSSPropertyObjectPosition: return 437;
    case CSSPropertyInternalCallback: return 438;
    case CSSPropertyShapeImageThreshold: return 439;
    case CSSPropertyColumnFill: return 440;
    case CSSPropertyTextJustify: return 441;
    case CSSPropertyTouchActionDelay: return 442;
    case CSSPropertyJustifySelf: return 443;
    case CSSPropertyScrollBehavior: return 444;
    case CSSPropertyWillChange: return 445;
    case CSSPropertyTransform: return 446;
    case CSSPropertyTransformOrigin: return 447;
    case CSSPropertyTransformStyle: return 448;
    case CSSPropertyPerspective: return 449;
    case CSSPropertyPerspectiveOrigin: return 450;
    case CSSPropertyBackfaceVisibility: return 451;

    // Add new features above this line (don't change the assigned numbers of the existing
    // items) and update maximumCSSSampleId() with the new maximum value.

    // Internal properties should not be counted.
    case CSSPropertyInternalMarqueeDirection:
    case CSSPropertyInternalMarqueeIncrement:
    case CSSPropertyInternalMarqueeRepetition:
    case CSSPropertyInternalMarqueeSpeed:
    case CSSPropertyInternalMarqueeStyle:
    case CSSPropertyInvalid:
        ASSERT_NOT_REACHED();
        return 0;
    }

    return 0;
}

static int maximumCSSSampleId() { return 451; }

void UseCounter::muteForInspector()
{
    UseCounter::m_muteCount++;
}

void UseCounter::unmuteForInspector()
{
    UseCounter::m_muteCount--;
}

UseCounter::UseCounter()
{
    m_CSSFeatureBits.ensureSize(lastCSSProperty + 1);
    m_CSSFeatureBits.clearAll();
}

UseCounter::~UseCounter()
{
    // We always log PageDestruction so that we have a scale for the rest of the features.
    blink::Platform::current()->histogramEnumeration("WebCore.FeatureObserver", PageDestruction, NumberOfFeatures);

    updateMeasurements();
}

void UseCounter::updateMeasurements()
{
    blink::Platform::current()->histogramEnumeration("WebCore.FeatureObserver", PageVisits, NumberOfFeatures);

    if (m_countBits) {
        for (unsigned i = 0; i < NumberOfFeatures; ++i) {
            if (m_countBits->quickGet(i))
                blink::Platform::current()->histogramEnumeration("WebCore.FeatureObserver", i, NumberOfFeatures);
        }
        // Clearing count bits is timing sensitive.
        m_countBits->clearAll();
    }

    // FIXME: Sometimes this function is called more than once per page. The following
    //        bool guards against incrementing the page count when there are no CSS
    //        bits set. http://crbug.com/236262.
    bool needsPagesMeasuredUpdate = false;
    for (int i = firstCSSProperty; i <= lastCSSProperty; ++i) {
        if (m_CSSFeatureBits.quickGet(i)) {
            int cssSampleId = mapCSSPropertyIdToCSSSampleIdForHistogram(i);
            blink::Platform::current()->histogramEnumeration("WebCore.FeatureObserver.CSSProperties", cssSampleId, maximumCSSSampleId());
            needsPagesMeasuredUpdate = true;
        }
    }

    if (needsPagesMeasuredUpdate)
        blink::Platform::current()->histogramEnumeration("WebCore.FeatureObserver.CSSProperties", totalPagesMeasuredCSSSampleId(), maximumCSSSampleId());

    m_CSSFeatureBits.clearAll();
}

void UseCounter::didCommitLoad()
{
    updateMeasurements();
}

void UseCounter::count(const Document& document, Feature feature)
{
    FrameHost* host = document.frameHost();
    if (!host)
        return;

    ASSERT(host->useCounter().deprecationMessage(feature).isEmpty());
    host->useCounter().recordMeasurement(feature);
}

void UseCounter::count(const ExecutionContext* context, Feature feature)
{
    if (!context || !context->isDocument())
        return;
    count(*toDocument(context), feature);
}

void UseCounter::countDeprecation(ExecutionContext* context, Feature feature)
{
    if (!context || !context->isDocument())
        return;
    UseCounter::countDeprecation(*toDocument(context), feature);
}

void UseCounter::countDeprecation(const DOMWindow* window, Feature feature)
{
    if (!window || !window->document())
        return;
    UseCounter::countDeprecation(*window->document(), feature);
}

void UseCounter::countDeprecation(const Document& document, Feature feature)
{
    FrameHost* host = document.frameHost();
    if (!host)
        return;

    if (host->useCounter().recordMeasurement(feature)) {
        ASSERT(!host->useCounter().deprecationMessage(feature).isEmpty());
        host->console().addMessage(DeprecationMessageSource, WarningMessageLevel, host->useCounter().deprecationMessage(feature));
    }
}

String UseCounter::deprecationMessage(Feature feature)
{
    switch (feature) {
    // Quota
    case PrefixedStorageInfo:
        return "'window.webkitStorageInfo' is deprecated. Please use 'navigator.webkitTemporaryStorage' or 'navigator.webkitPersistentStorage' instead.";

    // Performance
    case PrefixedPerformanceTimeline:
        return "'window.performance.webkitGet*' methods have been deprecated. Please use the unprefixed 'performance.get*' methods instead.";

    // HTML Media Capture
    case CaptureAttributeAsEnum:
        return "Using the 'capture' attribute as an enum is deprecated. Please use it as a boolean and specify the media types that should be accepted in the 'accept' attribute.";

    // Keyboard Event (DOM Level 3)
    case KeyboardEventKeyLocation:
        return "'KeyboardEvent.keyLocation' is deprecated. Please use 'KeyboardEvent.location' instead.";

    case ConsoleMarkTimeline:
        return "console.markTimeline is deprecated. Please use the console.timeStamp instead.";

    case FileError:
        return "FileError is deprecated. Please use the 'name' or 'message' attributes of DOMError rather than 'code'.";

    case ShowModalDialog:
        return "Chromium is considering deprecating showModalDialog. Please use window.open and postMessage instead.";

    case CSSStyleSheetInsertRuleOptionalArg:
        return "Calling CSSStyleSheet.insertRule() with one argument is deprecated. Please pass the index argument as well: insertRule(x, 0).";

    case PrefixedVideoSupportsFullscreen:
        return "'HTMLVideoElement.webkitSupportsFullscreen' is deprecated. Its value is true if the video is loaded.";

    case PrefixedVideoDisplayingFullscreen:
        return "'HTMLVideoElement.webkitDisplayingFullscreen' is deprecated. Please use the 'fullscreenchange' and 'webkitfullscreenchange' events instead.";

    case PrefixedVideoEnterFullscreen:
        return "'HTMLVideoElement.webkitEnterFullscreen()' is deprecated. Please use 'Element.requestFullscreen()' and 'Element.webkitRequestFullscreen()' instead.";

    case PrefixedVideoExitFullscreen:
        return "'HTMLVideoElement.webkitExitFullscreen()' is deprecated. Please use 'Document.exitFullscreen()' and 'Document.webkitExitFullscreen()' instead.";

    case PrefixedVideoEnterFullScreen:
        return "'HTMLVideoElement.webkitEnterFullScreen()' is deprecated. Please use 'Element.requestFullscreen()' and 'Element.webkitRequestFullscreen()' instead.";

    case PrefixedVideoExitFullScreen:
        return "'HTMLVideoElement.webkitExitFullScreen()' is deprecated. Please use 'Document.exitFullscreen()' and 'Document.webkitExitFullscreen()' instead.";

    case PrefixedMediaSourceOpen:
        return "'WebKitMediaSource' is deprecated. Please use 'MediaSource' instead.";

    case DOMImplementationCreateCSSStyleSheet:
        return "'DOMImplementation.createCSSStyleSheet()' is deprecated.";

    case MediaErrorEncrypted:
        return "'MediaError.MEDIA_ERR_ENCRYPTED' is deprecated. This error code is never used.";

    case HTMLSourceElementMedia:
        return "'HTMLSourceElement.media' is deprecated. This attribute doesn't do anything.";

    case PrefixedGetImageDataHD:
        return "'CanvasRenderingContext2D.webkitGetImageDataHD' is deprecated. Please use getImageData instead.";

    case PrefixedPutImageDataHD:
        return "'CanvasRenderingContext2D.webkitPutImageDataHD' is deprecated. Please use putImageData instead.";

    case PrefixedSpeechAttribute:
        return "The 'x-webkit-speech' input field attribute is deprecated. Please use the JavaScript API instead.";

    case PrefixedGamepad:
        return "'navigator.webkitGetGamepads' is deprecated. Please use 'navigator.getGamepads' instead.";

    case PrefixedRequestAnimationFrame:
        return "'webkitRequestAnimationFrame' is vendor-specific. Please use the standard 'requestAnimationFrame' instead.";

    case PrefixedCancelAnimationFrame:
        return "'webkitCancelAnimationFrame' is vendor-specific. Please use the standard 'cancelAnimationFrame' instead.";

    case PrefixedCancelRequestAnimationFrame:
        return "'webkitCancelRequestAnimationFrame' is vendor-specific. Please use the standard 'cancelAnimationFrame' instead.";

    case DocumentCreateAttributeNS:
        return "'Document.createAttributeNS' is deprecated and has been removed from DOM4 (http://w3.org/tr/dom).";

    case AttributeOwnerElement:
        return "'Attr.ownerElement' is deprecated and has been removed from DOM4 (http://w3.org/tr/dom).";

    case ElementSetAttributeNodeNS:
        return "'Element.setAttributeNodeNS' is deprecated and has been removed from DOM4 (http://w3.org/tr/dom).";

    // Features that aren't deprecated don't have a deprecation message.
    default:
        return String();
    }
}

void UseCounter::count(CSSParserContext context, CSSPropertyID feature)
{
    ASSERT(feature >= firstCSSProperty);
    ASSERT(feature <= lastCSSProperty);
    ASSERT(!isInternalProperty(feature));

    if (!isUseCounterEnabledForMode(context.mode()))
        return;

    m_CSSFeatureBits.quickSet(feature);
}

void UseCounter::count(Feature feature)
{
    ASSERT(deprecationMessage(feature).isEmpty());
    recordMeasurement(feature);
}

UseCounter* UseCounter::getFrom(const Document* document)
{
    if (document && document->frameHost())
        return &document->frameHost()->useCounter();
    return 0;
}

UseCounter* UseCounter::getFrom(const CSSStyleSheet* sheet)
{
    if (sheet)
        return getFrom(sheet->contents());
    return 0;
}

UseCounter* UseCounter::getFrom(const StyleSheetContents* sheetContents)
{
    // FIXME: We may want to handle stylesheets that have multiple owners
    //        http://crbug.com/242125
    if (sheetContents && sheetContents->hasSingleOwnerNode())
        return getFrom(sheetContents->singleOwnerDocument());
    return 0;
}

} // namespace WebCore
