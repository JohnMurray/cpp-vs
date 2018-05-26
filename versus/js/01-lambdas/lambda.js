const addOne = (x) => {
    return x + 1;
}

addOne(5);
// returns 6

// use lambda as a value
[1, 2, 3, 4, 5].map(addOne)
// returns [2, 3, 4, 5, 6]