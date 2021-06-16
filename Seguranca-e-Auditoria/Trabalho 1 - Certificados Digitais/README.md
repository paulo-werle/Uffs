# Assinatura de Certificado Digital 

Usamos a lib rbnacl para fazermos a parte de criptografia de dados

* [rbnacl](https://github.com/RubyCrypto/rbnacl)

Através dessa biblioteca construimos um programa funcional, com uma classe CertificadoDigital
e métodos próprios dessa classe para podemos manipular os dados e criar/validar certificados digitais

Nesta classe possuímos os seguintes atributos para manipular os dados: 

* `:credenciais` – Guarda as credenciais do(s) emissor(es) do certificado
* `:hash` – Guarda uma sequencia de caracteres, nesse caso usamos as próprias credenciais como hash
* `:hash_cifrado` –  Guarda uma sequencia de caracteres criptografados com uma chave privada
* `:chave_privada` – Guarda a chave privada (Só possui em processos que dependem de uma chave privada)
* `:chave_publica` – Guarda a chave publica

esta classe possui os seguintes métodos para auxiliar suas funcionalidades:

* `assinar_com_nova_chave` – Gera os dados de um certificado digital juntamente com uma chave privada
* `assinar_com_chave_existente` – Gera dados de um certificado assinando com uma chave privada previamente criada
* `gerar_base64` – Converte dados para base64
* `gerar_json` – Converte dados para json
* `analisar_base64` – Converte o base64 para o valor inicial
* `analisar_json` – Converte o json para o valor inicial
* `criar_arquivo_com_chave_privada` – Contem o processo de criar uma chave privada, salvando a em arquivo e a disponibilizando para acesso
* `criar_arquivo_com_certificado_digital` – Contem o processo de criar um certificado digital, salvando a em arquivo e a disponibilizando para acesso
* `atualizar_certificado_digital` – Atualiza os certificados digitais quando haver novas assinaturas
* `abrir_certificado_digital` – Abre arquivo do certificados para ser utilizada no programa
* `abrir_chave_privada` – Abre arquivo da chave privada para ser utilizada no programa
* `validar_certificado_digital` – Valida se o certificado digital é valido
* `atualizar_credenciais` – Atualiza as credenciais quando haver novas assinaturas


Funcionalidades do programa:

	1) Criar novo certificado digital
	2) Assinar certificado pré-existente com uma nova chave
	3) Assinar certificado pré-existente com uma chave existente
	4) Validar certificado digital