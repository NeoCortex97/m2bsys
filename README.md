# m2bsys

This project aims to be a toolset for quality of life as a programmer.
The long term goal is to enable automation of tedious, or repetitive tasks and things you always do.
I know that the Goal of this project are really ambitious and some features are really complex! But it is a side 
project that does not have a deadline and that does not need to be production ready at all. 
In the long run, I just want to provide language and platform independent convenience features that I would use for myself.

## Name

The name of this project is an acronym for Meta Meta Build SYStem. It stemmed from the Idea to abstract the complex and 
bad parts of CMake, which is a meta build-system. So a system that configures a meta build-system should be called meta 
meta build-system. Later the idea expanded into replacing all my other scripts as well as my cmake code generators.

## Rationale

I accumulated a bunch of scripts, tools, helpers and templates that I use in many projects.
I have written some scripts to do the same task for different languages, 
but the downside to my collection is that these usually only work for me and my personal system setup.
Most of my scripts are written in BASH, Python or even Java.
I'm also very tired of maintaining the Java tools and bash scripts every time I change something about my environment.  
So I decided to harmonize my collection of things into a set of tools that can work on all major platforms.

## Goals

I want a set of tools that remove all tedious and annoying tasks into an opinionated set of tools that remains 
configurable for different preferences. You could say that I want tools that do everything like you would do manually, 
so you don't have to do them manually. And I partially want to automate some refactorings, or restructurings so existing 
projects can be managed by this toolset as well as new ones. So mostly a set of tools that I wanted, when I first started 
developing in a larger team.

I am sorry, that I cannot explain everything in detail here, without having explained the tools that I have planned. 
I will detail these later.

As a side-goal with low priority I would like to enable organisations with high contributor throughput and inexperienced 
programmers to ensure a unified environment for everyone, or at least provide sensible defaults and allow more 
experienced programmers to customize their setup and have the differences handled by the tooling.  

## My setup

This is not about hardware, but about the structure that I use to structure projects. My examples are mainly taken from C++, 
but I use them for every other language, if sensible.

### Workspace

A workspace is a base directory for a group of projects. It contains everything that this group of projects needs to be built.
I usually call them with a clear naming scheme that has the organisation, or group name with a `WS` postfix. 
Some Examples would be `toolsWS`, `robotWS`, `gameWS`. Typically, I place them either in my documents directory, 
or my home directory.  
A workspace has it's own package manager cache and directory for libraries that are normally installed into the system.
I do this, so I am not bound to specific versions of libraries within different workspaces.  
The workspace usually is a cmake super build project too. 
The way I use workspaces implies that they are typically built together and maybe even depend on each other.

### Project

A project is always a single application that can run on its own, or a library that is maintained by me, or my group.
In my first larger group the projects were not setup so they could be cloned and built independently, but if I have a 
say int that I usually use cmakes `fetch_content`, `ExternalProject_Add`, or git submodules and test if I have to use 
my sources, or if the dependencies can be found in the workspace.

### Library

I usually configure self written libraries with the following folder structure:
```
include
  CMakeLists.txt
  library
    library.hpp
    library.cpp
    CMakeLists.txt
```
That way I can encapsulate special configuration for single libraries in its own CMakeLists.txt file.

## Tools

### Structure

The structure component will be used to ensure that the directory structure and config files for tools are in the right place. 
It will also generate new structures.  
I would suggest making the exact structure configurable and maybe even include the option of a scripting language to 
allow generation of file contents, or accessing the configuration for customisation.

To explain what it does more easily, I should place some usage examples here.  
 - `$ m2b structure create workspace robot` - creates the folowind directory structure:
    ```
    robotWS
     .build
     .lib
     .m2b
     CMakeLsits.txt
    ```

 - `$ m2b structure create project motion` - when executed inside a workspace, it will create the following directory structure.
