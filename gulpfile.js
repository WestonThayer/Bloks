var gulp = require("gulp");
var gulpUtil = require("gulp-util");
var through = require("through2");
var source = require('vinyl-source-stream');
var buffer = require("vinyl-buffer");
var browserify = require("browserify");
var tsify = require("tsify");
var shell = require("gulp-shell");
var del = require("del");

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
                contents += "\n//loader(7).updateSelectedBlokContainer({ flexDirection: 0, justifyContent: 0, alignItems: 0, flexWrap: 0 });"
                contents += "\n//loader(7).createBlokContainerFromSelection({ flexDirection: 0, justifyContent: 0, alignItems: 0, flexWrap: 0 });"
                contents += "\n//loader(7).updateSelectedBlok({ flex: undefined, alignSelf: 0 });"
                
                file.contents = new Buffer(contents);
            }
            
            this.push(file);
            callback();
        }))
        .pipe(gulp.dest("jsx/"));
});

// ZXP building

var pwd = undefined;

try {
    var creds = require("./zxp-tools/certificate-creds.json");
    pwd = creds.password;
}
catch (e) {
    /*if (e.code === "MODULE_NOT_FOUND") {
        throw new Error("./zxp-tools/certificate-creds.json doesn't exist! Please create it. Ex: { password: 'pwd' }");
    }
    else {
        throw e;
    }*/
}

gulp.task("zxp-html-extension-copy-css", function() {
   return gulp.src(["css/**/*.css"])
       .pipe(gulp.dest("release/com.westonthayer.bloks/css/"));
});

gulp.task("zxp-html-extension-copy-manifest", function() {
   return gulp.src(["CSXS/manifest.xml"])
       .pipe(gulp.dest("release/com.westonthayer.bloks/CSXS/"));
});

gulp.task("zxp-html-extension-copy-icons", function() {
   return gulp.src(["icons/*.png"])
       .pipe(gulp.dest("release/com.westonthayer.bloks/icons/"));
});

gulp.task("zxp-html-extension-copy-js", function() {
   return gulp.src(["js/**/*.js"])
       .pipe(gulp.dest("release/com.westonthayer.bloks/js/"));
});

gulp.task("zxp-html-extension-copy-jsx", function() {
   return gulp.src(["jsx/hostscript.jsx"])
       .pipe(gulp.dest("release/com.westonthayer.bloks/jsx/"));
});

gulp.task("zxp-html-extension-copy-html", function() {
   return gulp.src(["index.html"])
       .pipe(gulp.dest("release/com.westonthayer.bloks/"));
});

gulp.task("zxp-html-extension-sign", [
    "zxp-html-extension-copy-css",
    "zxp-html-extension-copy-manifest",
    "zxp-html-extension-copy-icons",
    "zxp-html-extension-copy-js",
    "zxp-html-extension-copy-jsx",
    "zxp-html-extension-copy-html"
    ],
    shell.task("zxp-tools\\ZXPSignCmd.exe -sign release\\com.westonthayer.bloks release\\com.westonthayer.bloks.zxp zxp-tools\\selfWT.p12 " + pwd + " -tsa https://timestamp.geotrust.com/tsa")
);

gulp.task("zxp-html-extension", ["zxp-html-extension-sign"], function() {
    return del(["release/com.westonthayer.bloks"]);
});

gulp.task("zxp-plugin-mac", function() {
    return gulp.src(["BloksAIPlugin/Mac/release/**/*"])
        .pipe(gulp.dest("release/MAC/"));
});

gulp.task("zxp-plugin-win-64", function() {
    return gulp.src(["BloksAIPlugin/x64/Release/BloksAIPlugin.aip"])
        .pipe(gulp.dest("release/WIN_64/"));
});

gulp.task("zxp-plugin-win-32", function() {
    return gulp.src(["BloksAIPlugin/Release/BloksAIPlugin.aip"])
        .pipe(gulp.dest("release/WIN_32/"));
});

gulp.task("zxp-samples", function() {
    return gulp.src("sample-files/*.ai")
        .pipe(gulp.dest("release/samples/"));
});

gulp.task("zxp",
    [
        "zxp-html-extension",
        "zxp-plugin-mac",
        "zxp-plugin-win-64",
        "zxp-plugin-win-32",
        "zxp-samples"
    ]
);