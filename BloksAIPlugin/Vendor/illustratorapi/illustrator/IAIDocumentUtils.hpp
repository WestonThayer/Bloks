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

/*	Utility functions for operations on AIDocumentSuite.
*/
#pragma once
#include "AIBasicTypes.h"
#include "AITypes.h"
#include "AIRealMath.h"
#include "AITransformArt.h"

namespace ai
{
	namespace DocumentUtils
	{
		/** For each document with document scale factor X, each object's dimension have to multiplied by X to get the 
			correct dimensions of the object in UI
			For example, if document scale factor is X, then  a 10x10 rectangle will actually will be displayed as
			 (10*X)x(10*X) rectangle in UI
			  Geting the scale associated with the current document
				@param docScale [out] A buffer in which to return the scale factor corresponding to the current document.
				 it is a wrapper over AIDocumentSuite::GetDocumentScale() and asserts if no document is present.
			*/
		AIReal GetDocumentScale();

        /** Getting the transform matrix for converting the user defind artworks to tranform to documents with scale factor greater than 1
         @param [out] returns tranformation matrix for scale factor of the current document about the Canvas center point
            */
        AIRealMatrix GetTransFormMatrixForDocumentScale();
        
        /** Getting the transform matrix for converting the user defind artworks to tranform to documents with scale factor greater than 1 from a given reference point
         @param [in] reference point from which transformation is required
         @param [out] returns tranformation matrix for scale factor of the current document about the given reference point
         */
        
        AIRealMatrix GetTransformMatrixForDocumentScaleFromReference( const AIRealPoint& referencePoint);
        
        /** Getting the transform matrix for converting the user defind artworks to tranform to documents with specified scale factor
         @param [out] returns tranformation matrix for scale factor of the current document about the Canvas center point
         */
        AIRealMatrix GetTransFormMatrixForScaleFactor(const AIReal& scaleFactor );
        
        /** Getting the transform matrix for converting the user defind artworks to tranform to documents with specified scale factor  from a given reference point
         @param [in] reference point from which transformation is required
         @param [out] returns tranformation matrix for scale factor of the current document about the given reference point
         */
        
        AIRealMatrix GetTransformMatrixForScaleFactorFromReference(const AIReal& scaleFactor, const AIRealPoint& referencePoint);
        
		/** Multiply the coordinates of the AIRealRect with given scale value.
			@param inRect  Rectangle with coordinates in unscaled coordinate system.
			@param outRect [out] A buffer in which to return the corresponding coordinates in scaled coordinate system
			@param scale Input scale value that will be applied to coordinates of Rect
		*/
		template <typename Rect>
		void ApplyScaleToRect(const Rect& inRect, Rect& outRect, const AIReal scale)
		{
			outRect.left = inRect.left * static_cast<decltype(inRect.left)>(scale);
			outRect.top = inRect.top * static_cast<decltype(inRect.top)>(scale);
			outRect.right = inRect.right * static_cast<decltype(inRect.right)>(scale);
			outRect.bottom = inRect.bottom * static_cast<decltype(inRect.bottom)>(scale);
		}

		/**Converting the coordinates of the AIRealRect to  scaled coordinate System
			@param inRect  Rectangle with coordinates in unscaled coordinate system.
			@param outRect [out] A buffer in which to return the corresponding  coordinates in scaled coordinate system
			*/
        
        template <typename Rect>
		void ApplyDocumentScaleToRect( const Rect& inRect, Rect& outRect)
        {
            AIReal docScale = GetDocumentScale();
			ApplyScaleToRect(inRect, outRect, docScale);
        }
				
		/**Converting the coordinates of the AIPoint to  scaled coordinate System
			@param inPoint  point with coordinates in unscaled corrdinate system.
			@param outPoint [out] A buffer in which to return the cooresponding  coordinates in scaled coordinate system
			*/
        template <typename Point>
        void ApplyDocumentScaleToPoint(const Point& inPoint, Point& outPoint)
        {
            AIReal docScale = GetDocumentScale();
            outPoint.h = inPoint.h *  static_cast<decltype(inPoint.h)>(docScale);
            outPoint.v = inPoint.v *  static_cast<decltype(inPoint.v)>(docScale);
            
        }

		/**Converting the value of AIReal to  scaled coordinate System
			@param inReal  AIReal  in unscaled corrdinate system.
			@param outReal [out] A buffer in which to return the cooresponding  value in scaled coordinate system
			*/
		void ApplyDocumentScaleToAIReal( const AIReal& inReal, AIReal& outReal);
		
        /**Converting the coordinates of the scaled Rect to  unscaled coordinate System
         @param inRect  Rectangle with coordinates in scaled corrdinate system.
         @param outRect [out] A buffer in which to return the cooresponding  coordinates in unscaled coordinate system
         */
        template <typename Rect>
        void DropDocumentScaleFromRect( const Rect& inRect, Rect& outRect)
        {
            AIReal docScale = GetDocumentScale();
            outRect.left = inRect.left / static_cast<decltype(inRect.left)>(docScale);
            outRect.top = inRect.top / static_cast<decltype(inRect.top)>(docScale);
            outRect.right = inRect.right / static_cast<decltype(inRect.right)>(docScale);
            outRect.bottom = inRect.bottom / static_cast<decltype(inRect.bottom)>(docScale);
        }
        
        /**Converting the coordinates of the AIPoint to  scaled coordinate System
         @param inPoint  point with coordinates in scaled corrdinate system.
         @param outPoint [out] A buffer in which to return the cooresponding  coordinates in unscaled coordinate system
         */
        template <typename Point>
        void DropDocumentScaleFromPoint(const Point& inPoint, Point& outPoint)
        {
            AIReal docScale = GetDocumentScale();
            outPoint.h = inPoint.h / static_cast<decltype(inPoint.h)>(docScale);
            outPoint.v = inPoint.v / static_cast<decltype(inPoint.v)>(docScale);
        }
        
        /**Converting the value of AIReal to  scaled coordinate System
         @param inReal  AIReal  in scaled corrdinate system.
         @param outReal [out] A buffer in which to return the cooresponding  value in unscaled coordinate system
         */
        void DropDocumentScaleFromAIReal( const AIReal& inReal, AIReal& outReal);

		class ArtScaler
		{
		public:
			ArtScaler(AIReal scale, ai::int32 transformOptions)
				: mScaleFactor{ scale },
				mTransformOptions{ transformOptions }
			{}

			AIErr ScaleArt(AIArtHandle art);

			AIErr DownScaleArt(AIArtHandle art);

			bool IsScaleFactorOne()
			{
				return mScaleFactor == kAIRealOne;
			}

		private:
			AIReal mScaleFactor{ kAIRealOne };
			ai::int32 mTransformOptions{ 0 };
            AIRealMatrix GetScaledXformMatrix(AIArtHandle art, AIReal scale);
		};
	} // Document Utils
} // ai
