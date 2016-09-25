import sys


def print_parenthesis(curr_str, left, right, maxp):
	if (left == maxp and right == maxp):
		print curr_str
		return
	if left < maxp:
		print_parenthesis(curr_str + "(", left + 1, right, maxp)
	if right < left:
		print_parenthesis(curr_str + ")", left, right+1, maxp)


def main():
	print_parenthesis("",0,0, int(sys.argv[1]))


if __name__ == "__main__":
    main()
