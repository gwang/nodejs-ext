//Now we can test our addon. Create a test.js file in your addon's folder and require the 
//compiled library (you can omit the .node extension):
var addon = require('./build/Release/stdstring');

//Next, create a new instance of our object:
var test = new addon.STDString('test');

//And do something with it, like adding or converting it to a string:
test.add('!');
console.log('test\'s contents: %s', test);