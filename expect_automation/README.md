## How to use expect scripting for automation in the interactive application
This examples will help to understand how to use the Linux __expect__ command to automate interactive command-line applications. The expect command is a powerful automation tool that allows scripts to interact with programs that require user input.

**mock_ssh_server.py:**
a python application, which is a mock ssh server simulation interactive program which needs user inputs to do a ssh login.

**expect_auto_ssh.exp:**
an ecpect script used to do automate the interactive python script ssh login. The inputs are entered based on the prompt we get.


### How to do:
**Independent python script execution:** run `mock_ssh_server.py` on the terminal like `python3 mock_ssh_server.py` to know how this requires user interation.

**Automation with expect:** Now run `expect_auto_ssh.exp` on the terminal like `expect expect_auto_ssh.exp` to know how it automates by providing the inputs to the python application.

**Note:**
This code will work on Linux, not on windows.
Install the tools:
	sudo apt-get install -y expect
	pip/pip3 install stdiomask
