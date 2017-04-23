g++ NucDataOb/convert.cpp -o NucDataOb/converter
rm -rf NucDataOb/autohead/*.h
./NucDataOb/converter NucDataOb/input/*.*

for f in NucDataOb/manhead/*.h
do
echo "#include \""$f"\"" >> NucDataOb/autohead/data_data.h
done

echo "private:" > include/NucDataHeaders.h
cat NucDataOb/autohead/data_headers.h  >> include/NucDataHeaders.h
echo "public:" >> include/NucDataHeaders.h
cat NucDataOb/autohead/function_declarations.h >> include/NucDataHeaders.h

	
