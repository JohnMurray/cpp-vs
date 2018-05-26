const _ = require('lodash');

function sum(a, b) {
    return a + b;
}

const addFive = _.partial(sum, 5);

addFive(10);
// returns 15