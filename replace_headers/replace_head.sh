#!/bin/sh
# Sometimes the header file path will change. This script is used to update the header file path.
# The new header filenames shall contain in headlist_file, like emerson/aem/aem.h but without < > or " "
# This script will search all *.c and *.h in current dir and subdir and replace each match.

# NOTE:
#   1. The base name of header file in headlist_file shall not be duplicate, like emerson/aa/debug.h, emerson/bb/debug.h.
#      There is another script check_dup_head.sh used to examine such case.
#   2. The base name of header file in headlist_file shall not be the same as the glibc's, like emerson/wsman/type.h.
#      It probably will cause chaos in your source code. However emerson/wsman/wstype.h shall be fine.

headlist_file=./header_list
modification_record=./modification_record
date=`date`

echo -e "\nModification in $date\n" >> $modification_record;

while read line
do
    base_name=$(echo $line|awk -F/ '{print $NF}');
    echo -e "Finding and replacing $base_name now..." >> $modification_record;
    for each_file in `find . -name "*.[ch]"`
    do
        line_no=$(sed -n '1,100p' $each_file | sed -n "/[<\"\/]${base_name}/=");
        if [ -z "$line_no" ]; then
            continue;
        fi;
        #echo "find $line_no";

        #It shall not have multiple matches in a single file.
        match_cnt=$(echo $line_no|awk '{print NF}');
        if [ $match_cnt -ne 1 ]; then
            echo -e "Find a multiple results!!! Line NO: $line_no in $each_file...";
            echo -e "Find a multi results!!! Line NO: $line_no in $each_file..." >> $modification_record;
            continue;
        fi;

        matched_line=$(sed -n "${line_no}p" $each_file);
        if [ "${matched_line:0:9}" != "#include " ]; then
            echo -e "Find a unmatched line: $matched_line" >> $modification_record;
            continue;
        fi
        
        #echo "find $matched_line";
        echo -e "\tModify $each_file at line${line_no}:\n\t\t${matched_line}" >> $modification_record;
        sed -i "${line_no}d" $each_file;
        sed -i ${line_no}i"#include \<$line\>" $each_file;
    done;
done < $headlist_file;

