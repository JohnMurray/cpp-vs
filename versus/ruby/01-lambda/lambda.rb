addOne = -> (x) { x + 1 }

addOne.call(5)
# returns 6

# do in-place modification
v = [1, 2, 3, 4, 5]
v.map! &addOne
# new value of 'v' is [2, 3, 4, 5, 6]
