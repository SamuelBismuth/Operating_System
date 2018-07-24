package synchronous;

import java.util.concurrent.LinkedBlockingQueue;

public class ThreadPool {
	
	private final int num_of_threads;
	private final Task[] threads;
	private final LinkedBlockingQueue thread_queue;
	
	
	private class Task extends Thread {
		
		public void run() {
			Runnable task;
			while(true) {
				synchronized(thread_queue) {
					while (thread_queue.isEmpty()) {
						try {
							thread_queue.wait();
						} catch(InterruptedException e) {
							System.out.println("Interrupted Exception: " + e.getMessage());
						}
					}
					task = (Runnable) thread_queue.poll();
				}
				try {
					task.run();
				} catch(RuntimeException e) {
					System.out.println("RuntimeException: " + e.getMessage());
				}
			}
		}
		
	}
	
	ThreadPool(int num) {
		num_of_threads = num;
		threads = new Task[num];
		thread_queue = new LinkedBlockingQueue();
		for (int i = 0; i < num_of_threads; i++) {
			threads[i] = new Task();
			threads[i].start();
		}
	}
	
	public void execute(Runnable task) {
		synchronized(thread_queue) {
			thread_queue.add(task);
			thread_queue.notify();
		}
	}
	
}
