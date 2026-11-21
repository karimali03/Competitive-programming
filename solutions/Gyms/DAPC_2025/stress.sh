g++ "$1.cpp" -o sol
g++ "$2.cpp" -o brute
g++ "$3.cpp" -o gen
g++ "$4.cpp" -o checker

for ((i=1; ; i++)); do
    ./gen > in.txt
    ./sol < in.txt > out.txt
    ./brute < in.txt > ans.txt

    if ! ./checker in.txt out.txt ans.txt; then
        echo "WA on test $i"
        cat in.txt
        break
    fi

    echo "AC $i"
done