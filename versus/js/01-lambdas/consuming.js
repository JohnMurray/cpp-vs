function sendEmail(to, from, subject, message,
        success_cb, failure_cb) {
    // pretend we tried to send an email and call the
    // success or failure callback randomly.
    if (Math.random() > 0.5) {
        success_cb(to);
    } else {
        failure_cb(to);
    }
}

sendEmail('you@your_domain.com', 'me@my_domain.com', 
    'Very Important Email',
    'TODO: remember to write email body. :-D ',
    (to) => { 
        console.log('successful email sent to: ' + to);
    },
    (to) => {
        console.log('OH NO! Very important email not sent to ' + to);
    });