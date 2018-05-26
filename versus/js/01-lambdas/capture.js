function addX(x) {
    return (n) => {
        return n + x;
    }
}

const addFive = addX(5);

addFive(10);
// returns 15