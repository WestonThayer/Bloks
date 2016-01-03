(function () {
    'use strict';
    
    var BlokVm = (function() {        
        function BlokVm() {
            this.title = ko.observable("Not set");
            this.isContainerSettingsVisible = ko.observable(false);
            this.isCreateButtonVisible = ko.observable(false);
            
            // Blok settings
            this.fixedWidth = undefined;
            this.fixedHeight = undefined;
            this.flex = undefined;
            this.alignSelf = undefined;
            
            // BlokContainer settings
            this.flexDirection = ko.observable(0);
            this.justifyContent = ko.observable(0);
            this.alignItems = ko.observable(0);
            this.flexWrap = ko.observable(0);
        }
        
        return BlokVm;
    })();
    
    /** Function container for dealing with Blok JSX API */
    var BlokScripts = (function() {
        var csInterface = new CSInterface();
        
        // TODO: how does this handle exceptions? We should crash too
        
        return {
            /** Register a callback for when there's an exception from JSX */
            onException: function(cb) {
                csInterface.addEventListener("microsoft.design.bloks.JsxExceptionRaised", function(ret) {
                    cb(ret.data);
                });
            },
            /** Register a callback for whenever Illustrator's SELECTION_CHANGED event fires (a lot) */
            onSelectionChanged: function(cb) {
                csInterface.addEventListener("com.adobe.csxs.events.SelectionChanged", function(ret) {
                    // Only listen for our plugin's events, we could be hearing others
                    if (ret.extensionId === "microsoft.design.bloks") {
                        cb();
                    }
                });
            },
            getActionsFromSelection: function(cb) {                
                csInterface.evalScript("loader(7).getActionsFromSelection()", function(ret) {
                    var result = JSON.parse(ret);
                    cb(result);
                });
            },
            createBlokContainerFromSelection: function(settingsStr, cb) {
                csInterface.evalScript("loader(7).createBlokContainerFromSelection(" + settingsStr + ")", function(ret) {
                    if (cb) {
                        cb();
                    }
                });
            },
            updateSelectedBlokContainer: function(settingsStr, cb) {
                csInterface.evalScript("loader(7).updateSelectedBlokContainer(" + settingsStr + ")", function(ret) {
                    if (cb) {
                        cb();
                    }
                });
            }
        };
    })();
    
    
    
    
    // Execution starts here
    try {
        BlokScripts.onException(function(ret) {
            alert("JSX crashed: " + JSON.stringify(ret));
        });

        themeManager.init();

        var viewModel = new BlokVm();
        ko.applyBindings(viewModel);

        BlokScripts.onSelectionChanged(function() {
            BlokScripts.getActionsFromSelection(function(result) {
                if (result.action === 0) {
                    viewModel.title("No Options");
                    viewModel.isContainerSettingsVisible(false);
                }
                else if (result.action === 1) {
                    // Container sel
                    alert("container");
                }
                else if (result.action === 2) {
                    // child sel
                    alert("child");
                }
                else if (result.action === 3) {
                    // Create group
                    viewModel.title("Blok Group");
                    viewModel.isContainerSettingsVisible(true);
                    viewModel.isCreateButtonVisible(true);
                    viewModel.flexDirection(0);
                    viewModel.justifyContent(0);
                    viewModel.alignItems(0);
                }
                else {
                    throw new Error("Unexpected action value: " + result);
                }
            });
        });

        // On-the-fly updates

        function handleBlokContainerPropertyChanged(newValue) {
            BlokScripts.updateSelectedBlokContainer(ko.toJSON(viewModel));
        }

        viewModel.flexDirection.subscribe(handleBlokContainerPropertyChanged);
        viewModel.justifyContent.subscribe(handleBlokContainerPropertyChanged);
        viewModel.alignItems.subscribe(handleBlokContainerPropertyChanged);


        // Group creation
        $("#create-btn").click(function() {
            viewModel.isCreateButtonVisible(false);
            BlokScripts.createBlokContainerFromSelection(ko.toJSON(viewModel));
        });



        // Helps with debugging
        $("#reload-btn").click(function () {
            /*var event = new CSEvent("com.adobe.csxs.events.SilentTransformRequestedEvent", "APPLICATION", "ILST", "microsoft.design.bloks");
            event.data = "need to put a matrix here...";
            csInterface.dispatchEvent(event);*/

            location.reload(); 
        });
    }
    catch (ex) {
        alert("CEP crashed: " + ex.toString());
    }

}());
    
