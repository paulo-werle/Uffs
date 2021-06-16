//Escreva um programa em Java para imprimir "Hello" na tela e depois imprima seu nome
// em uma linha separada

import java.util.Scanner;
public class Nome{
	public static void main(String args[]){

		System.out.print("Informe seu Nome: ");
		Scanner scanner = new Scanner(System.in);
		String name = scanner.nextLine();


		System.out.println("Hello");
		System.out.println(name);

	} 
}
