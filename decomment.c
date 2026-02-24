#include <stdio.h>
/* Initialized states for the DFA */
enum StateType {
    NORMAL,
    SEEN_SLASH,
    IN_COMMENT,
    SEEN_STAR,
    IN_STRING,
    IN_CHAR,
    ESCAPE_STRING,
    ESCAPE_CHAR
};

/* how to handle when in NORMAL state */
StateType handleNormal(int c) {
    if (c == '/') {
        return SEEN_SLASH;
    }
    if (c == '"') {
        putchar(c);
        return IN_STRING;
    }
    if (c == '\'') {
        putchar(c);
        return IN_CHAR;
    }

    putchar(c);
    return NORMAL;
}

/* how to handle when in SEEN_SLASH state */
StateType handleSeenSlash(int c, int line, int *commentStart) {
    if (c == '*') {
        *commentStart = line;
        return IN_COMMENT;
    }

    /* print previous slash if found to not be a comment */
    putchar('/');

    if (c == '"') {
        putchar(c);
        return IN_STRING;
    }
    if (c == '\'') {
        putchar(c);
        return IN_CHAR;
    }

    putchar(c);
    return NORMAL;
}

/* how to handle IN_COMMENT state */
StateType handleComment(int c) {
    if (c == '\n') {
        putchar('\n');  /* keep next line characters */
    }
    if (c == '*') {
        return SEEN_STAR;
    }
    return IN_COMMENT;
}

/* how to handle SEEN_STAR state */
StateType handleSeenStar(int c) {
    if (c == '/') {
        putchar(' ');  /* replace comment with space */
        return NORMAL;
    }
    if (c == '\n') {
        putchar('\n');
        return IN_COMMENT;
    }
    if (c == '*') {
        return SEEN_STAR;
    }
    return IN_COMMENT;
}

/* how to handle IN_STRING state */
StateType handleString(int c) {
    putchar(c);

    if (c == '\\') {
        return ESCAPE_IN_STRING;
    }
    if (c == '"') {
        return NORMAL;
    }

    return IN_STRING;
}

/* how to handle IN_CHAR state */
StateType handleChar(int c) {
    putchar(c);

    if (c == '\\') {
        return ESCAPE_IN_CHAR;
    }
    if (c == '\'') {
        return NORMAL;
    }

    return IN_CHAR;
}

/* how to handle ESCAPE_STRING state */
StateType handleEscapeInString(int c) {
    putchar(c);
    return IN_STRING;
}

/* how to handle ESCAPE_CHAR state */
StateType handleEscapeInChar(int c) {
    putchar(c);
    return IN_CHAR;
}

/* iterates through stdin and returns a version to stdout that replaces all comments with a space while leaving the rest untouched */
int main(void) {
    int c;
    int line = 1;
    int commentStart = 0;
    enum StateType state = NORMAL;

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            line++;
        }

        switch (state) {

            case NORMAL:
                state = handleNormal(c);
                break;

            case SEEN_SLASH:
                state = handleSeenSlash(c, line, &commentStart);
                break;

            case IN_COMMENT:
                state = handleComment(c);
                break;

            case SEEN_STAR:
                state = handleSeenStar(c);
                break;

            case IN_STRING:
                state = handleString(c);
                break;

            case IN_CHAR:
                state = handleChar(c);
                break;

            case ESCAPE_STRING:
                state = handleEscapeInString(c);
                break;

            case ESCAPE_CHAR:
                state = handleEscapeInChar(c);
                break;
        }
    }

    /* handle trailing slash at EOF */
    if (state == SEEN_SLASH) {
        putchar('/');
    }

    /* handle unterminated comment error */
    if (state == IN_COMMENT || state == SEEN_STAR) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", commentStart);
        return 1;
    }

    return 0;
}
