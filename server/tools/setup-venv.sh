
#!/usr/bin/env bash

set -e 

echo "----Starting virtual environment setup----"

BASE_DIR="$( pwd )"
cd server
echo "$BASE_DIR"
# check if venv directory is presents
if [ ! -d "venv" ]; then
    # create venv 
    python3 -m venv venv
fi

# activate env
source venv/bin/activate

# upgrade pip
echo "----Upgrading pip----"
sudo apt --fix-broken install
sudo apt install python3-pip
pip install -q --upgrade pip

echo "Installing dependencies in requirements.txt ..."
if [ -e "$BASE_DIR/server/tools/requirements.txt" ]; then
    pip install -U -r tools/requirements.txt
else 
    echo "requirements.txt not found"
fi




