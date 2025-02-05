# 🛠️ libuserlinux - Biblioteca para Gerenciamento de Usuários em Sistemas Unix Embarcados

## 📌 Sobre o Projeto

A **libuserlinux** é uma biblioteca escrita em **C** para facilitar a criação, exclusão e gerenciamento de usuários em **sistemas Unix embarcados real-time (RTOS)**.  

Projetada para operar **sem interface gráfica**, a biblioteca permite manipular usuários em sistemas embarcados com **recursos limitados**, como dispositivos IoT, equipamentos industriais e plataformas de automação.  

A biblioteca oferece funções para:  

✅ Criar usuários no sistema  
✅ Definir senhas para os usuários  
✅ Remover usuários do sistema  
✅ Verificar se um usuário já existe  
✅ Alterar senhas de usuários  

⚠️ **Observação**: Algumas operações exigem **reboot** para serem totalmente aplicadas.

## 🚀 Tecnologias Utilizadas

### 📌 Linguagens e Bibliotecas
- **C** – Linguagem de programação principal  
- **POSIX APIs** – Para interação com o sistema operacional  
- **`crypt.h` e `shadow.h`** – Para gerenciamento de senhas e autenticação  
- **`unistd.h` e `sys/types.h`** – Para operações no sistema  
- **RTOS/Linux Embarcado** – Compatível com sistemas baseados em **Linux embarcado e Unix-like de tempo real**  

## 🎯 Público-Alvo e Aplicações

Esta biblioteca é ideal para sistemas que precisam de **gerenciamento de usuários sem interface gráfica**, incluindo:

- 🏭 **Automação Industrial** – Sistemas embarcados Unix em máquinas industriais.  
- 📡 **Dispositivos IoT** – Equipamentos que exigem controle remoto e múltiplos usuários.  
- 🚀 **Sistemas em Tempo Real (RTOS)** – Aplicações críticas com requisitos de resposta rápida.  
- 🔐 **Infraestrutura Segura** – Plataformas que precisam de autenticação baseada em Unix.  

## 🖥️ Como Usar

### 📥 Clonando o Repositório
```sh
git clone https://github.com/seu-usuario/libuserlinux.git
cd libuserlinux
```

## 🤝 Contribuições & Sugestões

Caso tenha alguma sugestão ou feedback sobre o projeto, sinta-se à vontade para abrir uma issue ou entrar em contato.

## 🌟 Agradecimento

Obrigado por conferir este projeto! Espero que ele seja útil como referência ou inspiração. 😊  
Se gostou, não esqueça de dar uma ⭐ no repositório! 🚀

