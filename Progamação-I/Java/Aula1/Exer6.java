//Escreva um programa em Java para imprimir a soma (adição), multiplicação, subtração, divisão e
//restante de dois números.

import java.util.Scanner;
public class Exer6{
	public static void main(String args[]){
		Scanner scanner = new Scanner(System.in);

		int x,y,adi,sub,mux;
		double div,mod;

		System.out.println("Infome um numero");
		x = scanner.nextInt();

		System.out.println("Infome outro numero");
		y = scanner.nextInt();

		adi = x + y;
		sub = x - y;
		mux = x * y;
		div = x / y;
		mod = x % y;

		System.out.println(x + " + " + y + "= " + adi);
		System.out.println(x + " - " + y + "= " + sub);
		System.out.println(x + " * " + y + "= " + mux);
		System.out.println(x + " / " + y + "= " + div);
		System.out.println(x + " % " + y + "= " + mod);
	}
} 
