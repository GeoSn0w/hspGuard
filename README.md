# hspGuard - macOS Kernel Task Port Checker Tool
hsp comes from `host_special_port(4)` patch implemented by @s1guza in his <a href ="https://github.com/Siguza/hsp4">hsp4 kext.</a>

Checks macOS for Kernel Task Port. It may help detect intrusive kexts that would leak the kernel task.

Pretty much checks for the possibility to obtain the Kernel Task Port on macOS. 
By default, nothing should be able to obtain the kernel task port, root or not. The task port is pretty dangerous stuff. 
You have it, you pwn the kernel in all the right places. Simple as that. 

Apple introduced back in El Capitan a new concept called `SIP` (System Integrity Protection). It was also dubbed as ``ROOTLESS`` by early media coverage. It now represents an additional layer of protection, for all the good it does. One can disable SIP with literally a terminal command.

The tool I made came as an idea after I saw @s1guza's kext that is able to bring the task port back to userland. 
One simply has to load the kext (kextload), granted SIP is disabled or weakened and BOOM. Kernel Task Port for any program 
asking for it and running as ROOT. @s1guza's kext is pretty useful for pen-testing, and other ethical stuff, but imagine that
running on your mac without you knowing about it. Kernel Task for anyone!!

### How the program works
Simple. At first we check if we are root. We can't access kernel stuff if we're not privileged enough (`sudo program`).
Then we check if we can obtain the task port for the Kernel. Normally, we should not be able to do so even as root. 
The task should always return 0. If it returns any other number, it is bad.
Then we proced to check for SIP. It is never a bad idea to check whether the System Integrity Protection is enabled or not.
In fact, this whole kext made by @s1guza couldn't be abused by a malicious character unless SIP is seriously weakened or
disabled altogether.

In theory, if a kext akin to the one made by @s1guza is loaded, all it takes for a program that is running privileged is to do something like this:

```c
task_t get_kernel_task_port(){
    task_t kernel_task;
    host_get_special_port(mach_host_self(), HOST_LOCAL_NODE, 4, &kernel_task);
    return kernel_task;
}
```
Done. This will return the kernel task port if the system is compromised. So as you can see, it is a trivial task.
macOS El Capitan is actually the main target here. Although @s1guza's kext does work on macOS Sierra and High Sierra, 
Apple did something relatively interesting. Instead of attempting to limit the programs from grabbing the kernel task port, they limited what the program can do after grabbing it. With the release of macOS 10.12.4, you can grab the kern task port, but most of the APIs will see it like `MACH_PORT_NULL`, rendering it useless.

@s1guza has a way better documentation of the matter and you can <a href = "https://github.com/Siguza/hsp4">check it out here.</a>

Suffices to say that macOS El Capitan is a better target for someone who may wanna use such kext, but that does not make Sierra and High Sierra flawless.

### Compiling
  ``gcc hspGuard.c -o hspGuard``
  
You can ignore the warnings.

### License
Do whatever you want with the code. Remix, adapt, sell, I don't give a damn.

### Special Thanks
@IBSparkes for motivation to pursue the demystifying of how csrutil works in order to grab more SIP data :P

@s1guza for his amazing hsp4 kext. Very useful thingy if you know how to use it and how not to expose your system to all the malware you can get :P Seriously, don't run this kext unless you really know what the hell you are doing.

### Contact
If you wanna talk with me about the ehernal life, cats, electronics, iOS, or whatever, my twitter is GeoSn0w (``@FCE365``). I also run the F.C.E. 365 TV - iDevice Central on YouTube so you can drop me a PM there too.
