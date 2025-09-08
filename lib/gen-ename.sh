#!/bin/bash
# Generate ename.c.inc with indices starting from 0, filling gaps with ""

OUTFILE="ename.c.inc"

# collect errno defines (name + value)
ERRNOS=$(cpp -dM /usr/include/errno.h \
    | grep -E '^[[:space:]]*#define[[:space:]]+E[A-Z0-9_]+[[:space:]]+[0-9]+' \
    | awk '{print $2, $3}')

# find max errno number
MAX=$(echo "$ERRNOS" | awk '{print $2}' | sort -n | tail -1)

{
    echo "static char *ename[] = {"
    for i in $(seq 0 $MAX); do
        name=$(echo "$ERRNOS" | awk -v v=$i '$2==v {print $1}')
        if [ -n "$name" ]; then
            echo "/* $i */ \"$name\","
        else
            echo "/* $i */ \"\","
        fi
    done
    echo "};"
    echo "#define MAX_ENAME $MAX"
} > "$OUTFILE"

echo "Generated $OUTFILE ✅ (0..$MAX)"
