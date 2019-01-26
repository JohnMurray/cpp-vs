def addX(x)
  -> (n) { x + n }
end

addFive = addX(5)

addFive.call(10) # returns 15
