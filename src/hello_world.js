console.log("Hello World from embedded JS!")

var nodeEngine = process.binding('NodeEngine')
// -> this will call onRegisterModule and return its exports argument
