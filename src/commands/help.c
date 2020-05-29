void cmd_help() {
    printf("usage: nyarlyeh [num_repeats] <command> [<args>]\n\n");
    printf("commands:\n");
    printf("    m, mod <m> [<n>]                use modulo generator\n");
    printf("    v, variant [<variants>]         choose random variant from the list\n");
    printf("    f, file <filepath>              choose random line from the file\n");
    printf("    d, dir <dirpath> [<pattern>]    choose random file from the directory\n");
    printf("    t, test <command> [<args>]      test command (eg print freq distribution)\n");
}
