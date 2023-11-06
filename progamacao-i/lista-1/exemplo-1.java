// Escreva um programa para imprimir qual dia da semana é

import java.util.Scanner;
public class Exem1{
	public static void main(String args[]){

		Scanner scanner = new Scanner(System.in);
		int x;

		System.out.println("Infome um numero para o dia da Semana");
		x = scanner.nextInt();

		switch (x) {
			case 1: {
			System.out.println("Domingo");		
			break;
			}
			case 2: {
			System.out.println("Segunda-Feira");		
			break;
			}
			case 3: {
			System.out.println("Terça-Feira");		
			break;
			}
			case 4: {
			System.out.println("Quarta-Feira");		
			break;
			}
			case 5: {
			System.out.println("Quinta-Feira");		
			break;
			}
			case 6: {
			System.out.println("Sexta-Feira");		
			break;
			}
			case 7: {
			System.out.println("Sabado");	
			break;
			}
			default: {
			System.out.println("Opção Invalida");
			}
			
		}

	}
}
