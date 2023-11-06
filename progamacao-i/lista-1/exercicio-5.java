//Escreva um programa em Java que tenha dois numeros comoentrada e exiba o produto de dois numeros

import java.util.Scanner;
public class Exer5{
	public static void main(String args[]){

		Scanner scanner = new Scanner(System.in);
		int a,b,mux;

		System.out.print("Informe um Numero: ");
		a = scanner.nextInt();

		System.out.print("Informe outro Numero: ");
		b = scanner.nextInt();

		mux = a * b;

		System.out.println("A resposta é "+ mux);
	}
}
