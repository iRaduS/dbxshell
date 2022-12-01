//
// Created by Radu Vrinceanu on 01.12.2022.
//
#include <string>
#include <vector>
#include <tuple>
using namespace std;

#ifndef DBXSHELL_COLORS_H
#define DBXSHELL_COLORS_H

#endif //DBXSHELL_COLORS_H
#define COLOR_BLUE 	"\033[94m"
#define COLOR_RESET "\033[39m"
#define COLOR_WARNING "\033[33m"
#define COLOR_DANGER "\033[31m"
#define COLOR_SUCCESS "\033[92m"

const string globalPrefix = string(COLOR_RESET) + string("[") +
                            string(COLOR_BLUE) + string("dbxshell")+
                            string(COLOR_RESET) + string("]");
const string dbxcliPath = "/Users/raduvrinceanu/dbxshell/dbxcli/dist/dbxcli-darwin-amd64";
const vector<tuple<string, string, bool>> commands = {
        make_tuple(string(COLOR_RESET) + "cp", string(COLOR_WARNING) + "Copy a file or folder to a different location in the user's dropbox.", false),
        make_tuple(string(COLOR_RESET) + "du", string(COLOR_WARNING) + "Display informations about the usage.", false),
        make_tuple(string(COLOR_RESET) + "get", string(COLOR_WARNING) + "Download a file.", false),
        make_tuple(string(COLOR_RESET) + "put", string(COLOR_WARNING) + "Upload a file.", false),
        make_tuple(string(COLOR_RESET) + "mv", string(COLOR_WARNING) + "Move files.", false),
        make_tuple(string(COLOR_RESET) + "restore", string(COLOR_WARNING) + "Restore files.", false),
        make_tuple(string(COLOR_RESET) + "rm", string(COLOR_WARNING) + "Remove files.", false),
        make_tuple(string(COLOR_RESET) + "mkdir", string(COLOR_WARNING) + "Create a new directory.", false),
        make_tuple(string(COLOR_RESET) + "ls", string(COLOR_WARNING) + "List file and folders.", false),
        make_tuple(string(COLOR_RESET) + "revs", string(COLOR_WARNING) + "List file revisions.", false),
        make_tuple(string(COLOR_RESET) + "logout", string(COLOR_WARNING) + "Logout from the current session.", false),
        make_tuple(string(COLOR_RESET) + "account", string(COLOR_WARNING) + "Display informations about the current session.", false),
        make_tuple(string(COLOR_RESET) + "version", string(COLOR_WARNING) + "Display the current version of the dbxcli utility.", false),
        make_tuple(string(COLOR_RESET) + "search", string(COLOR_WARNING) + "Search option.", false),
        make_tuple(string(COLOR_RESET) + "team", string(COLOR_WARNING) + "Team management commands.", true),
};