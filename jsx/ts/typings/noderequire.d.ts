// All we need from node is the module system. Copied from
// https://github.com/borisyankov/DefinitelyTyped/blob/master/node/node.d.ts

interface NodeRequireFunction {
    (id: string): any;
}

interface NodeRequire extends NodeRequireFunction {
    resolve(id:string): string;
    cache: any;
    extensions: any;
    main: any;
}

declare var require: NodeRequire;