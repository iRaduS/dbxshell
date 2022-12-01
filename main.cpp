#include "utils.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
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

void forkNewProcessForDbxcliUtiity(vector<string> args) {
    const char **argv = new const char*[args.size() + 2];

    argv[0] = dbxcliPath.c_str();
    for (unsigned int i = 1; i <= args.size(); i++) {
        argv[i] = args[i - 1].c_str();
    }
    argv[args.size() + 1] = NULL;

    pid_t processId = fork();
    if (processId == 0) {
        execv(dbxcliPath.c_str(), (char**)argv);
    }

    waitpid(processId, NULL, 0);
}

void toLower(string& cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), [](char c) -> int {
        return tolower(c);
    });
}

vector<string> parseArgs(string& cmd) {
    vector<string> tokens;

    char *token = strtok(const_cast<char*>(cmd.c_str()), " ");
    while (token != nullptr)
    {
        tokens.push_back(string(token));
        token = strtok(NULL, " ");
    }

    return tokens;
}

int main() {
    cout << globalPrefix << " Welcome back, to our terminal!\n"
         << globalPrefix << " To check the prefix you can use the help command.\n"
         << globalPrefix << " First we'll have you to login inside the Dropbox account.\n"
         << "If you're not authenticated then you'll need to insert an authorization token inside the shell.\n";

    checkAuthenticationOnShellStart();

    vector<string> fullArgs;
    for (string cmd; ;) {
        cout << globalPrefix << " $ "; getline(cin, cmd);
        if (!cmd.size()) continue;

        fullArgs = parseArgs(cmd); toLower(fullArgs[0]);

        auto it = find_if(commands.begin(), commands.end(), [fullArgs](auto command) {
            return string(COLOR_RESET) + fullArgs[0] == get<0>(command);
        });
        if (it == commands.end()) {
            cout << COLOR_DANGER << "Command doesn't exists, please use help!\n";
        }

        if (string(COLOR_RESET) + fullArgs[0] == get<0>(*it) && !get<2>(*it)) {
            forkNewProcessForDbxcliUtiity(fullArgs);
        }

        if (fullArgs[0] == "help") {
            for (auto command : commands) {
                cout << get<0>(command) << "\t" << get<1>(command) << "\n";
            }
        }

        if (fullArgs[0] == "exit") {
            cout << COLOR_SUCCESS << "Exit with success, see you another time!\n";
            break;
        }
    }

    return 0;
}