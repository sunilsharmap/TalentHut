* Softwares Required:
	sudo apt-get install build-essential

* Naming the Package:
	<package_name>-<version>_<architecture>
	helloworld-1.0_amd64

	System takes package name as `helloworld`

* Keep the directory structure like below:

	├── helloworld-1.0_amd64
	│   ├── DEBIAN
	│   │   └── control
	│   └── usr
	│       └── bin
	│           └── Helloworld

	Here
	"DEBIAN"  - This directory is must to create the .deb package
	"control" - contains the package information
	"usr/bin" - Location where the executable(Helloworld) will be installed

* Creating package:
	`dpkg-deb --build helloworld-1.0_amd64`

	This command will generate "helloworld-1.0_amd64.deb" file.

* Source Directory:
	`helloworld_src` is the source directory to create the executable. This is nothing
	to do with .deb packaging. Only the executable is needed. Just have complete flow,
	I added this directory here.

	To build the main.c: `gcc -Wall main.c Helloworld`

* Installing .deb package:
	There are two ways to install .deb package:
	1. Double click on helloworld-1.0_amd64.deb file.
	   Ubuntu Software will open displaying this package information.
	   There will be `Install` button, clicking it will install `Helloworld` in /usr/bin

	2. Through command line also we can install. Either of one can be used
	   sudo dpkg -i ./helloworld-1.0_amd64.deb
	   OR
	   sudo apt install ./helloworld-1.0_amd64.deb

* Removing .deb package:
	There are two ways to uninstall/remove .deb package:
	1. Double clock on helloworld-1.0_amd64.deb file.
	   Ubuntu Software will open displaying this package information.
	   There will be `Remove` button if already installed, clicking it will remove `helloworld`
	   package i.e removes Helloword executable from /usr/bin

	2. Through command line also we can uninstall/remove. Either of one can be used
	   sudo dpkg -r helloworld
	   OR
	   sudo apt remove helloworld

