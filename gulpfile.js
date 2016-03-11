var gulp = require("gulp");
var gulpUtil = require("gulp-util");
var through = require("through2");
var source = require('vinyl-source-stream');
var buffer = require("vinyl-buffer");
var browserify = require("browserify");
var tsify = require("tsify");

gulp.task("build-jsx", function() {
    var b = browserify("jsx/ts/index.ts").plugin(tsify);
    
    return b.bundle()
        .pipe(source("hostscript.jsx"))
        .pipe(buffer())
        .pipe(through.obj(function(file, encoding, callback) {
            if (file.isNull()) {
                this.push(null);
                callback();
                return;
            }

            if (file.isStream()) {
                this.emit("error", new gulpUtil.PluginError("my-modifier", "Streams are not supported!"));
                callback();
                return;
            }

            if (file.isBuffer()) {
                var contents = file.contents.toString("utf-8");
                
                // Assign the self-executing function that Browserify creates
                // to a 'loader' variable so that it can be accessed from
                // the CEP extension. For example, loader(7) gives you access to all
                // the functions that index.ts exports.
                contents = "var loader = " + contents;
                
                // Append some debugging helpers
                contents += "\n\n//loader(7).checkSelectionForRelayout();"
                contents += "\n//loader(7).relayoutSelection();"
                contents += "\n//loader(7).updateSelectedBlokContainer({ flexDirection: 0, justifyContent: 0, alignItems: 0, flexWrap: 0});"
                contents += "\n//loader(7).createBlokContainerFromSelection({ flexDirection: 0, justifyContent: 0, alignItems: 0, flexWrap: 0});"
                
                file.contents = new Buffer(contents);
            }
            
            this.push(file);
            callback();
        }))
        .pipe(gulp.dest("jsx/"));
});