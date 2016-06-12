(function () {
    'use strict';
    
    try {
        // Filters an input to either undefined or a positive number
        ko.extenders.positiveNumeric = function(target, sec) {
            var result = ko.pureComputed({
                read: target,
                write: function(newValue) {
                    var current = target();
                    var newValueAsNum = isNaN(newValue) || newValue === "" ? undefined : Math.abs(parseFloat(+newValue));
                    
                    if (current !== newValueAsNum) {
                        target(newValueAsNum);
                    }
                    else {
                        if (current !== newValue) {
                            target.notifySubscribers(newValueAsNum);
                        }
                    }
                }
            }).extend({ notify: "always" });
            
            result(target);
            return result;
        };
        
        var BlokVm = (function() {        
            function BlokVm() {
                this.isErrorStateVisible = ko.observable(true);
                this.title = ko.observable("Not set");
                this.isContainerSettingsVisible = ko.observable(false);
                this.isChildSettingsVisible = ko.observable(false);
                this.isCreateButtonVisible = ko.observable(false);
                this.isLayoutButtonVisible = ko.observable(false);

                // Blok settings
                this.flex = ko.observable(undefined).extend({ positiveNumeric: 0 });
                this.alignSelf = ko.observable(undefined);
                this.parentBlokContainerFlexDirection = ko.observable(0);

                // BlokContainer settings
                this.flexDirection = ko.observable(0);
                this.justifyContent = ko.observable(0);
                this.alignItems = ko.observable(0);
                this.flexWrap = ko.observable(0);
            }

            BlokVm.prototype.blokEquals = function(settings) {
                return this.flex() === settings.flex &&
                    this.alignSelf() === settings.alignSelf;
            };

            BlokVm.prototype.blokContainerEquals = function(settings) {
                return this.blokEquals(settings) &&
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
                    csInterface.addEventListener("com.westonthayer.bloks.events.JsxExceptionRaised", function(ret) {
                        cb(ret.data);
                    });
                },
                /** Register a callback for whenever Illustrator is about to undo an action. Will fire before SELECTION_CHANGED */
                onPreUndo: function(cb) {
                    csInterface.addEventListener("com.westonthayer.bloks.events.PreUndo", function(ret) {
                        cb();
                    });
                },
                /** Register a callback for whenever Illustrator is about to show or hide the rulers. */
                onPreShowHideRulers: function(cb) {
                    csInterface.addEventListener("com.westonthayer.bloks.events.PreShowHideRulers", function(ret) {
                        cb();
                    });
                },
                /** Register a callback for whenever Illustrator's SELECTION_CHANGED event fires (a lot) */
                onSelectionChanged: function(cb) {
                    csInterface.addEventListener("com.westonthayer.bloks.events.SelectionChanged", function(ret) {
                        // Only listen for our plugin's events, we could be hearing others
                        if (ret.extensionId === "com.westonthayer.bloks") {
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
                updateSelectedBlok: function(settingsStr, cb) {
                    csInterface.evalScript("loader(7).updateSelectedBlok(" + settingsStr + ")", function(ret) {
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
                },
                relayoutSelection: function() {
                    csInterface.evalScript("loader(7).relayoutSelection()");
                },
                hideSpacers: function() {
                    csInterface.evalScript("loader(7).hideSpacers()");
                },
                showSpacers: function() {
                    csInterface.evalScript("loader(7).showSpacers()");
                }
            };
        })();
        
        
        // Execution starts here
        BlokScripts.onException(function(ret) {
            alert("JSX crashed. FileName: " + ret.fileName + ", Line: " + ret.line + ", Name: " + ret.name + ", Message: " + ret.message);
        });

        themeManager.init();

        var viewModel = new BlokVm();
        ko.applyBindings(viewModel);
        
        // Global which tracks whether a selection changed event is caused by an undo
        var isUndo = false;
        
        // Global which tracks when the last time a ruler was shown/hidden
        var lastRulerTime = new Date();
        
        BlokScripts.onPreUndo(function() {
            isUndo = true;
        });
        
        BlokScripts.onPreShowHideRulers(function() {
            var endTime = new Date();
            var diff = endTime - lastRulerTime;
            lastRulerTime = endTime;
            
            // We allow the user to use <CTRL + R> to trigger a relayout
            // since clicking our UI is inconvenient. Illustrator doesn't let us
            // register for keyboard shortcuts, so we listen instead for the show/hide
            // ruler menu command. Since invoking that command shows the ruler, it's probably
            // typical that you would want to hit <CTRL + R> 2x quickly to just toggle the ruler
            // yet still get the relayout behavior. So, we check to see if it's been "quickly"
            // toggled to avoid the overhead of another layout pass.
            if (diff > 1000) {                
                BlokScripts.relayoutSelection();
            }
        });
        
        function respondToActions(result) {
            // If we ever hear back from the plugin, no more need for
            // initial state to show
            viewModel.isErrorStateVisible(false);
            
            if (result.action === 0) {
                viewModel.title("No Options");
                viewModel.isChildSettingsVisible(false);
                viewModel.isContainerSettingsVisible(false);
                viewModel.isCreateButtonVisible(false);
                viewModel.isLayoutButtonVisible(false);
            }
            else if (result.action === 1) {
                // Container sel
                viewModel.title("Blok Group");

                if (result.blok.isAlsoChild) {
                    viewModel.isChildSettingsVisible(true);
                    viewModel.flex(result.blok.flex);
                    viewModel.alignSelf(result.blok.alignSelf);
                    viewModel.parentBlokContainerFlexDirection(result.blok.parentBlokContainer.flexDirection);
                }
                else {
                    viewModel.isChildSettingsVisible(false);
                }

                viewModel.isContainerSettingsVisible(true);
                viewModel.isCreateButtonVisible(false);
                viewModel.isLayoutButtonVisible(true);

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
                viewModel.isLayoutButtonVisible(true);

                viewModel.flex(result.blok.flex);
                viewModel.alignSelf(result.blok.alignSelf);
                viewModel.parentBlokContainerFlexDirection(result.blok.parentBlokContainer.flexDirection);
            }
            else if (result.action === 3) {
                // Create group
                viewModel.title("Blok Group");
                viewModel.isChildSettingsVisible(false);
                viewModel.isContainerSettingsVisible(true);
                viewModel.isCreateButtonVisible(true);
                viewModel.isLayoutButtonVisible(false);
                viewModel.flexDirection(0);
                viewModel.justifyContent(0);
                viewModel.alignItems(0);
            }
            else {
                throw new Error("Unexpected action value: " + result);
            }
        }

        BlokScripts.onSelectionChanged(function() {  
            BlokScripts.getActionsFromSelection(respondToActions);
            
            if (!isUndo) {
                BlokScripts.checkSelectionForRelayout();
            }
            
            isUndo = false;
        });

        // On-the-fly updates
        
        function handleBlokPropertyChanged(newValue) {
            BlokScripts.getActionsFromSelection(function(result) {
                if (result.action === 2 && !viewModel.blokEquals(result.blok)) {
                    BlokScripts.updateSelectedBlok(ko.toJSON(viewModel));
                }
                else if (result.action === 1 &&
                         result.blok.isAlsoChild &&
                         !viewModel.blokContainerEquals(result.blok)) {
                    BlokScripts.updateSelectedBlokContainer(ko.toJSON(viewModel));
                }
            });
        }
        
        viewModel.flex.subscribe(handleBlokPropertyChanged);
        viewModel.alignSelf.subscribe(handleBlokPropertyChanged);

        
        function handleBlokContainerPropertyChanged(newValue) {
            BlokScripts.getActionsFromSelection(function(result) {
                if (result.action === 1 && !viewModel.blokContainerEquals(result.blok)) {
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
            
            var settings = {
                flexDirection: viewModel.flexDirection(),
                justifyContent: viewModel.justifyContent(),
                alignItems: viewModel.alignItems(),
                flexWrap: viewModel.flexWrap()
            };
            
            BlokScripts.createBlokContainerFromSelection(JSON.stringify(settings));
        });
        
        // Force a layout
        $("#layout-btn").click(function() {
            BlokScripts.relayoutSelection();
        });
        
        // Easy show/hide of .spacer PageItems
        $("#spacer-hide-btn").click(function() {
            BlokScripts.hideSpacers();
        });
        
        $("#spacer-show-btn").click(function() {
            BlokScripts.showSpacers();
        });



        // Helps with debugging
        $("#reload-btn").click(function () {
            location.reload();
        });
        
        // Make an initial query on first boot
        BlokScripts.getActionsFromSelection(respondToActions);
    }
    catch (ex) {
        alert("CEP crashed: " + ex.toString());
    }

}());
    
