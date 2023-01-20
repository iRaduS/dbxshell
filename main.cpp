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
    int pipefd[2]; char str[512];
    const char **argv = new const char*[args.size() + 2];

    argv[0] = dbxcliPath.c_str();
    for (unsigned int i = 1; i <= args.size(); i++) {
        argv[i] = args[i - 1].c_str();
    }
    argv[args.size() + 1] = NULL;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t processId = fork();
    if (processId == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (processId == 0) {
        dup2(pipefd[1], STDERR_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execv(dbxcliPath.c_str(), (char**)argv);
    } else {
        close(pipefd[1]);

        puts(globalPrefix.c_str());
        int nbytes = read(pipefd[0], str, sizeof(str));
        printf("%s%.*s\n", COLOR_DANGER, nbytes, str);

        wait(NULL);
    }
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
        if (!cmd.size()) {
            continue;
        }

        fullArgs = parseArgs(cmd); toLower(fullArgs[0]);
        auto it = find_if(commands.begin(), commands.end(), [fullArgs](auto command) -> bool {
            return string(COLOR_RESET) + fullArgs[0] == get<0>(command);
        });
        if (it == commands.end()) {
            cout << globalPrefix << COLOR_DANGER << " Command doesn't exists, please use help!\n";
            continue;
        }

        if (string(COLOR_RESET) + fullArgs[0] == get<0>(*it) && !get<2>(*it)) {
            forkNewProcessForDbxcliUtiity(fullArgs);
        }

        if (fullArgs[0] == "help") {
            for (auto command : commands) {
                cout << get<0>(command) << "\t" << get<1>(command) << "\n";
            }
        }

        if (fullArgs[0] == "team") {
            toLower(fullArgs[1]);

            auto tit = find_if(teamParameters.begin(), teamParameters.end(), [fullArgs](auto teamParameter) -> bool {
                return fullArgs[1] == teamParameter;
            });
            if (tit == teamParameters.end()) {
                cout << globalPrefix << COLOR_DANGER << " Parameters available: add-member, info, list-groups, list-members, remove-member.\n";
                continue;
            }

            forkNewProcessForDbxcliUtiity(fullArgs);
        }

        if (fullArgs[0] == "exit") {
            cout << COLOR_SUCCESS << "Exit with success, see you another time!\n";
            break;
        }
    }

    return 0;
}