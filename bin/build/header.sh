echo "// James physics library master " $(date "+%d %b %Y") > include/jphysmaster.h


for f in include/james*.h
do
h=${f:8:${#f}} 
echo "#include <"$h">" >> include/jphysmaster.h
done

echo "#include <LeeNucleus.h>" >> include/jphysmaster.h