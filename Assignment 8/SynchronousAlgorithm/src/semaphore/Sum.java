package semaphore;

import java.util.Arrays;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Sum implements Runnable {

	static public CyclicBarrier barrier = new CyclicBarrier(6); //dynamically
	static public Semaphore mutex = new Semaphore(1);
	static public int[] A = {2, 2, 5, 1, 7, 8};
	static public int step = 1;

	@Override
	public void run() {
		try 
		{
			int[] temp = new int[A.length];
			for (int i = 0; i < A.length; i++) {
				temp[i] = A[i];
			}
			while (step <= A.length)
			{
				barrier.await();
				mutex.acquire();
				int id = Integer.parseInt(Thread.currentThread().getName());
				if (id >= step)
					A[id] = temp[id] + temp[id - step];
				mutex.release();
				barrier.await();
				System.out.println("A: "+Arrays.toString(A)) ;
				if (id == 5)
					step *= 2;
				for (int i = 0; i < A.length; i++) {
					temp[i] = A[i];
				}			
				barrier.await();
			}
		}
		catch (InterruptedException | BrokenBarrierException e) {
			e.printStackTrace();
		}

	}

}
