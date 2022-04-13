/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 *
 * Copyright 2020 Adobe
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

#pragma once

#include "AITypes.h"
#include "AIHitTest.h"
#include "IAIAutoBuffer.h"
//#include "IAIArtSet.hpp"
#include "AIArtSet.h"
#include "AIHeaderBegin.h"

#define kAIRepeatSuite                  "AI Repeat Suite"
#define kAIRepeatSuiteVersion2          AIAPI_VERSION(2)
#define kAIRepeatSuiteVersion           kAIRepeatSuiteVersion2
#define kAIRepeatVersion                kAIRepeatSuiteVersion

namespace AIRepeat
{
    enum class AIRepeatMergeState : ai::uint8
    {
        /** stroke ovverides fill at arts intersection */
        kOverlap,
        /** fill ovverides stroke at arts intersection */
        kCombine,
    };

    enum class AIRepeatGridShiftType : ai::uint8
    {
        /** create a normal grid of arts*/
        kNone,
        /** create a grid after shifting alternate rows by half*/
        kHorizontal,
        /** create a grid after shifting alternate columns by half*/
        kVertical,
        /** create a grid after shifting both alternate rows and columns by half*/
        kHorizontalAndVertical
    };

    enum class AIRepeatGridFlipType : ai::uint8
    {
        /** create a normal grid of arts*/
        kNone,
        /** flip the alternate rows about y axis */
        kHorizontal,
        /** flip the alternate rows about x axis */
        kVertical,
        /** flip the alternate rows about both x and y axis */
        kHorizontalAndVertical
    };
    /** Radial repeat, repeats an art in a circular fashion with multiple instances.
        User can change its properties like center, radius, startAngle of the circular arc,
        total engle of the arc, number of instances and Merge state which combines all arts
        such that the stroke of intersecting arts does not override the fill of those arts.
        With all these properties RadialConfig is constructed.
     */
    struct RadialConfig
    {
        /** center of radial repeat art */
		AIRealPoint center;
        /** radius of radial repeat art */
        AIReal radius = 0;
        /** start angle of the radial repeat art's circular arc */
        AIReal startAngle = 0;
        /** total angle of the radial repeat art's circular arc */
        AIReal totalAngle = 0;
        /** angle by which the object is rotated about the centre of radial config
         Also, 0 for this value means base art is at the top i.e. in Cartesian coordinates, base art is at +Y axis line */
        AIReal rotationAlongTheCircle = 0;
        /** number of instances of radial repeat art */
        ai::uint32 numberOfInstances = 8;
        /** reverse overlap of radial repeat art */
        AIBoolean reverseOverlap = false;
        /** whether the radial repeat art's circular arc from startAngle to (startAngle + totalAngle) is in clockwise direction or not */
        AIBoolean clockwiseArc = true;
        /** Merge State of radial repeat art */
        AIRepeatMergeState mergeState = AIRepeatMergeState::kOverlap;
    };
    /** RadialUpdate is an enum class with each flag represent which property of
        radial repeat gets updated.
     */
    enum class RadialUpdate : ai::uint8
    {
        /** update the center of radial repeat art */
        kCenter = 1 << 0,
        /** update the radius of radial repeat art */
        kRadius = 1 << 1,
        /** update the start angle of radial repeat art */
        kStartAngle = 1 << 2,
        /** update the end angle of radial repeat art */
        kEndAngle = 1 << 3,
        /** update the end angle of radial repeat art */
        kRotationAngle = 1 << 4,
        /** update number od instances of radial repeat art */
        kNumberOfInstances = 1 << 5,
        /** update the merge state of radial repeat art */
        kMergeState = 1 << 6,
        /** update all the properties of Radial Repeat*/
        kAll = (kCenter | kRadius | kStartAngle | kEndAngle | kRotationAngle | kNumberOfInstances | kMergeState)
    };

