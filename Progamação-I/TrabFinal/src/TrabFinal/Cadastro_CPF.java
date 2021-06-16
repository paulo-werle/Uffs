package TrabFinal;
import java.util.Scanner;

public class Cadastro_CPF extends Cadastro{
	Scanner scanner = new Scanner(System.in);
	
	private String Nome,Documento,Idade,Senha;
	
	@Override
	public void Nome() {
		System.out.println("Informe o seu Nome Completo");
		Nome = scanner.nextLine();
		setNome(Nome);
		
	}@Override
	public void Idade() {
		System.out.println("Informe o sua Nascimento");
		Idade = scanner.next();
		setIdade(Idade);
		
	}@Override
	public void Documento() {
		System.out.println("Informe o Numero do CPF");
		Documento = scanner.next();
		setDocumento(Documento);
		
	}@Override
	public void NConta(int Contas) {
		setNconta(Contas);
		System.out.println("O Numero da sua Conta é:"+ Contas);
		System.out.println("");
		
	}@Override
	public void Senha() {
		boolean confirm = false;
		
		for(int i=0;i<5;i++) {
		System.out.println("Crie sua Senha");
		Senha = scanner.next();
		System.out.println("Digite Novamente a Senha");
		String aut = scanner.next();
		
		if(Senha.equals(aut)) {
			System.out.println("CADASTRADO");
			confirm = true;
			setSenha(Senha);
		}else {
			System.out.println("ERRO");
			confirm = false;
		}if(confirm) {
			break;
			}}}}