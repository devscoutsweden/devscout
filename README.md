# The /dev/scout kernel module

This is probably not interesting unless you already know what 
[/dev/scout](http://devscout.se) is.

# Usage

- You'll need generic build essentials for Linux (and ofc, you need to run 
Linux). You can install build essentials on Ubuntu using 
`# apt-get install build-essentials` or on Fedora using
`# yum install make automake gcc gcc-c++ kernel-devel`

You _should_ be able to compile the kernel module by simply run `make`, if not,
please troubleshoot or file an issue on GitHub.

Insert the module into the kernel using `# insmod scout.ko` in the directory
where you compiled the module (remove it using `# rmmod scout` from anywhere).

The device can be read using for example `cat /dev/scout` which will output
an ASCII 4 and a new line. That's about it.

