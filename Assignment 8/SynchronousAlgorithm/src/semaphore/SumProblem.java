package semaphore;

import java.util.Arrays;
import java.util.concurrent.Semaphore;

public class SumProblem {

	public static void main(String[] args) {
		int[] A = {2, 3, 4, 2, 2};
		Semaphore[] arrayMutex = {
				new Semaphore(1),
				new Semaphore(0), 
				new Semaphore(0),
				new Semaphore(0), 
				new Semaphore(0)};
		for (int i = 0; i < A.length; i++) {
			Thread th = new Thread(new Sum(A, arrayMutex));
			th.start();
			try {
				th.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println(Arrays.toString(A));
	}
}
