require 'rack'
require 'rack/contrib/try_static'

env = ENV['RACK_ENV'] || 'development'
dir = if env == 'development' then 'build/site' else '__released_site' end

# enable compression
use Rack::Deflater

# static configuration (file path matches reuest path)
use Rack::TryStatic,
      :root => dir,  # static files root dir
      :urls => %w[/],    # match all requests
      :try => ['.html', 'index.html', '/index.html'], # try these postfixes sequentially
      :gzip => true,     # enable compressed files
      :header_rules => [
        [:all, {'Cache-Control' => 'public, max-age=86400'}],
        [['css', 'js'], {'Cache-Control' => 'public, max-age=604800'}]
      ]

# otherwise 404 NotFound
notFoundPage = File.open("#{dir}/index.html").read
run lambda { |_| [200, {'Content-Type' => 'text/html'}, [notFoundPage]]}
