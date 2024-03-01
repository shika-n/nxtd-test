balance, N = [int(x) for x in input().split(" ")]

usages = []
for i in range(N):
	usages.append(int(input()))

points = 0
for usage in usages:
	if points >= usage:
		points -= usage
	else:
		balance -= usage
		points += usage * 0.1
	print(balance, points)