import java.util.*;

public class Main {

	private class Input {
		private int balance;
		private int N;
		private ArrayList<Integer> usages = new ArrayList<>();

		public int getBalance() {
			return balance;
		}

		public int getN() {
			return N;
		}

		public ArrayList<Integer> getUsagas() {
			return usages;
		}

	}


	private Input getInput() {
		Scanner scanner = new Scanner(System.in);
		String parts[] = scanner.nextLine().split(" ");

		Input input = new Input();

		input.balance = Integer.parseInt(parts[0]);
		input.N = Integer.parseInt(parts[1]);

		for (int i = 0; i < input.getN(); ++i) {
			input.usages.add(scanner.nextInt());
		}

		scanner.close();

		return input;
	}

	public Main() {
		Input input = getInput();
		int balance = input.getBalance();
		int points = 0;

		for (int usage : input.getUsagas()) {
			if (points >= usage) {
				points -= usage;
			} else {
				balance -= usage;
				points += usage * 0.1;
			}
			System.out.printf("%d %d\n", balance, points);
		}
	}

	public static void main(String[] args) {
		new Main();
	}

}
