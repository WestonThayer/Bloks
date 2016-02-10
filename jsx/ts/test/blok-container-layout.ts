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
    Assert.areEqual(blokContainer.getFixedWidth(), undefined);
    Assert.areEqual(blokContainer.getFixedHeight(), undefined);
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

//TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepRow);
//TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepRowStretch);
//TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepRowChildStretch);
//TestFramework.run("blok-container-layout-one-deep.ai", testOneDeepColumn);
//TestFramework.run("blok-container-layout-one-deep-3.ai", testOneDeepRowSpaceBetween);
//TestFramework.run("blok-container-layout-two-deep.ai", testTwoDeepRow);
//TestFramework.run("blok-container-layout-two-deep.ai", testTwoDeepMixed);
//TestFramework.run("blok-container-layout-two-deep-alt.ai", testTwoDeepRowAlt);
//TestFramework.run("blok-container-layout-nested-groups.ai", testNestedGroups);
TestFramework.run("blok-container-layout-strokes.ai", testStrokes);