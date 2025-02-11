# 🛠️ **libuserlinux - Library for User Management in Embedded Unix Systems**  

## 📌 About the Project  
**libuserlinux** is a C library designed to simplify the creation, deletion, and management of users in real-time embedded Unix systems (RTOS).
Designed to operate without a graphical interface, the library enables user management in resource-limited embedded systems, such as IoT devices, industrial equipment, and automation platforms.  

The library provides functions to:  

✅ Create users in the system  
✅ Set passwords for users  
✅ Remove users from the system  
✅ Check if a user already exists  
✅ Change user passwords  

⚠️ **Note:** Some operations require a reboot to be fully applied.

## 📌 Languages and Libraries

- **C** – Main programming language  
- **POSIX APIs** – For interaction with the operating system  
- **crypt.h and shadow.h** – For password management and authentication  
- **unistd.h and sys/types.h** – For system operations  
- **RTOS/Embedded Linux** – Compatible with embedded Linux-based and real-time Unix-like systems  

## 🎯 Target Audience and Applications  
This library is ideal for systems that require user management without a graphical interface, including:  

🏭 **Industrial Automation** – Embedded Unix systems in industrial machines.  
📡 **IoT Devices** – Equipment requiring remote control and multiple users.  
🚀 **Real-Time Systems (RTOS)** – Critical applications with fast response requirements.  
🔐 **Secure Infrastructure** – Platforms requiring Unix-based authentication.  

## 🖥️ How to Use

### 📥 Cloning the Repository  
```sh
git clone https://github.com/gerhardteduardo/libuserlinux.git
cd libuserlinux
```

## 🤝 Contributions & Suggestions

If you have any suggestions or feedback about the project, feel free to open an issue or get in touch.

## 🌟 Acknowledgment

Thank you for checking out this project! I hope it serves as a useful reference or inspiration. 😊  
If you liked it, don't forget to give a ⭐ to the repository! 🚀
