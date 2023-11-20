# Remotely Debug C++ Programs on RPI Using VS Code

<br>

# Step 1 : Download and install the following items

## 1) [Visual Studio Code](https://code.visualstudio.com/)

-   Once you've opened VS Code
-   Click `EXTENSIONS` on the menu towards the left
-   Type in the search bar the following items and click `INSTALL`
    -   Remote -SSH
    -   C/C++
    -   C/C++ Extension packs

![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/08181185-6223-4e83-8dcc-3f4c9836022e)
![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/dfaf99cd-9188-4c05-bc30-63eb5fc56ea2)
![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/b1b211ef-a6f2-4511-8d1e-c864ae1a14e0)

## 2) [VcXsrv Windows X Server](https://sourceforge.net/projects/vcxsrv/)

## 3) [This repository to the DESKTOP of your Rasbperry PI](https://github.com/Digital1O1/Hello_World_Debugger_VSCode.git)

<br>

# Step 2 : Change The `DISPLAY` Envionment Variable

<s>
## 1) Open Powershell

-   Press Windows key
-   Type in search bar `Powershell`
-   Type in the following in your Powershell instance and the Notepad application should launch
    ```bash
    notepad $PROFILE
    ```
-   Enter the following in your Notepad instance
-   Save the written contents
    ```bash
    # You can pick whatever numerical value for local host
    # Example --> $env:DISPLAY = "localhost:10.0
    $env:DISPLAY = "localhost:10.0"
    ```
-   Restart Powershell
    -   You MUST close and re-open PowerShell for the changes to take effect
    -   To double check if the `DISPLAY` variable was saved, copy/paste the following
    ```bash
    $env:DISPLAY
    ```
-   Changing the PowerShell Execution Policy - Open Powershell - Enter the following
    `bash
    Set-ExecutionPolicy RemoteSigned
    ` - You'll be prompted the following, just enter [Y] to confirm the action hit ENTER
    `       Execution Policy Change
        The execution policy helps protect you from scripts that you do not trust. Changing the execution policy might expose you to the
        security risks described in the about_Execution_Policies help topic at https:/go.microsoft.com/fwlink/?LinkID=135170. Do you want to
        change the execution policy?
        [Y] Yes  [A] Yes to All  [N] No  [L] No to All  [S] Suspend  [?] Help (default is "N"): 
  `
    </s>

## 1) Add DISPLAY Variable To Enviornment Variables in WINDOWS

-   Press Windows key
-   Type in the search bar `ENVIRONMENT VARIABLES` then press ENTER
    -   Click on `Edit the system environment variables`
    -   Once the `Enironment Variables` window pops up, click on `new`
        -   For `Variable name` enter `DISPLAY`
        -   For `Variable value` enter the local host value you set earlier in your NotePad instance
            -   In this example, set `localhost` to `localhost:10.0`

![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/ab8295f5-143d-4b42-876d-a039b7bf490f)
![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/511515c8-0c48-4d2f-96b8-5ae97307cfe7)
![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/0eb77108-6957-4a95-bd83-668758a093e0)

<br>

# Step 3 : Generate SSH Key On Your Host Machine/Workstation

## 1) Create .ssh 'folder'

-   Open `Powershell` press `Windows key`
-   Type in the following

```bash
mkdir .ssh
```

## 2) Generate SSH Key

-   Enter the following

```bash
ssh-keygen -t ed25519
```

-   When prompted :
    -   `Enter file in which to save the key (/home/local/.ssh/id_rsa)`
        -   <s>Choose `.ssh`</s>
        - Just press ENTER
    -   `Enter passphrase (empty for no passphrase): `
        -   Just press ENTER
    -   `Enter same passphrase again:`
        -   Just press ENTER again
-   You'll then be prompted with your `key fingerprint` and your key's `randomart image` as shown in the example screenshot below
    ![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/0293f80d-ad1e-4e73-b473-93715c6ef266)

-   Find the directory where your newly generated SSH keys are stored
    - In my case, it's in the following directory
    - Copy the newly generated SSH key since we're going to paste it into a different file in the Raspberry PI/Linux device
 
```bash
 C:\Users\S123456789\.ssh
```

-   Use the `ls` command to list the contents of the `.ssh` directory
-   We're going to need the `public key` that has the `.pub` ending as shown in the screenshot below
-   You can use either `VI` or `VIM` to view the contents of your `public key`
    ![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/d00623bc-6fb1-465d-aa29-97f43a78b550)

## 3) Save SSH Key on Raspberry PI or LINUX device

-   Type in the following commands in your Raspberry PI terminal

```bash
cd ~
sudo nano ~/.ssh/authorized_keys
```

-   If the `.ssh` folder DOESN'T exist, use the following commands

```bash
cd ~
mkdir authorized_keys
sudo nano ~/.ssh/authorized_keys
```

-   Then :
    -   Paste your `.pub` SSH key into the `authorized_keys` file
    -   Press `Control + X` --> `Y` --> `ENTER` to save and exit out of the file

## 4) Obtain your Raspberry PI IP address

