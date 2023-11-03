cd target
make -k 2>&1 | tee target_build.log
./Executable.out
