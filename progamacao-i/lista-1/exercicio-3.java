//Escreva um programa em Java para dividir dois numeros e apresentar na tela

import java.util.Scanner;
public class Exer3{
	public static void main(String args[]){
		Scanner scanner = new Scanner(System.in);
		int x,y,divisao;

		System.out.println("Infome um numero");
		x = scanner.nextInt();

		System.out.println("Infome outro numero");
		y = scanner.nextInt();

		divisao = x / y;

		System.out.println("A resposta é "+ divisao);
	}
} 