-   Open a terminal on the Raspberry PI
-   Type in the following and take note of the value that's displayed under the `wlan0` section
    ```bash
    ifconfig
    ```
    ![image](https://github.com/Digital1O1/Remotely-Debug-C-Programs-on-RPI-Using-VS-Code/assets/39348633/5094e115-1d6a-4775-b6e3-224ddad1cc65)

## 5) Enable X11 Port Fowarding On The Host Machine

-   On your host machine

    -   Open a Powershell instance
    -   Use the :

        -   `cd` command to return back to the `.ssh` folder
        -   `-ls -a` command to list everything stored in the `.ssh` folder

            -   You should see a `config` file
                -   If not, use the following command
                ```bash
                vim config
                ```
            -   Use either `vim` or `nano` to edit the `config` file and enter the following WITHOUT THE BRACKETS

            ```bash
                Host [YOUR RASPBERRY PI IP ADDRESS]
                    HostName [YOUR RASPBERRY PI IP ADDRESS]
                    User [YOUR RASPBERRY PI USER NAME]
                    ForwardAgent yes
                    ForwardX11 yes
                    ForwardX11Trusted yes

                # Example
                Host 192.123.56.111
                    HostName 192.123.56.111
                    User pi
                    ForwardAgent yes
                    ForwardX11 yes
                    ForwardX11Trusted yes
            ```

## 6) Configuring VcXsrv Windows X Server

-   Upon running the setup file
    -   Select `Multiple Windows`
-   Set the `Display number` to whatever value you set your `localhost:10.0` to
    -   Which in this case is 10
-   Select `Start no client`
-   Select `Disable access control`

    ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/19709946-09d7-436d-8727-9ac44e0297b4)
    ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/6597c263-ed76-41df-b720-cd9d1a607167)
    ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/0d0eb291-a93b-4490-84e3-57c5a0a04dd7)

    <br>

# Step 4 : Configuring VS Code for remote development

-   Open VS Code - Right click on `Remote-SSH`
-   Click on `Extension Settings`
-   Ensure the following boxes are checked:
    -   Remote.SSH: Enable Agent Forwarding
    -   Remote.SSH: Enable Dynamic Forwarding
    -   Remote.SSH: Enable X11 Forwarding
        ![image](https://github.com/Digital1O1/Remotely-Debug-C-Programs-on-RPI-Using-VS-Code/assets/39348633/28e62abd-0267-4eba-b8f2-7ac6be5c3d1e)
-   Establish connection to host

    -   Press `Control + Shift + P`
    -   Type in the following : `connect to host` and choose either option
    -   Click on `Add New SSH Host`
    -   To verify that you're connected to the Raspberry PI you can :
        -   Check the lower left corner and you should see the Raspberry PI IP address
            ![image](https://github.com/Digital1O1/Remotely-Debug-C-Programs-on-RPI-Using-VS-Code/assets/39348633/ab9e3ef0-2a4c-4739-a223-259bc104bca7)
            ![image](https://github.com/Digital1O1/Remotely-Debug-C-Programs-on-RPI-Using-VS-Code/assets/39348633/609af753-9a70-40cb-adf2-df4efb71ff68)
        -   Both a bash terminal and the IP address should show up as indicated in the screenshot below
            ![image](https://github.com/Digital1O1/Remotely-Debug-C-Programs-on-RPI-Using-VS-Code/assets/39348633/dbc7e89a-8005-4e03-9830-d74ac7eda989)

-   To open a project that's saved on the Raspberry PI
    -   Click the first icon on the left side menu
    -   Click on `Open Folder`
        -   Then you can navagate to the `Desktop` where the [repository](https://github.com/Digital1O1/Hello_World_Debugger_VSCode) should be stored
            ![image](https://github.com/Digital1O1/Remotely-Debug-C-Programs-on-RPI-Using-VS-Code/assets/39348633/39dee248-9492-41bc-aa46-68ed690abb24)

# Step 5 : Running the VS Code Debugger

## 1) Setting up the debugger

-   In VS Code find the `run` option
    -   Then click on :
        -   `Add Configruation`
        -   `C++(GDB/LLDB)`
        -   `Add configuration`
        -   `C/C++: (gdb) Launch`
    -   References for the mentioned steps can be found in the screenshots below
        ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/2f574e99-6530-43af-b9a3-d1a0127ddab4)
        ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/3a412b3a-d9c6-4ee4-b4b5-58ab8670ae18)
        ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/08cc15da-4919-4171-ae01-330b3ac594f9)
        ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/64c45fce-493b-4513-bd5e-34548dfbd6a5)
-   Afterwards you should see a .vscode folder in the `EXPLORER` menu
-   A `launch.json` file should be generated at this point
    -   The only changes that need to be made is the `"program"` argument since the debugger needs to `point` towards the executiable file
        -   Original version
        ```bash
        "program": "enter program name, for example ${workspaceFolder}/a.out",
        ```
        -   Modified version
        ```bash
        "program": "${workspaceFolder}/main",
        ```
        ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/67b7e494-c5af-4ee0-9203-57cc52dcfd5b)
        ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/f1f52815-cf26-424b-b58c-e366d702c091)

## 2) Running the Debugger

-   Set a break point anywhere in the `main.cpp` file as indicated by the `RED ARROW`
    ![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/4c7f23d6-1207-4a3d-baa6-671d773c8598)

-   There's two ways to run the Debugger
-   In the `Run` options you can manually select `Start Debugger` - Or you can just press `F5`
-   Once the Debugger runs
    -   The `yellow line` indicates where you're at in the program
    -   The menu circled in red does the following
        -   The `play` button
            -   When pressed, the program will run until it hits the next breakpoint
        -   The `step-over` button
            -   When pressed, if the next line the debugger is about to 'step into' is a function, you can esentially skip over it
        -   The `step into` button
            -   As the name implies, you can step into any function
            -   Or manually step through every line of code to have a better understanding of what's going on with the program
        -   The `step out` button
            -   When pressed while in a C++ function
            -   You can 'exit' out of the function and use a different debugging command
        -   The `restart` and `stop` button
            -   I'm pretty sure these buttons can explain themselves

![image](https://github.com/Digital1O1/Hello_World_Debugger_VSCode/assets/39348633/e61214a5-ac5d-48be-a520-4e5a6adc9a93)
