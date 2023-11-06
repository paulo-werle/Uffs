//Escreva um programa em Java para imprimir a soma de dois numeros 

import java.util.Scanner;
public class Exer2{
	public static void main(String args[]){
		Scanner scanner = new Scanner(System.in);
		int x,y,soma;

		System.out.println("Infome um numero");
		x = scanner.nextInt();

		System.out.println("Infome outro numero");
		y = scanner.nextInt();

		soma = x + y;

		System.out.println("A resposta é "+ soma);
	}
} 
