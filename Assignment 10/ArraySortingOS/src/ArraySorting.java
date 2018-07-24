import java.util.Arrays;
import java.util.concurrent.BrokenBarrierException;

public class ArraySorting 
{

	public static void main(String[] args) 
	{
		int[] array = {485, 41, 340, 526, 188, 739, 489, 387, 988, 488};  // Even array.
		try 
		{
			arrayParallelSorting(array);
		} catch (InterruptedException | BrokenBarrierException e) 
		{
			e.printStackTrace();
		}
		System.out.println("Finish array: " + Arrays.toString(array));
		
		int[] array2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};  // Even array.
		try 
		{
			arrayParallelSorting(array2);
		} catch (InterruptedException | BrokenBarrierException e) 
		{
			e.printStackTrace();
		}
		System.out.println("Finish array2: " + Arrays.toString(array2));
	}

	private static void arrayParallelSorting(int[] array) throws InterruptedException, BrokenBarrierException 
	{
		boolean evenPhase = true;  // Should we begin with an even or an odd phase ?
		for (int j = 0; j < array.length; j++)
		{
			if (evenPhase)
			{
				System.out.println("begining of the even phase");
				for (int i = 0; i < array.length / 2; i++)
				{
					Thread th = new Thread(new Run((i * 2), array));
					th.start();
					th.join();
				}
				evenPhase = false;
				System.out.println("end of the even phase");
			}
			else  // Odd phase.
			{
				System.out.println("begining of the odd phase");
				for (int i = 0; i < array.length / 2 - 1; i++)
				{
					Thread th = new Thread(new Run((i * 2 + 1), array));
					th.start();
					th.join();
				}
				evenPhase = true;
				System.out.println("end of the odd phase");
			}
		}
	}

}
