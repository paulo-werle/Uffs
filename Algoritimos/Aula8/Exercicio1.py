#Dado a lista de numeros abaixo, faça um programa que caucule a media desses Numeros
#x=[ 5, 6, 7, 8.8, 5, 6, 7.8, 9.8, 7]

'''x=[5,6,7,8.8,5,6,7.8,9.8,7]
resultado = 0

for num in x:
	resultado += num
	
print("A Media é: {:.2f}".format(resultado/9))'''

#Dado a lista de numeros abaixo, faça um programa que caucule a media desses Numeros
#x=[ 5, 6, 7, 8.8, 5, 6, 7.8, 9.8, 7]

x=[5,6,7,8.8,5,6,7.8,9.8,7]
resultado = 0
num = 0

while num < 9:
	resultado += x[num]
	num+=1
	
print("A Media é: {:.2f}".format(resultado/9))


