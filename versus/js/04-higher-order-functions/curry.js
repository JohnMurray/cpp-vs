const concat = function(a, b){
	return a.concat(b);
};

// --- Example with vanilla Currying ---
const curry2 = function(func){
	return function(x){
		return function(y){
			return func(x, y);
		};
	};
};

const head = [0, 1, 2];
const tail = [7, 8, 9];

const concatCurried = curry2(concat);
const prepend012 = concatCurried(head);

prepend012(tail);
// returns [0, 1, 2, 7, 8, 9]

// --- Example with Auto-Currying ---
const _ = require('lodash');

const sum = function(a, b) {
	return a + b;
};
	
const biOp = function(a, b, c) {
	return a(b + c);
};

// use auto-currying for functions with fixed arity of func.length
const biOpCurried = _.curry(biOp);
const plus = biOpCurried(sum);
const addFivePFive = plus(5.5);
	
addFivePFive(4.5);
// returns 10
