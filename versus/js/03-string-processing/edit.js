// String with mixed-character whitespace at beginning and end
const msg = "Total Price -> [1.23]";

msg.toLowerCase();
// returns "total price -> [1.23]"

msg.toUpperCase();
// returns "TOTAL PRICE -> [1.23]"

msg.replace('[', '(').replace(']', ')');
// returns "Total Price -> (1.23)"

msg.replace(/[\[\]\->]/, '');
// returns "Total Price  1.23"
