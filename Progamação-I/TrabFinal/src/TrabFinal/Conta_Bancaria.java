package TrabFinal;
import java.util.Scanner;

public class Conta_Bancaria {
	private static Scanner scanner;

	public static void main(String[]args){
		scanner = new Scanner(System.in);
		
		Cadastro[] Conta = new Cadastro [10];
		int Contas = -1;
		Opera�oes op = new Opera�oes();
		
		for(int x=1;x!=0;){
		System.out.println("Informe a Op��o Desejada: ");
		System.out.println("");
		System.out.println("1� CADASTRAR PESSOA FISICA");
		System.out.println("2� CADASTRAR PESSOA JURIDICA");
		System.out.println("3� DEPOSITAR");
		System.out.println("4� SACAR");
		System.out.println("5� TRANSFERIR");
		System.out.println("");
		x = scanner.nextInt();
		
		switch (x) {
		case 1: {
				Contas+=1;
				Conta[Contas] = new Cadastro_CPF();
				Conta[Contas].Nome();
				Conta[Contas].Idade();
				Conta[Contas].Documento();
				Conta[Contas].NConta(Contas);
				Conta[Contas].Senha();
				break;
		}case 2: {
				Contas+=1;
				Conta[Contas] = new Cadastro_CNPJ();
				Conta[Contas].Nome();
				Conta[Contas].Idade();
				Conta[Contas].Documento();
				Conta[Contas].NConta(Contas);
				Conta[Contas].Senha();
				break;
		}case 3: {
				System.out.println("Informe o Valor que deseja Depositar");
				double valor = scanner.nextDouble();
				op.Depositar(Conta,valor);
				break;	
		}case 4: {
			System.out.println("Informe o Valor que deseja Sacar");
			double valor = scanner.nextDouble();
			op.Sacar(Conta,valor);
				break;	
		}case 5: {
			System.out.println("Informe o Valor que Deseja Transferir");
			double valor = scanner.nextDouble();
			op.Transferir(Conta,valor);
				break;	
		}case 6: {
				op.Juros();
				break;	
		}case 7: {
			op.Consultar_Saldo(Conta);
				break;	
		}}}}}