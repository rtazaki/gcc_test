cd target
make all -k 2>&1 | tee target_build.log
./Executable.out
