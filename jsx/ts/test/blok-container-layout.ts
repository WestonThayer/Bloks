/// <reference path="../typings/noderequire.d.ts" />
/// <reference path="../typings/illustrator.d.ts" />

"use strict";

// Typescript imports
import Assert = require("./assert");
import TestFramework = require("./test-framework");
import Blok = require("../blok");
import BlokUserSettings = require("../blok-user-settings");
import BlokContainer = require("../blok-container");
import BlokContainerUserSettings = require("../blok-container-user-settings");
import BlokAdapter = require("../blok-adapter");
import Rect = require("../rect");
import Css = require("../css");

// npm imports
var JSON2: any = require("JSON2");

// To run:
//     connect ExtendScript Toolkit to Illustrator
//     run

function testOneDeepRow() {
    let pageItem = app.activeDocument.pageItems[0];

    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 250, 200])));
    Assert.areEqual(blokContainer.getFlex(), undefined);
    Assert.areEqual(blokContainer.getAlignSelf(), undefined);
    Assert.areEqual(blokContainer.getFlexDirection(), Css.FlexDirections.ROW);
    Assert.areEqual(blokContainer.getJustifyContent(), Css.Justifications.FLEX_START);
    Assert.areEqual(blokContainer.getAlignItems(), Css.Alignments.FLEX_START);
    Assert.areEqual(blokContainer.getFlexWrap(), Css.FlexWraps.NOWRAP);

    let settings = blokContainer.getUserSettings();

    Assert.areEqual(settings.alignSelf, undefined);
    Assert.areEqual(settings.flexDirection, 0);
    Assert.areEqual(settings.alignItems, 0);
    Assert.areEqual(settings.flexWrap, 0);

    let cssNode = blokContainer.computeCssNode();

    Assert.areEqual(cssNode.style.width, undefined);
    Assert.areEqual(cssNode.style.height, undefined);
    Assert.areEqual(cssNode.style.flex, undefined);
    Assert.areEqual(cssNode.style.alignSelf, undefined);
    Assert.areEqual(cssNode.style.flexDirection, "row");
    Assert.areEqual(cssNode.style.justifyContent, "flex-start");
    Assert.areEqual(cssNode.style.alignItems, "flex-start");
    Assert.areEqual(cssNode.style.flexWrap, "nowrap");

    Assert.areEqual(cssNode.children.length, 2);

    Assert.areEqual(cssNode.children[0].style.width, 100);
    Assert.areEqual(cssNode.children[0].style.height, 100);
    Assert.areEqual(cssNode.children[0].style.flex, undefined);

    Assert.areEqual(cssNode.children[1].style.width, 50);
    Assert.areEqual(cssNode.children[1].style.height, 200);
    Assert.areEqual(cssNode.children[1].style.flex, undefined);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 150, 200])));
}

/** Container set to stretch */
function testOneDeepRowStretch() {
    let pageItem = app.activeDocument.pageItems[0];

    let settings = new BlokContainerUserSettings();
    settings.alignItems = Css.Alignments.STRETCH;

    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    let cssNode = blokContainer.computeCssNode();

    Assert.areEqual(cssNode.style.alignItems, "stretch");

    Assert.areEqual(cssNode.children.length, 2);

    Assert.areEqual(cssNode.children[0].style.width, 100);
    Assert.areEqual(cssNode.children[0].style.height, undefined);
    Assert.areEqual(cssNode.children[0].style.flex, undefined);

    Assert.areEqual(cssNode.children[1].style.width, 50);
    Assert.areEqual(cssNode.children[1].style.height, undefined);
    Assert.areEqual(cssNode.children[1].style.flex, undefined);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 150, 200])));
}

