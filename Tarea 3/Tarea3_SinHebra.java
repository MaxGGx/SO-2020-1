import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class Tarea3_SinHebra
{
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
 
	public static void main(String[] args)
	{
		int i;
		
		//posicion 0 almacena el valor, y el 1 la cantidad de divisores
		int actual[] = new int[2];
		actual[0] = 0;
		actual[1] = 0;

		Scanner scan = new Scanner(System.in);
		System.out.println("Ingrese el valor para obtener el rango:");
		int n = scan.nextInt();
		scan.close();

		long s = System.currentTimeMillis();
		for (i=0 ; i<=n ; i++)
		{
			int a = BuscaDiv(i);
			if (a > actual[1])
			{
				actual[0] = i;
				actual[1] = a;
			}
		}
		long e = System.currentTimeMillis();
		System.out.println("El numero con mayor cantidad de divisores en el rango entregado es:");
		System.out.printf("%d\n", actual[0]);
		System.out.println("El tiempo que le tomo al algoritmo para hallar el numero es de:");
		System.out.printf("%d milisegundos\n", (e-s));
	}	
}