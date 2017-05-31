
echo "export JAMESPHYS="$(pwd) > bin/thisjlib.sh
echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$JAMESPHYS/bin:\$JAMESPHYS/bin/build:\$JAMESPHYS">> bin/thisjlib.sh
echo "export CPATH=\$CPATH:\$JAMESPHYS/include">> bin/thisjlib.sh
echo "export PATH=\$PATH:\$JAMESPHYS/include:\$JAMESPHYS/src:\$JAMESPHYS/bin:\$JAMESPHYS/bin/build">> bin/thisjlib.sh
echo "export LIBRARY_PATH=\$LIBRARY_PATH:\$JAMESPHYS/bin:\$JAMESPHYS/bin/build:\$JAMESPHYS/src:\$JAMESPHYS/include:\$JAMESPHYS">> bin/thisjlib.sh

echo "{gSystem->Load(\"libjames_phys.so\");cos2(0.1);}" > bin/root_start.C
echo "{gSystem->Load(\"libjames_phys_export.so\");cos2(0.1);}" > bin/root_start_export.C

# alias root='root -l /home/jsmallcombe/test.C'
