// run for 11 days
const keepAliveTimer = setTimeout(function keepAlive(){}, 1.0e+9);

function quitAfterGreetingPerson(name) {
	console.log("Hello " + name + "!");
	
	clearTimeout(keepAliveTimer);
}

const greetTimer = setTimeout(quitAfterGreetingPerson, 1000, "World");