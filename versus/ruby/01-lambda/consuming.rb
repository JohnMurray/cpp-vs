def sendEmail(to, from, subject, body, success_cb, failure_cb)
  if rand > 0.5
    success_cb.call(to)
  else
    failure_cb.call(to)
  end
end

sendEmail('you@your_domain.com', 'me@my_domain.com',
          'Very Important Email',
          'TODO: remember to write email body. :-D',
          ->(to) { puts "Succcessful email sent to #{to}" },
          ->(to) { puts "OH NO! Very important email not sent to #{to}" })
