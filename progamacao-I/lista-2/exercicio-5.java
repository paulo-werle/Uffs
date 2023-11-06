//Escreva um programa em Java para encontrar o número de dias em um mês.

import java.util.Scanner;
public class Exer5{
	public static void main(String args[]){

		Scanner scanner = new Scanner(System.in);
		int ano, mes;

		System.out.println("Insira o numero de um mes: ");
		mes = scanner.nextInt();
		System.out.println("Insira o numero de um ano: ");
		ano = scanner.nextInt();

		switch (mes) {
			case 1: {
			System.out.println("Janeiro de "+ ano +" tem 31 dias");		
			break;
			}
			case 2: {
			int mod = ano%4;
			if(mod==0){
				System.out.println("Fevereiro de "+ ano +" tem 29 dias");
			}else{
			System.out.println("Fevereiro de "+ ano +" tem 28 dias");	
			}	
			break;
			}
			case 3: {
			System.out.println("Março de "+ ano +" tem 31 dias");		
			break;
			}
			case 4: {
			System.out.println("Abril de "+ ano +" tem 30 dias");		
			break;
			}
			case 5: {
			System.out.println("Maio de "+ ano +" tem 31 dias");		
			break;
			}
			case 6: {
			System.out.println("Junho de "+ ano +" tem 30 dias");		
			break;
			}
			case 7: {
			System.out.println("Julho de "+ ano +" tem 31 dias");	
			break;
			}
			case 8: {
			System.out.println("Agosto de "+ ano +" tem 31 dias");		
			break;
			}
			case 9: {
			System.out.println("Setembro de "+ ano +" tem 30 dias");		
			break;
			}
			case 10: {
			System.out.println("Outubro de "+ ano +" tem 31 dias");		
			break;
			}
			case 11: {
			System.out.println("Novembro de "+ ano +" tem 30 dias");		
			break;
			}
			case 12: {
			System.out.println("Dezembro de "+ ano +" tem 31 dias");		
			break;
			}
			
		}
	}
}

