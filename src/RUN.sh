cd ..
del bin/H2.exe;
g++  src/H2.cpp -o bin/H2.exe;
bin/H2.exe
pip install -r src/requirements.txt
python3 src/presentation.py
