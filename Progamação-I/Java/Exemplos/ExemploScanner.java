import java.util.Scanner;
class ExemploScanner {
	public static void main(String[] args){
		Scanner sacanner = new Scanner(System.in);

		System.out.print("Digite seu Nome Completo: ");
		Styring name = scanner.nextLine();

		System.out.print("Digite seu Signo: ");
		Styring zodiac = scanner.next();

		System.out.print("Digite seu Peso (kg): ");
		double weight = scanner.nextDouble();

		System.out.print("Digite o Numero da Sorte: ");
		Styring luckyNum = scanner.nextInt();

		System.out.println("\n\nOlá, " + nome + "!");
		System.out.println(" Seu numero da sorte é " + luckyNum + "-");
		System.out.println("Voce pesa " + weight + "kg.");
		System.out.println("Seu signo é " + zodiac + ".\n");






	}
}