/** Container not set to stretch, but a child is */
function testOneDeepRowChildStretch() {
    let pageItem = app.activeDocument.pageItems[0];
    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    let childPageItem = pageItem.pageItems[1];
    let childSettings = new BlokUserSettings();
    childSettings.alignSelf = Css.Alignments.STRETCH;
    BlokAdapter.getBlok(childPageItem, childSettings);

    let cssNode = blokContainer.computeCssNode();

    Assert.areEqual(cssNode.children.length, 2);

    Assert.areEqual(cssNode.children[0].style.width, 100);
    Assert.areEqual(cssNode.children[0].style.height, undefined);
    Assert.areEqual(cssNode.children[0].style.flex, undefined);

    Assert.areEqual(cssNode.children[1].style.width, 50);
    Assert.areEqual(cssNode.children[1].style.height, 200);
    Assert.areEqual(cssNode.children[1].style.flex, undefined);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 150, 200])));
}

function testOneDeepColumn() {
    let pageItem = app.activeDocument.pageItems[0];

    let settings = new BlokContainerUserSettings();
    settings.flexDirection = Css.FlexDirections.COLUMN;

    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    Assert.areEqual(blokContainer.getFlexDirection(), Css.FlexDirections.COLUMN);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 100, 300])));
}

function testOneDeepRowSpaceBetween() {
    let pageItem = app.activeDocument.pageItems[0];

    let settings = new BlokContainerUserSettings();
    settings.justifyContent = Css.Justifications.SPACE_BETWEEN;

    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    blokContainer.invalidate();
}

function testOneDeepRowFlex() {
    let pageItem = app.activeDocument.pageItems[0];
    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    let firstChild = pageItem.pageItems[2];
    let secondChild = pageItem.pageItems[1];
    let thirdChild = pageItem.pageItems[0];

    let childSettings = new BlokUserSettings();
    childSettings.flex = 1;
    BlokAdapter.getBlok(firstChild, childSettings);
    BlokAdapter.getBlok(thirdChild, childSettings);

    blokContainer.invalidate();

    // Should not have changed width
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 350, 200])));

    Assert.areEqual(firstChild.width, 150);
    Assert.areEqual(secondChild.width, 50); // This one should not have grown
    Assert.areEqual(thirdChild.width, 150);
}

function testTwoDeepRow() {
    let pageItem = app.activeDocument.pageItems[0];

    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 200, 200])));
}

function testTwoDeepMixed() {
    let pageItem = app.activeDocument.pageItems[0];

    // Set the child group to be column layout
    let childGroupPageItem = pageItem.pageItems[0];
    let childSettings = new BlokContainerUserSettings();
    childSettings.flexDirection = Css.FlexDirections.COLUMN;
    BlokAdapter.getBlokContainer(childGroupPageItem, childSettings);

    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 150, 250])));
}

function testTwoDeepRowAlt() {
    let pageItem = app.activeDocument.pageItems[0];

    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([144, 71, 332, 231])));
}

function testNestedGroups() {
    // Find the groups, from the inner-most to outer-most
    let firstGroupItem = app.activeDocument.pageItems[0].pageItems[1].pageItems[1];
    let secondGroupItem = app.activeDocument.pageItems[0].pageItems[1];
    let thirdGroupItem = app.activeDocument.pageItems[0];

    // Inner-most is laid out with defaults
    let firstBlokContainer = BlokAdapter.getBlokContainer(firstGroupItem);
    firstBlokContainer.invalidate();

    // Next will have flex-end
    let secondSettings = new BlokContainerUserSettings();
    secondSettings.alignItems = Css.Alignments.FLEX_END;
    let secondBlokContainer = BlokAdapter.getBlokContainer(secondGroupItem, secondSettings);
    secondBlokContainer.invalidate();

    // Last will have vertical layout and center alignment
    let thirdSettings = new BlokContainerUserSettings();
    thirdSettings.flexDirection = Css.FlexDirections.COLUMN;
    thirdSettings.alignItems = Css.Alignments.CENTER;
    let thirdBlokContainer = BlokAdapter.getBlokContainer(thirdGroupItem, thirdSettings);
    thirdBlokContainer.invalidate();

    Assert.isTrue(thirdBlokContainer.getRect().equals(new Rect([144, 71, 332, 266])));
}

function testStrokes() {
    let pageItem = app.activeDocument.pageItems[0];
    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 190, 120])));
}

