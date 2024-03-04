import java.util.*;

public class Main {
	
	private class Rule {
		public int target; // N - Target
		public int maxSpeed; // X - Coding speed
		public int reduceAfterDev; // F - Reduce speed by F after writing code
		public int gainAfterSleep; // S - Gain speed by S after sleep for 3 hours
	
		public Rule(int target, int maxSpeed,int reduceAfterDev, int gainAfterSleep) {
			this.target = target;
			this.maxSpeed = maxSpeed;
			this.reduceAfterDev = reduceAfterDev;
			this.gainAfterSleep = gainAfterSleep;
		}
	}

	private enum State {
		ROOT,
		SLEEP,
		DEVELOP
	}

	private Rule getInput() {
		Scanner scanner = new Scanner(System.in);
		String line = scanner.nextLine();
		scanner.close();

		String parts[] = line.split(" ");
		return new Rule(
			Integer.parseInt(parts[0]),
			Integer.parseInt(parts[1]),
			Integer.parseInt(parts[2]),
			Integer.parseInt(parts[3])
		);
	}

	private int getHours(Rule rule, int hoursSpent, int currentSpeed, int linesLeftToWrite, State state) {
		if (currentSpeed <= 0) { // Force sleep
			hoursSpent += 3;
			currentSpeed = rule.gainAfterSleep;
		} else if (currentSpeed >= rule.maxSpeed) { // Force develop
			hoursSpent += 1;
			linesLeftToWrite -= currentSpeed;
			currentSpeed = Math.max(currentSpeed - rule.reduceAfterDev, 0);
		} else if (state == State.SLEEP) { // sleep
			hoursSpent += 3;
			currentSpeed = Math.min(currentSpeed + rule.gainAfterSleep, rule.maxSpeed);
		} else if (state == State.DEVELOP) { // develop
			hoursSpent += 1;
			linesLeftToWrite -= currentSpeed;
			currentSpeed = Math.max(currentSpeed - rule.reduceAfterDev, 0);
		}

		if (linesLeftToWrite <= 0) {
			return hoursSpent;
		}

		return Math.min(
			getHours(rule, hoursSpent, currentSpeed, linesLeftToWrite, State.SLEEP),
			getHours(rule, hoursSpent, currentSpeed, linesLeftToWrite, State.DEVELOP)
		);
	}

	public Main() {
		Rule rule = getInput();

		System.out.println(getHours(rule, 0, rule.maxSpeed, rule.target, State.ROOT));
	}

	public static void main(String[] args) {
		new Main();
	}

}
