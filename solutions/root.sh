#!/bin/bash

# ================= CONFIGURATION =================
ROOT_DIR=$(pwd)
LOG_FILE="$ROOT_DIR/progress_log.csv"
ARCHIVE_DIR="$ROOT_DIR/archive"
# Change "code" to "xdg-open" or "nano" if you don't use VS Code
EDITOR_CMD="code" 

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Ensure Log file exists
if [ ! -f "$LOG_FILE" ]; then
    echo "Date,Action,Type,Name,Count_or_Note" > "$LOG_FILE"
fi

# ================= HELPER FUNCTIONS =================
select_type() {
    echo -e "${BLUE}Select Category:${NC}"
    options=("Contest" "Gym" "Sheet" "Misc")
    select opt in "${options[@]}"; do
        case $opt in
            "Contest") TARGET_DIR="Contests"; TYPE="Contest"; return 0 ;;
            "Gym")     TARGET_DIR="Gyms";     TYPE="Gym";     return 0 ;;
            "Sheet")   TARGET_DIR="Sheets";   TYPE="Sheet";   return 0 ;;
            "Misc")    TARGET_DIR="Misc";     TYPE="Misc";    return 0 ;;
            *) echo "Invalid option";;
        esac
    done
}

# ================= MAIN MENU =================
echo -e "----------------------------------------"
echo -e "  🚀 ${BLUE}CP Manager & Archive Tool${NC} "
echo -e "----------------------------------------"
PS3="Choose an action: "
main_options=("Create New" "Open Existing" "Archive (Finished)")

select action in "${main_options[@]}"; do
    case $action in
        "Create New")
            MODE="CREATE"
            break
            ;;
        "Open Existing")
            MODE="OPEN"
            break
            ;;
        "Archive (Finished)")
            MODE="ARCHIVE"
            break
            ;;
        *) echo "Invalid option $REPLY";;
    esac
done

# ================= LOGIC HANDLERS =================

# ---------------- [1] CREATE NEW ----------------
if [ "$MODE" == "CREATE" ]; then
    select_type # Sets TARGET_DIR and TYPE
    
    read -p "Enter folder name (No spaces preferred): " folder_name
    read -p "Enter number of problems: " num_problems

    FULL_PATH="$ROOT_DIR/$TARGET_DIR/$folder_name"
    
    if [ -d "$FULL_PATH" ]; then
        echo -e "${RED}Error: Folder already exists! Use 'Open Existing'.${NC}"
        exit 1
    fi

    mkdir -p "$FULL_PATH"
    cd "$FULL_PATH" || exit

    # Create .cpp files
    for ((i = 0; i < num_problems; i++)); do
        letter=$(printf "\\$(printf '%03o' $((65 + i)))")
        cat <<EOF > "${letter}.cpp"
#include <bits/stdc++.h>
using namespace std;

void solve(){
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
EOF
    done

    # Create helpers
    touch in.txt out.txt
    
    # Create run.sh
    cat <<'EOF' > run.sh
#!/bin/bash
if [ $# -ne 1 ]; then echo "Usage: ./run.sh <file>"; exit 1; fi
g++ -std=c++17 -O2 -Wall "$1.cpp" -o "$1.out" && ./$1.out < in.txt > out.txt
rm -f "$1.out"
echo "Done."
EOF
    chmod +x run.sh

    # Create Notes
    echo "# $folder_name" > notes.md
    echo "Created: $(date)" >> notes.md

    # Log
    echo "$(date +%Y-%m-%d),Created,$TYPE,$folder_name,$num_problems problems" >> "$LOG_FILE"

    echo -e "${GREEN}✅ Created $folder_name in $TARGET_DIR${NC}"
    $EDITOR_CMD .
 

# ---------------- [2] OPEN EXISTING ----------------
elif [ "$MODE" == "OPEN" ]; then
    select_type
    SEARCH_DIR="$ROOT_DIR/$TARGET_DIR"
    
    # Check if empty
    if [ -z "$(ls -A $SEARCH_DIR)" ]; then
        echo -e "${RED}No folders found in $TARGET_DIR${NC}"
        exit 1
    fi

    echo -e "${BLUE}Available Folders:${NC}"
    # List folders and let user select
    options=($(ls "$SEARCH_DIR"))
    select folder_name in "${options[@]}"; do
        if [ -n "$folder_name" ]; then
            FULL_PATH="$SEARCH_DIR/$folder_name"
            echo -e "${GREEN}Opening $folder_name...${NC}"
            
            # Open in Editor
            cd "$FULL_PATH"
            $EDITOR_CMD .
            break
        else
            echo "Invalid selection."
        fi
    done

# ---------------- [3] ARCHIVE ----------------
elif [ "$MODE" == "ARCHIVE" ]; then
    select_type
    SEARCH_DIR="$ROOT_DIR/$TARGET_DIR"
    DEST_DIR="$ARCHIVE_DIR/$TARGET_DIR"

    # Check if empty
    if [ -z "$(ls -A $SEARCH_DIR)" ]; then
        echo -e "${RED}Nothing to archive in $TARGET_DIR${NC}"
        exit 1
    fi

    echo -e "${BLUE}Select folder to ARCHIVE (Move to $DEST_DIR):${NC}"
    options=($(ls "$SEARCH_DIR"))
    select folder_name in "${options[@]}"; do
        if [ -n "$folder_name" ]; then
            SRC_PATH="$SEARCH_DIR/$folder_name"
            FINAL_DEST="$DEST_DIR/$folder_name"
            
            # Ensure archive subfolder exists
            mkdir -p "$DEST_DIR"

            # Move
            mv "$SRC_PATH" "$FINAL_DEST"
            
            echo -e "${GREEN}✅ Moved $folder_name to Archive.${NC}"
            
            # Log the archiving
            read -p "Any quick note for log? (e.g. 'Solved 4/5'): " note
            echo "$(date +%Y-%m-%d),Archived,$TYPE,$folder_name,$note" >> "$LOG_FILE"
            break
        else
            echo "Invalid selection."
        fi
    done
fi
