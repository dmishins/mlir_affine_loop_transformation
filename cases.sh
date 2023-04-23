cd cases
for filename in *.c; do
    itemname="${filename%.c}"
    echo "[[ Building <${itemname}> ]]"
    ./buildscript.sh -f ${filename}
done
cd ..