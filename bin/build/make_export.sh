
echo "export J_PHYS="$(pwd) > bin/thisjlib.sh
echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$J_PHYS/bin:\$J_PHYS/bin/build:\$J_PHYS">> bin/thisjlib.sh
echo "export CPATH=\$CPATH:\$J_PHYS/include">> bin/thisjlib.sh
echo "export PATH=\$PATH:\$J_PHYS/include:\$J_PHYS/src:\$J_PHYS/bin:\$J_PHYS/bin/build">> bin/thisjlib.sh
echo "export LIBRARY_PATH=\$LIBRARY_PATH:\$J_PHYS/bin:\$J_PHYS/bin/build:\$J_PHYS/src:\$J_PHYS/include:\$J_PHYS">> bin/thisjlib.sh

echo "{gSystem->Load(\"libjroot_phys.so\");cos2(0.1);}" > bin/root_start.C
echo "{gSystem->Load(\"libjroot_phys_export.so\");cos2(0.1);}" > bin/root_start_export.C

# alias root='root -l /home/jsmallcombe/test.C'
