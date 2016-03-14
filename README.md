A UX for flexbox layout within Illustrator. Work in progress.

# Development

Instructions are Windows-only for now.

1. Clone the repo to `%appdata%\Adobe\CEP\extensions\`
2. Rename the folder from `Bloks` to `com.westonthayer.bloks`
3. Open the registry editor (`<WINKEY + R>` then `regedit`) and add a value at `HKEY_CURRENT_USER\SOFTWARE\Adobe\CSXS.6` of type `REG_SZ` and value `PlayerDebugMode`. Set the data to `1`
4. Open `BloksAIPlugin.sln` in Visual Studio and build debug. Be sure to choose a build flavor that matches your Illustrator flavor (e.g. if Illustrator is installed as 64-bit, choose x64)
5. Open Illustrator, go to Preferences > Plugins & Scratch Disks. Set an additional plugin folder that points to the `BloksAIPlugin.aip` you built in step 4. Example path: `...\com.westonthayer.bloks\BloksAIPlugin\x64\Debug`
6. Close Illustrator
7. Install node.js if you haven't already
8. From the project directory, run `npm run build-jsx`. This builds `jsx\hostscript.jsx`
9. Boot Illustrator and open a new document. Go to Window > Extensions > Bloks and the extension should launch

The bulk of the plugin is written in TypeScript. I recommend using Visual Studio or Visual Studio code to edit. Whenever you change a file under `jsx\ts`, run `npm run build-jsx`, then restart Illustrator to see your changes. To debug the ExtendScript, make sure ExtendScript Toolkit is installed and open hostscript.jsx in it. Connect to Illustrator. Uncomment the helpers at the bottom to execute basic API functionality. Unfortunately it's not possible to set a breakpoint in the CEP UI and step into JSX. You have to figure out what JSX API the UI is calling and manually call it from ExtendScript Toolkit.

If you're making changes at the CEP level (`index.html`, `js\main.js`), you can use the Reload button in the UI to referesh the plugin without restarting Illustrator. To debug at the CEP level, point Chrome to `localhost:8089` and use the standard Chrome debugging tools.

To debug the BloksAIPlugin in Visual Studio, go to project > Properties > Configuration Properties > Debugging > Command. Set that to the path to Illustrator.exe on your computer.

For more tips on CEP plugin development, see [Davide Barranca's blog](http://www.davidebarranca.com/).
