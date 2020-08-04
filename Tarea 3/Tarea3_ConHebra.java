import java.util.Scanner;
import java.util.concurrent.TimeUnit;
import java.lang.Thread;

public class Tarea3_ConHebra
{
	static int actual1[] = new int[2];
	static int actual2[] = new int[2];

	public static int BuscaDiv( int n )
	{
		//almacenara la cantidad de divisores que posee el numero a buscar
		int t = 0; 
		for (int i = 1; i<Math.sqrt(n); i++)
		{
			if (n%i == 0)
			{
				if (n/i == i)
					t+=1;
				else
					t+=2;
			}
		}
		return t;
	}

	public static class PTask implements Runnable
	{
		private int[] valoract;
		public PTask(int[] valoract)
		{
			this.valoract = valoract;
		}
		public void run()
		{
			int i;
			if (valoract[0] == 1)
			{	
				//posicion 0 almacena el valor, y el 1 la cantidad de divisores
				actual1[0] = 0;
				actual1[1] = 0;

				for (i=0 ; i<=valoract[1] ; i++)
				{
					int a = BuscaDiv(i);
					if (a > actual1[1])
					{
						actual1[0] = i;
						actual1[1] = a;
					}
				}
				return;
			}

			if(valoract[0] == 2)
			{
				//posicion 0 almacena el valor, y el 1 la cantidad de divisores
				actual2[0] = 0;
				actual2[1] = 0;

				for (i=(valoract[1]/2) ; i<=valoract[1] ; i++)
				{
					int a = BuscaDiv(i);
					if (a > actual2[1])
					{
						actual2[0] = i;
						actual2[1] = a;
					}
				}
				return;
			}
		}
	}

	public static void main(String[] args)
	{	
		Scanner scan = new Scanner(System.in);
		System.out.println("Ingrese el valor para obtener el rango:");
		int n = scan.nextInt();
		scan.close();

		int[] ola = new int[2];
		ola[0] = 1;
		ola[1] = n/2;
		int[] ola1 = new int[2];
		ola1[0] = 2;
		ola1[1] = n;

		Thread t1 = new Thread(new PTask(ola), "t1");
		Thread t2 = new Thread(new PTask(ola1), "t2");

		long s = System.currentTimeMillis();
		
		t1.start();
		t2.start();
		try
		{
			t1.join();
		}
		catch(Exception ex)
		{
			System.out.println("Error atrapado");
		}
		try
		{
			t2.join();
		}
		catch(Exception ex)
		{
			System.out.println("Error atrapado");
		}

		System.out.println("El numero con mayor cantidad de divisores en el rango entregado es:");

		if(actual1[1]>actual2[1])
			System.out.printf("%d\n", actual1[0]);
		if(actual1[1]<actual2[1])
			System.out.printf("%d\n", actual2[0]);
		else
			System.out.printf("%d\n", actual1[0]);
		
		long e = System.currentTimeMillis();

		System.out.println("El tiempo que le tomo al algoritmo para hallar el numero es de:");
		System.out.printf("%d milisegundos\n", (e-s));
	}	
}