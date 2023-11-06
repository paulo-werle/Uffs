//Escreva um programa em Java para ler o valor de um inteiro m e exiba o valor de n é 1 quando m é
//maior que 0, 0 quando m é 0 e -1 quando m é menor que 0.

import java.util.Scanner;
public class Exer3{
	public static void main(String args[]){
	
	Scanner scanner = new Scanner(System.in);
	int m;
	
	System.out.println("Digite um Numero: ");
	m = scanner.nextInt();
	
	if(m>0){
		System.out.println("n=1");
	}else if(m==0){
		System.out.println("n=0");
	}else{
		System.out.println("n=-1");
	}
	
	}
}