    /** Grid repeat, repeats an art in a grid fashion.
        User can change its properties like number of instances in a row,
        number of instances in a column, manipulate spacing between rows and columns,
        and Merge state which combines all arts such that the stroke of intersecting
        arts does not override the fill of those arts.
        With all these properties GridConfig is constructed.
     */
    struct GridConfig
    {
        /** spacing between each rows */
        AIReal horizontalSpacing = 10;
        /** spacing between each columns */
        AIReal verticalSpacing = 10;
        /** horizontal offset of first instance */
        AIReal horizontalOffset = 0;
        /** vertical offset of first instance */
        AIReal verticalOffset = 0;
        /** main art bounds */
        AIRealRect bounds;
        /** Merge State of grid repeat art */
        AIRepeatMergeState mergeState = AIRepeatMergeState::kOverlap;
        /** shift type of grid repeat art */
        AIRepeatGridShiftType patternType = AIRepeatGridShiftType::kNone;
        /** row flip type of grid repeat art */
        AIRepeatGridFlipType rowFlipType = AIRepeatGridFlipType::kNone;
        /** flip type of grid repeat art */
        AIRepeatGridFlipType columnFlipType = AIRepeatGridFlipType::kNone;
    };


    /** GridUpdate is an enum class with each flag represent which property of grid
        repeat gets updated.
     */
    enum class GridUpdate : ai::uint8
    {
        /** update the number of instances in each column of grid repeat art */
        kRowInstances = 1 << 0,
        /** update the number of instances in each column of grid repeat art */
        kColumnInstances = 1 << 1,
        /** Update spacing between rows of grid repeat art */
        kHorizontalSpacing = 1 << 2,
        /** Update spacing between coloumns of grid repeat art */
        kVerticalSpacing = 1 << 3,
        /** update the bounds of grid repeat art */
        kBounds = 1 << 4,
        /** update the merge state of grid repeat art */
        kMergeState = 1 << 5,
        /** update all the properties of Grid Repeat*/
        kAll = (kRowInstances | kColumnInstances | kHorizontalSpacing | kVerticalSpacing | kBounds | kMergeState)
    };
    /** Symmetry repeat, repeats an art in a symmetry fashion around a symmetry axis.
     User can change its properties like changing spacing between object to its symmetry axis,
     and Merge state which combines all arts such that the stroke of intersecting
     arts does not override the fill of those arts.
     With all these properties SymmetryConfig is constructed.
     */
    struct SymmetryConfig
    {
        /** spacing between object to symmetry axis */
        AIRealPoint axisCenter;
        /** symmetry axis rotation angle wrt x-axis in anti-clockwise fashion*/
        AIReal axisRotationAngleInRadians = 0;
        /** Angle of normal to symmetry axis. This axis normal has same axisCenter as that of symmetry axis. At new
         object creation, initially axis normal should be at an angle of 90 degrees from axis in anti-clockwise fashion.*/
        AIReal axisNormalAngleInRadians = 0;
        /** Merge State of symmetry repeat art */
        AIRepeatMergeState mergeState = AIRepeatMergeState::kOverlap;
    };
    /** SymmetryUpdate is an enum class with each flag represent which property of symmetry
     repeat gets updated.
     */
    enum class SymmetryUpdate : ai::uint8
    {
        /** Update spacing between symmetry axis to object */
        kAxisCenter = 1 << 0,
        /** Update axis rotation angle wrt x-axis */
        kAxisRotation = 1 << 1,
        /** update the merge state of symmetry repeat art */
        kMergeState = 1 << 2,
        /** update all the properties of Symmetry Repeat*/
        kAll = (kAxisCenter | kAxisRotation | kMergeState)
    };
    /** Concentric repeat, repeats an art in a concentric fashion.
     User can change its properties like changing number of instances inside,
     and Merge state which combines all arts such that the stroke of intersecting
     arts does not override the fill of those arts.
     With all these properties ConcentricConfig is constructed.
     */
    struct ConcentricConfig
    {
        /** number of instances of Concentric repeat art */
        ai::uint32 numberOfInstances = 1;
        /** Merge State of Concentric repeat art */
        AIRepeatMergeState mergeState = AIRepeatMergeState::kOverlap;
    };
    /** ConcentricUpdate is an enum class with each flag represent which property of Concentric
     repeat gets updated.
     */
    enum class ConcentricUpdate : ai::uint8
    {
        /** update number of instances of Concentric repeat art */
        kNumberOfInstances = 1 << 0,
        /** update the merge state of Concentric repeat art */
        kMergeState = 1 << 1,
        /** update all the properties of Concentric Repeat*/
        kAll = (kNumberOfInstances | kMergeState)
    };

}

