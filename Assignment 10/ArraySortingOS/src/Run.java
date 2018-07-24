import java.util.Arrays;

public class Run implements Runnable 
{
	private int x;
	private int[] array;
	
	Run(int x, int[] array)
	{
		this.x = x;
		this.array = array;
	}

	@Override
	public void run() {
		if (array[x] > array[x + 1])
		{
			int temp = array[x];
			array[x] = array[x + 1];
			array[x + 1] = temp;
		}
		System.out.println(Arrays.toString(array));
	}

}
