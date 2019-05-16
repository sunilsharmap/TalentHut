#! /usr/bin/env python

import paramiko

host_ip   = "remote_ip_address"
user_name = "remote_username"
pass_word = "remote_password"

# Give the command you want to run on remote machine
cmd = "ifconfig"

# Create the ssh object
ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

# Connect to the remote machine
ssh.connect(hostname = host_ip, username = user_name, password = pass_word)

# Execute the command on remote machine
stdin, stdout, stderr = ssh.exec_command(cmd)

# This will print the stdout data 
print "\nSTDOUT: "
for line in stdout.readlines():
	print line.strip()

# This will print the stderr data 
print "STDERR: "
for line in stderr.readlines():
	print line.strip()

# Close the ssh session
ssh.close()
