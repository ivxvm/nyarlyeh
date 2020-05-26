void cmd_help() {
    printf("usage: nyarlyeh [num_repeats] <command> [<args>]\n\n");
    printf("commands:\n");
    printf("    m, mod <m> [<n>]              use modulo generator\n");
    printf("    v, variant [<variants>]       choose variant from the list\n");
    printf("    f, file [<filepath>]          choose variant from the file\n");
    printf("    t, test <command> [<args>]    test command (eg print freq distribution)\n");
}
