// Escreva um programa em Java que tenha um número como entrada e imprima sua tabela de multiplicação
//até 10.

import java.util.Scanner;
public class Exer7{
	public static void main(String args[]){

		Scanner scanner = new Scanner(System.in);
		int x;

		System.out.print("Informe um numero = ");
		x = scanner.nextInt();

		for(int var1=0;var1<=10;var1++){

		System.out.println(x + "*" + var1 + "= " + x*var1);

		}

	}
}

