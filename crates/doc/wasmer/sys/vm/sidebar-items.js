window.SIDEBAR_ITEMS = {"enum":[["VMExtern","The value of an export passed from one instance to another."]],"struct":[["VMExternRef","Represents an opaque reference to any data within WebAssembly."],["VMFuncRef","A function reference. A single word that points to metadata about a function."],["VMFunction","A function export value."],["VMFunctionBody","A placeholder byte-sized type which is just used to provide some amount of type safety when dealing with pointers to JIT-compiled function bodies. Note that it’s deliberately not Copy, as we shouldn’t be carelessly copying function body bytes around."],["VMFunctionEnvironment","Underlying FunctionEnvironment used by a `VMFunction`."],["VMGlobal","A Global instance"],["VMInstance","A handle holding an `Instance` of a WebAssembly module."],["VMMemory","Represents linear memory that can be either owned or shared"],["VMTable","A table instance."]],"type":[["VMExternFunction",""],["VMExternGlobal",""],["VMExternMemory",""],["VMExternTable",""],["VMTrampoline",""]]};