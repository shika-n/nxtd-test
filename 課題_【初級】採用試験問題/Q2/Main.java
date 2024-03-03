import java.util.*;

public class Main {

	public Main() {
		Scanner scanner = new Scanner(System.in);
		String[] size = scanner.nextLine().split(" ");
		int height = Integer.parseInt(size[0]);
		int width = Integer.parseInt(size[1]);

		char strikes[] = new char[width * height];

		for (int y = 0; y < height; ++y) {
			char[] lineStrikes = scanner.nextLine().toCharArray();
			for (int x = 0; x < width; ++x) {
				strikes[x + y * width] = lineStrikes[x];
			}
		}

		int ans = 0;
		for (int y = 0; y < height; ++y) {
			String[] lineValues = scanner.nextLine().split(" ");
			for (int x = 0; x < width; ++x) {
				if (strikes[x + y * width] == 'o') {
					ans += Integer.parseInt(lineValues[x]);
				}
			}
		}

		scanner.close();
		
		System.out.println(ans);
	}
	
	public static void main(String[] args) {
		new Main();
	}

}
