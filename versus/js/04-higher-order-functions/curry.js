const R = require('ramda');

const
	sum = function(a, b) {
		return a + b;
	},
	
	biOp = function(a, b, c) {
		return a(b + c);
	},
	
   biOpCurried = R.curry(biOp),
	plus = biOpCurried(sum),
	addFivePFive = plus(5.5);
	
addFivePFive(4.5); // -> 10
