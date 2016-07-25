#ifndef __AI192Art__
#define __AI192Art__

/*
*        Name:	AIArt.h
*   $Revision: 25 $
*      Author:
*        Date:
*     Purpose:	Adobe Illustrator  Artwork Object Suite.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1986-2016 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/


/*******************************************************************************
**
**	Imports
**
**/

#include "AIArt.h"

#include "AIHeaderBegin.h"

/** @file AI192Art.h */

/*******************************************************************************
**
**	Constants
**
**/

#define kAI192ArtSuite				"AI Art Suite"
#define kAIArtSuiteVersion17		AIAPI_VERSION(17)
#define kAI192ArtSuiteVersion		kAIArtSuiteVersion17
#define kAI192ArtVersion			kAI192ArtSuiteVersion


/*******************************************************************************
**
**	Suite
**
**/


/** @ingroup Suites
This suite allows you to access and modify the artwork in Illustrator documents.
It provides functions to create and delete objects,	rearrange objects, and get
and set information about objects. You use these functions to navigate the tree
of art objects, and to retrieve or modify generic information about art objects,
such as their bounds or lock status.

The Art suite is fundamental to implementing most plug-ins. An Illustrator document
consists of a collection of art objects referenced by an \c #AIArtHandle. This
is an opaque pointer to an art object in the document’s artwork database. Access
the fields through the Art suite's accessor functions.

An art object can represent an individual entity, such as a path, block of text or
placed image, or a group of objects, such as a collection of paths.
The art type identifier (\c #AIArtType) indicates the type of an art object.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIArtSuite and \c #kAIArtVersion.
*/