struct AIRepeatSuite
{
	 /** Create a new repeat art. This API converts input AIArtHandle to radial repeat object
     
        @Param ai::ArtSet arts: Input arts which needs to be repeated
        @Param RadialConfig radial repeat configurations
        @Param AIArtHandle *newRadialRepeatArt: Radial repeat art
     */
    AIAPI AIErr(*CreateRadialRepeatArt) (const ai::AutoBuffer<AIArtHandle>& arts, const AIRepeat::RadialConfig& config, AIArtHandle& newRadialRepeatArt);
    
    /** Create a new repeat art. This API converts input AIArtHandle to grid repeat object
     
         @Param ai::ArtSet arts: Input arts which needs to be repeated
         @Param GridConfig grid repeat configurations
         @Param AIArtHandle *newGridRepeatArt: Radial repeat art
     */
    AIAPI AIErr(*CreateGridRepeatArt) (const ai::AutoBuffer<AIArtHandle>& arts, const AIRepeat::GridConfig& config, AIArtHandle& newGridRepeatArt);

    /** Create a new repeat art. This API converts input AIArtHandle to symmetry repeat object
     
     @Param ai::ArtSet arts: Input arts which needs to be repeated
     @Param SymmetryConfig symmetry repeat configurations
     @Param AIArtHandle *newSymmetryRepeatArt: Symmetry repeat art
     */
    AIAPI AIErr(*CreateSymmetryRepeatArt) (const ai::AutoBuffer<AIArtHandle>& arts, const AIRepeat::SymmetryConfig& config, AIArtHandle& newSymmetryRepeatArt);

    /** Create a new repeat art. This API converts input AIArtHandle to concentric repeat object
     
     @Param ai::ArtSet arts: Input arts which needs to be repeated
     @Param ConcentricConfig concentric repeat configurations
     @Param AIArtHandle *newConcentricRepeatArt: Concentric repeat art
     */
    AIAPI AIErr(*CreateConcentricRepeatArt) (const ai::AutoBuffer<AIArtHandle>& arts, const AIRepeat::ConcentricConfig& config, AIArtHandle& newConcentricRepeatArt);

    /** Update Grid repeat configurations i.e. number of rows, columns, spacing etc
     
        @Param AIArtHandle art: Grid repeat art whose configuration needs to be changed
        @Param GridConfig config: updated grid repeat configurations
        @Param GridUpdate state: specify which properties of grid repeat gets updated
     */
    AIAPI AIErr (*SetGridConfiguration) (AIArtHandle art, const AIRepeat::GridConfig& config, AIRepeat::GridUpdate state);
    
    /** Get Grid repeat configurations i.e. number of rows, columns, spacing etc
     
        @Param AIArtHandle art: Grid repeat art whose configuration is required
        @Param GridConfig config: Return grid configurations in this variable
     */
    AIAPI AIErr (*GetGridConfiguration) (AIArtHandle art, AIRepeat::GridConfig& config);
    
    /** Update Radial repeat configurations i.e. number of arts, center, radial radius etc
     
        @Param AIArtHandle art: Radial repeat art whose configuration needs to be changed
        @Param RadialConfig config: updated radial repeat configurations
        @Param RadialUpdate state: specify which properties of radial repeat gets updated
     */
    AIAPI AIErr (*SetRadialConfiguration) (AIArtHandle art, const AIRepeat::RadialConfig& config, AIRepeat::RadialUpdate state);
    
