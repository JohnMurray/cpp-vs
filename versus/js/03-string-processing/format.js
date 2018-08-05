const name = "FOOBAR";
const max_gain = 0.15;
const max_loss = 0.76;

console.log(`Weekly Changes: ${name} +${max_gain * 100}%` +
    ` -${max_loss * 100}%`);
// prints "Weekly Changes: FOOBAR +15% -76%"

// Print list as a right-aligned list of hex values
const someNumbers = [123456, 90346873, 28];
for (i in someNumbers) {
    const hex = someNumbers[i].toString(16);
    let padding = "";
    if (hex.length < 8) {
        padding = "0".repeat(8 - hex.length);
    }
    console.log(`\t0x${padding}${hex}`);
}
/* Prints:
    0x0001e240
    0x05629579
    0x0000001c
*/
