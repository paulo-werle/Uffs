import java.util.Scanner;
class Conta{

	double saldo,limite;
	int numero;
	String titular;

	void saca(double valor){

		if(valor<limite){
		saldo = saldo-valor;
		}else{
		System.out.println("Saldo Indisponivel !!!!");
		}
	}
	void deposita(double valor){
		saldo = saldo+valor;
	}

//	void calculaRendimentos(){
//	}
}

class Programa{
	public static void main(String[]args){
	Scanner scanner = new Scanner(System.in);
//_______________________________________________________________________________
	
	Conta minhaconta;
	minhaconta = new Conta();
	double valor;
//_______________________________________________________________________________
	

	System.out.println("Informe o Saldo Inicial para abertura de conta: ");
	minhaconta.saldo = scanner.nextDouble();
	minhaconta.limite = minhaconta.saldo;
//_______________________________________________________________________________
		for(int x=1;x!=0;){
		System.out.println("Informe a Opção desejada: ");
		System.out.println("");
		System.out.println("1º SACAR");
		System.out.println("2º DEPOSITAR");
		System.out.println("3º CALCULAR RENDIMENTO");
		System.out.println("0º SAIR");
		x = scanner.nextInt();

		switch (x) {
				case 1: {
				System.out.println("Quanto deseja Sacar R$: ");
				valor = scanner.nextDouble();
				minhaconta.saca(valor);
				System.out.println("Seu novo Saldo é de R$"+saldo);

				break;
				}
				case 2: {
				System.out.println("Quanto deseja Depositar R$: ");
				valor = scanner.nextDouble();
				minhaconta.deposita(valor);
				System.out.println("Seu novo Saldo é de R$"+saldo);
			
				break;
				}
		}
	}
	}
}
