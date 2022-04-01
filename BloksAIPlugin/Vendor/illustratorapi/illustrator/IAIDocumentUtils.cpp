/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 *
 * Copyright 2019 Adobe
 *
 * All Rights Reserved.
 *
 * NOTICE: Adobe permits you to use, modify, and distribute this file in
 * accordance with the terms of the Adobe license agreement accompanying
 * it. If you have received this file from a source other than Adobe,
 * then your use, modification, or distribution of it requires the prior
 * written permission of Adobe.
 *
 **************************************************************************/

#include "AIDocument.h"
#include "IAIDocumentUtils.hpp"
#include "AIAssert.hpp"
#include "AIRealMath.h"
#include "AILimits.h"
#include "AIHardSoft.h"

#if AI_AUTO_SUITE_AVAILABLE
#include "AutoSuite.h"
use_suite_required(AIDocument)
use_suite_required(AIRealMath)
use_suite_required(AILimits)
use_suite_required(AIHardSoft)
use_suite_required(AITransformArt)
use_suite_required(AIArt)

#elif defined(_IAIDOCUMENTUTILS_SUITE_INCLUDE_H_)
#include _IAIDOCUMENTUTILS_SUITE_INCLUDE_H_
#else
extern "C" AIDocumentSuite* sAIDocument;
extern "C" AIRealMathSuite* sAIRealMath;
extern "C" AILimitsSuite*   sAILimits;
extern "C" AIHardSoftSuite* sAIHardSoft;
extern "C" AITransformArtSuite* sAITransformArt;
#endif



namespace ai
{
	namespace DocumentUtils
	{
		AIReal GetDocumentScale()
		{
            AIReal docScale {kAIRealOne};
			if(sAIDocument)
			{
				AIErr error = sAIDocument->GetDocumentScale(docScale);
				AIMsgAssert(error==kNoErr, "Error in fetching document scale");
				ai::NOTUSED(error);
			}
			return docScale;
		}
        
        AIRealMatrix GetTransformMatrixForScaleFactorFromReference(const AIReal& scaleFactor, const AIRealPoint& referencePoint)
        {
            AIRealMatrix matrix;
            matrix.Init();
            sAIRealMath->AIRealMatrixConcatTranslate(&matrix, -referencePoint.h, -referencePoint.v);
            sAIRealMath->AIRealMatrixConcatScale(&matrix, scaleFactor, scaleFactor);
            sAIRealMath->AIRealMatrixConcatTranslate(&matrix, referencePoint.h, referencePoint.v);
            return matrix;
        }
        
         AIRealMatrix GetTransFormMatrixForScaleFactor(const AIReal& scaleFactor )
        {
            
            /*
              In sAILimits->GetCanvasSize() / 2
             we have purposefully divided by int 2 and not 2.0 so that the result remains a int So as to get the exact pixel value
             */
            AIReal canvasSizeHalved = static_cast<AIReal>(sAILimits->GetCanvasSize() / 2 );
            AIRealPoint canvasCenter{ canvasSizeHalved, canvasSizeHalved };
            sAIHardSoft->AIRealPointSoften(&canvasCenter, &canvasCenter);
            return GetTransformMatrixForScaleFactorFromReference(scaleFactor, canvasCenter);
        }
        
        AIRealMatrix GetTransformMatrixForDocumentScaleFromReference( const AIRealPoint& referencePoint)
        {            
            auto scaleFactor = GetDocumentScale();
            return GetTransformMatrixForScaleFactorFromReference(scaleFactor, referencePoint);
        }
        
        AIRealMatrix GetTransFormMatrixForDocumentScale()
        {
            return GetTransFormMatrixForScaleFactor(GetDocumentScale());
        }
        
        void ApplyDocumentScaleToAIReal(const AIReal& inReal, AIReal& outReal)
		{
			AIReal docScale = GetDocumentScale();
			outReal = inReal * docScale;
		}

        void DropDocumentScaleFromAIReal(const AIReal& inReal, AIReal& outReal)
        {
            AIReal docScale = GetDocumentScale();
            outReal = inReal / docScale;
        }

        AIRealMatrix ArtScaler::GetScaledXformMatrix(AIArtHandle art, AIReal scale)
        {
            AIRealRect bounds{ 0.0, 0.0, 0.0, 0.0 };
            sAIArt->GetArtBounds(art, &bounds);
            AIRealPoint centre;
            
            centre.h = (bounds.right + bounds.left)/2;
            centre.v = (bounds.top + bounds.bottom)/2;
            return GetTransformMatrixForScaleFactorFromReference(scale, centre);
        }

		AIErr ArtScaler::ScaleArt(AIArtHandle art)
		{
			if (mScaleFactor == kAIRealOne)
				return kNoErr;

			if (art)
			{
                AIRealMatrix artTransform = GetScaledXformMatrix(art, mScaleFactor);
                
                return sAITransformArt->TransformArt(art, &artTransform, mScaleFactor, mTransformOptions);
			}
			return kBadParameterErr;
		}

		AIErr ArtScaler::DownScaleArt(AIArtHandle art)
		{
			if (mScaleFactor == kAIRealOne)
				return kNoErr;

			if (art)
			{
				auto scale = kAIRealOne / mScaleFactor;
                
				AIRealMatrix artTransform = GetScaledXformMatrix(art, scale);
				return sAITransformArt->TransformArt(art, &artTransform, scale, mTransformOptions);
			}
			return kBadParameterErr;
		}

	} // DocumentUtils
}	// namespace ai
