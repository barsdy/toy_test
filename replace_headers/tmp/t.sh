line_no=2
line=aa/bb/cc.h
each_file=11.c

sed -i ${line_no}i"#include \"$line\"" $each_file;
