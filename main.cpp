#include "utils.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void checkAuthenticationOnShellStart() {
    const char **args = new const char*[3];
    args[0] = dbxcliPath.c_str(), args[1] = "account", args[2] = NULL;

    pid_t processId = fork();
    if (processId == 0) {
        execv(args[0], (char**)args);
    }

    waitpid(processId, NULL, 0);
}

int main() {
    cout << globalPrefix << " Welcome back, to our terminal!\n"
         << globalPrefix << " To check the prefix you can use the help command.\n"
         << globalPrefix << " First we'll have you to login inside the Dropbox account.\n"
         << "If you're not authenticated then you'll need to insert an authorization token inside the shell.\n";

    checkAuthenticationOnShellStart();

    for(string cmd; cin >> cmd; ) {

    }
    return 0;
}