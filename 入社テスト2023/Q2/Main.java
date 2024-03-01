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

	private static class Pair<M, N> {
		public M first;
		public N second;

		public Pair(M first, N second) {
			this.first = first;
			this.second = second;
		}
	}

	private class Job {
		private int hoursSpent;
		private int currentSpeed;
		private int linesToWriteLeft;

		public Job (int hoursSpent, int currentSpeed, int linesToWriteLeft) {
			this.hoursSpent = hoursSpent;
			this.currentSpeed = currentSpeed;
			this.linesToWriteLeft = linesToWriteLeft;
		}

		public void develop(Rule rule) {
			linesToWriteLeft -= currentSpeed;
			currentSpeed = Math.max(0, currentSpeed - rule.reduceAfterDev);
			hoursSpent += 1;
		}

		public void sleep(Rule rule) {
			hoursSpent += 3;
			currentSpeed = Math.min(currentSpeed + rule.gainAfterSleep, rule.maxSpeed);
		}

		public static Pair<Integer, Integer> getPotentialAndHoursTaken(Rule rule, int speed) {
			int pot = 0;
			int hoursTaken = 0;

			while (speed > 0) {
				pot += speed;
				speed -= rule.reduceAfterDev;
				hoursTaken += 1;
			}

			return new Pair<>(Integer.valueOf(pot), Integer.valueOf(hoursTaken));
		}

		public int getHoursSpent() {
			return hoursSpent;
		}

		public int getCurrentSpeed() {
			return currentSpeed;
		}

		public int getLineToWriteLeft() {
			return linesToWriteLeft;
		}
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

	public Main() {
		Rule rule = getInput();

		Job job = new Job(0, rule.maxSpeed, rule.target);

		while (job.linesToWriteLeft > 0) {
			if (job.currentSpeed <= 0) {
				job.sleep(rule);;
			}

			Pair<Integer, Integer> currentPotentialHours = Job.getPotentialAndHoursTaken(rule, job.getCurrentSpeed());
			int currentPotential = currentPotentialHours.first;
			float currentEfficiency = 1.0f * currentPotential / currentPotentialHours.second;
			
			Pair<Integer, Integer> sleepPotentialHours = Job.getPotentialAndHoursTaken(rule, Math.min(job.getCurrentSpeed() + rule.gainAfterSleep, rule.maxSpeed));
			int potentialAfterSleep = sleepPotentialHours.first;
			float sleepEfficiency = 1.0f * potentialAfterSleep / (sleepPotentialHours.second + 3);

			if (currentPotential < job.getLineToWriteLeft() && sleepEfficiency >= currentEfficiency) {
				job.sleep(rule);
			} else {
				job.develop(rule);
			}
		}

		System.out.println(job.getHoursSpent());
	}

	public static void main(String[] args) {
		new Main();
	}

}
