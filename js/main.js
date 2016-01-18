(function () {
    'use strict';
    
    var BlokVm = (function() {        
        function BlokVm() {
            this.title = ko.observable("Not set");
            this.isContainerSettingsVisible = ko.observable(false);
            this.isChildSettingsVisible = ko.observable(false);
            this.isCreateButtonVisible = ko.observable(false);
            
            // Blok settings
            this.fixedWidth = undefined;
            this.fixedHeight = undefined;
            this.flex = undefined;
            this.alignSelf = ko.observable(undefined);
            
            // BlokContainer settings
            this.flexDirection = ko.observable(0);
            this.justifyContent = ko.observable(0);
            this.alignItems = ko.observable(0);
            this.flexWrap = ko.observable(0);
        }
        
        BlokVm.prototype.equals = function(settings) {
            return this.fixedWidth === settings.fixedWidth &&
                this.fixedHeight === settings.fixedHeight &&
                this.flex === settings.flex &&
                this.alignSelf === settings.alignSelf &&
                this.flexDirection() === settings.flexDirection &&
                this.justifyContent() === settings.justifyContent &&
                this.alignItems() === settings.alignItems &&
                this.flexWrap() === settings.flexWrap;
        };
        
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
            /** Register a callback for whenever Illustrator is about to undo an action. Will fire before SELECTION_CHANGED */
            onPreUndo: function(cb) {
                csInterface.addEventListener("com.adobe.csxs.events.PreUndo", function(ret) {
                    cb();
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
            },
            checkSelectionForRelayout: function() {
                csInterface.evalScript("loader(7).checkSelectionForRelayout()");
            }
        };
    })();
    
    
    
    
    // Execution starts here
    try {
        BlokScripts.onException(function(ret) {
            alert("JSX crashed. FileName: " + ret.fileName + ", Line: " + ret.line + ", Name: " + ret.name + ", Message: " + ret.message);
        });

        themeManager.init();

        var viewModel = new BlokVm();
        ko.applyBindings(viewModel);
        
        // Global which tracks whether a selection changed event is caused by an undo
        var isUndo = false;
        
        BlokScripts.onPreUndo(function() {
            isUndo = true;
        });

        BlokScripts.onSelectionChanged(function() {
            if (!isUndo) {
                BlokScripts.checkSelectionForRelayout();
            }
            
            isUndo = false;
            
            BlokScripts.getActionsFromSelection(function(result) {
                if (result.action === 0) {
                    viewModel.title("No Options");
                    viewModel.isChildSettingsVisible(false);
                    viewModel.isContainerSettingsVisible(false);
                    viewModel.isCreateButtonVisible(false);
                }
                else if (result.action === 1) {
                    // Container sel
                    viewModel.title("Blok Group");
                    viewModel.isChildSettingsVisible(false);
                    viewModel.isContainerSettingsVisible(true);
                    viewModel.isCreateButtonVisible(false);

                    viewModel.flexDirection(result.blok.flexDirection);
                    viewModel.justifyContent(result.blok.justifyContent);
                    viewModel.alignItems(result.blok.alignItems);
                }
                else if (result.action === 2) {
                    // child sel
                    viewModel.title("Blok Item");
                    viewModel.isChildSettingsVisible(true);
                    viewModel.isContainerSettingsVisible(false);
                    viewModel.isCreateButtonVisible(false);
                }
                else if (result.action === 3) {
                    // Create group
                    viewModel.title("Blok Group");
                    viewModel.isChildSettingsVisible(false);
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
            BlokScripts.getActionsFromSelection(function(result) {
                if (result.action === 1 && !viewModel.equals(result.blok)) {
                    BlokScripts.updateSelectedBlokContainer(ko.toJSON(viewModel));
                }
            });
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
            location.reload();
        });
    }
    catch (ex) {
        alert("CEP crashed: " + ex.toString());
    }

}());
    
