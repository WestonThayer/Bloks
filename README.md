A humble fork of the [Bloks project](https://github.com/WestonThayer/Bloks) by [Weston Thayer](https://github.com/WestonThayer)

# Bloks

A UX for flexbox layout within Illustrator. [Read the blog post](http://westonthayer.com/writing/2016/07/27/layout-experiments-in-adobe-illustrator/).

![Feature img](https://raw.githubusercontent.com/WestonThayer/Bloks/master/feature.png)

## Installation

v0.2.0+ Requires **Illustrator 2022**

1. [Download latest bloks.zip](https://github.com/wcork/Bloks/releases/download/v0.2.0/bloks-v0.2.0.zip)
2. Unzip
3. Copy the `com.westonthayer.bloks` folder to
    1. Windows: `C:\Program Files (x86)\Common Files\Adobe\CEP\extensions\`
    2. Mac(**NOT YET SUPPORTED**): `/Library/Application Support/Adobe/CEP/extensions/`
4. Copy the native plugin to
    1. Windows (x86): copy `WIN_32\BloksAIPlugin.aip` to `C:\Program Files\Adobe\Adobe Illustrator 2022\Plug-ins\`
    2. Windows (x64): copy `WIN_64\BloksAIPlugin.aip` to `C:\Program Files\Adobe\Adobe Illustrator 2022\Plug-ins\`
    3. Mac(**NOT YET SUPPORTED**): copy `MAC/BloksAIPlugin.aip` to `/Applications/Adobe Illustrator 2022/Plug-ins/`

Finder/File Explorer may ask you for adminsitrator permission to copy to those folders. To uninstall, simply delete the files you copied.

Get started by opening a document in Illustrator and going to *Window > Extensions > Bloks*. Select two or more objects to create a BlokGroup.

## Tutorial

For a quick introduction to how Bloks works, open `samples/BloksTutorial.ai`.
