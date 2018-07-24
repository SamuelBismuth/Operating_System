package semaphore;

public class SumProblem {

	public static void main(String[] args) {
		Thread[] th = {  // create an array of thread. (dynamically)
				new Thread(new Sum(), "0"),
				new Thread(new Sum(), "1"),
				new Thread(new Sum(), "2"),
				new Thread(new Sum(), "3"),
				new Thread(new Sum(), "4"),
				new Thread(new Sum(), "5"),
		};
		for (int j = 0; j < th.length; j++) {
			th[j].start();
		}
	}
}
