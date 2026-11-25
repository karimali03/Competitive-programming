g++ "$1.cpp" -o sol
g++ "$2.cpp" -o brute
g++ "$3.cpp" -o gen
g++ "$4.cpp" -o chk

for ((i=1; ; i++)); do
    ./gen $i > in.txt
    ./sol < in.txt > out.txt
    ./brute < in.txt > ans.txt

    if ! ./chk in.txt out.txt ans.txt; then
        echo "WA on test $i  (rerun this test: ./gen $i)"
        cat in.txt
        break
        # continue (if you dont want it to stop)
    fi

    echo "AC $i"
done

rm -f -- sol brute gen chk  ans.txt
