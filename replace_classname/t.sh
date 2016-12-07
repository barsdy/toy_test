for filename in `ls -1 *.c`
do
    classname=`echo "$filename" |awk -F"." '{if($1~/^[IC]/) print $1}'`;
    if [ -z $classname ]; then
        continue;
    fi;
    servicename=`echo "$classname"|awk -F"_" '{print $2}'`;
    sed -i s/"${classname}""Service"/"Lenovo_""${servicename}""Service"/g $filename
    sed -i s/"CLASSNAME_""${classname}"/"CLASSNAME_Lenovo_""${classname}"/g $filename
    echo $servicename;
done
