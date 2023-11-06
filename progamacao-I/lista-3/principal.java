import java.util.Scanner;
class Funcionario{

	String nome;
	double salario;
	int idade;
	Scanner scanner = new Scanner(System.in);

	void ler(){
	System.out.println("Informe o Nome do Funcionario");
		this.nome = scanner.nextLine();
	System.out.println("Informe a Idade do Funcionario");
		this.idade = scanner.nextInt();
	System.out.println("Informe o Salario do Funcionario");
		this.salario = scanner.nextDouble();
	}
	void bonifica(){
	System.out.println("Informe quanto de Bonificação o Funcionario terá !!!");
	System.out.println("OBS: Informe em Porcentual, para ser calculado a partir do Salario");
		double x = scanner.nextDouble();
		x = x/100;
	salario = salario+(salario*x);
	}
}

//________________________________________________________________________________

class Principal{
public static void main(String[]args){
	Scanner scanner = new Scanner(System.in);

	Funcionario funcionario1;
	funcionario1 = new Funcionario();

	for(int x=1;x!=0;){
	System.out.println("Informe a Opção desejada: ");
	System.out.println("");
	System.out.println("1º LER FUNCIONARIO");
	System.out.println("2º CALCULAR BONIFICAÇÃO");
	System.out.println("0º SAIR");
	x = scanner.nextInt();

	switch (x) {
		case 1: {
			funcionario1.ler();
		break;
		}case 2: {
			funcionario1.bonifica();
		break;
		}
			}
	if(x==0) {
	}else {
	System.out.println("O Funcionario:" +funcionario1.nome);
	System.out.println("Recebe:" +funcionario1.salario);
	}}
}}
