#!/bin/bash

# ----------- User Inputs -----------
read -p "Enter folder base name: " folder_name
read -p "Enter number of problems (e.g. 4 for a.cpp to d.cpp): " num_problems

# ----------- Create Folder -----------
date_str=$(date +%Y-%m-%d)
full_folder="${folder_name}_${date_str}"
mkdir -p "$full_folder"
cd "$full_folder" || exit 1

# ----------- Create .cpp Files -----------
for ((i = 0; i < num_problems; i++)); do
    letter=$(printf "\\$(printf '%03o' $((97 + i)))")  # a=97
    cat <<EOF > "${letter}.cpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Your code here

    return 0;
}
EOF
done

# ----------- Create Input/Output Files -----------
touch in.txt out.txt

# ----------- Create run.sh Script -----------
cat <<'EOF' > run.sh
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./run.sh <filename_without_extension>"
    exit 1
fi

file="$1.cpp"
exe="$1.out"

if [ ! -f "$file" ]; then
    echo "$file not found!"
    exit 1
fi

g++ -std=c++17 -O2 -Wall "$file" -o "$exe"
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

./"$exe" < in.txt > out.txt
echo "Execution finished. Output is in out.txt"

rm -f "$exe"
EOF

chmod +x run.sh

# ----------- Done -----------
echo "✅ Environment '$full_folder' created with $num_problems problems."

