g++ convert.cpp -o converter
rm -rf NucDataOb/autohead/*.h
./converter NucDataOb/input/*.*

for f in NucDataOb/manhead/*.h
do
echo "#include \"data_ob/"$f"\"" >> NucDataOb/autohead/data_data.h
done

