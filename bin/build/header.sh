echo "// jPhysics library master " $(date "+%d %b %Y") > include/jphysmaster.h


for f in include/j_*.h
do
h=${f:8:${#f}} 
echo "#include <"$h">" >> include/jphysmaster.h
done

echo "#include <LeeNucleus.h>" >> include/jphysmaster.h
