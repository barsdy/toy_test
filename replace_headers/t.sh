while read line 
do
    if [ ${line%%"^#include "*} = "#include " ]; then
        echo "the line is $line";
    fi
done < CIM_ConcreteJobAgent.c;
