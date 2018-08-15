default: docker-serve

# Dev / Docker Comamnds
#
# If you are developing/hacking on this project, then this is likely the set of
# commands that you are interested in. These commands will launch a docker container
# with your changes compiled and running. Any time you want ot launch a server, just
# run:
#
#   make docker-serve
#
# If you make changes and want to see those reflected, just re-run the same command.
# If you are done working, you can run:
#
#   make docker-stop

.PHONY: docker-dev-build
docker-dev-build:
	docker build --label cpp-vs-dev --tag cpp-vs:latest --file Dockerfile.dev .

.PHONY: docker-serve
docker-serve: docker-stop docker-dev-build
	docker run -d=true -p 1234:1234 cpp-vs:latest
	@echo "cpp-vs.com running at http://localhost:1234/"

.PHONY: docker-stop
docker-stop:
	./scripts/stop-docker-dev.sh


# Release Docker Commands
#
# Unless you are trusted and/or have access to publish the site, these commands
# really not for you. Look away. :-)

current_dir := $(shell pwd)

.PHONY: docker-release
docker-release: docker-dev-build
	@bash -c "git diff-index --quiet HEAD --"
	@rm -rf __released_site && git rm -rf __released_site && mkdir __released_site
	docker build --label cpp-vs-release --tag cpp-vs-release:latest --file Dockerfile.release .
	docker run -v "$(current_dir)/__released_site:/released_site:rw" cpp-vs-release:latest
	@git add __released_site
	@date=`date` git commit -m "Site release: $(shell date)"
	@echo "Latest site added to source control"



# Compile & Build/Generate Commands
#
# These commands are what take care of compiling the C++ code that does the site
# templating as well as the code to generate the site. For these commands to work,
# you'll need to setup an environment with all of the correct dependencies. If
# you're just looking to do basic development or test some changes, take a look at
# the docker commands above.

CXX = clang++-6.0
CXX_LINK_FLAGS = -l ctemplate_nothreads -l boost_system -l boost_filesystem -l yaml-cpp
CXX_INCLUDE_FLAGS = -I . -I ./gen/

export BUILD_ENV := development

.PHONY: clean
clean:
	rm -rf build/site

.PHONY: compile
compile:
	mkdir -p build/bin/
	$(CXX) -o build/bin/builder gen/main.cc $(CXX_LINK_FLAGS) $(CXX_INCLUDE_FLAGS) -std=c++17

.PHONY: generate-setup
generate-setup:
	@mkdir -p build/site/style
	@mkdir -p build/site/js
	@mkdir -p build/site/assets
	@mkdir -p build/site/versus

.PHONY: generate
generate: generate-setup
	@echo 'Generating Site...'
	@lessc site/less/app.less build/site/style/app.css
	@cp site/js/prism.js      build/site/js/prism.js
	@cp logo/logo.png         build/site/assets/logo.png
	@ENV=$(BUILD_ENV) build/bin/builder site

.PHONY: serve
serve: generate-setup
	@bundle exec puma -t 5:5 -p 1234
