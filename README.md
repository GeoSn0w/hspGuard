# hspGuard
Checks macOS for Kernel Task Port. It may help detect intrusive kexts that would leak the kernel task.

Pretty much checks for the possibility to obtain the Kernel Task Port on macOS. 
By default, nothing should be able to obtain the kernel task port, root or not. The task port is pretty dangerous stuff. 
You have it, you pwn the kernel in all the right places. Simple as that. 

With introduction of SIP (System Integrity Protection) also dubbed as "ROOTLESS" by Apple in El Capitan, 
there is now an additional layer of protection, for all the good it does. One can disable SIP with literally a terminal command.

The tool I made came as an idea after I saw @s1guza's kext that is able to bring the task port back to userland. 
One simply has to load the kext (kextload), granted SIP is disabled or weakened and BOOM. Kernel Task Port for any program 
asking for it and running as ROOT. @s1guza's kext is pretty useful for pen-testing, and other ethical stuff, but imagine that
running on your mac without you knowing about it. Kernel Task for anyone!!

<B>How the program works</B>
Simple. At first we check if we are root. We can't access kernel stuff if we're not privileged enough (sudo program).
Then we check if we can obtain the task port for the Kernel. Normally, we should not be able to do so even as root. 
The task should always return 0. If it returns any other number, it is bad.
Then we proced to check for SIP. It is never a bad idea to check whether the System Integrity Protection is enabled or not.
In fact, this whole kext made by @s1guza couldn't be abused by a malicious character unless SIP is seriously weakened or
disabled altogether.

<B>How to compile</B>
<h3>gcc hspGuard.c -o hspGuard</h3>
You can ignore the warnings.
