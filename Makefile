default: clean compile generate

.PHONY: clean
clean:
	rm -rf build

.PHONY: compile
compile:
	mkdir -p build/bin/
	clang++ -o build/bin/builder gen/main.cpp -lctemplate_nothreads -std=c++17

.PHONY: generate
generate:
	@echo 'generate site'