import java.util.*;

public class Main {

	public Main() {
		Scanner scanner = new Scanner(System.in);
		int itemCount = scanner.nextInt();
		scanner.nextLine();
		int itemPrices[] = new int[itemCount];

		String parts[] = scanner.nextLine().split(" ");
		for (int i = 0; i < itemCount; ++i) {
			itemPrices[i] = Integer.parseInt(parts[i]);
		}

		parts = scanner.nextLine().split(" ");
		int balance = Integer.parseInt(parts[0]);
		int ordersCount = Integer.parseInt(parts[1]);

		for (int i = 0; i < ordersCount; ++i) {
			parts = scanner.nextLine().split(" ");
			int itemIndex = Integer.parseInt(parts[0]) - 1;
			int itemQuantity = Integer.parseInt(parts[1]);

			int requiredBalance = itemPrices[itemIndex] * itemQuantity;
			if (balance >= requiredBalance) {
				balance -= requiredBalance;
			}
		}

		scanner.close();

		System.out.println(balance);
	}

	public static void main(String[] args) {
		new Main();
	}

}
