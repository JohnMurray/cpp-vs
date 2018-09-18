/****** Browser ******/

// Nothing to do here: The process runs as long as the
// browser tab is not closed.

setTimeout(function(){
    console.log("Hello Browser-World!");
}, 0);

/******Node.js *******/

// run for 11 days
const runTimer = setTimeout(function keepAlive(){}, 1.0e+9);

function shutdown() {
	console.log("exiting...");
	clearTimeout(runTimer);
}

process.on('SIGINT', shutdown);
process.on('SIGTERM', shutdown);

process.nextTick(function(){
    console.log("Hello Node.js-World!");
});

console.log("setup done.");
