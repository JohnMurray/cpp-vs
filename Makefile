#CXX = g++-8
CXX = clang++-6.0
CXX_LINK_FLAGS = -l ctemplate_nothreads -l boost_system -l boost_filesystem -l yaml-cpp
CXX_INCLUDE_FLAGS = -I . -I ./gen/

default: clean generate

.PHONY: clean
clean:
	rm -rf build

.PHONY: compile
compile:
	mkdir -p build/bin/
	$(CXX) -o build/bin/builder gen/main.cpp $(CXX_LINK_FLAGS) $(CXX_INCLUDE_FLAGS) -std=c++17

.PHONY: generate-setup
generate-setup:
	@mkdir -p build/site/style
	@mkdir -p build/site/assets

.PHONY: generate
generate: generate-setup compile
	@echo 'Generating Site...'
	@lessc site/less/app.less build/site/style/app.css
	@cp logo/logo.png build/site/assets/logo.png
	@build/bin/builder site

.PHONY: serve
serve: generate-setup
	@cp -R server/* build/
	@cd build && bundle exec puma -t 5:5 -p 1234
