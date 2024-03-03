import java.util.*;

public class Main {


	private int getCount(int X) {
		if (X / 100 >= 1) {
			return 1;
		}

		int ans = 0;

		if (X / 10 >= 1) {
			// XX?
			if (X < 36) { // [10-35][0-9]
				ans += 10;
			} else if (X == 36) { // 36[0-4]
				ans += 5;
			} 

			// ?XX
			ans += 3; // XX, 1XX, 2XX XX->11~99
			if (X < 65) {
				ans += 1;
				if (X % 10 <= 3 && X / 10 == X % 10) { // 3XX, dupe -> X[XX] & [XX]X
					ans -= 1;
				}
			}
		} else {
			// X
			ans += 1;
			// X?
			if (X != 0) {
				ans += 10; // X[0-9]
			}

			// ?X
			if (X > 0) {
				ans += 9 - 1; // -1 -> Included in X? in case of [X]X
			} else {
				ans += 9; // 0 has no such problem
			}

			// X??
			if (X > 0 && X < 3) { // 1?? 2??
				ans += 100;
			} else if (X == 3) { // 3??
				ans += 65;
			}

			// ?X?
			for (int f = 1; f <= 3; f++) {
				if (f == X) continue; // Dupe in X??
				for (int t = 0; t < 10; t++) {
					if (f == 3 && X * 10 + t >= 65) break; // 364 max
					ans += 1;
				}
			}

			// ??X
			for (int f = 1; f <= 3; f++) {
				if (f == X) continue; // Dupe in X??
				for (int s = 0; s < 10; s++) {
					if (f == 3 && s * 10 + X >= 65) break; // 364 max
					if (s == X) continue; // Dupe in ?X?
					ans += 1;
				}
			}
		}

		return ans;
	}

	private int bruteTest(int X) {
		int ans = 0;
		for (int i = 0; i < 365; ++i) {
			if (String.valueOf(i).contains(String.valueOf(X))) {
				ans += 1;
			}
		}
		return ans;
	}

	private void testAll() {
		Boolean mistake = false;
		for (int i = 0; i < 365; ++i) {
			int countAnswer = getCount(i);
			int bruteAnswer = bruteTest(i);

			if (countAnswer != bruteAnswer) {
				System.out.println(i + " | " + countAnswer + " != " + bruteAnswer + " | Diff: " + (countAnswer - bruteAnswer));
				mistake = true;
			}
		}
		if (!mistake) {
			System.out.println("All good");
		}
	}

	public Main() {
		// testAll();

		Scanner scanner = new Scanner(System.in);
		int X = scanner.nextInt();
		scanner.close();

		System.out.println(getCount(X));
		System.out.println("Brute Result: " + bruteTest(X));
	}

	public static void main(String[] args) {
		new Main();
	}

}