typedef struct AI192ArtSuite {

	/** Creates a new art object.
	This can fail if the layer is locked or hidden. Otherwise, the object is inserted into the
	paint order with respect another art object. For example, this creates \c new_art above \c old_art in the paint order.
	@code
	AIArtHandle new_art;
	error = sArt->NewArt(kPathArt, kPlaceAbove, old_art, &new_art);
	@endcode
	This places \c new_art in the specified \c group above all other objects in the group.
	@code
	error = sArt->NewArt(kPathArt, kPlaceInsideOnTop, group, &new_art);
	@endcode
	This places \c new_art on top of all artwork in the document.
	@code
	error = sArt->NewArt(kPathArt, kPlaceAboveAll, nil, &new_art);
	@endcode

	@param type The art type. See \c ::AIArtType.
	If the new object type is a path then it is typically given the path style that would be assigned
	to a path created by a tool (for example, the pen tool). Tool plug-ins can depend on this.
	Plug-ins that are not tools should make no assumptions about the style assigned to paths.
	@param paintOrder The paint order position, relative to the \c prep object, an \c #AITypes::AIPaintOrder value.
	@param prep The prepositional art object. This can be an object whose boundaries might overlap this one,
	or a compound path or group that might contain this path.
	@param newArt [out] A buffer in which to return the new art object.

	@note Change in AI 11.0: If the art is being created during the execution of an effect,
	and \c prep is styled art, the new art has a path style with a black fill and no stroke.
	This prevents effect executions from accidentally using the current path style
	*/
	AIAPI AIErr(*NewArt) (ai::int16 type, ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt);

	/** Removes an art object from the document. If it is a group or compound path,
	also removes its children.
	@param art The art object. After the call, this reference is no longer valid.
	*/
	AIAPI AIErr(*DisposeArt) (AIArtHandle art);

	/** Changes the paint order of an art object, or moves a path in or out of a compound path or group.

	@param art The art object.
	@param paintOrder The paint order, relative to the \c prep object, an \c #AITypes::AIPaintOrder value.
	@param prep The prepositional art object for the paint order.
	*/
	AIAPI AIErr(*ReorderArt) (AIArtHandle thisArt, ai::int16 paintOrder, AIArtHandle prep);

	/** Duplicates an art object with a deep copy (children of groups and compound paths are also duplicated).
	The copied objects have the same coordinates as the original, so you must do a deep move on them.
	@param art The art object.
	@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
	@param prep The prepositional art object for the paint order.
	@param newArt [out] A buffer in which to return the new art object.
	*/
	AIAPI AIErr(*DuplicateArt) (AIArtHandle thisArt, ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt);

	/** Retrieves the first art object in a layer, which is the group that contains all of the art in that layer.
	You can use this to traverse the art objects contained in the layer.
	@param layer The layer. Use \c nil for the current layer. See \c #AILayerSuite
	@param art [out] A buffer in which to return the new art object.
	@see  \c #GetArtFirstChild(), \c #GetArtParent(), \c #GetArtSibling(), \c #GetArtPriorSibling() */
	AIAPI AIErr(*GetFirstArtOfLayer) (AILayerHandle layer, AIArtHandle *art);

	/** Retrieves an art object’s parent layer, if any.
	This function is useful with \c #AIMatchingArtSuite::GetSelectedArt() and \c #AIMatchingArtSuite::GetMatchingArt(),
	which give you a list of art objects. For example, if your filter gets all of the selected objects and
	creates a path on top of each layer with objects on it, you would need to know the layer of the objects
	in order to place the new path on top:
	@code
	AILayerHandle layer;
	AIArtHandle group, new_path;
	error = sArt->GetLayerOfArt(art, &layer);
	error = sArt->GetFirstArtOfLayer(layer, &group);
	error = sArt->NewArt(kPathArt, kPlaceInsideOnTop, group, &new_path);
	@endcode
	@param art The art object.
	@param layer [out] A buffer in which to return the layer object. See \c #AILayerSuite

	@note Art that is stored in a dictionary or an array is not considered to be on a layer even though
	the dictionary may belong to an art object that is on a layer. */

	AIAPI AIErr(*GetLayerOfArt) (AIArtHandle art, AILayerHandle *layer);

	/** Retrieves the type of an art object.
	Before you begin manipulating an object’s type-specific attributes you need to know
	what kind of art object it is. For example, you can call path functions if the art
	is a path, or text functions if it is text.
	@code
	short type;
	error = sArt->GetArtType(art, &type);
	if (error)
	return error;
	switch (type) {
	case kGroupArt:
	...
	}
	@endcode

	@param art The art object.
	@param type [out] A buffer in which to return the type, an \c #AIArtType constant.
	*/

	AIAPI AIErr(*GetArtType) (AIArtHandle art, short *type);

	/** Retrieves user attributes of an art object; that is, flags that show whether it is selected, hidden, or locked.
	The user attributes of an object do not directly affect the geometry or printing of the artwork.
	They are temporary and primarily used while the user is editing the document.
	An art object must be unlocked before making changes to it through the API.
	Unlocking and locking should therefore be the first and last things done to an object.
	An object cannot be selected if it is hidden or locked.
	Because most filters operate on the current selection, it is not usually not necessary to unlock objects.

	<br>Example:
	@code
	long attr;
	error = sArt->GetArtUserAttr(art, kArtLocked | kArtHidden, &attributes);
	if (error) return error;
	if (!(attributes & kArtLocked) || !(attributes & kArtHidden)) {
	error = sArt->SetArtUserAttr(art, kArtSelected, kArtSelected);
	if (error) return error;
	}
	@endcode
	@param art The art object.
	@param whichAttr  A mask for the attributes of interest, a logical OR of \c #AIArtType constant values.
	@param attr [out] A buffer in which to return the type, a logical OR of \c #AIArtType constant values, masked by \c whichAttr.
	(Note that this is NOT boolean).
	@see \c #GetArtTextWrapProperty(), \c #SetArtTextWrapProperty()

	*/
	AIAPI AIErr(*GetArtUserAttr) (AIArtHandle art, ai::int32 whichAttr, ai::int32 *attr);

	/** Sets user attributes of an object; that is, flags that show whether it is selected, hidden, or locked.
	Changing the selection state of an object is considered by the plug-in interface to be a
	modification to the document; that is, the document is marked dirty and needs to be saved.
	<br>Example:
	@code
	// unlocks the object
	error = sArt->SetArtUserAttr(art, kArtLocked, 0);
	// locks the object
	error = sArt->SetArtUserAttr(art, kArtLocked, kArtLocked);
	@endcode
	@param art The art object.
	@param whichAttr  A mask for the attributes of interest, a logical OR of \c #AIArtType constant values.
	@param attr The new attribute value, a logical OR of \c #AIArtType constant values, masked by \c whichAttr.
	(Note that this is NOT boolean).
	@see \c #GetArtTextWrapProperty(), \c #SetArtTextWrapProperty()
	*/
	AIAPI AIErr(*SetArtUserAttr) (AIArtHandle art, ai::int32 whichAttr, ai::int32 attr);

	/** Retrieves the parent group of an art object. This example shows a non-recursive tree walk:
	@code
	...
	// see if parent has sibling
	error = sArt->GetArtParent(nextart, &nextart);
	if (error) return error;
	error = sArt->GetArtSibling(nextart, &nextart);
	if (error) return error;
	if (nextart) {  // parent has sibling
	...
	}
	@endcode
	@param art The art object.
	@param parent [out] A buffer in which to return the parent object, or a null object if
	the specified art object is the topmost group of its layer,
	or the topmost object in a container such as a dictionary or array.\
	*/
	AIAPI AIErr(*GetArtParent) (AIArtHandle art, AIArtHandle *parent);

	/**	Retrieves the first child of a group object. For example:
	@code
	AIArtHandle child;
	...
	error = sArt->GetArtType(art, &type);
	if (error) return error;
	switch (type) {
	case kGroupArt:
	error = sArt->GetArtFirstChild(art, &child);
	if (error) return error;
	error = doArtAndSiblings(message, child);
	if (error) return error;
	break;
	...
	@endcode
	@param art The art object.
	@param child [out] A buffer in which to return the child object, or a null object if
	the specified art object is not a container such as a group, graph, or text frame,
	or is an empty container.
	*/
	AIAPI AIErr(*GetArtFirstChild) (AIArtHandle art, AIArtHandle *child);

	/** Retrieves the next object in the same group. This is the opposite of \c #GetArtPriorSibling().
	Use with \c #GetArtFirstChild() and \c #GetArtParent() to look at
	all of the objects in a container. For example:
	@code
	...
	// see if parent has sibling
	error = sArt->GetArtParent(nextart, &nextart);
	if (error) return error;
	error = sArt->GetArtSibling(nextart, &nextart);
	if (error) return error;
	if (nextart) {    // parent has sibling
	...
	}
	@endcode
	@param art The art object.
	@param sibling [out] A buffer in which to return the sibling object, or a null object if
	the specified art object is the last child in its container.
	*/
	AIAPI AIErr(*GetArtSibling) (AIArtHandle art, AIArtHandle *sibling);

	/** Retrieves the previous object in the same group. This is the opposite of \c #GetArtSibling().
	<br>Example:
	@code
	// get the previous art
	error = sArt->GetArtPriorSibling(art, &art);
	if (error) return error;
	if (!art){
	// art was first in group
	// see if parent has previous art
	error = sArt->GetArtParent(art, &art);
	if (error) return error;
	...
	@endcode
	@param art The art object.
	@param sibling [out] A buffer in which to return the sibling objector a null object if
	the specified art object is the first child in its container.
	*/
	AIAPI AIErr(*GetArtPriorSibling) (AIArtHandle art, AIArtHandle *sibling);


	/** Retrieves the enclosing rectangle of an art object.
	@param art The art object.
	@param bounds [out] A buffer in which to return the value.
	@note This function has the same behavior as \c #GetArtTransformBounds() with
	a null transform and \c kVisibleBounds|kExcludeGuideBounds.
	Call \c #GetArtTransformBounds() with a null transform to
	specify non-default flags.
	*/
	AIAPI AIErr(*GetArtBounds) (AIArtHandle art, AIRealRect *bounds);

	/** Updates cached information for the enclosing rectangle (bounding box)
	of an art object.
	@param art The art object.
	*/
	AIAPI AIErr(*SetArtBounds) (AIArtHandle art);

	/** Checks whether the center point of an art object is visible.
	This option can be set by the user using the Attributes dialog.
	<br> Example:
	@code
	error = sArt->GetArtCenterPointVisible (art, &visible);
	if (error) return error;
	if (!visible) {
	// it’s not visible so we do something based on that fact
	...
	@endcode
	@param art The art object.
	@param visible [out] A buffer in which to return the value, true if the center point is visible.
	*/
	AIAPI AIErr(*GetArtCenterPointVisible) (AIArtHandle art, AIBoolean *visible);

	/** Makes the center point of an art object visible or invisible when the object is selected.
	@param art The art object.
	@param visible True to make the center point visible, false to make it invisible.
	*/
	AIAPI AIErr(*SetArtCenterPointVisible) (AIArtHandle art, AIBoolean visible);

	/** Retrieves the geometric bounds of an art object after applying a transformation matrix.
	Returns single-precision coordinates.
	@param art The art object.
	@param transform A pointer to a transformation matrix to apply.
	Can be \c NULL to indicate the identity matrix. You cannot use a non-null matrix
	if the \c #kControlBounds option is set in \c flags.
	@param flags Bit flags that specify which bounds to return. A logical OR of \c #AIArtBoundsOptions constants.
	The flags must include either \c kVisibleBounds or \c kControlBounds,
	and can include additional flags depending on which of these is included.
	@param bounds [out] A buffer in which to return the bounds value containing single-precision coordinates.
	@see \c #GetPreciseArtTransformBounds(), \c #GetArtRotatedBounds()
	*/
	AIAPI AIErr(*GetArtTransformBounds) (AIArtHandle art, AIRealMatrix *transform, ai::int32 flags, AIRealRect *bounds);

	/* New in Illustrator 7.0 */

	/** Checks whether any linked objects (linked images or placed objects)
	contained in the subtree of a given container need updating, and updates them if needed.
	A linked object needs updating if its file has been modified since the contents were
	last read.

	@param art The art object.
	@param force When true, objects are updated regardless of whether they have changed.
	@param updated [out] Optional, a buffer in which to return true if any objects were updated. */
	AIAPI AIErr(*UpdateArtworkLink) (AIArtHandle art, AIBoolean force, AIBoolean *updated);

	/* New in Illustrator 8.0 */

	/** Returns true if an art object reference is valid.
	(Note that the function returns a boolean value, not an error code.)
	A reference can test as invalid and still refer to an object that exists in the document,
	if that object is not found in the searched layer.
	@param art The art object.
	@param searchAllLayerLists When true, searches through all layers in
	all layer lists. Otherwise, searches only the current layer list. */
	AIAPI AIBoolean(*ValidArt) (AIArtHandle art, AIBoolean searchAllLayerLists);

	/** Get the paint order or containment relation of  two art objects.
	This function reflects the order in which the objects are encountered
	in a \c #GetArtSibling() tree traversal. "Before" means above
	or in front in the paint order, and "After" means behind or below in the paint order.
	@param art1 The first art object.
	@param art2 The second art object.
	@param order [out] A buffer in which to return the result.
	See \c #AIArtOrder for the possible ordering values. */
	AIAPI AIErr(*GetArtOrder) (AIArtHandle art1, AIArtHandle art2, short *order);

	/** Selects specified artwork of a layer by matching a string to the contents
	of art object notes. You can select multiple art objects by specifying a partial
	string and a matching style.
	@param layer The layer object. See \c #AILayerSuite.
	@param name A string to match to the note contents of art objects in the layer.
	If the empty string, matches all leaf objects without notes.
	@param matchWholeWord When true, an art object is selected if its note contents
	exactly matches the \c name string.
	When false, an art object is selected if any part of its note contents
	matches the \c name string.
	@param caseSensitive When true, perform case-sensitive matching. When false, ignore case.
	*/
	AIAPI AIErr(*SelectNamedArtOfLayer) (AILayerHandle layer, const ai::UnicodeString& name,
		AIBoolean matchWholeWord, AIBoolean caseSensitive);

	/** Retrieves the enclosing rectangle of an art object after rotation.
	This is the same as \c #GetArtTransformBounds(), except that the
	transformation is specified by a rotation angle rather than a matrix.
	@param art The art object.
	@param angle The rotation angle in radians.
	@param flags Option flags for which bounds to return.
	A logical OR of \c #AIArtBoundsOptions constant values.
	@param bounds [out] A buffer in which to return the value.
	*/
	AIAPI AIErr(*GetArtRotatedBounds) (AIArtHandle art, AIReal angle, ai::int32 flags, AIRealRect *bounds);

	/** Returns true if an art object or a descendent object draws something that
	should be considered a fill. The distinguishing property of a fill is that
	it is drawn behind all other objects when applied to an object that is part
	of a clipping mask. (Note that the function returns a boolean value, not an error code.)
	@param art The art object.
	@return True if the object or a descendant has fill.
	*/
	AIAPI AIBoolean(*ArtHasFill) (AIArtHandle art);

	/** Returns true if an art object or a descendent object draws something that
	should be considered a stroke. The distinguishing property of a stroke is that
	it is drawn in front of all other objects when applied to an object that is part
	of a clipping mask.
	(Note that the function returns a boolean value, not an error code.)
	@param art The art object.
	@return True if the object or a descendant has stroke.
	*/
	AIAPI AIBoolean(*ArtHasStroke) (AIArtHandle art);

	/** Returns true if two art objects contain nothing other than groups, paths and
	compound paths and they have identical geometry (control points). The path styles
	and other appearance attributes may be different.
	(Note that the function returns a boolean value, not an error code.)
	@param art1 The first art object.
	@param art2 The second art object.
	@return True if the objects have equal paths.
	@see also \c #ObjectsAreEquivalent
	*/
	AIAPI AIBoolean(*ArtsHaveEqualPaths) (AIArtHandle art1, AIArtHandle art2);

	/** Not implemented in AI11 and later; returns \c kNotImplementedErr. */
	AIAPI AIErr(*ArtCopyFillStyleIfEqualPaths) (AIArtHandle dstArt, AIArtHandle srcArt);
	/** Not implemented in AI11 and later; returns \c kNotImplementedErr. */
	AIAPI AIErr(*ArtCopyStrokeStyleIfEqualPaths) (AIArtHandle dstArt, AIArtHandle srcArt);

	/* New in Illustrator 9.0 */

	/** Retrieves the insertion point for a document.
	This is the position in the art tree at which a drawing tool should create new art.

	@param art The art object.
	@param paintorder The position in the paint order, relative to the specified art object.
	See \c #AITypes::AIPaintOrder for the possible positions.
	@param editable [out] A buffer in which to return true if it is possible to create art
	at the returned position. For example, you cannot create art in a locked layer.
	Pass null if not needed.
	*/
	AIAPI AIErr(*GetInsertionPoint) (AIArtHandle *art, short *paintorder, AIBoolean *editable);

	/** Sets the insertion point for a document.
	This is the position in the art tree at which a drawing tool should create new art.
	The new position is a paint-order position with respect to the given art object.
	See \c #AITypes::AIPaintOrder for details.
	If the object is a group, the new position is \c kPlaceInsideOnTop;
	otherwise it is  \c kPlaceAbove. If the art object is in a position where an
	insertion point cannot be set (for example, inside a plug-in group)
	the position is set relative to the nearest parent defining a valid insertion point.
	If no valid insertion point can be determined, the function returns an error.

	@param art The art object.
	*/
	AIAPI AIErr(*SetInsertionPoint) (AIArtHandle art);

	/** Retrieves the key object for object alignment. The key object is the one to which
	other objects are aligned. It is usually the object most recently clicked with the Select tool.
	@param art [out] A buffer in which to return the art object, or a null object if there is no key object.
	*/
	AIAPI AIErr(*GetKeyArt) (AIArtHandle *art);


	/** Clears the key object for object alignment. The key object is the one to which
	other objects are aligned. It is usually the object most recently clicked with the
	Select tool.
	@deprecated */
	AIAPI AIErr(*CancelKeyArt) (void);

	/** Retrieves the dictionary associated with an art object. Arbitrary data can be
	attached to an art object in its dictionary. See the \c #AIDictionarySuite..
	The same dictionary is accessed by the \c #AITagSuite for setting and getting
	string values.

	Dictionaries are reference counted. You must call \c sAIDictionary->Release()
	when you no longer need the reference. It is recommended that you use the C++
	\c #ai::Ref template class, which takes care memory management.
	@param art The art object.
	@param dictionary [out] A buffer in which to return a pointer to the dictionary reference.
	*/
	AIAPI AIErr(*GetDictionary) (AIArtHandle art, struct _AIDictionary** dictionary);

	/** Sets the name of an art object. This is the name that appears in the Layers
	palette.
	@param art The art object.
	@param name The new name. Use the empty string to reset the name to
	the default for the object type. */
	AIAPI AIErr(*SetArtName) (AIArtHandle art, const ai::UnicodeString& name);

	/** Retrieves the name of an art object. This is the name that appears in the Layers
	palette.
	@param art The art object.
	@param name [out] A buffer in which to return the name.
	@param isDefaultName [out] A buffer in which to return true if the returned name is a
	default descriptive name, rather than a user-assigned name. May be null.
	*/
	AIAPI AIErr(*GetArtName) (AIArtHandle art, ai::UnicodeString& name, ASBoolean *isDefaultName);

	/** Reports whether an art object is a group that corresponds to a layer or a sublayer.
	@param art The art object.
	@param name [out] A buffer in which to return true if the art object is a layer group.
	*/
	AIAPI AIErr(*IsArtLayerGroup) (AIArtHandle art, ASBoolean *isLayerGroup);

	/** Releases elements of a layer, group, or plug-in group to separate layers.
	Plug-in groups can be inside styled art. In this case:
	\li If the art style consists of only the plug-in group, the plug-in group is
	expanded and the original art deleted.
	\li If there is more than one plug-in group or other element in the styled art,
	the specified art is left in place and the remaining styled art is left intact.

	@param art The art object.
	@param build When true, new layers are built upon one another such that
	the topmost released layer contains everything in the original art and
	the bottommost released layer contains only the highest object in the
	stacking order. This order is used because the Flash exporter takes the
	bottommost layer as the first animation frame and the topmost layer as the
	last frame. */
	AIAPI AIErr(*ReleaseToLayers) (const AIArtHandle art, ASBoolean build);

	/** Modifies the set of targeted objects in the document using a specified action.
	@param list A set of objects to be used as an additional parameter, for actions that need it.
	@param count The number of objects in \c list.
	@param action The action to take; see \c #AIArtTargettingAction for the possible actions.
	*/
	AIAPI AIErr(*ModifyTargetedArtSet) (AIArtHandle *list, ai::int32 count, ai::int32 action);

	/** Returns true if art is part of the styled art of another object.
	(Note that the function returns a boolean value, not an error code.)
	@param art The art object;
	@return True if the object is part of the style art of another object.
	*/
	AIAPI AIBoolean(*IsArtStyledArt) (AIArtHandle art);

	/** Returns true if \c art adds to clipping. (Note that the function returns
	a boolean value, not an error code.) Call this function only on descendents
	of a clip group or a mask object.
	@param art The art object.
	@return True if the specified object is an appropriate art object with the
	\c kArtIsClipMask flag set, or if it is a non-clip group with a clipping descendent
	that is not bounded by another clip group.
	*/
	AIAPI AIBoolean(*IsArtClipping) (AIArtHandle art);


	/* New in Illustrator 10.0 */

	/** Transfers attributes from a source art object to a destination art object.
	Use, for example, when converting an art object from one type to another.
	@param srcart The art object from which to copy attributes.
	@param dstart The art object to which to copy attributes.
	@param which The attributes to transfer, a logical OR of
	\c #AIArtTransferAttrsOptions values. */
	AIAPI AIErr(*TransferAttributes) (AIArtHandle srcart, AIArtHandle dstart, ai::uint32 which);

	/* New in Illustrator 11.0 */

	/**	Retrieves the last child of a container art object. Applies to container
	objects such as groups, graphs and text frame objects.
	@param art The art object.
	@param child [out] A buffer in which to return the last child art object, or nil if
	the specified art object is not a container or is an empty container.
	*/
	AIAPI AIErr(*GetArtLastChild) (AIArtHandle art, AIArtHandle *child);

	/** Sets the properties that affect how text wraps around a text wrap object;
	that is, one in which the \c kArtIsTextWrap attribute is set.
	Use \c #GetArtUserAttr() and \c #SetArtUserAttr() to inspect and set the \c kArtIsTextWrap attribute.

	@param art The art object.
	@param offset The distance in points from the geometric outline of an object
	that defines an offset for wrapping.
	@param invert When true, text wraps inside the outline of the offset object.
	When false, text wraps around the outside of the offset object.
	@return \c kBadParameterErr if the object does not have the \c kArtIsTextWrap attribute set.
	*/
	AIAPI AIErr(*SetArtTextWrapProperty) (AIArtHandle art, AIReal offset, AIBoolean invert);

	/** Retrieves the properties that affect how text wraps around a text wrap object;
	that is, one in which the \c kArtIsTextWrap attribute is set.
	Use  \c #GetArtUserAttr() and \c #SetArtUserAttr() to inspect and set the
	\c kArtIsTextWrap attribute.

	@param art The art object.
	@param offset [out] A buffer in which to return the distance in points from
	the geometric outline of an object that defines an offset for wrapping.
	@param invert [out] A buffer in which to return true if text wraps inside the outline
	of the offset object, or false if text wraps around the outside of the offset object.
	@return \c kBadParameterErr if the object does not have the \c kArtIsTextWrap attribute set. */
	AIAPI AIErr(*GetArtTextWrapProperty) (AIArtHandle art, AIReal *offset, AIBoolean *invert);

	/** Creates and instates a copy scope. Scopes are reference counted. You must
	use \c #DestroyCopyScope to release the reference when it is no longer needed.
	It is recommended that you use the C++ wrapper \c #ai::CopyScope, which takes
	care of memory management.

	@param kind The type of scope to create, an \c ::AICopyScopeKind value.
	@param scope [out] A buffer in which to return the new scope reference. */
	AIAPI AIErr(*CreateCopyScope) (enum AICopyScopeKind kind, AICopyScopeHandle* scope);

	/** Uninstates and destroys a copy scope. It is recommended that you use the
	C++ wrapper \c #ai::CopyScope, which takes care of memory management.
	@param scope The scope reference, as returned by \c #CreateCopyScope().
	*/
	AIAPI AIErr(*DestroyCopyScope) (AICopyScopeHandle scope);

	/* New in Illustrator 12.0 */

	/** Checks to see if it is OK to create or insert an art object of a given type at a given insertion point.
	@param paintOrder The insertion point in the paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
	@param prep The prepositional art object for the paint order.
	@param artType The type of art object, an \c #AIArtType value.

	@return \c kNoErr if it is OK, and \c #kInvalidArtTypeForDestErr if it is not.
	*/
	AIAPI AIErr(*InsertionPointBadForArtType) (ai::int16 paintOrder, AIArtHandle prep, ai::int16 artType);

	/** Check to see if it is OK to insert an art object or a duplicate copy of it at the indicated
	insertion point, based on attributes of the insertion context and the candidate art, without actually
	attempting the insertion. This is mainly intended for use during drag-drop mouseover,
	to give proper cursor feedback, and so that an insertion is not attempted if it will fail.
	@param candidateArt The art object to test.
	@param paintOrder The position for the insertion point, with respect to \c prep, an \c AITypes::AIPaintOrder value.
	@param prep The prepositional object for the \c paintOrder position.
	@return \c kNoErr if it is OK. Possible non-OK returns are \c #kTooDeepNestingErr,
	\c #kInvalidArtTypeForDestErr, and \c #kUntouchableArtObjectErr.


	*/
	AIAPI AIErr(*PreinsertionFlightCheck) (AIArtHandle candidateArt, ai::int16 paintOrder, AIArtHandle prep);

	/** Sets the note attribute for an art object, which typically contains text entered by the user.
	To attach private data to an art object, plug-ins should use the art dictionary interface (see \c #GetDictionary())
	rather than using the note.
	@param art The art object.
	@param inNote The new text for the note.
	*/
	AIAPI AIErr(*SetNote) (AIArtHandle art, const ai::UnicodeString& inNote);

	/** Retrieves the note attribute text for an art object, which typically contains text entered by the user.
	@param art The art object
	@param outNote [out] A buffer in which to return the contents of the note.
	Returns an empty string if the art object has no note.
	@see \c #SetNote()
	*/
	AIAPI AIErr(*GetNote) (AIArtHandle art, ai::UnicodeString& outNote);

	/** Checks whether an art object has a note attached. (Note this function returns a boolean value, not an error code.)
	@param art The art object.
	@return True if there is a note attached. */
	AIAPI AIBoolean(*HasNote) (AIArtHandle art);

	/** Deletes the note attached to an art object, if there is one. No error code is returned.
	@param art The art object. */
	AIAPI void(*DeleteNote) (AIArtHandle art);

	/** Gets the size of the XMP metadata associated with an art object.
	@param art The art object.
	@param size [out] A buffer in which to return the number of bytes, or 0 if there is no XMP metadata.
	*/
	AIAPI AIErr(*GetArtXMPSize)(AIArtHandle art, size_t* size);

	/** Retrieves the XML packet associated with an art object's XMP metadata. The format is UTF-8
	Unicode.
	@param art The art object.
	@param xmp [out] A buffer in which to return the XML packet. Allocate a buffer using \c #GetArtXMPSize().
	@param size The number of bytes in the \c xmp buffer.
	*/
	AIAPI AIErr(*GetArtXMP)(AIArtHandle art, char *xmp, size_t size);

	/** Sets XMP metadata for an art object, replacing any existing data. Format must be UTF-8
	Unicode.
	@param art The art object.
	@param xmp The new XML packet.Use a null XMP pointer or empty one to remove the existing metadata.
	*/
	AIAPI AIErr(*SetArtXMP)(AIArtHandle art, const char *xmp);

	/** Retrieves the geometric bounds of an art object after applying a transformation matrix.
	Returns double-precision coordinates.
	@param art The art object.
	@param transform A pointer to a transformation matrix to apply.
	@param flags Bit flags that specify which bounds to return. A logical OR of \c #AIArtBoundsOptions constants.
	The flags must include either \c kVisibleBounds or \c kControlBounds,
	and can include additional flags depending on which of these is included.
	@param bounds [out] A buffer in which to return the bounds value, containing double-precision coordinates.
	@see \c #GetArtTransformBounds()
	*/
	AIAPI AIErr(*GetPreciseArtTransformBounds) (AIArtHandle art, AIRealMatrix *transform, ai::int32 flags, AIDoubleRect *bounds);

	/** Removes an art object from the art tree, performing minimal checks for validity of the input
	in order to maximize performance. Disposing of a group or compound path
	also removes the children.
	@param art The art object. Upon return, the reference is no longer valid.
	*/
	AIAPI AIErr(*UncheckedDisposeArt) (AIArtHandle art);

	/* New in Illustrator 13.0 */

	/** Reports whether an art object is a graph object type.
	Graphs (for historical reasons) have no specific art type in
	\c #AIArtType enum, and get the type \c #kUnknownArt.
	@param art The art object to query.
	@param artisgraph [out] A buffer in which to return true if the object
	is a graph.
	*/
	AIAPI AIErr(*ArtIsGraph)(AIArtHandle art, AIBoolean *artisgraph);

	/* New in Illustrator 14.0 */

	/** Sets the art as KeyArt for object alignment.The key object is the one to which other objects are aligned.
	If art is NULL, it cancels key art. Use this API to Cancel KeyArt instead of CancelKeyArt().
	@param art [in] The art object to be set as Key Art
	The art needs to be currently selected.
	@return an AIErr. In case of success returns kNoErr else give kBadParameterErr
	@see \c #GetKeyArt()
	*/
	AIAPI AIErr(*SetKeyArt)(AIArtHandle art);

	/* New in Illustrator 15.0 */

	/** Retrieves the drawing mode for current document.
	@param mode [out] A buffer in which to return the drawing mode,  an \c #AIDrawingMode constant.
	*/
	AIAPI AIErr(*GetDrawingMode)(ai::int32* mode);

	/** Sets the drawing mode for current document.
	@param mode [in] The drawing mode to be set for a document, an \c #AIDrawingMode constant.
	*/
	AIAPI AIErr(*SetDrawingMode)(ai::int32 mode);

	/** Retrieves the insertion point for current document based on the drawing mode.
	This is the position in the art tree at which a drawing tool should create new art.
	@param mode [in] The drawing mode, an \c #AIDrawingMode constant.
	@param art [out] The art object.
	@param paintorder [out] The position in the paint order, relative to the specified art object.
	See \c #AITypes::AIPaintOrder for the possible positions.
	@param editable [out] A buffer in which to return true if it is possible to create art
	at the returned position. For example, you cannot create art in a locked layer.
	Pass null if not needed.
	*/
	AIAPI AIErr(*GetInsertionPointForDrawingMode) (ai::int32 mode, AIArtHandle *art, short *paintorder, AIBoolean *editable);

	/** Retrieves the insertion point for current document based on the current drawing mode.
	This is the position in the art tree at which a drawing tool should create new art.
	@param art [out] The art object.
	@param paintorder [out] The position in the paint order, relative to the specified art object.
	See \c #AITypes::AIPaintOrder for the possible positions.
	@param editable [out] A buffer in which to return true if it is possible to create art
	at the returned position. For example, you cannot create art in a locked layer.
	Pass null if not needed.
	*/
	AIAPI AIErr(*GetInsertionPointForCurrentDrawingMode) (AIArtHandle *art, short *paintorder, AIBoolean *editable);
	/** Retrieves the path polarity of an art object.

	@param art The art object.
	@param polarity [out] A buffer in which to return the polarity value.
	Value of polarity is set to \c #kAIPolarPath or \c #kAINonPolarPath.
	*/

	AIAPI AIErr(*GetPathPolarity) (AIArtHandle art, ai::int32* polarity);

	/** Reports whether an art object is in pixel-perfect mode.
	@param art [in]: The art object
	Note that this API returns a boolean value and not an error.
	@return True of the pixel-perfect property is on, false if it is off.
	*/
	AIAPI AIBoolean(*IsPixelPerfect) (AIArtHandle art);

	/** Turns the pixel-perfect mode on or off for an art object.
	@param art [in] The art object
	@param isPixelPerfect [in] True to turn pixel-perfect mode on, false to turn it off.
	*/
	AIAPI AIErr(*SetPixelPerfect) (AIArtHandle art, AIBoolean isPixelPerfect);

	/** Compare two art objects to determine if they are equivalient in geometry, appearance attributes,
	and dictionary contents.Typically, one object is in the current document, and the other
	is in another document. This function uses the same sense of equivalence in which two patterns
	or symbol definitions are considered equivalent when retargeting an external symbol or pattern
	to the current document. In particular, if one object is in a document with a different color
	mode than the other, then non-global process colors are converted to the color mode of the
	first object before comparison, and named global objects are considered equivalent if the
	definitions match and the names are equal except for trailing numerical suffixes.
	(Note that this function returns a Boolean value, not an error code.)

	@param art1	 The first art object.
	@param art2The second art object.
	@return True if the objects are equivalent, false otherwise.

	@see \c #AISymbolSuite::RetargetForCurrentDocument() and \c #AIPathStyleSuite::RetargetForCurrentDoc()
	*/
	AIAPI AIBoolean(*ObjectsAreEquivalent) (AIArtHandle art1, AIArtHandle art2);

	/** Reports whether an art object acts as a layer within a symbol pattern.
	This is a simulated layer that functions as a group, except when isolated or expanded.
	It is not a layer object and cannot be manipulated with the \c #AILayerSuite.
	@param art [in] The art object
	@param isLayerInSymbol [out] A buffer in which to return true if
	this is a simulated layer in a symbol pattern, false otherwise.
	*/
	AIAPI AIErr(*IsArtALayerInSymbol) (AIArtHandle art, AIBoolean* isLayerInSymbol);

	/** Retrieves the modification time stamp for an art object.
	@param art [in] The art object
	@param timeStamp [out] A buffer in which to return the modification time stamp.
	*/
	AIAPI AIErr(*GetArtTimeStamp) (AIArtHandle art, size_t* timeStamp);

	AIAPI AIErr(*ConvertPointTypeToAreaType) (AIArtHandle art, AIArtHandle* newArtHandle);

	AIAPI AIErr(*ConvertAreaTypeToPointType) (AIArtHandle art, AIArtHandle* newArtHandle);

} AI192ArtSuite;

#include "AIHeaderEnd.h" // __cplusplus

#endif // __AI192Art__

