<div align=center>
<h1>
AATMS
<br>
    <a href="#"><img src="https://komarev.com/ghpvc/?username=AATMS&label=views&color=0e75b6&style=flat" alt="Repo Views"></a>
    <a href="https://github.com/Jed556/AATMS/releases"><img alt="GitHub release (latest by date including pre-releases)" src="https://img.shields.io/github/v/release/Jed556/AATMS?include_prereleases&color=35566D&logo=github&logoColor=white&label=latest"></a>
    <a href="https://github.com/Jed556/AATMS/releases"><img alt="GitHub downloads" src="https://img.shields.io/github/downloads/Jed556/AATMS/total?label=downloads&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAA2klEQVQ4jZ2SMWpCQRCGv5WHWKQIHsAj5Ah2IR7ByhvYpUiVxkqipPCE5gKKBB5Y+KXIIzzXWX3mh2FhZ/5vZ3YXAqkzdavumtiqs6g2MvfV2kvVaj+v7wWMChgE+4MmdxMQ7RVz14r/Dbirg7+Z1BHw2ERJT+oe2KeUvs4y6ntw8yUtLtAq6rqDeaPG/XWAlM0Z5KOzWZ2owwCybJk/c7M6VCf4+0XHhU5e1bfoZHWs1hVwInjflBLA6vrAnCrgADyrxwZGa83Va60vwCGpU2ADPNw4Ldc3MP8Bk60okvXOxJoAAAAASUVORK5CYII="></a>


</h1>
</div>

Advanced Automated Teller Machine System (AATMS) is a GUI + System program that simulates an ATM machine. On top of the basic functionalities of an ATM machine, AATMS also provides additional features such as deposit interest, loan system, and account management.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
    - [Dependencies](#dependencies)
    - [Setup](#setup)
    - [Build](#build)
- [Usage](#usage)

<details>
  <summary><h2>Features</h2></summary>

- Deposit Interest System: Our Advanced ATM System will provide customers with the advantage of earning interest on their deposits. This feature encourages savings and financial growth for individuals, fostering a culture of financial responsibility.
- Withdraw and Deposit System: Customers can easily access their funds or add to their account balance without the need for a physical branch visit. This convenience saves time and effort for users while reducing congestion in bank branches.
- Loan System: Our Advanced ATM System will incorporate a loan system that enables customers to apply for loans directly through the machine. The program will calculate and display the applicable interest rate, providing users with transparency and facilitating informed decision-making.
- Loan Tracking System: Customers can monitor their loan balances, track repayment schedules, and receive notifications about upcoming payments. This functionality helps users stay on top of their financial commitments and avoid unnecessary penalties.
- Create, Remove, and Edit Account: The Advanced ATM System will provide users with the ability to create new accounts, remove existing accounts, and make account modifications such as updating contact information or linking additional services. This flexibility empowers customers to manage their accounts conveniently without having the need to go to bank branches and adapt them to their needs.
- Check Balance: Users can easily check their account balance at any time through the Advanced ATM System. This feature provides quick access to financial information, enabling customers to make informed financial decisions without the need for additional consultations or online access.
- Log-in System: To ensure security and privacy, our program will implement a robust log-in system, requiring customers to authenticate their identities through PINs or other media that can hold these PINs such as credit cards or mobile managers.
- Designed for Scalability and Performance: Our Advanced ATM System's architecture will support a large number of concurrent users, ensuring smooth and efficient operation even during peak usage periods. This design approach enhances customer satisfaction and minimizes service disruptions.

</details>

<details open>
  <summary><h2>Installation</h2></summary>

### Dependencies
Install the following dependencies before proceeding with the setup.
- [Visual Studio Code](https://code.visualstudio.com)
- [Msys2](https://www.msys2.org)
- [Git](https://git-scm.com)
- [CMake](https://cmake.org)
- [vcpkg](https://vcpkg.io) (installed in [setup](#setup))

### Setup
The following instructions are for Windows with Visual Studio Code and CMake Tools extension. Other IDEs and platforms may require different steps.
1. Clone the following repositories to your local machine
```bash
git clone https://github.com/Jed556/AATMS.git
```
```bash
git clone https://github.com/Microsoft/vcpkg.git
```
2. Open the `vcpkg` folder in Visual Studio Code and install the extensions `ms-vscode.cpptools`, `twxs.cmake`, and `ms-vscode.cmake-tools`.
3. In the `vcpkg` folder, run the following command to build vcpkg.
```bash
.\bootstrap-vcpkg.bat
```
4. In the `vcpkg` folder, run the following command to install the required packages.
```bash
./vcpkg install sqlite3:x64-windows sdl2:x64-windows sdl2-image:x64-windows sdl2-ttf:x64-windows
```
> **Note**<br>
> Please refer to the [vcpkg documentation](https://vcpkg.io/en/getting-started.html) for more information on how to setup vcpkg and install packages.

### Build
1. Open the `AATMS` folder in Visual Studio Code.
2. Allow the **CMake Tools** extension to configure the project. CMake Tools will automatically include the required dependencies through vcpkg.
3. Select the **CMake: Build** command from the command palette. With the target `PackU` selected, this will build the project and pack the program inside `build/package`.

</details>