For this example I will assume that it is executed inside the robotWS.
    ```
    motion
      CMakeLists.txt
      external
        CMakeLists.txt
      include
        CMakeLists.txt
      src
        CMakeLists.txt
        main.cmake
        main.cpp
      tests
        CMakeLists.txt
    ```

 - `$ m2b structure create library test` - when executed inside a project, it will create the following stucture:
    ```
   include
     CMakeLists.txt
     test
       CMakeLists.txt
       test.cpp
       test.hpp
   ```
   The `include` directory is not part of the created structure and serves only to help you locate it in the whole file tree.

 - `$ m2b structure create executable client` - when executed inside a project, it will create the following files 
    inside the `src` directory of the project.
    ```
   client.cmake
   client.cpp
   ```
 After running all these commands, the whole workspace would look like this:
```
robotWS
  .build
  .lib
  .m2b
  CMakeLsits.txt
  motion
    CMakeLists.txt
    external
      CMakeLists.txt
    include
      CMakeLists.txt
      test
        CMakeLists.txt
        test.cpp
        test.hpp
    src
      CMakeLists.txt
      main.cmake
      main.cpp
      client.cmake
      client.cpp
    tests
      CMakeLists.txt
```

### Macro

I was working with a tool like pythons [`poetry`](https://python-poetry.org/), or nodejs' [`npm`](https://www.npmjs.com/) and liked the commands. 
So I would like this toolset to be capable of executing macros for common tasks.
Preferably I would directly offer some macros that only need some config parameters if desired.
I.E. to run cmake configure, or to run cmake builds.  
The macros should be written in a language that is embedded inside the application, so it does not depend on any 
external interpreters.

I would recommend one, or more of the following languages:  
 - [Python](https://www.python.org/)
 - [Jinx](https://jamesboer.github.io/Jinx/index.htm)
 - [wren](https://wren.io/)

[Lua](https://www.lua.org/) is not on the list, because I personally don't like it. It could be included to a later point in time tho.
I was thinking about [ChaiScript](https://chaiscript.com/) as a language, but since it is not under development anymore, I would exclude it for now.
Other languages could be included later, but we only need one to start with something that works.  

### package

I used [`myrepos`](https://myrepos.branchable.com/) or mr for short, which is used to update a list of git repositories with one command.
So I would like to allow my toolset to allow updating everything in a workspace, or in all Workspaces with one command.
The update module should enable that, but I would prefer if it could also run the update/upgrade commands of the various
package managers that might be used. Even if the linux package managers like [`apt`](https://wiki.ubuntuusers.de/APT/), [`yum`](https://linuxwiki.de/yum), [`dnf`](https://docs.fedoraproject.org/en-US/quick-docs/dnf/), [`pacman`](https://wiki.archlinux.org/title/pacman), ... would 
require some more magic, like working inside a container, or something else. [`pip`](https://pypi.org/project/pip/), [`npm`](https://www.npmjs.com/), [`nix`](https://github.com/NixOS/nix) would be simpler to 
support. I would like to add support for at least one of the source package managers from the following list:
 - [conan](https://conan.io/)
 - [vcpkg](https://vcpkg.io/en/index.html)
 - [Hunter](https://hunter.readthedocs.io/en/latest/)
 - [nuget](https://www.nuget.org/)
 - [Buckaroo](https://buckaroo.pm/)
 - [Spack](https://spack.io/)
 - ...

For convenience should the package module permit searching all the configured package managers for a package and the available versions.
I would like to allow switching between different package sources and the automatic removal of unused packages.

### generator

This part of my project should be used in cooperation with the structure module. It is supposed to allow generation of 
configuration files and source code.
I would like to use existing generators, if there are any available but to use the builtin scripting language, 
or templates to generate files if no external generator exists.
My main goal to have a system for code generation that outputs code that looks as good as handwritten code and that is formatted properly.
I will build a library to generate cmake code in particular, so nobody has to fight with cmake's odd syntax anymore.
The generator should be able to pick up on changes that the user made to the generated files and should at least warn the user.
I would also like that it could offer to update the generation template if it is not too much hassle.  
Since generating a bunch of stuff might take a long time, I would prefer if this module could figure out when a file needs to be regenerated and generate only if needed.

### versioning

This module should be responsible for management of the projects versions and enforcing a certain workflow. 
Since git is the most commonly used version control system, I would concentrate on supporting git.
Nonetheless, support for other systems would be a nice to have in the future.  
There is not much more to tell you about this module, besides some convenience features that I thought of:
 - automatic branching  
   If you start working on a bugfix, feature, release, it should create the appropriate branches and automatically switch to them.
 - automatic commits  
   At different points in time you should commit your work and this module should do that automatically.
 - assisted rollback  
   When you realized that you made a mistake or went in the wrong direction, it should assist you in finding the right 
   commit to go back to and help you avoid problems with uncommitted changes, or other weird things.
 - assisted merging  
   If you are ready to submit a feature, bugfix, release, it should help you merge the branches. 
   It should automatically merge whitespace only conflicts and should run a merge tool for the others.
   If there are no conflicts, it should automate merging completely.

### launch

This module might look redundant, but at least in my head it isn't. It is supposed to allow launching a number of 
things in sequence. The idea for this module is taken from [ROS](https://www.ros.org/) and `roslaunch` in particular.
I did not like the structure of launchfiles from ROS at all, but I liked the idea.  
So I would like the launch module to allow launching directly, or to compile the launchfiles into scripts that can run independently.
I also would like to permit that single applications from the launchfile could be rebuilt and rerun without tearing 
down and relaunching the whole stack, if that is am option.
HMR support would be nice, but is most likely a goal for the far future.

### environment

This module should be a wrapper around `env`-files. Mainly it should offer commands, to add, remove or change 
environment variables and offer different environments like `dev`, `testing`, `staging`, `production`.

### storage

This module should allow for somewhat safe keeping of secrets or keys in an encrypted file. I would like to let users configure 
if they allow committing the encrypted file to version control, or if that should be prevented.  
I don't know if this would be a good thing, but I would be tempted to allow automatic obtaining of the tokens and keys.
That would avoid writing lengthy guides how to obtain every secret and token manually.

__Note:__ This module is not really supposed to keep the secrets safe from hackers, but to avoid having them around in plain text.
Maybe the file encryption gets dropped, because it offers not that many advantages while carrying some disadvantages.

Maybe this module gets merged with the environment module.

### document

This module is supposed to help with documenting changes, so changelogs and change lists for commit messages can be generated somewhat automagically.
It could also be expanded to allow for generating migration scripts if applicable.  
If you change the name of a config value, you should tell this module, that you did, and it should ask if you want to create a migration script to automatically update an old config to the new format.
Maybe it could offer a library for applications to embed the migrations feature and automatically migrate if wanted.

I did not make up my mind, how these migrations should work.
I can think of five options that would make sense for me:
 1. Generate migrations as scripts in an embeddable scripting language.  
    This option would imply, that the module could apply the migrations as well as an application could embed an 
    interpreter and apply the migrations itself.
 2. Generate migrations as scripts in a primitive dsl.
    This option would be best, if you wanted the module to apply migrations, or if this module would add a script/simple program
    into the project to apply the migrations.  
    This would mean, that applications should not try to migrate anything by itself.
 3. Generate migrations as libraries in the language of the project.
    This option seems to be a lot of work, since generators for many languages will have to be written.  
    I added this option anyway, because I think using the migrations as libraries in your application could be beneficial, 
    or it could be used to dynamically migrate on every execution.  
    I think that would be a nice feature - at least for the quicker languages.
 4. Generate migrations as markup files like json, toml or yaml that follow a specific format.
 5. Generate migrations as scripts in an external language like python.