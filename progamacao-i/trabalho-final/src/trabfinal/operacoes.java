package TrabFinal;
import java.util.Scanner;

public class Operaçoes<Conta> extends Conta_Bancaria{
Scanner scanner = new Scanner(System.in);


	void Depositar(Cadastro[] Contas,double valor) {
		for(int i=0;i<10;) {
		System.out.print("Infome o numero da conta: ");
		int num = scanner.nextInt();
		System.out.println("A conta desejada esta em Nome de: " + Contas[num].getNome());
		System.out.println("Digite 's' para SIM");
		System.out.println("Digite 'n' para NAO");
		String confirm = scanner.next();
		
		if (confirm.equals("n")) {
			System.out.println("TENTE NOVAMENTE");
		}else {
			Contas[num].setSaldo(Contas[num].getSaldo() + valor);
			System.out.println("DEPOSITADO");
			break;
		}}
		
		}void Sacar(Cadastro[] Contas,double valor) {
			for(int i=0;i<10;) {
			System.out.print("Infome o numero da conta: ");
			int num = scanner.nextInt();
			System.out.println("A conta desejada esta em Nome de: " + Contas[num].getNome());
			System.out.println("Digite 's' para SIM");
			System.out.println("Digite 'n' para NAO");
			String confirm = scanner.next();
			
			if (confirm.equals("s")) {
				if(Contas[num].getSaldo()>valor) {
					System.out.println("Digite a Senha");
					String senha = scanner.next();
					if(Contas[num].getSenha().equals(senha)) {
						Contas[num].setSaldo(Contas[num].getSaldo() - valor);
						System.out.println("RETIRE SEU DINHEIRO");
						break;
					}else{ 
						System.out.println("TENTE NOVAMENTE,SENHA INCORRETA");
					}}else{ 
						System.out.println("TENTE NOVAMENTE, SALDO INDISPONIVEL");
					}}else{ 
						System.out.println("TENTE NOVAMENTE");
					}}
	}void Transferir(Cadastro[] Contas,double valor) {
		for(int i=0;i<10;) {
		System.out.print("Numero da Conta para transferir: ");
		int num0 = scanner.nextInt();
		System.out.print("Numero da Conta para Receber: ");
		int num1 = scanner.nextInt();
		System.out.println("De: " + Contas[num0].getNome());
		System.out.println("Para: " + Contas[num1].getNome());
		System.out.println("Digite 's' para SIM");
		System.out.println("Digite 'n' para NAO");
		String confirm = scanner.next();
		
		if (confirm.equals("s")) {
			if(Contas[num0].getSaldo()>valor) {
				System.out.println("Digite a Senha");
				String senha = scanner.next();
				if(Contas[num0].getSenha().equals(senha)) {
					Contas[num1].setSaldo(Contas[num1].getSaldo() + valor);
					Contas[num0].setSaldo(Contas[num0].getSaldo() - valor);
					System.out.println("TRANSFERENCIA CONCLUIDA !!!");
					break;
				}else{ 
					System.out.println("TENTE NOVAMENTE,SENHA INCORRETA");
				}}else{ 
					System.out.println("TENTE NOVAMENTE, SALDO INDISPONIVEL");
				}}else{ 
					System.out.println("TENTE NOVAMENTE");
				}}
	}void Juros(){
		
	}void Consultar_Saldo(Cadastro[] Contas){
		System.out.println("Digite a Senha");
		String senha = scanner.next();
		System.out.print("Informe o Numero da Conta: ");
		int num = scanner.nextInt();
		if(Contas[num].getSenha().equals(senha)) {
		System.out.println("Titular: " + Contas[num].getNome());
		System.out.println("Saldo: " + Contas[num].getSaldo());
		}}
}
