# CPP-VS

Comparing Cpp to other languages to showcase modern C++ and make 
it less scary.

# Not Yet Launched

__This site is not yet live, you can keep reading but it's more of a glimpse into
the future more than anything.__

----

This project generates the site/code for [cpp-vs](cpp-vs.com).All code samples is
licensed under the Apache V2 license, as is this site. If you whish to contribute
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
  + Scare people away from the language


## Contributing

Please read the __Goals__ section of this page before continuing on.

If you would like to contribute or have an idea you would like to see, please open an
issue so we can discuss. Please use the following template for your issues
```
TITLE: C++ VS LANGUAGE - PROBLEM or CODE-EXAMPLE

Please write a few sentances describing what you'd like added.

Why is this a good problem/example for the site? How does it meet the goals?

Are you willing to provide code, or is this a request?
```

If you see an issue you'd like implemented, please using the voting features 
(thumbs up/down emojis) on the issues and avoid the `+1` comments please.

## Building the Site

In order to build the site, you will need to have the following dependencies installed

+ [Less Compiler](http://lesscss.org/)
+ [CTemplate](https://github.com/rockdreamer/ctemplate)
+ [Boost Filesystem][b_fs] support (and thus [Boost System][b_sy] as a transitive dep)
+ Compiler with C++ 17 support

You can generate the site by running `make`.



  [b_fs]: https://www.boost.org/doc/libs/1_67_0/libs/filesystem/doc/index.htm
  [b_sy]: https://www.boost.org/doc/libs/1_67_0/libs/system/doc/index.html