    /** Get Radial repeat configurations i.e. number of arts, circle center, radius etc
     
        @Param AIArtHandle art: Radial repeat art whose configuration is required
        @Param RadialConfig config: Return radial configurations in this variable
     */
    AIAPI AIErr (*GetRadialConfiguration) (AIArtHandle art, AIRepeat::RadialConfig& config);
    
    /** Update Symmetry repeat configurations i.e. perpendicular distance from symmetry axis, symmetry axis rotation angle wrt x-axis etc
     
     @Param AIArtHandle art: Symmetry repeat art whose configuration needs to be changed
     @Param SymmetryConfig config: updated symmetry repeat configurations
     @Param SymmetryUpdate state: specify which properties of symmetry repeat gets updated
     */
    AIAPI AIErr (*SetSymmetryConfiguration) (AIArtHandle art, const AIRepeat::SymmetryConfig& config, AIRepeat::SymmetryUpdate state);
    
    /** Get Symmetry repeat configurations i.e. perpendicular distance from symmetry axis, symmetry axis rotation angle wrt x-axis etc
     
     @Param AIArtHandle art: Symmetry repeat art whose configuration is required
     @Param SymmetryConfig config: Return symmetry configurations in this variable
     */
    AIAPI AIErr (*GetSymmetryConfiguration) (AIArtHandle art, AIRepeat::SymmetryConfig& config);
    
    /** Update Concentric repeat configurations i.e. number of instances etc
     
     @Param AIArtHandle art: Concentric repeat art whose configuration needs to be changed
     @Param ConcentricConfig config: updated concentric repeat configurations
     @Param ConcentricUpdate state: specify which properties of concentric repeat gets updated
     */
    AIAPI AIErr (*SetConcentricConfiguration) (AIArtHandle art, const AIRepeat::ConcentricConfig& config, AIRepeat::ConcentricUpdate state);
    
    /** Get Concentric repeat configurations i.e. number of instances etc
     
     @Param AIArtHandle art: Concentric repeat art whose configuration is required
     @Param ConcentricConfig config: Return concentric configurations in this variable
     */
    AIAPI AIErr (*GetConcentricConfiguration) (AIArtHandle art, AIRepeat::ConcentricConfig& config);

     /** Get main art which was repeated
     
     @Param AIArtHandle art: Radial/Grid/Symmetry/Concentric repeat art whose main art is required
     @Param AIArtHandle mainArt: Return main art
     */
    AIAPI AIErr (*GetMainArt) (AIArtHandle art, AIArtHandle& mainArt);
    
    /** Get all children arts of main art which was repeated
     
     @Param AIArtHandle art: Radial/Grid/Symmetry/Concentric repeat art whose children arts of main art are required
     @Param AIArtHandle mainArts: Return children arts of main art
     */
    AIAPI AIErr (*GetMainArts) (AIArtHandle art, AIArtSet& mainArts);
    
    /** Get height and width of main art
    
    @Param AIArtHandle art: Radial/Grid/Symmetry/Concentric repeat art whose main arts are required
    @Param double& height: Out param to return height of main art
    @Param double& width: Out param to return width of main art
    */
    AIAPI AIErr (*GetMainArtSize)(AIArtHandle art, AIReal& height, AIReal& width);
    
    /**
     Checks if given art is Repeat art
	 
     @Param AiArtHandle art: Art which has to checked for repeat art type
     */
    AIAPI AIBoolean (*IsRepeatArt)(AIArtHandle art);

    /**
     Checks if Repeat art is Symmetry or Radial Repeat or Grid Repeat Art

     @Param ai::int16 artType: ArtType of the Repeat art to be checked (kSymmetryArt / kRadialRepeatArt / kGridRepeatArt)
     */
    AIAPI AIBoolean(*IsRepeatArtType)(ai::int16 artType);

    /**
     Invalidate Repeat art 

     @Param AiArtHandle art: Art which has to be invalidated
     */
    AIAPI AIErr(*Invalidate)(AIArtHandle art);

};

#include "AIHeaderEnd.h"
