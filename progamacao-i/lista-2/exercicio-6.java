//Escreva um programa em Java que leve o usuário a fornecer um único caractere do alfabeto. Imprima
//vogal ou consoante, dependendo da entrada do usuário. Se a entrada do usuário não for uma letra
//(entre a e z ou A e Z), ou se for uma cadeia de comprimento > 1, imprima uma mensagem de erro

import java.util.Scanner;
public class Exer6{
	public static void main(String args[]){

		Scanner scanner = new Scanner(System.in);
		String entrada;

		System.out.print("Digite um Caracter: ");
		entrada = scanner.nextLine();

		switch (entrada) {
			case "a": {
			System.out.println("A Letra é Vogal");		
			break;
			}
			case "b": {
			System.out.println("A letra é Consoante");	
			break;
			}
			case "c": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "d": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "e": {
			System.out.println("A Letra é Vogal");		
			break;
			}
			case "f": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "g": {
			System.out.println("A letra é Consoante");	
			break;
			}
			case "h": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "i": {
			System.out.println("A Letra é Vogal");		
			break;
			}
			case "j": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "k": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "l": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "m": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "n": {
			System.out.println("A letra é Consoante");	
			break;
			}
			case "o": {
			System.out.println("A Letra é Vogal");		
			break;
			}
			case "p": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "q": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "r": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "s": {
			System.out.println("A letra é Consoante");	
			break;
			}
			case "t": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "u": {
			System.out.println("A Letra é Vogal");		
			break;
			}
			case "v": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "w": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "x": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "y": {
			System.out.println("A letra é Consoante");		
			break;
			}
			case "z": {
			System.out.println("A letra é Consoante");		
			break;
			}
			default: {
			System.out.println("ERRRRRRRRRRRRRRRRRRRRRRRRRRRRo");
			}
			
		}
		

	}
}
