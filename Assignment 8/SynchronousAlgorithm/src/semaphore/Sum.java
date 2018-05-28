package semaphore;

import java.util.concurrent.Semaphore;

public class Sum implements Runnable {

	static private int register = 0;
	static public Semaphore mutex = new Semaphore(1);

	private int[] A;
	private Semaphore[] mutexArray;

	Sum(int[] A, Semaphore[] mutexArray) {
		this.A = A;
		this.mutexArray = mutexArray;
	}

	@Override
	public void run() {
		try {
			mutex.acquire();
			int id = register++;
			mutex.release();
			mutexArray[id].acquire();
			if (id != 0)
				A[id] += A[id - 1];
			if (id != A.length - 1)
				mutexArray[id + 1].release();
			Thread.currentThread().interrupt();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
