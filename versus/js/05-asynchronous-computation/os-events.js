/****** Browser ******/

// Nothing to do here: The process runs as long as the browser tab is not closed.

setTimeout(function(){ console.log("Hello World!"); }, 0);

/******Node.js *******/

function shutdown() {
	process.exit(1);
}

process.on('SIGINT', shutdown);
process.on('SIGTERM', shutdown);

process.nextTick(function(){ console.log("Hello World!"); });