function testTextFrameArea() {
    let pageItem = app.activeDocument.pageItems[0];
    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 294, 200])));

    let textFrame = pageItem.pageItems[0];
    let textFrameBlok = BlokAdapter.getBlok(textFrame);
    Assert.isTrue(textFrameBlok.getRect().equals(new Rect([150, 0, 294, 65])));
    Assert.areEqual(textFrame.textRange.horizontalScale, 100);
    Assert.areEqual(textFrame.textRange.size, 12);
    Assert.areEqual(textFrame.textRange.autoLeading, true);
}

function testTextFrameAreaStretch() {
    let pageItem = app.activeDocument.pageItems[0];
    let settings = new BlokContainerUserSettings();
    settings.alignItems = Css.Alignments.STRETCH;
    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 294, 200])));

    let textFrame = pageItem.pageItems[0];
    let textFrameBlok = BlokAdapter.getBlok(textFrame);
    Assert.isTrue(textFrameBlok.getRect().equals(new Rect([150, 0, 294, 200])));
    Assert.areEqual(textFrame.textRange.horizontalScale, 100);
    Assert.areEqual(textFrame.textRange.size, 12);
    Assert.areEqual(textFrame.textRange.autoLeading, true);
}

function testTextFrameAreaMiddle() {
    let pageItem = app.activeDocument.pageItems[0];
    let textFrame = pageItem.pageItems[0];
    textFrame.zOrder(ZOrderMethod.SENDBACKWARD);

    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    // Now layout
    blokContainer.invalidate();

    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 294, 200])));

    textFrame = pageItem.pageItems[1];
    let textFrameBlok = BlokAdapter.getBlok(textFrame);
    Assert.isTrue(textFrameBlok.getRect().equals(new Rect([100, 0, 244, 65])));
    Assert.areEqual(textFrame.textRange.horizontalScale, 100);
    Assert.areEqual(textFrame.textRange.size, 12);
    Assert.areEqual(textFrame.textRange.autoLeading, true);
}

function testInteractiveResizeRow() {
    let pageItem = app.activeDocument.pageItems[0];
    app.activeDocument.selection = pageItem; // Select it
    let blokContainer = BlokAdapter.getBlokContainer(pageItem);

    blokContainer.invalidate();
    app.redraw(); // Create undo waypoint 1

    pageItem.width = 500; // Resize width
    app.redraw(); // Create undo waypoint 2

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it didn't change size
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 150, 200])));
    Assert.areEqual(pageItem.width, 150);

    pageItem.height = 300; // Resize height
    app.redraw(); // Create undo waypoint 3

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it didn't change size
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 150, 200])));
    Assert.areEqual(pageItem.width, 150);
}

function testInteractiveResizeColumn() {
    let pageItem = app.activeDocument.pageItems[0];
    app.activeDocument.selection = pageItem; // Select it

    let settings = new BlokContainerUserSettings();
    settings.flexDirection = Css.FlexDirections.COLUMN;
    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    blokContainer.invalidate();
    app.redraw(); // Create undo waypoint 1

    pageItem.width = 500; // Resize width
    app.redraw(); // Create undo waypoint 2

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it didn't change size
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 100, 300])));
    Assert.areEqual(pageItem.height, 300);

    pageItem.height = 200; // Resize height
    app.redraw(); // Create undo waypoint 3

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it didn't change size
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 100, 300])));
    Assert.areEqual(pageItem.height, 300);
}

function testInteractiveResizeRowDistributed() {
    let pageItem = app.activeDocument.pageItems[0];
    app.activeDocument.selection = pageItem; // Select it

    let settings = new BlokContainerUserSettings();
    settings.justifyContent = Css.Justifications.SPACE_BETWEEN;
    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    blokContainer.invalidate();
    app.redraw(); // Create undo waypoint 1

    // Verify it stayed distributed
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 444, 200])));

    pageItem.width = 600; // Resize width
    app.redraw(); // Create undo waypoint 2

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it is the new width
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 600, 200])));
    Assert.areEqual(pageItem.width, 600);

    // Verify that each item is original size
    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 100);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 200);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 65);

    pageItem.height = 300; // Resize height
    app.redraw(); // Create undo waypoint 3

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it didn't change size
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 600, 200])));
    Assert.areEqual(pageItem.height, 200);
}

