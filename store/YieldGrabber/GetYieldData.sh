DATE=$(echo *.date)

if [ ${#DATE} -lt 7 ]; #put the loop where you need it
then
DATE="0.date"
fi

set -- $DATE
DATE=$1
DATE=${DATE:0:${#DATE}-5}
# $(date "+%Y%m%d")
TODAY=$(date "+%Y%m")
# echo $TODAY


if [ $TODAY -gt $DATE ]; #put the loop where you need it
then

rm -rf *.date
echo "data marker file" > $TODAY.date 

rm -f ./Data/Si ./Data/Ti ./Data/Ni ./Data/Zr ./Data/Nb ./Data/Ta ./Data/Th U

wget http://mis.triumf.ca/science/planning/yield/target/Si 
wget http://mis.triumf.ca/science/planning/yield/target/Ti 
wget http://mis.triumf.ca/science/planning/yield/target/Ni 
wget http://mis.triumf.ca/science/planning/yield/target/Zr 
wget http://mis.triumf.ca/science/planning/yield/target/Nb 
wget http://mis.triumf.ca/science/planning/yield/target/Ta 
wget http://mis.triumf.ca/science/planning/yield/target/Th
wget http://mis.triumf.ca/science/planning/yield/target/U

mv Si ./Data
mv Ti ./Data
mv Ni ./Data
mv Zr ./Data
mv Nb ./Data
mv Ta ./Data
mv Th ./Data
mv U  ./Data

python ./Data/Read.py ./Data/Si ./Data/SiC.dat
python ./Data/Read.py ./Data/Ti ./Data/TiC.dat
python ./Data/Read.py ./Data/Ni ./Data/NiO.dat
python ./Data/Read.py ./Data/Zr ./Data/ZrC.dat
python ./Data/Read.py ./Data/Nb ./Data/Nb.dat
python ./Data/Read.py ./Data/Ta ./Data/Ta.dat
python ./Data/Read.py ./Data/Th ./Data/Th.dat
python ./Data/Read.py ./Data/U ./Data/U.dat

fi

