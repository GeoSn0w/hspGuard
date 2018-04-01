// hspGuard 1.0
// Copyright GeoSn0w 2018
// Use as you want.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <unistd.h> //geteuid();

kern_return_t get_privileges_status(){

    if(geteuid() != 0){
        printf("[hspGuard] ERROR: You are not running the program as root.\n");
        printf("[hspGuard] INFO: Please run the program with sudo.\n");
        return KERN_FAILURE;
    } else if (geteuid() == 0){
        printf("[hspGuard] SUCCESS: The program has enough privileges to perform the checks.\n");
    }
    return KERN_SUCCESS;
}

task_t get_kernel_task_port(){
    task_t kernel_task;
    host_get_special_port(mach_host_self(), HOST_LOCAL_NODE, 4, &kernel_task);
    return kernel_task;
}
kern_return_t check_SIP_status(){
    printf("[hspGuard] INFO: Checking SIP Status...\n");
    FILE *fork_process = popen("csrutil status", "r"); //Need a better way to do this.
    char sip_status[100];
    char control[100] = "System Integrity Protection status: disabled."; //Control string we check against.
    while (fgets(sip_status, sizeof(sip_status), fork_process) != 0) {
        //Get shit into the buffer
    }
    pclose(fork_process);
    if(strcmp(control, sip_status)){
        printf("[hspGuard] DANGER: ");
        printf("%s", &sip_status);
        return KERN_FAILURE;
        
    } else {
        printf("[hspGuard] SUCCESS: ");
        printf("%s", &sip_status);
    }
    return KERN_SUCCESS;
}
kern_return_t get_macos_version(){
    char placeholder[256];
    size_t howbig = sizeof(placeholder);
    int juicy_data = sysctlbyname("kern.osrelease", str, &size, NULL, 0);
    if(strcmp(placeholder,"0"){
        printf("[hspGuard] ERROR: You may wanna run this on macOS...");
       return KERN_FAILURE;
    }
       return KERN_SUCCESS;
}
int main(){
    task_t kernel_port;
    system("clear"); //Reserve a blank screen for out tool.
    printf("hspGuard 1.0 - macOS Kernel Special Port Checker\n");
    printf("Created by GeoSn0w (@FCE365)\n\n");
    get_macos_version();
    printf("[hspGuard] INFO: Checking application privileges.\n");
    if (get_privileges_status() == KERN_SUCCESS){
        check_SIP_status();
        printf("[hspGuard] INFO: Attempting to get the Kernel Task Port. We shouldn't be able to!\n");
        kernel_port = get_kernel_task_port();
        if(kernel_port != 0){
            printf("[hspGuard] INFO: Got Kernel Task Port: %u\n", kernel_port);
            printf("[hspGuard] DANGER: We got the Kernel Task Port! The system is tampered with.\n");
            printf("[hspGuard] WARNING: It is possible that a malicious kext is loaded! The system is unsafe.\n");
            printf("[hspGuard] Please check the loaded kexts for anything that may seem suspicious.\n");
        } else {
            printf("[hspGuard] SUCCESS: We couldn't grab the Kernel Task Port!\n");
            printf("[hspGuard] INFO: From this standpoint, the system is secure. Random apps can't get hsp(4)\n");
        }
    } else {
        exit(EXIT_FAILURE);
    }
    return 0;
}