function testInteractiveResizeColumnDistributed() {
    let pageItem = app.activeDocument.pageItems[0];
    app.activeDocument.selection = pageItem; // Select it

    let settings = new BlokContainerUserSettings();
    settings.flexDirection = Css.FlexDirections.COLUMN;
    settings.justifyContent = Css.Justifications.SPACE_BETWEEN;
    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    blokContainer.invalidate();
    app.redraw(); // Create undo waypoint 1

    // Verify it stacked with no distribution.
    // Align to pixel grid is turned on for this file and it has a TextFrameItem, so the numbers get
    // slightly wonky
    Assert.isTrue(blokContainer.getRect().equals(new Rect([-0.01171875, 0, 144, 365])));

    pageItem.height = 500; // Resize height
    app.redraw(); // Create undo waypoint 2

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it is the new height. Again, a bit wonky due to TextFrameItem
    Assert.isTrue(blokContainer.getRect().equals(new Rect([-0.0234375, 0, 143.98828125, 500])));
    Assert.areEqual(pageItem.height, 500);

    // Verify that each item is original size
    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 100);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 200);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 65);

    pageItem.width = 200; // Resize width
    app.redraw(); // Create undo waypoint 3

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it didn't change size
    Assert.isTrue(blokContainer.getRect().equals(new Rect([-0.0234375, 0, 143.98828125, 500])));
    Assert.areEqual(pageItem.width, 144);
}

function testInteractiveResizeRowDistributedStretch() {
    let pageItem = app.activeDocument.pageItems[0];
    app.activeDocument.selection = pageItem; // Select it

    let settings = new BlokContainerUserSettings();
    settings.justifyContent = Css.Justifications.SPACE_BETWEEN;
    settings.alignItems = Css.Alignments.STRETCH;
    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    blokContainer.invalidate();
    app.redraw(); // Create undo waypoint 1

    // Verify it stayed distributed
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 444, 200])));

    pageItem.width = 600; // Resize width
    app.redraw(); // Create undo waypoint 2

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it is the new width
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 600, 200])));
    Assert.areEqual(pageItem.width, 600);

    // Verify that each item is stretched
    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 200);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 200);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 200);

    pageItem.height = 300; // Resize height
    app.redraw(); // Create undo waypoint 3

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify stretch
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 600, 300])));
    Assert.areEqual(pageItem.height, 300);

    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 300);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 300);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 300);
}

function testInteractiveResizeRowDistributedChildStretch() {
    let pageItem = app.activeDocument.pageItems[0];
    app.activeDocument.selection = pageItem; // Select it

    let settings = new BlokContainerUserSettings();
    settings.justifyContent = Css.Justifications.SPACE_BETWEEN;
    let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);

    let childSettings = new BlokUserSettings();
    childSettings.alignSelf = Css.Alignments.STRETCH;
    BlokAdapter.getBlok(pageItem.pageItems[0], childSettings);

    blokContainer.invalidate();
    app.redraw(); // Create undo waypoint 1

    // Verify it stayed distributed
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 444, 200])));

    // Verify that only last item is stretched
    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 100);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 200);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 200);

    pageItem.width = 600; // Resize width
    app.redraw(); // Create undo waypoint 2

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that it is the new width
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 600, 200])));
    Assert.areEqual(pageItem.width, 600);

    // Verify that only last item is stretched
    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 100);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 200);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 200);

    pageItem.height = 300; // Resize height
    app.redraw(); // Create undo waypoint 3

    // Attempt relayout
    blokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify stretch
    Assert.isTrue(blokContainer.getRect().equals(new Rect([0, 0, 600, 300])));
    Assert.areEqual(pageItem.height, 300);

    Assert.areEqual(pageItem.pageItems[2].width, 100);
    Assert.areEqual(pageItem.pageItems[2].height, 100);
    Assert.areEqual(pageItem.pageItems[1].width, 50);
    Assert.areEqual(pageItem.pageItems[1].height, 200);
    Assert.areEqual(pageItem.pageItems[0].width, 144);
    Assert.areEqual(pageItem.pageItems[0].height, 300);
}

