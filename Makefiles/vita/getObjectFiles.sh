getObjectFiles(){
    for i in $(ls src); do
        echo "$i.o"
    done
}