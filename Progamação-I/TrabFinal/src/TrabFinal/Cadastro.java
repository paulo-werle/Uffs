package TrabFinal;

public abstract class Cadastro implements Cadastrar{

	private String Nome,Documento,Idade,Senha;
	private double Saldo;
	protected int Nconta;

	public abstract void Nome();
	public abstract void Idade();
	public abstract void Documento();
	public abstract void NConta(int Contas);
	public abstract void Senha();
	
	public String getNome() {
		return Nome;
	}public void setNome(String nome) {
		Nome = nome;
	}public String getIdade() {
		return Idade;
	}public void setIdade(String idade) {
		Idade = idade;
	}public String getDocumento() {
		return Documento;
	}public void setDocumento(String documento) {
		Documento = documento;
	}public String getSenha() {
		return Senha;
	}public void setSenha(String senha) {
		Senha = senha;
	}public double getSaldo() {
		return Saldo;
	}public void setSaldo(double saldo) {
		Saldo = saldo;
	}public int getNconta() {
		return Nconta;
	}public void setNconta(int nconta) {
		Nconta = nconta;
	}}

