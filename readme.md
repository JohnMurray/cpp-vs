<p align="center">
    <img 
      src="https://raw.githubusercontent.com/JohnMurray/cpp-vs/master/logo/logo.png" 
      width="300px"
      alt="cpp-vs">
</p>

This is an experiment/idea I had to see if people would find it useful, in their
endeavour to learn C++, to compare similar examples to a language they may already
know. This does mean that this site is targeted toward those that are _not_ learning
C++ as their first language.

This project generates the site/code for [cpp-vs](http://www.cpp-vs.com).All code samples are
licensed under the Apache V2 license, as is this site (see __Copyright & Licensing__ section
below for full/exact details). If you whish to contribute
additional examples, fixes, etc. then please read the __Goals__ section below to
make sure we're all on the same page, then continue reading the __Contributing__
section for the juicy details.

## Goals

This project has specific goals which should be kept in mind while adding/editing
code examples. These goals are achieved by comparing C++ to other, popular,
programming languages and are simply:

  + Showcase the comparative ease in which tasks can be accomplished when compared
    with language X.
  + Introduce non-C++ programmers to modern C++ code/techniques, comparing a language
    they may know.
  + Introduce novice programmers to C++ by comparing it to more popular (better known)
    languages.

The theme/spirit of these goals is to both introduce more people to C++ while also
showcasing the good/better parts of the language/ecosystem.

What this project goes __not__ aim to do:

  + Show the _superiority_ of C++
  + Bash other languages
  + Be a showcase for clever hacks or terse solutions
  + Scare people away from the language with hard to read/understand code examples


## Contributing

Please read the __Goals__ section of this page before continuing on.

If you would like to contribute or have an idea you would like to see, please open an
issue so we can discuss. Please use the following template for your issues
```
TITLE: C++ VS LANGUAGE - PROBLEM or CODE-EXAMPLE

Please write a few sentences describing what you'd like added.

Why is this a good problem/example for the site? How does it meet the goals?

Are you willing to provide code, or is this a request?
```

If you see an issue you'd like implemented, please using the voting features 
(thumbs up/down emojis) on the issues and avoid the `+1` comments please.

## Building the Site

You can build changes and view them via a docker-based build. This does mean
that you need docker installed. I've only tested this with the latest version
of docker (version `18.0.6-ce` at time of writing), but I'm not doing much fancy,
so older versions will likely work as well. To build and run locally, run:

```bash
make docker-serve

# or just simply

make
```

If you make changes and would like to see them reflected, simply re-run this command.
After running, you should be able to navigate to `http://localhost:1234/` to see the
site.

To stop all running instances, you can run:

```bash
make docker-stop
```


## Building Without Docker

In order to build the site without Docker, you will need to have the following
dependencies installed and likely be running on a Linux environment (at least that
is the only environment I've tested with).

+ [Less Compiler](http://lesscss.org/)
+ [CTemplate](https://github.com/rockdreamer/ctemplate)
+ [Boost Filesystem][b_fs] support (and thus [Boost System][b_sy] as a transitive dep)
+ [yaml-cpp](https://github.com/jbeder/yaml-cpp) (tested with v0.5)
+ Compiler with C++ 17 support (mostly cause I haven't tested with anything else)

You can generate the site by running `make compile && make generate`.


## Copyright & Licensing

All rights are reserved for the image/logo assets associated with cpp-vs, including all files
located within the `logos` and `__released_site/assets` folders (relative to project root).

All other files in this repository are licensed under the Apache V2 license. Full license
details located within the __LICENSE__ file.


  [b_fs]: https://www.boost.org/doc/libs/1_67_0/libs/filesystem/doc/index.htm
  [b_sy]: https://www.boost.org/doc/libs/1_67_0/libs/system/doc/index.html
