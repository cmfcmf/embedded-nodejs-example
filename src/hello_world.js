console.log("Hello World from embedded JS!")

var cppDemoModule = process.binding('CppDemoModule')
cppDemoModule.demoExport()
// -> this will call onRegisterModule and return its exports argument