function testInteractiveResizeNested() {
    // Find the groups, from the inner-most to outer-most
    let firstGroupItem = app.activeDocument.pageItems[0].pageItems[1].pageItems[0];
    let secondGroupItem = app.activeDocument.pageItems[0].pageItems[1];
    let thirdGroupItem = app.activeDocument.pageItems[0];
    
    let firstSettings = new BlokContainerUserSettings();
    firstSettings.alignItems = Css.Alignments.CENTER;
    let firstBlokContainer = BlokAdapter.getBlokContainer(firstGroupItem, firstSettings);
    
    let secondSettings = new BlokContainerUserSettings();
    secondSettings.flexDirection = Css.FlexDirections.COLUMN;
    secondSettings.justifyContent = Css.Justifications.SPACE_BETWEEN;
    let secondBlokContainer = BlokAdapter.getBlokContainer(secondGroupItem, secondSettings);
    
    let thirdSettings = new BlokContainerUserSettings();
    thirdSettings.alignItems = Css.Alignments.CENTER;
    thirdSettings.justifyContent = Css.Justifications.SPACE_BETWEEN;
    let thirdBlokContainer = BlokAdapter.getBlokContainer(thirdGroupItem, thirdSettings);

    // Select the root
    app.activeDocument.selection = thirdGroupItem;

    thirdBlokContainer.invalidate();
    app.redraw(); // Undo waypoint 1

    // Verify that it stayed distributed
    Assert.isTrue(thirdBlokContainer.getRect().equals(new Rect([0, 0, 321, 162])));

    app.activeDocument.selection = secondGroupItem; // select the second item
    secondGroupItem.height = 120; // Make the 2nd group distribute taller
    app.redraw(); // Undo waypoint 2

    secondBlokContainer.checkForRelayout(app.activeDocument.selection);

    // Verify that the second group doesn't stretch (0.5 is layout rounded after we finish)
    Assert.isTrue(secondBlokContainer.getRect().equals(new Rect([139.5, 21, 139.5 + 78, 21 + 120])));

    // But we do stretch if alignSelf is stretch
    secondSettings.alignSelf = Css.Alignments.STRETCH;
    secondBlokContainer = BlokAdapter.getBlokContainer(secondGroupItem, secondSettings);
    secondBlokContainer.invalidate();

    Assert.isTrue(secondBlokContainer.getRect().equals(new Rect([139.5, 0, 139.5 + 78, 162])));
}

TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepRow);
TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepRowStretch);
TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepRowChildStretch);
TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepColumn);
TestFramework.run("blok-container-layout-one-deep-3.ai", testOneDeepRowSpaceBetween);
TestFramework.run("blok-container-layout-one-deep-3.ai", testOneDeepRowFlex);
TestFramework.run("blok-container-layout-two-deep.ai", testTwoDeepRow);
TestFramework.run("blok-container-layout-two-deep.ai", testTwoDeepMixed);
TestFramework.run("blok-container-layout-two-deep-alt.ai", testTwoDeepRowAlt);
TestFramework.run("blok-container-layout-nested-groups.ai", testNestedGroups);
TestFramework.run("blok-container-layout-strokes.ai", testStrokes);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testTextFrameArea);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testTextFrameAreaStretch);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testTextFrameAreaMiddle);
TestFramework.run("blok-container-layout-one-deep.ai", testInteractiveResizeRow);
TestFramework.run("blok-container-layout-one-deep.ai", testInteractiveResizeColumn);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testInteractiveResizeRowDistributed);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testInteractiveResizeColumnDistributed);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testInteractiveResizeRowDistributedStretch);
TestFramework.run("blok-container-layout-one-deep-textframearea.ai", testInteractiveResizeRowDistributedChildStretch);
TestFramework.run("blok-container-layout-nested-groups-alt.ai", testInteractiveResizeNested);