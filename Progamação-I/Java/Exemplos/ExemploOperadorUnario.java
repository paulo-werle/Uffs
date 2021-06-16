//Exemplo do uso dos operadores aritimedicos

public class ExemploOperadorUnario{
	public static void main(String args[]) {
		int var1 = 10;
		int var2 = 20;
		int res = 0;
		System.out.println("res: " + res);
		res = var1++ + var2;
		System.out.println("res: " + res);
		res = var1 + var2;
		System.out.println("res: " + res);
		res = var1 + --var2;
		System.out.println("res: " + res);

	}
}
