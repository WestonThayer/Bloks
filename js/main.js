/*jslint vars: true, plusplus: true, devel: true, nomen: true, regexp: true, indent: 4, maxerr: 50 */
/*global $, window, location, CSInterface, SystemPath, themeManager*/

(function () {
    'use strict';

    var csInterface = new CSInterface();
    
    function getGroupBlokObjectPayloadFromUI() {
        var blokObject = {
            type: "container",

            // child properties
            fixedWidth: undefined,
            fixedHeight: undefined,
            flex: undefined, // same as flex-grow
            alignSelf: undefined,

            // container properties
            flexDirection: "row", // orientation
            justifyContent: "flex-start", // spacing (only allow flex-start and space-between)
            alignItems: "flex-start", // alignment
            flexWrap: "nowrap", // wrapping
            
            // both
            layoutWidth: undefined,
            layoutHeight: undefined
        };

        if ($("#orientation-vertical-btn").is(":checked")) {
            blokObject.flexDirection = "column";
        }

        if ($("#spacing-space-between-btn").is(":checked")) {
            blokObject.justifyContent = "space-between";
        }

        if ($("#alignment-center-btn").is(":checked")) {
            blokObject.alignItems = "center";
        }
        else if ($("#alignment-flex-end-btn").is(":checked")) {
            blokObject.alignItems = "flex-end";
        }
        else if ($("#alignment-stretch-btn").is(":checked")) {
            blokObject.alignItems = "stretch";
        }

        var payload = JSON.stringify(blokObject);
        
        return payload;
    }
    
    function showNoUI() {
        $("#title").text("No options");
        
        $("#create-group-items").hide();
        $("#edit-child-items").hide();
    }
    
    function showCreateGroupUI() {
        $("#title").text("Create layout group");
        
        $("#create-group-items").show();
        $("#edit-child-items").hide();
        
        $("#create-group-btn").show();
        $("#edit-group-btn").hide();
    }
    
    function showEditGroupUI(currentBlok) {
        $("#title").text("Edit layout group");
        
        $("#create-group-items").show();
        $("#edit-child-items").hide();
        
        $("#create-group-btn").show();
        $("#edit-group-btn").hide();
        
        $("#create-group-btn").hide();
        $("#edit-group-btn").show();
        
        // Make UI match blok object
        
        if (currentBlok.flexDirection === "row") {
            $("#orientation-horizontal-btn").prop("checked", true);
        }
        else if (currentBlok.flexDirection === "column") {
            $("#orientation-vertical-btn").prop("checked", true);
        }
        
        if (currentBlok.justifyContent === "flex-start") {
            $("#spacing-flex-start-btn").prop("checked", true);
        }
        else if (currentBlok.justifyContent === "space-between") {
            $("#spacing-space-between-btn").prop("checked", true);
        }
        
        if (currentBlok.alignItems === "flex-start") {
            $("#alignment-flex-start-btn").prop("checked", true);
        }
        else if (currentBlok.alignItems === "center") {
            $("#alignment-center-btn").prop("checked", true);
        }
        else if (currentBlok.alignItems === "flex-end") {
            $("#alignment-flex-end-btn").prop("checked", true);
        }
        else if (currentBlok.alignItems === "stretch") {
            $("#alignment-stretch-btn").prop("checked", true);
        }
    }
    
    function showEditChildUI(currentBlok) {
        $("#title").text("No options");
        
        $("#create-group-items").hide();
        $("#edit-child-items").show();
    }
    
    function init() {
                
        themeManager.init();
        
        // Register for AI selection changed (very noisy)
        AIEventAdapter.getInstance().addEventListener(AIEvent.ART_SELECTION_CHANGED, function(event) {
            csInterface.evalScript("getActionsFromSelection()", function(ret) {
                var r = JSON.parse(ret);
                
                if (r.action === 0) {
                    showNoUI();
                }
                else if (r.action === 1) {
                    showEditGroupUI(r.blok);
                }
                else if (r.action === 2) {
                    showEditChildUI(r.blok);
                }
                else if (r.action === 3) {
                    showCreateGroupUI();
                }
                else { showNoUI();}
            });
            
            // This does bad things for the undo stack
            csInterface.evalScript("runBlokLayoutFromSelection()");
        });
                
        $("#create-group-btn").click(function () {
            var payload = getGroupBlokObjectPayloadFromUI();
            
            csInterface.evalScript("createBlokLayoutGroupFromSelection(" + payload + ")");
        });
        
        $("#edit-group-btn").click(function() {
            var payload = getGroupBlokObjectPayloadFromUI();
            
            csInterface.evalScript("updateBlokFromSelection(" + payload + ")");
        });
        
        $("#edit-child-btn").click(function() {
            var blokObject = {
                type: "child",

                // child properties
                fixedWidth: undefined,
                fixedHeight: undefined,
                flex: undefined, // same as flex-grow
                alignSelf: undefined,

                // container properties
                flexDirection: undefined, // orientation
                justifyContent: undefined, // spacing (only allow flex-start and space-between)
                alignItems: undefined, // alignment
                flexWrap: undefined, // wrapping
                
                // both
                layoutWidth: undefined,
                layoutHeight: undefined
            };
            
            var payload = JSON.stringify(blokObject);
            
            csInterface.evalScript("updateBlokFromSelection(" + payload + ")");
        });
        
        // Helps with debugging
        $("#reload-btn").click(function () {
            /*var event = new CSEvent("com.adobe.csxs.events.SilentTransformRequestedEvent", "APPLICATION", "ILST", "microsoft.design.bloks");
            event.data = "need to put a matrix here...";
            csInterface.dispatchEvent(event);*/
            
            location.reload(); 
        });
    }
        
    init();

}());
    
