import random

ran_num = 0
user_num = 0
count = 0

def init_random():
	global ran_num
	ran_num = random.randrange(25)

def init_game():
	print "It is an integer number less than 25."

def user_input():
	global ran_num, user_num, count
	while(True):
		user_num = int(raw_input("\nEnter your number:"))
		count = count + 1
		if (ran_num == user_num):
			print "Correct..!! The number is %d" % user_num
			print "You took %d steps to reach %d" % (count, user_num)
			print "Congratulations...!!"

			return 0

		elif (ran_num > user_num):
			print "The number is greater than the number you entered ",

		elif (ran_num < user_num):
			print "The number is lesser than the number you entered ",

		print "%d step" % count


init_game()
init_random()
user_input()
