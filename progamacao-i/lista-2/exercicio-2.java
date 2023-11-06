//Pegue três números do usuário e imprima o maior número

import java.util.Scanner;
public class Exer2{
	public static void main(String args[]){
	
	Scanner scanner = new Scanner(System.in);
	int num = -999999;
	int x;

	for(int i = 1; i <=3; i++){
		System.out.println("Informe um Numero: ");
		x = scanner.nextInt();
		if (x > num){
		num = x;
		}
	}
	System.out.println("O maior Numero é: "+ num);
	}
}
