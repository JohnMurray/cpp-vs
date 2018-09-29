setTimeout(function(){
	process.stdout.write("That's one small step for a man,");
	
	setTimeout(function() {
		console.log(" one giant leap for mankind.");
	}, 1000);
	
}, 1000);