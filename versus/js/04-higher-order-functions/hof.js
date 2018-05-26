function sum(a, b) {
    return a + b;
}

function collect(fn, init) {
    return function(list) {
        let out = init;
        for (var i = 0; i < list.length; i++) {
            out = fn(list[i], out);
        }
        return out;
    }
}

// compose 2 functions to create a new function
const sumList = collect(sum, 0);

// compose with a lambda to create a new function
const multList = collect((a, b) => a * b, 1);

sumList([1, 2, 3, 4])
// returns 10

multList([1, 2, 3, 4])
// returns 24