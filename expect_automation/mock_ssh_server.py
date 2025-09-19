#!/usr/bin/env python3
import time
import stdiomask # pip install stdiomask

print("\n**** SSH SEVER *****")
print("The authenticity of host 'mockserver' can't be established.")
print("RSA key fingerprint is SHA256:abcdefghijklmnopqrstuvwxyz123456.")
answer = input("Are you sure you want to continue connecting (yes/no)? :")
if answer.lower() != "yes":
    exit(1)

print("Warning: Permanently added 'mockserver' (RSA) to the list of known hosts.")
password = stdiomask.getpass(prompt="password: ", mask="*")
if password == "mockpassword":
    print("Last login: Wed Nov 1 12:00:00 2023 from 192.168.1.100\n")
    print("***** Welcome to Mock SSH Server *****\n")
    print("Help:")
    print("    close - close the connection")
    print("    anything else will be echoed\n")

    print("mockuser@mockserver:~$ ", end="")
    while True:
        cmd = input()
        if cmd == "close":
            replay = input("Do you want to close the session (yes/no)?: ")
            if replay == "yes":
                exit(0)
        else:
            print(f"Executing \"{cmd}\" . . .")
            time.sleep(1)
        print("\nmockuser@mockserver:~$ ", end="")
    # while loop end
else:
    print("Permission denied, please try again.")
    exit(-1)
