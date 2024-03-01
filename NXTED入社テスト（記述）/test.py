import sys

def main(str):
	d = {}
	for c in str:
		if ord(c) < 32 or ord(c) >= 127: # char -> int
			continue

		if (c in d): # 辞書にすでにあると重複があるのがわかる
			print('重複がある')
			return
		else: # 辞書にないと辞書に追加する
			d[c] = 1
	print('重複がない')

if __name__ == '__main__':
	main(sys.argv[1])