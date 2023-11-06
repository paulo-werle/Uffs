import java.util.Scanner;
public class Exem1{

	public static void main(String args[]){

class Conta{
	int numero;
	String dono;
	double saldo;

	void deposito(double valor){
	this.saldo += valor;
	}
	void sacar(double valor){
	this.saldo -= valor;
	}
}
		Conta minhaconta;
		minhaconta =new Conta();

		Scanner scanner = new Scanner(System.in);
		System.out.println("Informe o titular da conta: ");
		minhaconta.dono = scanner.nextLine();

		System.out.println("Informe o numero da conta: ");
		minhaconta.numero = scanner.nextInt();

		System.out.println("Informe o Saldo da conta: ");
		minhaconta.saldo = scanner.nextDouble();

		double valor = 
		minhaconta.deposito(valor);
		System.out.println("O novo saldo é: "+ minhaconta.saldo);
	

	}
}
