/// <reference path="../typings/illustrator.d.ts" />

"use strict";

/**
 * Open the given file in Illustrator from the given relative path. 
 *
 * @param fileName - the name of a file, with extension, relative to the executing script
 */
function open(fileName: string): void {
    // Awkwardly have to cast since File is already defined in lib.d.ts, but Illustrator
    // overrides it
    let F: any = File;
    
    let thisFile = new F($.fileName);
    let folder = thisFile.parent;

    app.open(new F(folder + "/" + fileName));
}


/**
 * Open the specified file and run the test function. Will alert if passing. The document
 * will be closed without saving.
 *
 * @param fileName - the name of a file, with extension, relative to the executing script
 * @param test - a function to run
 */
export function run(fileName: string, test: any): void {
    open(fileName);
    test();

    if (confirm("Passed! Close the document?")) {
        app.activeDocument.close(SaveOptions.DONOTSAVECHANGES);
    }
}