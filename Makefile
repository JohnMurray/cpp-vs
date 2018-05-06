# Compiler / Linker Flags
LD_FLAGS = LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"
CXX_FLAGS = CPPFLAGS="-I/usr/local/opt/llvm/include"
CLANG = /usr/local/opt/llvm/bin/clang++

default: clean compile generate

.PHONY: clean
clean:
	rm -rf build

.PHONY: compile
compile:
	mkdir -p build/bin/
	$(LD_FLAGS) $(CXX_FLAGS) $(CLANG) -o build/bin/builder gen/main.cpp -lctemplate_nothreads -std=c++17

.PHONY: generate
generate:
	@echo 'Generating Site...'
	@mkdir -p build/site/assets
	@cp site/index.html build/site/index.html
	@lessc site/less/app.less build/site/style/app.css
	@cp logo/logo.png build/site/assets/logo.png